// This code makes a bit more sense than the previous one at the moment, but I have high hopes that it will soon function as its name implies.
#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

vector <float> Vector(float x, float y, float z, float w = 1) {
	return { x, y, z, w };
}

vector <float> Add(vector <float> vec1, vector <float> vec2) {
	return { vec1[0] + vec2[0], vec1[1] + vec2[1], vec1[2] + vec2[2], 1};
}

vector <float> MultiplyByNumber(vector <float> vec, int num) {
	return { vec[0] * num, vec[1] * num, vec[2] * num, vec[3]};
}

vector <vector <float>> MatrixSum(vector <vector <float>> mat1, vector <vector <float>> mat2) {
	vector <vector <float>> matF = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; i < 4; j++) {
			matF[i][j] = mat1[i][0] * mat2[0][j] +
				mat1[i][1] * mat2[1][j] +
				mat1[i][2] * mat2[2][j] +
				mat1[i][3] * mat2[3][j];
		}
	}
	return matF;
}

vector <vector <float>> GetXRotation(float angle) {
	float rad = 3.1415 / 180 * angle;
	return {
		{1, 0, 0, 0},
		{0, cos(rad), -sin(rad), 0},
		{0, sin(rad), cos(rad), 0},
		{0, 0, 0, 1}
	};
}

vector <float> MultiplyVecByMat(vector <vector <float>> mat, vector <float> vec) {
	return { 
	mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3],
	mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3],
	mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3],
	mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3] 
	};
}

void print(vector <float> vec) {
	for (int i = 0; i < 4; i++) {
		cout << vec[i] << " ";
	}
	cout << "\n";
}

void DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, char* screen) {
	float a = x1 - x0;
	float b = y1 - y0;
	float c = z0 - z1;
	float len = sqrt(pow(a, 2) + pow(b, 2));
	float offsetX = (a / len), offsetY = (b / len), offsetZ = (c / len);
	float xn = x0 + offsetX, yn = y0 + offsetY, zn = z0 + offsetZ;
	float t = 1;
	if (x0 == x1 || y0 == y1) {
		t = 0;
	}
	screen[(int)(trunc(x0 + (30 - y0) * 120) - t)] = '@';
	for (int i = 1; i < len; i++) {
		screen[(int)trunc(xn + trunc(30 - yn) * 120)] = '@';
		xn += offsetX;
		yn += offsetY;
	}
}

void DrawSquare(vector <vector <float>> tops, vector <vector <int>> connect, char* screen) {
	for (int i = 0; i < 12; i++) {
		vector <float> top1 = MultiplyVecByMat(GetXRotation(30), tops[connect[i][0]]);
		vector <float> top2 = MultiplyVecByMat(GetXRotation(30), tops[connect[i][1]]);
		float x0 = top1[0], y0 = top1[1], z0 = top1[2];
		float x1 = top2[0], y1 = top2[1], z1 = top2[2];
		DrawLine(x0, y0, z0, x1, y1, z1, screen);
	}
}

int main() {
	const int SIZE = 120 * 30 + 1;
	char* output = new char[SIZE];
	output[SIZE - 1] = '\0';

	int ind = 0;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 120; j++) {
			output[ind] = '.';
			ind++;
		}
	}
	
	vector <vector <float>> tops = {
		{20, 20, 15, 1},
		{20, 20, 25, 1},
		{30, 20, 25, 1},
		{30, 20, 15, 1},
		{20, 10, 15, 1},
		{20, 10, 25, 1},
		{30, 10, 25, 1},
		{30, 10, 15, 1}
	};

	vector <vector <int>> connect = {
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},
		{4, 0},
		{1, 5},
		{2, 6},
		{3, 7},
		{4, 5},
		{4, 7},
		{5, 6},
		{6, 7}
	};

	DrawSquare(tops, connect, output);

	printf(output);

	delete[] output;
	return 0;
}
