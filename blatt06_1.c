#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "libBMP.h"
#include <math.h>
#include <windows.h>   // WinApi header

#define W 500			//TODO: fix bigger sizes / not equal
#define H 500
#define STEP 0.001

#define COLOR_YELLOW  0x00FFFF00
#define COLOR_PINK  0x00FF00FF
#define COLOR_LIGHTBLUE  0x0000FFFF

int debug = 0;															//Debug-Modus
double xmin = -5.0, xmax = 5.0;
double ymin = -2.0, ymax = 2.0;

void toMath(uint32_t bmpx, uint32_t bmpy, double *mathx, double *mathy) {
	*mathx = (bmpx*(xmax-xmin))/W;
	*mathy = H - (bmpy*(ymax-ymin))/H;
}

void toBMP(double mathx, double mathy, uint32_t *bmpx, uint32_t *bmpy) {
	*bmpx = W/(xmax-xmin)*(mathx-xmin);
	*bmpy = H/(ymax-ymin)*(ymax-mathy);
//	printf("%u\n",*bmpy);
	if (*bmpy>H) *bmpy=H;				//TODO: fix overflow in 2nd quadrant
}

void yfestlegen(double(f)(double)) {
	for (double i = xmin; i < xmax; i+=STEP) {
		if (f(i)<ymin) ymin = f(i);
		if (f(i)>ymax) ymax = f(i);
	}
}

void zeichnen(double(f)(double), int color, uint32_t *pointer) {
	uint32_t liniex = 0, liniey = 0;
	for (double i = xmin; i < xmax; i+=STEP) {
		toBMP(i, f(i), &liniex, &liniey);
		pointer[liniey*W+liniex]=color;
	}
}
double flatline(double x) {
	(void)x;
	return 0.0;
}
double square(double x) {
	return (x*x);
}

int main() {
	HANDLE  hConsole;													//Fuer Aenderung der Farbe unter windows benoetigt
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	uint32_t* pArray = (uint32_t*) malloc(W*H*sizeof(uint32_t));
	for (uint32_t i = 0; i < W*H; i++) pArray[i]=COLOR_WHITE; 	//weißer hintergrund
		
	yfestlegen(sin);
	yfestlegen(fabs); //nicht optional
	//yfestlegen(exp);
	//yfestlegen(log);
//	yfestlegen(square); //nicht optional

	zeichnen(flatline,COLOR_BLACK, pArray);						//Koord-Achsen
	uint32_t liniex = 0, liniey = 0;
	for (double i = ymin; i < ymax; i+=STEP) {
		toBMP(0.0, i, &liniex, &liniey);
		pArray[liniey*W+liniex]=COLOR_BLACK;
	}

	zeichnen(sin, COLOR_RED, pArray);							//Funktionen
	zeichnen(exp, COLOR_GREEN, pArray);
	zeichnen(log, COLOR_BLUE, pArray);
	zeichnen(asin, COLOR_LIGHTBLUE, pArray);
	zeichnen(fabs, COLOR_PINK, pArray);
	zeichnen(atan, COLOR_YELLOW, pArray);
//	zeichnen(square, COLOR_YELLOW, pArray);
	
	bmp_create("test.bmp", pArray, W, H);
	free(pArray);
	SetConsoleTextAttribute(hConsole, 2);
	printf("Sie haben gewonnen!");
	SetConsoleTextAttribute(hConsole, 6);
	return(0);
}