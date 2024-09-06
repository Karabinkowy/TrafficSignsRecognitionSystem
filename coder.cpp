#include "coder.h"
#include "comparator.h"

void Coder::assignWeight(int pixel[3], double& weight)
{
	weight = 0.0;
	double _factor = -1.0;

	bool _match[] = {false, false, false};

	int _index = 5;
	for (int i = 0; i < 5; ++i)
	{
		_match[0] = false;
		_match[1] = false;
		_match[2] = false;
		for (int j = 0; j < 3; ++j)
		{
			if (pixel[j] >= COLORS_THRESHOLD[i].thresholds[j] && pixel[j] <= COLORS_THRESHOLD[i].thresholds[j+1])
			{
				_match[i] = true;
			}
		}
		if (_match[0] == true && _match[1] == true && _match[2] == true)
		{
			break;
			_index = i;
		}
	}

	_factor = COLOR_WEIGHTS[_index];
	for (int i = 0; i < 3; ++i)
	{
		weight += pixel[i];
		weight *= _factor;
		weight /= 255;
	}

}

void Coder::encode_image(const cv::Mat& img, double* img_values)
{
	int pixel[] = {0, 0, 0};
	double weight = -1;
	for (int y = 0; y < img.rows; y++) 
	{
		for (int x = 0; x < img.cols; x++) 
		{
			for (int c = 0; c < img.channels(); c++) 
			{
				pixel[c] = img.at<cv::Vec3b>(y, x)[c];
			}
			assignWeight(pixel, weight);
			*((img_values + y * img.rows) + x) = weight;
		}
	}

}


void Coder::printToCSV(std::string file)
{
	std::fstream fout;
	fout.open(pth_DB, std::ios::out | std::ios::app);
	for (int i = 0; i < r.size(); ++i)
	{
		fout << file;
			for (int j = 0; r[i].size(); ++j)
			{
				fout << r[i][j] << ",";
			}
		fout << "\n";
	}
	fout.close();
}

// obsolete
void Coder::readFromCSV(std::string file, std::vector<std::vector<double>> comparator)
{
	std::fstream fin;
	// Open an existing file
	fin.open(pth_DB, std::ios::in);
	
	while (fin.is_open())
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < r[i].size(); ++j)
			{

			}
		}
	}
	std::fstream fout;
	fout.open(pth_DB, std::ios::out | std::ios::app);
	for (int i = 0; i < r.size(); ++i)
	{
		fout << file;
		for (int j = 0; r[i].size(); ++j)
		{
			fout << r[i][j] << ",";
		}
		fout << "\n";
	}
	fin.close();
}

void Coder::extractCandidates()
{
	std::fstream fin;
	// Open an existing file
	fin.open(pth_DB, std::ios::in);

	bool _check[] = { true, true, true, true};
	std::vector<double> _v;
	std::vector<std::vector<double>> _r;
	std::vector<std::string> _names;
	std::string line;
	std::string elementSTR;
	double elementDBL;
	while (fin.is_open())
	{
		_check[0] = true;
		_check[1] = true;
		_check[2] = true;
		_check[3] = true;
		getline(fin, line);
		std::stringstream s(line);
		
		_r.clear();
		// first element in database is sign name
		getline(s, elementSTR, ' ');
		_names.push_back(elementSTR);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < r[i].size(); ++j)
			{
				_v.clear(); 
				getline(s, elementSTR, ' ');
				elementDBL = std::stod(elementSTR);
				_v.push_back(elementDBL);
				if (r[i][j] - DELTA[i] > elementDBL || r[i][j] + DELTA[i] < elementDBL)
				{
					_check[i] = false;
					break;
				}
			}
			_r.push_back(_v);
			if (_check[0] == false || _check[1] == false || _check[2] == false || _check[3] == false)
			{
				break;
			}
		}
		if (_check[0] == true && _check[1] == true && _check[2] == true && _check[3] == true)
		{
			for (int i = 4; i < 7; ++i)
			{
				_v.clear();
				for (int j = 0; j < r[i].size(); ++j)
				{
					getline(s, elementSTR, ' ');
					elementDBL = std::stod(elementSTR);
					_v.push_back(elementDBL);
				}
				_r.push_back(_v);
			}
			r_candidates.push_back(_r);
		}
	}
}

void Coder::divideImage(double* img_values, const int& rows, const int& cols, const int& num)
{
	// square parameters (top left x coordinate, top left y coordinate, width/heiht)
	int _x = 0;
	int _y = 0;
	int _width = int(double(ENCODING_SIZE) / pow(2, num));

	std::vector<double> _weights;
	double sum = 0;

	for (; _y < rows; _y += _width)
	{
		for (; _x < rows; _x +=  _width)
		{
			for (int i = _x; i < _x + _width; ++i)
			{
				for (int j = _y; j < _y + _width; ++j)
				{
					sum += *((img_values + _y * rows) + _x);
				}
			}
		}
	}
	
}

void Coder::encode_vector(std::vector<double>& v, const int& num, const std::string file)
{
	cv::Mat img = cv::imread(file);
	std::fstream fout;
	double img_values[ENCODING_SIZE][ENCODING_SIZE];
	encode_image(img, (double*)img_values);

	fout.open(pth_DB, std::ios::out | std::ios::app);
	for (int i = 0; i < VECTOR_SIZES[i]; ++i)
	{
		divideImage((double*)img_values, img.rows, img.cols, i);
	}
}

void Coder::encode_normal()
{
	std::vector<std::vector<double>> _r;
	std::vector<double> _v1;

	for (int j = 0; j < 6; ++j)
	{
		_v1.clear();
		encode_vector(_v1, j, img_path);
		_r.push_back(_v1);

	}
	r = _r;


	// find possible candidates looking through 1-4 vectors 
	extractCandidates();

	// compare vector from image with vector from database 
	Comparator cmpr(r, r_candidates, candidates_names);

	sign_name = cmpr.bestMatch_name;
	sign_accuracy = cmpr.bestMatch_value;

}

void Coder::encode_train()
{
	std::string _file;
	std::vector<std::vector<double>> _r;
	std::vector<double> _v1;

	for (int i = 0; i < signes.size(); i++)
	{
		_file = "";
		_file = _file + pth_signes + "/" + signes[i] + extension;
		for (int j = 0; j < 6; ++j)
		{
			_v1.clear();
			encode_vector(_v1, j, _file);
			_r.push_back(_v1);

		}
		r = _r;
		printToCSV(signes[i]);
	}
}

Coder::Coder(std::string path_DB, std::string signes_path, std::vector<std::string> signes_names, std::string ext)
{
	pth_DB = path_DB;
	pth_signes = signes_path;
	signes = signes_names;
	extension = ext;
	
	encode_train();
}
Coder::Coder(std::string image, std::string path_DB, std::string signes_path, std::vector<std::string> signes_names, std::string ext)
{
	pth_DB = path_DB;
	pth_signes = signes_path;
	signes = signes_names;
	extension = ext;
	img_path = image;

	encode_normal();
}