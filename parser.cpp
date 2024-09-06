#include "parser.h"

Parser::Parser(int argc, char* argv[])
{
	if (argc == 3)
	{
		image_path = argv[1];
		mode = argv[2][0];
	}
	else if (argc == 5)
	{
		image_path = argv[1];
		mode = argv[2][0];
		threshold_path = argv[3];
		color_name = argv[4];
		color_index = set_enum(color_name);

		if (!color_index)
		{
			std::cout << "Color does not exist" << std::endl;
			throw std::runtime_error("error");

		}
		else if (argc > 5)
		{

			std::cout << " Too many command line arguments" << std::endl;
			throw std::runtime_error("error");

		}
	}

};