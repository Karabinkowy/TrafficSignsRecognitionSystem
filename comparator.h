#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <cmath>
class Comparator
{
public:
	double bestMatch_value;
	std::string bestMatch_name;
	Comparator(std::vector<std::vector<double>> r, std::vector<std::vector<std::vector<double>>> r_candidates, std::vector<std::string> names_candidates);

private:
	double d1(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double d2(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double d3(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double d4(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double d5(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double d6(std::vector<std::vector<double>> r1, std::vector<std::vector<double>> r2);
	double dif(double x);
};