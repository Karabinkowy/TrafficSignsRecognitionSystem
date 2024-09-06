#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

const double COLOR_WEIGHTS[] = {0.9, 0.9, 0.8, 0.3, 0.4, 0.1};//black, white, yellow, blue, red,  non-color,s
const double PIXEL_WEIGHTS[] = { 0.1, 0.2, 0.3};// first, second, third channel weight; weights to assign to a pixel

class Color {
public:
	int thresholds[6];
	Color(int lh, int ls, int lv, int hh, int hs, int hv)
	{
		thresholds[0] = lh;
		thresholds[1] = ls;
		thresholds[2] = lv;
		thresholds[3] = hh;
		thresholds[4] = hs;
		thresholds[5] = hv;
	}
};

Color black(0, 53, 143, 150, 43, 198);
Color white(0, 53, 143, 150, 43, 198);
Color yellow(0, 53, 143, 150, 43, 198);
Color blue(0, 53, 143, 150, 43, 198);
Color red(0, 53, 143, 150, 43, 198);

const double MIN_COLOR[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
const double MAX_COLOR[] = { 11.0, 22.0, 33.0, 44.0, 55.0, 66.0 };


const std::vector<Color> COLORS_THRESHOLD = {black, white, yellow, blue, red}; // black, white, yellow, blue, red; lower and higher threshold

const int DELTA[] = {15, 10, 5, 20};
const int VECTOR_SIZES[] = {1, 4, 16, 64, 128, 256};
const int ENCODING_SIZE = 32;

class Coder
{
	public:
		Coder(std::string path_DB, std::string signes_path, std::vector<std::string> signes_names, std::string ext);
		Coder(std::string image, std::string path_DB, std::string signes_path, std::vector<std::string> signes_names, std::string ext);

		std::string sign_name;
		double sign_accuracy;
	private:
		std::string pth_signes;
		std::string pth_DB;
		std::vector<std::string> signes;
		std::string extension;
		std::string sign_name;
		std::string img_path;

		std::vector<std::vector<double>> r;
		std::vector<std::vector<std::vector<double>>> r_candidates;
		std::vector<std::string> candidates_names;

		void encode_train();
		void encode_normal();
		void printToCSV(std::string file);
		void readFromCSV(std::string file, std::vector<std::vector<double>> comparator);
		void encode_vector(std::vector<double>& v, const int& num, const std::string file);
		void encode_image(const cv::Mat& img, double* img_values);
		void divideImage(double* img_values, const int& rows, const int& cols, const int& num);
		void assignWeight(int pixel[3], double& weight);
		void extractCandidates();

};