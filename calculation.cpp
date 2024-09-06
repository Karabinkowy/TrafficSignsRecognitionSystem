#include "calculation.h"

void Calculation::calc(cv::Rect object_1, cv::Rect object_2)
{
	cv::Rect object_1;
	cv::Rect object_2;
	cv::Rect* object_A = NULL;
	cv::Rect* object_B = NULL;
	if ((object_2.y - object_1.y) > 0)
	{
		object_A = &object_1;
		object_B = &object_2;
	}
	else {
		object_A = &object_2;
		object_B = &object_1;
	}

	int _A_x = object_A->x;
	int _A_y = object_A->y;
	int _A_width = object_A->width;
	int _A_height = object_A->height;

	int _B_x = object_B->x;
	int _B_y = object_B->y;
	int _B_width = object_B->width;
	int _B_height = object_B->height;


	// x,y - coordinates of the upper left corner
	d_h1 = std::abs(_B_y - (_A_y + _A_width));
	d_h2 = std::abs((_B_y + _B_width) - _A_y);
	d_hor = d_h1 / d_h2;

	d_v1 = std::abs((_B_x + _B_height) - _A_x);
	d_v2 = std::abs(_B_x - (_A_x + _A_height));
	d_ver = d_v1 / d_v2;

	p_h1 = std::abs(_B_y - _A_y);
	p_h2 = std::abs((_B_y + _B_width) - (_A_y + _B_width));
	p_h3 = d_h2;
	l_hor = (p_h1 + p_h2) / p_h3;

	p_v1 = std::abs(_B_x - _A_x);
	p_v2 = std::abs((_B_x + _B_height) - (_A_x + _A_height));
	p_v3 = d_v2;
	l_ver = (p_v1 + p_v2) / p_v3;

	area_A = (_A_height) * (_A_width);
	area_B = (_B_height) * (_B_width);

	int _x{ _A_x };
	int _y{ _A_y };
	for (; _x <= (_A_x + _A_height); ++_x)
	{
		if ((_B_x <= _x) && (_x <= (_B_x + _B_height)) && (_B_y <= _y) && (_y <= (_B_y + _B_width)))
		{

			b++;
		}
		for (; _y <= (_A_y + _A_width); ++_y)
		{
			if ((_B_x <= _x) && (_x <= (_B_x + _B_height)) && (_B_y <= _y) && (_y <= (_B_y + _B_width)))
			{

				a++;
			}
		}
	}
	if ((a + b) != 0)
		a = a / b;

	inter = (a * b) / std::min(area_A, area_B);

	ratio_A = _A_width / _A_height;
	ratio_B = _B_width / _B_height;

	return;
}

cv::Rect Calculation::connectBoxes(cv::Rect& box1, cv::Rect& box2)
{
	//find farthest corners
	cv::Point corner[8];
	int _distance = 0;
	int _maxDistance = 0;

	int _farCornerIndex1 = 0;
	int _farCornerIndex2 = 7;


	corner[0] = box1.tl();
	corner[1] = cv::Point(box1.x + box1.height, box1.y);
	corner[2] = cv::Point(box1.x, box1.y + box1.width);
	corner[3] = box1.br();
	corner[4] = box2.tl();
	corner[5] = cv::Point(box2.x + box2.height, box2.y);
	corner[6] = cv::Point(box2.x, box2.y + box2.width);
	corner[7] = box2.br();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			_distance = abs(corner[i].x - corner[j].x) + abs(corner[i].y - corner[j].y);
			if (_distance > _maxDistance)
			{
				_maxDistance = _distance;
				_farCornerIndex1 = i;
				_farCornerIndex2 = j;
			}
		}
	}
	cv::Rect _newBox;
	if (corner[_farCornerIndex1].x < corner[_farCornerIndex2].x)
		_newBox.x = corner[_farCornerIndex1].x;
	else
		_newBox.x = corner[_farCornerIndex2].x;
	if (corner[_farCornerIndex1].y < corner[_farCornerIndex2].y)
		_newBox.y = corner[_farCornerIndex1].y;
	else
		_newBox.y = corner[_farCornerIndex2].y;

	_newBox.height = abs(corner[_farCornerIndex1].x - corner[_farCornerIndex2].x);
	_newBox.width = abs(corner[_farCornerIndex1].y - corner[_farCornerIndex2].y);

	return _newBox;
}

void Calculation::checkBoxes(cv::Rect& box1, cv::Rect& box2)
{
	bool sameSign = false;
	if (inter >= INTER_L && inter < INTER_H)
	{
		sameSign = true;
	}
	if ((d_hor >= D_HOR_L && d_hor <= D_HOR_H) && ((l_ver >= L_VER_L && l_ver <= L_VER_H)))
	{
		sameSign = true;
	}
	if ((!(ratio_A >= RATIO_L && ratio_A <= RATIO_H) || !(ratio_B >= RATIO_L && ratio_B <= RATIO_H)) && (d_ver >= D_VER_L && d_ver <= D_VER_H) && (l_hor >= L_HOR_L && l_hor <= L_HOR_H))
	{
		sameSign = true;
	}

	if (sameSign)
	{
		cv::Rect _newBox = connectBoxes(box1, box2);
	}
}

Calculation::Calculation(cv::Rect object_1, cv::Rect object_2, std::vector<std::vector<cv::Rect>> improved_boxes)
{
	calc(object_1, object_2);
	checkBoxes(object_1, object_2);

}