#include <iostream>
#include <cmath>

const int HEIGTH = 30, WIDTH = 120;
const int SIZE = HEIGTH * WIDTH;
char* screen = new char[SIZE + 1];
int* distBuffer = new int[SIZE]; // Buffer to decide if the point is close enough to print it
double A = 0, B = 0, C = 0;
int cubeWidth = 44;
double incrementSpeed = 1.8; // Define increment speed for cordinates
double distanceFormCam = 250;
double scale = 40; // Constant scaling factor 

/* The 3 following functions were derived from rotation matrix */
double calculateX(double x, double y, double z) {
	return cos(A) * cos(B) * x + (cos(A) * sin(B) * sin(C) - sin(A) * cos(C)) * y + (sin(A) * sin(C) + cos(A) * sin(B) * cos(C)) * z;
}

double calculateY(double x, double y, double z) {
	return sin(A) * cos(B) * x + (cos(A) * cos(C) + sin(A) * sin(B) * sin(C)) * y + (sin(A) * sin(B) * cos(C) - cos(A) * sin(C)) * z;
}

double calculateZ(double x, double y, double z) {
	return -x * sin(B) + y * cos(B) * sin(C) + z * cos(B) * cos(C);
}

void calculateSurface(double x, double y, double z, char chr) {

	// Define rotated cordinates
	double x_rot = calculateX(x, y, z);
	double y_rot = calculateY(x, y, z);
	double z_rot = calculateZ(x, y, z) + distanceFormCam;

	// Define a distance scale large and small objects 
	double dist = 1 / z_rot;

	// Map 3D cordinates to 2D palne via perspective projection formula
	int xp = (int)(WIDTH / 2 + dist * 2 * scale * x_rot);
	int yp = (int)(HEIGTH / 2 + dist * scale * y_rot);
	// WIDTH / 2, HEIGTH / 2 were added to place cube at the center
	int idx = yp * WIDTH + xp;

	if (idx >= 0 && idx < SIZE) {
		if (distBuffer[idx] < dist) {
			screen[idx] = chr;
			distBuffer[idx] = dist;
		}
	}
}

int main() {
	screen[SIZE] = '\0';
	while (1) {
		memset(screen, ' ', SIZE);
		memset(distBuffer, 0, SIZE);
		for (double x = -cubeWidth; x < cubeWidth; x += incrementSpeed) {
			for (double y = -cubeWidth; y < cubeWidth; y += incrementSpeed) {
				// Define "changing" cordinates for each side
				calculateSurface(x, y, -cubeWidth, '#');
				calculateSurface(cubeWidth, y, x, '@');
				calculateSurface(-cubeWidth, y, -x, '&');
				calculateSurface(-x, y, cubeWidth, '+');
				calculateSurface(x, -cubeWidth, -y, '=');
				calculateSurface(x, cubeWidth, y, '()');
			}
		}
		printf(screen);
		printf("\x1b[H"); // Clear the screen
		A += 0.005;
		B += 0.005;
		C += 0.001;
	}

	delete[] screen;
	return 0;
}
