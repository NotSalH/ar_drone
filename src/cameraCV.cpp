#include <ar_drone/cameraCV.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//Constructor
camera::camera() : it_(n) {
	//Initilizes image transport
	front = it_.subscribe("ardrone/front/image_raw",1,&camera::imageFront, this);
	bottom = it_.subscribe("ardrone/bottom/image_raw",1,&camera::imageBottom, this);
}
camera::~camera(){
	cv::destroyWindow("front image");
	cv::destroyWindow("bottom image");
}

void camera::imageFront(const sensor_msgs::ImageConstPtr& msg){
	try{
		cv::namedWindow("front image ", cv::WINDOW_AUTOSIZE);
		front_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		cv::Mat f(front_ptr->image);
		cv::imshow("front image", f);
		cv::waitKey(1);
	}
		//cv::imshow("front image", cv_bridge::toCvShare(msg, "bgr8")->image);
	catch(cv_bridge::Exception& e){
		ROS_ERROR("front %s",e.what());
		return;
	}
}

void camera::imageBottom(const sensor_msgs::ImageConstPtr& msg){
	try{
		cv::namedWindow("bottom image", cv::WINDOW_AUTOSIZE);
		bottom_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
		cv::Mat b(bottom_ptr->image);
		cv::imshow("bottom image",b);
		cv::waitKey(1);
		//cv::imshow("bottom image", cv_bridge::toCvShare(msg, "bgr8")->image);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("bottom %s",e.what());
		return;
	}
}

int main(int argc, char** argv){
	ros::init(argc, argv, "cameraCV");
  	camera subCam;
  	ros::spin();
  	return 0;
}
		
