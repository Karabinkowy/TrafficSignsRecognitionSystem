#pragma once
#include <vector>
#include "calculation.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

class FuzzyController
{
public:
	std::vector<std::vector<cv::Rect>> improvedSigns_boxes;
	FuzzyController(std::vector<std::vector<cv::Rect>> potentialSigns_boxes);

private:
	void removeIncorrectObjects(std::vector<std::vector<cv::Rect>> boxes);
	void eraseDuplicateObjects(std::vector<std::vector<cv::Rect>> improvedSigns_boxes);
	
};