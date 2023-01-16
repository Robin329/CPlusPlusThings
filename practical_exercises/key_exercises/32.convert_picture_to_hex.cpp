#include <iostream>
#include <fstream>
#include <string>
#include "base.h"

using namespace std;

#define ARGB_IMAGE_1920_1080_INPUT_PATH                                        \
	"practical_exercises/key_exercises/res/argb_1920_1080.rgb"
#define RGB24_IMAGE_1920_1080_INPUT_PATH                                       \
	"practical_exercises/key_exercises/res/rgb24_1920_1080.rgb"
#define ARGB_IMAGE_1920_1080_OUTPUT_PATH                                       \
	"practical_exercises/key_exercises/res/argb_1920_1080_hex.txt"
#define RGB24_IMAGE_1920_1080_OUTPUT_PATH                                      \
	"practical_exercises/key_exercises/res/rgb24_1920_1080_hex.txt"
int main(int argc, char **argv)
{
	ifstream readFileArgb(
		FileSystem::getPath(ARGB_IMAGE_1920_1080_INPUT_PATH).c_str(),
		std::ifstream::binary);

	ifstream readFileRgb24(
		FileSystem::getPath(RGB24_IMAGE_1920_1080_INPUT_PATH).c_str(),
		std::ifstream::binary);
    ofstream(FileSystem::getPath(ARGB_IMAGE_1920_1080_OUTPUT_PATH).c_str());

    ofstream outRgb24File(
		FileSystem::getPath(RGB24_IMAGE_1920_1080_OUTPUT_PATH).c_str());

    ofstream outArgbFile(FileSystem::getPath(RGB24_IMAGE_1920_1080_OUTPUT_PATH).c_str());

    string s1, s2;

    int len = 0, count = 0;
	unsigned int valArgb;
	// get length of file
	readFileArgb.seekg(0, readFileArgb.end);
	len = readFileArgb.tellg();
	readFileArgb.seekg(0, readFileArgb.beg);
	cout << "readFileArgb length: " << len << endl;
	outArgbFile << "const char argb_8888_1920_1080[] = {\r\n";
	while (!readFileArgb.read((char *)&valArgb, 4).eof()) {
		outArgbFile << "0x" << std::hex << std::setfill('0')
			    << std::setw(8) << valArgb << ", ";
		count++;
		if (count % 4 == 0) {
			outArgbFile << "\r\n";
		}
		// printf("0x%08x\n", valArgb);
	}
	outArgbFile << "};\r\n";

	// get length of file
	readFileRgb24.seekg(0, readFileRgb24.end);
	len = readFileRgb24.tellg();
	readFileRgb24.seekg(0, readFileRgb24.beg);
	cout << "readFileRgb24 length: " << len << endl;
	outRgb24File << "const char rgb_888_1920_1080[] = {\r\n";
	while (!readFileRgb24.read((char *)&valArgb, 4).eof()) {
		outRgb24File << "0x" << std::hex << std::setfill('0')
			     << std::setw(8) << valArgb << ", ";
		count++;
		if (count % 4 == 0) {
			outRgb24File << "\r\n";
		}
		// printf("0x%08x\n", valArgb);
	}
	outRgb24File << "};\r\n";

	if (readFileArgb.is_open() || readFileRgb24.is_open() ||
	    outArgbFile.is_open() || outRgb24File.is_open()) {
		cout << "All file is closed" << endl;
		readFileArgb.close();
		readFileRgb24.close();
		outRgb24File.close();
		outArgbFile.close();
	}

    return 0;
}