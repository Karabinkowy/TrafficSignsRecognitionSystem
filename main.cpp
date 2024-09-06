#include "parser.h"
#include "imageProcessing.h"
#include "fuzzyController.h"
#include "coder.h"
#include "comparator.h"

std::string PATH_DB = "C:/db.csv"; // path to database (.csv file) with parameters describing signs
std::string PATH_IMAGES = "C:/images"; // path to folder with images, used to train program
// names of images in database, used to index images in database
std::vector<std::string> SIGNS_NAME = { "A-1", "A-2", "A-3", "A-4", "A-5", "A-6", "A-6-a", "A-6-b", "A-6-c", "A-6-d", "A-6-e", "A-7"
"A-8", "A-9", "A-10", "A-11", "A-11-a", "A-12-a", "A-12-b", "A-12-c", "A-13", "A-14", "A-15", "A-16", "A-17", "A-18-a", "A-19", "A-20", "A-21", "A-22", "A-23",
"A-24", "A-25", "A-26", "A-27", "A-28", "A-29", "A-30", "A-31", "A-32", "A-33", "A-34",
"B-1", "B-2", "B-3", "B-3-a", "B-4", "B-5", "B-6", "B-7", "B-8", "B-9", "B-10", "B-11", "B-12", "B-13", "B-14",
"B-15", "B-16", "B-17", "B-18", "B-19", "B-20", "B-21", "B-22", "B-23", "B-24", "B-25", "B-26", "B-27", "B-28",
"B-29", "B-30", "B-31", "B-32", "B-33", "B-44", "C-1", "C-2", "C-3", "C-4", "C-5", "C-6", "C-7", "C-8", "C-9",
"C-10", "C-11", "C-12", "C-13", "C-13-a", "C-14", "C-15", "C-16", "C-16-a", "C-17", "C-18", "C-19",
"D-1", "D-2", "D-3", "D-4-a", "D-4-b", "D-5", "D-6", "D-6-a", "D-6-b", "D-7", "D-8", "D-9", "D-10",
"D-11", "D-12", "D-13", "D-13-a", "D-14", "D-15", "D-16", "D-17", "D-18", "D-18-a", "D-18-b","D-19",
"D-20", "D-21", "D-21-a", "D-22", "D-23", "D-23-a", "D-24", "D-25", "D-26", "D-26-a", "D-26-b",
"D-26-c", "D-26-d", "D-27", "D-28", "D-29", "D-30", "D-31", "D-32", "D-33", "D-34", "D-34-a", "D-35",
"D-35-a", "D-36", "D-36-a", "D-37", "D-38", "D-40", "D-41", "D-42", "D-43", "D-44", "D-45", "D-46",
"D-47", "D-48", "D-49", "D-50", "D-51", "D-52", "D-53" };
std::string EXT = ".png"; // extension of an image file in database
std::string OUTPUT_PATH = "C:/output"; // foleer to which recognized images will be saved

int main(int argc, char *argv[])
{
	Parser parser(argc, argv);
	try 
	{
		ImageProcessing prc(parser);
		Coder cdr(prc.potentialSigns,PATH_DB, PATH_IMAGES, SIGNS_NAME, EXT, OUTPUT_PATH);
	}
	catch (const char* e)
	{

	}
	return 0;
}