package main

import (
	"fmt"
	"time"
	"math"
)

var (
	output 		[]rune
	zBuffer 	[]float64
	screenHeight 	int = 70
	screenWidght 	int = 120
	cubeWidght 	float64 = 80.0
	k2 		float64 = 250.0
	k1 		float64 = 40.0
	A 		float64 = 0.0
	B 		float64 = 0.0
	C		float64 = 0.0
	incrementSpeed  float64 = 1.8
)

func clear() {
	for i := 0; i < screenHeight * screenWidght; i++ {
		output[i] = ' '
		zBuffer[i] = 0.0
	}
}

func render(x, y, z float64, symb rune) {

	cosA := math.Cos(A)
	sinA := math.Sin(A)
	cosB := math.Cos(B)
	sinB := math.Sin(B)
	cosC := math.Cos(C)
	sinC := math.Sin(C)

	xRot := cosA * cosB * x + (cosA * sinB * sinC - sinA * cosC) * y + (cosA * sinB * cosC + sinA * sinC) * z
	yRot := sinA * cosB * x + (sinA * sinB * sinC + cosA * cosC) * y + (sinA * sinB * cosC - cosA * sinC) * z
	zRot := k2 - sinB * x + cosB * sinC * y + cosB * cosC * z
	ooz := 1.0 / zRot

	xp := int(float64(screenWidght) / 2 + ooz * k1 * xRot)
	yp := int(float64(screenHeight) / 2 + ooz * k1 * 0.5 * yRot)
	idx := yp * screenWidght + xp

	if idx >= 0 && idx < screenHeight * screenWidght {
		if ooz > zBuffer[idx] {
			zBuffer[idx] = ooz
			output[idx] = symb
		}
	}

}

func print() {
	fmt.Print("\x1b[H")
	for i := 0; i < screenHeight; i++ {
		fmt.Println(string(output[i * screenWidght : (i + 1) * screenWidght]))
	}
}

func main() {
	output = make([]rune, screenHeight * screenWidght)
	zBuffer = make([]float64, screenHeight * screenWidght)

	ticker := time.NewTicker(16 * time.Millisecond)
	defer ticker.Stop()

	for range ticker.C {

		clear()

		for x := -cubeWidght; x < cubeWidght; x += incrementSpeed {
			for y := -cubeWidght; y < cubeWidght; y += incrementSpeed {
				render(x, y, -cubeWidght, '#')
				render(cubeWidght, y, x, ')')
				render(-cubeWidght, y, -x, '&')
				render(-x, y, cubeWidght, '+')
				render(x, -cubeWidght, -y, '=')
				render(x, cubeWidght, y, '(')
			}
		}

		print()

		A += 0.014
		B += 0.012
		C += 0.011
	}
}
