#include <fstream>
#include <vector>

#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "segmentation.h"

const std::string TITLE_TRACKBAR_LOW_H = "H_low";
const std::string TITLE_TRACKBAR_HIGH_H = "H_high";
const std::string TITLE_TRACKBAR_LOW_S = "S_low";
const std::string TITLE_TRACKBAR_HIGH_S = "S_high";
const std::string TITLE_TRACKBAR_LOW_V = "V_low";
const std::string TITLE_TRACKBAR_HIGH_V = "V_high";

// scales for placing origin point
// origin point in Point(scale * number_of_columns, scale * number_of_rows)

// trackbar parameters
const int HUE_MAX = 180;
const int SATURATION_MAX = 255;
const int VALUE_MAX = 255;

const cv::Size WINDOW_SIZE(500, 500);

int h_low{ 0 }, s_low{ 0 }, v_low{ 0 };
int h_high{ 0 }, s_high{ 0 }, v_high{ 0 };

static void low_H_thresh_trackbar(int, void*)
{
	h_low = cv::min(h_high - 1, h_low);
	cv::setTrackbarPos(TITLE_TRACKBAR_LOW_H, TITLE_INPUT, h_low);
}

static void high_H_thresh_trackbar(int, void*)
{
	h_high = cv::max(h_high, h_low + 1);
	cv::setTrackbarPos(TITLE_TRACKBAR_HIGH_H, TITLE_INPUT, h_high);
}


static void low_S_thresh_trackbar(int, void*)
{
	s_low = cv::min(s_high - 1, s_low);
	cv::setTrackbarPos(TITLE_TRACKBAR_LOW_S, TITLE_INPUT, s_low);
}

static void high_S_thresh_trackbar(int, void*)
{
	s_high = cv::max(s_high, s_low + 1);
	cv::setTrackbarPos(TITLE_TRACKBAR_HIGH_S, TITLE_INPUT, s_high);
}


static void low_V_thresh_trackbar(int, void*)
{
	v_low = cv::min(v_high - 1, v_low);
	cv::setTrackbarPos(TITLE_TRACKBAR_LOW_V, TITLE_INPUT, v_low);
}

static void high_V_thresh_trackbar(int, void*)
{
	v_high = cv::max(v_high, v_low + 1);
	cv::setTrackbarPos(TITLE_TRACKBAR_HIGH_V, TITLE_INPUT, v_high);
}

Segmentation::Segmentation(cv::Mat &_img_edited) {
	img_in = _img_edited;
}



void Segmentation::normal_mode(std::ifstream& thr_file)
{
	// #TODO: do segmentation for all colors
	std::vector<c_th>thr = readThreshold(thr_file);
	cv::Mat _imgHSV;
	cv::Mat _imgOut;

	int h_low{ 0 }, s_low{ 0 }, v_low{ 0 };
	int h_high{ 0 }, s_high{ 0 }, v_high{ 0 };

	for (int i = 0; i < COLOR; ++i)
	{
		h_low = int(thr[i].low_thr[0] * HUE);
		h_high = int(thr[i].high_thr[0] * HUE);
		s_low = int(thr[i].low_thr[1] * DEPTH);
		s_high = int(thr[i].high_thr[1] * DEPTH);
		v_low = int(thr[i].low_thr[2] * DEPTH);
		v_high = int(thr[i].high_thr[2] * DEPTH);
		cv::cvtColor(img_in, _imgHSV, cv::COLOR_BGR2HSV);
		cv::inRange(_imgHSV, cv::Scalar(h_low, s_low, v_low), cv::Scalar(h_high, s_high, v_high), _imgOut);
		binarizedImages.push_back(_imgOut);
	}

	return;
}


void Segmentation::test_mode()
{
	cv::namedWindow(TITLE_INPUT, cv::WINDOW_NORMAL);
	cv::namedWindow(TITLE_OUTPUT, cv::WINDOW_NORMAL);
	cv::resizeWindow(TITLE_INPUT, WINDOW_SIZE);
	cv::resizeWindow(TITLE_OUTPUT, WINDOW_SIZE);

	cv::createTrackbar(TITLE_TRACKBAR_LOW_H, TITLE_INPUT, &h_low, HUE_MAX, low_H_thresh_trackbar);
	cv::createTrackbar(TITLE_TRACKBAR_HIGH_H, TITLE_INPUT, &h_high, HUE_MAX, high_H_thresh_trackbar);
	cv::createTrackbar(TITLE_TRACKBAR_LOW_S, TITLE_INPUT, &s_low, SATURATION_MAX, low_S_thresh_trackbar);
	cv::createTrackbar(TITLE_TRACKBAR_HIGH_S, TITLE_INPUT, &s_high, SATURATION_MAX, high_S_thresh_trackbar);
	cv::createTrackbar(TITLE_TRACKBAR_LOW_V, TITLE_INPUT, &v_low, VALUE_MAX, low_V_thresh_trackbar);
	cv::createTrackbar(TITLE_TRACKBAR_HIGH_V, TITLE_INPUT, &v_high, VALUE_MAX, high_V_thresh_trackbar);

	cv::Mat _imgInput, _imgHSV, _imgSegm;

	cv::Mat _imgResized;
	cv::resize(binarizedImages, _imgResized, cv::Size(), IMAGE_SCALE, IMAGE_SCALE, cv::INTER_LINEAR);
	cv::cvtColor(_imgResized, _imgHSV, cv::COLOR_BGR2HSV);

	cv::Point originPoint = cv::Point(int(_imgResized.rows * TEXT_POSITION_SCALE), int(_imgResized.cols * TEXT_POSITION_SCALE));
	double scale_font = FONT_SCALE;
	if (_imgResized.rows > 300)
		scale_font *= 2;

	while (true) 
	{
		_imgInput = _imgResized;
		cv::inRange(_imgHSV, cv::Scalar(h_low, s_low, v_low), cv::Scalar(h_high, s_high, v_high), _imgSegm);
		cv::putText(_imgInput, TITLE_INPUT, originPoint, cv::FONT_HERSHEY_COMPLEX, scale_font, TEXT_COLOR, FONT_THICKNESS, cv::LINE_8);

		cv::imshow(TITLE_INPUT, _imgInput);
		cv::imshow(TITLE_OUTPUT, _imgSegm);

		char key = (char)cv::waitKey(1);
		if (key == 27) // ESC is 27 in ASCII
		{
			break;
		}
		if ((cv::getWindowProperty(TITLE_INPUT, cv::WND_PROP_VISIBLE) < 1) || (cv::getWindowProperty(TITLE_OUTPUT, cv::WND_PROP_VISIBLE) < 1))
			break;
	}
	return;
}

std::vector<c_th> Segmentation::readThreshold(std::ifstream& thr_file)
{
	std::vector<c_th>thr;
	std::string row;
	std::string elements[NUMBER_OF_ELEMENTS];

	c_th color;
	int _index;
	while (!thr_file.eof())
	{
		_index = 0;
		getline(thr_file, row, '\n');

		std::istringstream ss(row);

		while (getline(ss, elements[_index], ','))
		{
			//std::cout << elements[_index] << std::endl;
			_index++;
		}

		color.name = elements[0];

		color.low_thr[0] = std::stof(elements[1]);
		color.high_thr[0] = std::stof(elements[2]);

		color.low_thr[1] = std::stof(elements[3]);
		color.high_thr[1] = std::stof(elements[4]);

		color.low_thr[2] = std::stof(elements[5]);
		color.high_thr[2] = std::stof(elements[6]);

		thr.push_back(color);
	}
	thr_file.close();


	return thr;
}
