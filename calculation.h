#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

const double D_HOR_L = 0.0;
const double D_HOR_H = 0.4;
const double D_VER_L = 0.0;
const double D_VER_H = 0.4;

const double INTER_L = 0.2;
const double INTER_H = 1;

const double L_HOR_L = 0.0;
const double L_HOR_H = 0.4;
const double L_VER_L = 0.0;
const double L_VER_H = 0.4;

const double RATIO_L = 0.5;
const double RATIO_H = 1.6;


class Calculation
{
public:
	double d_hor; // relative horizontal distance between two objects
	double d_ver; // relative vertical distance between two object
	double l_hor; // relative horizontal location difference between two objects
	double l_ver; // relative vertical location between two objects
	double area_A, area_B; // area of object A|B
	double inter; // intersection of two objects
	double ratio_A, ratio_B; // aspect ratio of the object (width to height)

	void calc(cv::Rect object_1, cv::Rect object_2);
	Calculation() {};
	Calculation(cv::Rect object_1, cv::Rect object_2, std::vector<std::vector<cv::Rect>> improved_boxes);
private:
	double d_h1, d_h2;
	double d_v1, d_v2;
	double p_h1, p_h2, p_h3;
	double p_v1, p_v2, p_v3;
	double a{ 0 }, b{ 0 }; // width and height of the intersection
	cv::Rect connectBoxes(cv::Rect& box1, cv::Rect& box2);
	void checkBoxes(cv::Rect& box1, cv::Rect& box2);

};