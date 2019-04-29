#ifndef __CAMERACV_H__
#define __CAMERACV_H_
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <std_msgs/String.h>
class camera{
private:
	ros::NodeHandle n;
	ros::Publisher redColor;
	image_transport::ImageTransport it_;
	image_transport::Subscriber front;
	std_msgs::String str;
	void imageFront(const sensor_msgs::ImageConstPtr& msg);
	void detectFace(const cv::Mat mat);
public:
	cv_bridge::CvImagePtr front_ptr;
	cv::CascadeClassifier face_cascade;
	camera();
	~camera();
};
#endif