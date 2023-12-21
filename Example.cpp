#include <iostream>
#include <cmath>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {
	const int SIZE = 120 * 30 + 1;
	char* output = new char[SIZE];
	float rad = 0.5;

	char gradient[8] = " *|$#@";

	output[120 * 30] = '\0';
	int mx = 10000000;

	for (int t = 0; t < 10000; t++) {

		float y = 1.0;
		int IndexNow = 0;

		for (int i = 0; i < 30; i++) {

			float x = -1.0;

			for (int j = 0; j < 120; j++) {

				float x1 = x * (24.0f / 11.0f);

				if (pow(x1 + cos(t * 0.003), 2) + pow(y + sin(t * 0.003), 2) <= rad) {

					char now = gradient[(int)roundf(10 * (rad - (pow(x1 + cos(t * 0.003), 2) + pow(y + sin(t * 0.003), 2))))];
					output[IndexNow] = now;

				}
				else {

					output[IndexNow] = ' ';

				}

				IndexNow += 1;
				x += (1.0f / 70.0f);
			}
			y -= (1.0f / 17.5f);
		}
		printf(output);
		printf("\x1b[H");
	}
	delete[] output;
	return 0;
}
