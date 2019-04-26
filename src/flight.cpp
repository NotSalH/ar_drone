#include <ar_drone/flight.h>
#include "ardrone_autonomy/Navdata.h"
#include <iostream>
#define MAX_STREAM_WIDTH 640
#define MAX_STREAM_HEIGHT 360
//Destructor for drone
Drone::~Drone(){
	std::cout<<"Object Destroyed" << "\n";
}
//Initilizes image transport and sets up subs and pubs
Drone::Drone() : it_(n), loop_rate(10){
	xyMove = n.advertise<geometry_msgs::Twist>("cmd_vel",100,true);
	flight = n.advertise<std_msgs::Empty>("ardrone/takeoff",1,true);
	land = n.advertise<std_msgs::Empty>("ardrone/land",10,true);
	camFront = it_.advertise("ardrone/front/image_raw",1);
	camBottom = it_.advertise("ardrone/bottom/image_raw",1);
	joyNode = n.subscribe<sensor_msgs::Joy>("joy",10, &Drone::joyStick, this);

	

}
void Drone::setZero(){
	vel.angular.x=0;
	vel.angular.y=0;
	vel.angular.z=0;
	vel.linear.x =0;
	vel.linear.y =0;
	vel.linear.z =0;
	xyMove.publish(vel);
	std::cout<<"stop"<< "\n";
}

void Drone::publishVideo(){
	image.width = MAX_STREAM_WIDTH;
	image.height = MAX_STREAM_HEIGHT;
	image.encoding = "rgb8";
	image.is_bigendian= false;
	image.step = MAX_STREAM_WIDTH*3;
	image.data.resize(MAX_STREAM_WIDTH*MAX_STREAM_HEIGHT*3);
	ci.width = MAX_STREAM_WIDTH;
	ci.height = MAX_STREAM_HEIGHT;
	camFront.publish(image);
	camBottom.publish(image);
}

void Drone::moveForward(){
	vel.linear.x = .5;
	xyMove.publish(vel);
}

void Drone::moveBackwards(){
	vel.linear.x = -.5;
	xyMove.publish(vel);
}

void Drone::moveRight(){
	vel.linear.y = .5;
	xyMove.publish(vel);
}

void Drone::moveLeft(){
	vel.linear.y = -.5;
	xyMove.publish(vel);
}

void Drone::moveUp(){
	vel.linear.z = .5;
	xyMove.publish(vel);
}

void Drone::moveDown(){
	vel.linear.z = -.5;
	xyMove.publish(vel);
}


void Drone::joyStick(const sensor_msgs::Joy::ConstPtr& joy){
	
	
	//Hover
	if(joy->buttons[0] == 1){
		std::cout << "Hover" << "\n";
		flight.publish(em);
		//setZero();
	} 
	//Land
	if(joy->buttons[1] == 1){
		std::cout << "Land" << "\n";
		land.publish(em);
	} 

	//X+
	if(joy->axes[0] > .5){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+.05){
			std::cout<<"x Pos" << "\n";
			moveRight();
			ros::spinOnce();
			loop_rate.sleep();
		}

	}
	//X-
	else if(joy->axes[0] < -.5){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+.05){
			std::cout<<"x Neg" << "\n";
			moveLeft();
			ros::spinOnce();
			loop_rate.sleep();
		
		}
	
	}
	//Y+
	else if(joy->axes[1] > .5){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+.05){
			std::cout<<"Y pos" << "\n";
			moveForward();
			ros::spinOnce();
			loop_rate.sleep();
		}
	
	}
	//Y-
	else if(joy->axes[1] < -.5){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+.05){
			std::cout<<"Y Neg" << "\n";
			moveBackwards();
			ros::spinOnce();
			loop_rate.sleep();

		}

	}
	else{
		setZero();
	}
	//Z+
	/*else if(joy->axes[3] > 0){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+1){
			std::cout<<"Z pos" << "\n";
			moveUp();
			ros::spinOnce();
			loop_rate.sleep();
			break;
		}
	}
	//Z-
	else if(joy->axes[3] < 0){
		double start = ros::Time::now().toSec();
		while((double)ros::Time::now().toSec() < start+1){
			std::cout<<"Z neg" << "\n";
			moveDown();
			ros::spinOnce();
			loop_rate.sleep();
			break;
		}
	}*/
}

int main( int argc, char **argv ){
	ros::init(argc,argv,"flight");
	
	Drone drone;
	
	while(ros::ok()){
		drone.publishVideo();
		ros::spinOnce();
		drone.loop_rate.sleep();
	}
}


