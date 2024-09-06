#pragma once
#include <fstream>
#include <iostream>

// Command line arguments:
// TrafficSignRecognition.exe D:\signs\drawings\forb3.jpg T D:\praca_wlasna\fuzzyColors.csv red

// default parameters
const std::string IMG_PATH = "D:/praca_wlasna/programowanie/CMPO/TrafficSignRecognition/TrafficSignRecognition/signs/drawings/forb3.jpg";
const char MODE = 'N';
const std::string THR_PATH = "D:/praca_wlasna/programowanie/CMPO/TrafficSignRecognition/TrafficSignRecognition/fuzzyColors.csv";
const int CLR_N = 2;

// path where files should be saved
const std::string SAVE_PATH = "C:/Users/barte/OneDrive/Programy/Pulpit/segmentated/";
// saved file name

enum color
{
	blank = 0,// color does not exist;
	red = 1,
	yellow = 2,
	blue = 3,
	white = 4,
	black = 5,
	navy_blue = 6

};

const color CLR = color::red;

color set_enum(std::string name)
{
	color id = color::blank;
	if (name == "red")
		id = color::red;
	else if (name == "yellow")
		id = color::yellow;
	else if (name == "blue")
		id = color::blue;
	else if (name == "white")
		id = color::white;
	else if (name == "black")
		id = color::black;
	else if (name == "navy_blue")
		id = color::navy_blue;

	return id;
}

class Parser {
public:
	std::string image_path = IMG_PATH;
	std::string threshold_path = THR_PATH;
	std::string color_name{ CLR };
	color color_index = static_cast<color>(CLR_N);
	char mode{ MODE };
	Parser(int argc, char* argv[]);
};