#include "comparator.h"

double dif(double x)
{
	double diff;
	double _pi = 3.14159;

	if (x == 0)
	{
		diff = 0;
	}
	else if (x > 0)
	{
		diff = (atan(x - 5) + _pi / 2) / _pi;
	}
	
	return diff;
}


double d1(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d1 = 0.0;
	double _diff;

	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d1 += _diff;
		}
	}
	_d1 *= 1;
	return _d1;
}
double d2(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d2 = 0.0;
	double _diff;
	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d2 += _diff;
		}
	}
	_d2 *= 0.25;
	return _d2;
}
double d3(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d3 = 0.0;
	double _diff;
	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d3 += _diff;
		}
	}
	_d3 *= 0.063;
	return _d3;
}
double d4(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d4 = 0.0;
	double _diff;
	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d4 += _diff;
		}
	}
	_d4 *= 0.016;
	return _d4;
}
double d5(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d5;
	double _diff;
	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d5 += _diff;
		}
	}
	_d5 *= 0.008;
	return _d5;
}
double d6(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2)
{
	double _d6;
	double _diff;
	for (int i = 0; i < r1.size(); ++i)
	{
		for (int j = 0; j < r1[i].size(); ++j)
		{
			_diff = dif(fabs(r1[i][j] - r2[i][j]));
			_d6 += _diff;
		}
	}
	_d6 *= 0.004;
	return _d6;
}




Comparator::Comparator(std::vector<std::vector<double>> r, std::vector<std::vector<std::vector<double>>> r_candidates, std::vector<std::string> names_candidates)
{
	int _index = 0;
	double _sim = 0;

	int bestMatch_index = 0;
	bestMatch_value = 0;
	double _d1, _d2, _d3, _d4, _d5, _d6;
	
	for (int i = 0; i < r_candidates.size(); ++i)
	{
		_d1 = d1(r, r_candidates[i]);
		_d2 = d2(r, r_candidates[i]);
		_d3 = d3(r, r_candidates[i]);
		_d4 = d4(r, r_candidates[i]);
		_d5 = d5(r, r_candidates[i]);
		_d6 = d6(r, r_candidates[i]);

		_sim = 1 - (0.01 * _d1 + 0.02 * _d2 + 0.07 * _d3 + 0.1 * _d4 + 0.2 * _d5 + 0.6 * _d6);
		if (bestMatch_value > _sim) {
			bestMatch_index = _index;
			bestMatch_value = _sim;
		}
	}

	bestMatch_name = names_candidates[bestMatch_index];
}