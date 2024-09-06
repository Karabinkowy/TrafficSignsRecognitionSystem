#pragma once
#include <fstream>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <iostream>

const int COLOR = 6; // color which must be segmentated

const int NUMBER_OF_ELEMENTS = 7;
const int HUE = 180;
const int DEPTH = 255;

const std::string TITLE_INPUT = "Orig.";
const std::string TITLE_OUTPUT = "Segm.";

const double IMAGE_SCALE = 0.25; // scale factor of the image

const double TEXT_POSITION_SCALE = 0.1; // used for calculation of the origin point of the text, e.g. (0.1 * rows, 0.1 * cols)

// parameters for text
const double FONT_SCALE = 0.6;
const int FONT_THICKNESS = 2;

const cv::Scalar TEXT_COLOR = cv::Scalar(0, 0, 0);

typedef struct color_threshold
{
	std::string name;
	float low_thr[3]{ 0,0,0 };
	float high_thr[3]{ 0,0,0 };

}c_th;


class Segmentation
{
public:
	cv::Mat img_in;
	std::vector<cv::Mat> binarizedImages;
	
	void test_mode();
	void normal_mode(std::ifstream& thr_file);
	
	Segmentation(cv::Mat &_img_edited);
private:
	std::vector <c_th> readThreshold(std::ifstream& thr_file);
};