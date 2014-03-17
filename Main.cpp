#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "point.h"

using namespace std;

//screen width and height
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//window and screen 
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//global variables
vector<point> v;
int num;
point pointAns1(0, 0);
point pointAns2(0, 0);

bool init()
{
  bool success = true;
  //initilize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
	cout << "SDL initialization error! " << endl << SDL_GetError();
	success = false;
  }
  else
  {
	//create window
	gWindow = SDL_CreateWindow("Largest Distance", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
	  cout << "Window could not be created! " << endl << SDL_GetError();
	  success = false;
	}
	else
	{
	  gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	  if (gRenderer == NULL)
	  {
		cout << "Renderer creation failure!" << endl << SDL_GetError();
		success = false;
	  }
	  else{
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		  printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		  success = false;
		}
	  }
	}
  }
  return success;
}

//load points and calculate
bool loadPoints()
{
  srand(time(0));
  bool success = true;
  cout << "Enter num of point: ";
  cin >> num;
  for (int i = 0; i < num; i++)
  {
	point p1((rand() % SCREEN_WIDTH), (rand() % SCREEN_HEIGHT));
	v.push_back(p1);
  }

  float dis = v[1].distance(v[2]);
  for (int i = 0; i < v.size(); i++)
  {
	for (int j = i+1; j < v.size(); j++)
	{
	  if (v[i].distance(v[j]) > dis)
	  {
		dis = v[i].distance(v[j]);
		pointAns1 = v[i];
		pointAns2 = v[j];
	  }
	}
  }
  return success;
}

//quit and destroy resources
void close()
{
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}


int main(int argc, char* argv[])
{
  SDL_Event e;
  bool quit = false;
  if (!init())
  {
	cout << "Failed to initialize! " << endl;
  }
  else
  {
	if (!loadPoints())
	{
	  cout << "Unable to load points! " << endl;
	}
	else
	{
	  while (!quit)
	  {
		//check for event and update as needed
		while (SDL_PollEvent(&e))
		{
		  if (e.type == SDL_QUIT)
		  {
			quit = true;
		  }
		}
		SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(gRenderer);
		for (int i = 0; i < num; i++)
		{
		  SDL_Rect rect = { v[i].getX(), v[i].getY(), 2, 2 };
		  SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		  SDL_RenderFillRect(gRenderer, &rect);
		}
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(gRenderer, pointAns1.getX(), pointAns1.getY(), pointAns2.getX(), pointAns2.getY());
		SDL_RenderPresent(gRenderer);
	  }
	}
  }
  close();
  return 0;
}
