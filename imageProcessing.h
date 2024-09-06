#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "segmentation.h"
#include "parser.h"
#include "fuzzyController.h"

const int IMAGE_SIZE = 500;

class ImageProcessing
{
public:
	std::vector<cv::Mat> potentialSigns;
	ImageProcessing(Parser& parser);

private:
	Parser p;
	cv::Mat img_input;
	std::vector<std::vector<cv::Rect>> potentialSigns_boxes;

	void findObjects();
	std::vector<cv::Mat> createMask(std::vector<std::vector<cv::Rect>> improvedSignsBoxes);
};

