#include <iostream>
#include <vector>
#include <cstdlib>

#include "imageProcessing.h"

ImageProcessing::ImageProcessing(Parser& parser) : p(parser)
{
	cv::Mat _img_edited;
	img_input = cv::imread(p.image_path, cv::IMREAD_COLOR);

	_img_edited = img_input.clone();
	if (_img_edited.empty())
	{
		std::cout << "Could not read the image:" << p.image_path << std::endl;
		throw;
	}
	// Open file with threshold values for segmentation
	std::ifstream thr_file;
	thr_file.open(p.threshold_path);
	if (thr_file.is_open())
	{
		std::cout << "File with threshold values opened" << std::endl;
	}
	else
	{
		std::cout << "File with threshold values not found" << std::endl;
		throw;
	}

	// Segmentate image
	Segmentation segm(_img_edited);
	if (p.mode == 'T')
	{
		segm.test_mode();
		potentialSigns = segm.binarizedImages;
	}
	else if (p.mode == 'N')
	{
		segm.normal_mode(thr_file);
		potentialSigns = segm.binarizedImages;
	}
	// Find contours and circumscribe them with boxes
	findObjects();
	// Analyse objects to find arguments for fuzzyController + improve boundingBoxes
	FuzzyController obj(potentialSigns_boxes);
	// Tear potential signs
	potentialSigns = createMask(obj.improvedSigns_boxes);
}

void ImageProcessing::findObjects()
{
	std::vector<cv::Rect> boundRect;
	for (int i = 0; i < potentialSigns.size(); ++i)
	{
		cv::Mat _img = img_input.clone();
		cv::cvtColor(_img, _img, cv::COLOR_BGR2GRAY);

		std::vector<cv::Vec4i> hierarchy;
		std::vector<std::vector<cv::Point>> contours;

		cv::findContours(_img, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		// assign value to send to fuzzyController
		std::vector<std::vector<cv::Point>> contours_poly(contours.size());

		for (int idx = 0; idx < contours.size(); ++idx)
		{
			cv::approxPolyDP(contours[idx], contours_poly[idx], 3, true);
			boundRect.push_back(cv::boundingRect(contours_poly[idx]));
		}
		potentialSigns_boxes.push_back(boundRect);
	}
	return;
}
std::vector<cv::Mat> ImageProcessing::createMask(std::vector<std::vector<cv::Rect>> improvedSignsBoxes)
{
	std::vector<cv::Mat> _potentialSigns;
	cv::Mat _img;
	for (int i = 0; i < improvedSignsBoxes.size(); ++i)
	{
		for (int j = 0; j < improvedSignsBoxes[i].size(); ++j)
		{
			_img = img_input(cv::Range(improvedSignsBoxes[i][j].x, improvedSignsBoxes[i][j].x + improvedSignsBoxes[i][j].height), cv::Range(improvedSignsBoxes[i][j].y, improvedSignsBoxes[i][j].y + improvedSignsBoxes[i][j].width));
			_potentialSigns.push_back(_img);
		}
	}
	return _potentialSigns;
}