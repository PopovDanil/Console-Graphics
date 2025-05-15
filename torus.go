package main

import (
	"fmt"
	"time"
	"math"
)

var (
	output 		[]rune
	zBuffer         []float64
	screenHeight 	int = 70
	screenWidght 	int = 100
	thetaIncrement  float64 = 0.003
	phiIncrement 	float64 = 0.007
	r1 		float64 = 1.0
	r2 		float64 = 2.0
	k2 		float64 = 10.0
	k1 		float64 = float64(screenWidght) * k2 * 3 / (8 * (r1 + r2))
	symbols 	string = ".,-~:;=!*#$@"
)

func clear() {
	for i := 0; i < screenHeight * screenWidght; i++ {
		output[i] = ' '
		zBuffer[i] = 0.0
	}
}

func render(A, B float64) {

	clear()

	cosA := math.Cos(A)
	sinA := math.Sin(A)
	cosB := math.Cos(B)
	sinB := math.Sin(B)

	for theta := 0.0; theta < math.Pi * 2; theta += thetaIncrement {
		cosT := math.Cos(theta)
		sinT := math.Sin(theta)

		for phi := 0.0; phi < math.Pi * 2; phi += phiIncrement {
			cosP := math.Cos(phi)
			sinP := math.Sin(phi)

			circleX := r2 + r1 * cosT
			circleY := r1 * sinT

			x := circleX * (cosB * cosP + sinA * sinB * sinP) - circleY * cosA * sinB
			y := circleX * (sinB * cosP - sinA * cosB * sinP) + circleY * cosA * cosB
			z := k2 + cosA * circleX * sinP + circleY * sinA
			ooz := 1.0 / z 

			xp := int(float64(screenWidght) / 2 + ooz * k1 * x)
			yp := int(float64(screenHeight) / 2 - ooz * k1 * 0.5 * y)

			l := cosP * cosT * sinB - cosA * cosT * sinP - sinA * sinT + cosB * (cosA * sinT - cosT * sinA * sinP)

			idx := yp * screenWidght + xp

			if (l > 0 && idx >= 0 && idx < screenHeight * screenWidght) {
				if (ooz > zBuffer[idx]) {
					zBuffer[idx] = ooz
					lumenIdx := int(l * 8.0)
					output[idx] = rune(symbols[lumenIdx])
				}
			}
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

	A := 0.0
	B := 0.0

	for range ticker.C {

		render(A, B)

		print()

		A += 0.04
		B += 0.02
	}
}
