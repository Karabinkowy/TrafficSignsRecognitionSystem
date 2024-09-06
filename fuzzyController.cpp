#include "fuzzyController.h"
#include "calculation.h"

void FuzzyController::removeIncorrectObjects(std::vector<std::vector<cv::Rect>> boxes)
{
	std::vector<std::vector<cv::Rect>> _boxes;
	std::vector<cv::Rect> _v;
	for (int j = 0; j < boxes.size(); ++j)
	{
		_v.clear();
		for (int i = 0; i < boxes[j].size(); ++i)
		{
			if (boxes[j][i].width <= 32 && boxes[j][i].height <= 32)
			{
				double ratio = (boxes[j][i].height / double(boxes[j][i].width));
				if (ratio > 0.24 && ratio < 4.0)
				{
					_v.push_back(boxes[j][i]);
				}
			}
		}
		_boxes.push_back(_v);
	}
	boxes = _boxes;
}

FuzzyController::FuzzyController(std::vector<std::vector<cv::Rect>> potentialSigns_boxes)
{
	int _k;
	int _numberOfBoxes = 0;
	improvedSigns_boxes = potentialSigns_boxes;
	while (!(improvedSigns_boxes.size() == _numberOfBoxes))
	{
		_numberOfBoxes = improvedSigns_boxes.size();
		for (int i = 0; i < improvedSigns_boxes.size(); ++i)
		{
			for (int j = 0; j < improvedSigns_boxes[i].size() - 1; ++j)
			{
				_k = j + 1;
				Calculation clc(improvedSigns_boxes[i][j], improvedSigns_boxes[i][_k], improvedSigns_boxes);
			}
		}
	}
	eraseDuplicateObjects(improvedSigns_boxes);
	removeIncorrectObjects(improvedSigns_boxes);
}

void FuzzyController::eraseDuplicateObjects(std::vector<std::vector<cv::Rect>> improvedSigns_boxes)
{
	std::vector<std::vector<int>> _duplicates;
	std::vector<int> _duplicatesIndexes;
	std::vector<std::vector<cv::Rect>> _improvedSigns_boxes;

	for (int i = 0; i < improvedSigns_boxes.size(); ++i)
	{
		for (int j = 0; j < improvedSigns_boxes[i].size(); ++j)
		{
			for (int k = 0; k < i; ++i)
			{
				for (int l = 0; l < j; ++l)
				{
					if (improvedSigns_boxes[i][j] == improvedSigns_boxes[k][l])
					{
						_duplicatesIndexes[0] = i;
						_duplicatesIndexes[1] = j;

					}
					_duplicates.push_back(_duplicatesIndexes);
				}
			}
		}
	}
	std::vector<cv::Rect> _improvedSigns_boxes_dupl;
	for (int i = 0; i < improvedSigns_boxes.size(); ++i)
	{
		for (int j = 0; j < improvedSigns_boxes[i].size(); ++j)
		{
			for (int k = 0; k < _duplicates.size(); ++k)
			{
				if (!(_duplicates[k][0] == i && _duplicates[k][1] == j))
					_improvedSigns_boxes_dupl.push_back(improvedSigns_boxes[i][j]);
			}
		}
	_improvedSigns_boxes.push_back(_improvedSigns_boxes_dupl);
	}
	improvedSigns_boxes = _improvedSigns_boxes;
}
