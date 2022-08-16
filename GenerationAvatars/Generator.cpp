#include <iostream>
#include <algorithm>
#include <ctime>
#include <array>
#include <string>
#include "CImg.h"

using namespace std;
typedef array<array<bool, 5>, 5> pict;

void tranc(pict& data) {
	pict ccc = {};
	for (int i = 0; i < 5; i++)
		for (int x = 0; x < 5; x++) {
			ccc[i][x] = data[x][i];
		}
	data = ccc;
}

pict gen() {
	pict output = {};
	array<array<bool, 5>, 2>columns;

	for (int i = 0; i < 2; i++) {
		for (int c = 0; c < 5; c++) {
			columns[i][c] = rand() % 2;
		}
	}
	output[0] = columns[0];
	output[1] = columns[1];

	for (int i = 0; i < 5; i++) output[2][i] = rand() % 2;

	output[3] = columns[1];
	output[4] = columns[0];

	tranc(output);

	return output;

}

void create(const string& path) {
	auto pict = gen();
	cimg_library::CImg<unsigned char>img(50 * 5, 50 * 5, 1, 3);

	unsigned char color[3] = { rand() % 256, rand() % 256, rand() % 256 };
	unsigned char back[3] = { 255, 255, 255};

	img.draw_rectangle(0, 0, 50 * 10, 50 * 10, back);

	for (int i = 0; i < 5; i++)
		for (int x = 0; x < 5; x++)
			if (pict[x][i]) img.draw_rectangle(50 * i, 50 * x, 50 * i + 50, 50 * x + 50, color);

	img.save(path.c_str());
}

int main() {
	srand(time(0));
	for (int i = 0; i < 20; i++) {
		create(to_string(i) + ".bmp");
	}
	return 0;


}