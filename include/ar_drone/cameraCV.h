#ifndef __CAMERACV_H__
#define __CAMERACV_H_
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

class camera{
protected:
	ros::NodeHandle n;
	image_transport::ImageTransport it_;
	image_transport::Subscriber front;
	image_transport::Subscriber bottom;

	void imageFront(const sensor_msgs::ImageConstPtr& msg);
	void imageBottom(const sensor_msgs::ImageConstPtr& msg);
public:
	cv_bridge::CvImagePtr front_ptr;
	cv_bridge::CvImagePtr bottom_ptr;
	camera();
	~camera();
};
#endif