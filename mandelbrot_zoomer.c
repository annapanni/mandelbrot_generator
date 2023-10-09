#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <complex.h>
#define Resolution 500

typedef struct Color{
	int r,g,b;
} Color;
int pixels[Resolution][Resolution];
int thismin;

int korlatos_e(double complex c){
  double complex zn =  c;
  for (int i = 1; i <= 100; i++) {
    zn = zn*zn + c;
    if (cabs(zn)>2){
      return i*2.5;
    }
  }
  return 255;
}

void genMandelbrot(double minx, double miny, double range){
	int i, j;
	double delta = range/Resolution;
	for (int i = 0; i < Resolution; i++) {
		for (int j = 0; j < Resolution; j++) {
			double complex c = j*delta+minx + I*(range - i*delta +miny);
			int k = korlatos_e(c);
			pixels[i][j] = k;
			if (k<thismin){
				thismin = k;
			}
		}
	}
}

Color getColor(int a){
	int r, g, b;
	double x = (a-thismin)*(255/(255-thismin));
	r = pow(x, 1.0/3)*pow(255, 2.0/3);
	g = pow(x, 1.0/2)*pow(255, 1.0/2);
	b = pow(x,1.0/4)*pow(255,3.0/4);
	return (Color){r,g,b};
}

void drawMandelbrot(SDL_Renderer *renderer){
	for (int i = 0; i < Resolution; i++) {
		for (int j = 0; j < Resolution; j++) {
			Color c = getColor(pixels[i][j]);
			pixelRGBA(renderer, j, i, c.r, c.g, c.b, 255);
		}
	}
}

void clear(SDL_Renderer *renderer){
	boxRGBA(renderer, 0, 0, Resolution, Resolution, 0, 0, 0, 255);
}

int main(void) {
	//setting SDL up
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
      SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
      exit(1);
  }
  SDL_Window *window = SDL_CreateWindow("Mandelbrot zoomer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Resolution, Resolution, 0);
  if (window == NULL) {
      SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
      exit(1);
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
      SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
      exit(1);
  }

	thismin = 255;
	genMandelbrot(-2, -1.5, 3);
	drawMandelbrot(renderer);
	SDL_RenderPresent(renderer);

	SDL_Event ev;
	double targetx = -1;
	double targety = -1;
	double range = 3;
	do {
		while (!SDL_PollEvent(&ev)) {
			if (targetx != -1) {
				range = range*0.97;
				thismin = 255;
				genMandelbrot(targetx-range/2, targety-range/2, range);
				clear(renderer);
				drawMandelbrot(renderer);
			  SDL_RenderPresent(renderer);
			}
			usleep(1000000/30);
		}
		switch (ev.type) {
			case SDL_MOUSEBUTTONDOWN:
				if (ev.button.button == SDL_BUTTON_LEFT) {
					if (targetx==-1) {
						targetx = ((double)ev.button.x/Resolution - 0.5)*range - 0.5;
		        targety = -1*((double)ev.button.y/Resolution - 0.5)*range;
					} else {
						targetx = ((double)ev.button.x/Resolution - 0.5)*range + targetx;
		        targety = -1*((double)ev.button.y/Resolution - 0.5)*range  + targety;
					}
				}
				break;
		}
	} while(ev.type != SDL_QUIT);

	SDL_Quit();
  return 0;
}
