#include "funcs.h"
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL.h>
//#include <iostream>
#define TRUE 1
#define FALSE 0
using namespace std; //for i/o to work w/o std::

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Window *window=NULL;
SDL_Surface *screen=NULL;
SDL_Surface *cards=NULL;
SDL_Renderer *renderer=NULL;
//ASTEROID SURFACES
SDL_Surface *bigBrownAst1=NULL;
SDL_Surface *bigGreyAst1=NULL;
SDL_Surface *bigGreyAst2=NULL;
SDL_Surface *medBrownAst1=NULL;
SDL_Surface *medGreyAst1=NULL;
SDL_Surface *medGreyAst2=NULL;
SDL_Surface *smallGreyAst1=NULL;
SDL_Surface *smallGreyAst2=NULL;
SDL_Surface *smallBrownAst1=NULL;
SDL_Surface *smallBrownAst2=NULL;

void createWindow();

//class for asteroid waves and various computer duties
class computer
{
	public:
	int waveCompleted;
	
	computer();	
	int makeWave(void);
	~computer();
};

computer::computer() //constructer loads all images, but doesn't blit anything yet.
{
	bigBrownAst1=SDL_LoadBMP("../src/images/bigBrownAst1.bmp");
	bigGreyAst1=SDL_LoadBMP("../src/images/bigGreyAst1.bmp");
	bigGreyAst2=SDL_LoadBMP("../src/images/bigGreyAst2.bmp");
	medBrownAst1=SDL_LoadBMP("../src/images/medBrownAst1.bmp");
	medGreyAst1=SDL_LoadBMP("../src/images/medGreyAst1.bmp");
	medGreyAst2=SDL_LoadBMP("../src/images/medGreyAst2.bmp");
	smallGreyAst1=SDL_LoadBMP("../src/images/smallGreyAst1.bmp");
	smallGreyAst2=SDL_LoadBMP("../src/images/smallGreyAst2.bmp");
	smallBrownAst1=SDL_LoadBMP("../src/images/smallBrowAst1.bmp");
	smallBrownAst2=SDL_LoadBMP("../src/images/smallBrownAst2.bmp");
}

int computer::makeWave(void)
{
//ASTEROID OFFSETS FOR MOVEMENT
SDL_Rect OFFSET_bigBrownAst1;
OFFSET_bigBrownAst1.x=50;
OFFSET_bigBrownAst1.y=50;
return (waveCompleted);
}

int main(int argc,char* argv[])
{
	bool running = true;	
	createWindow();
	//int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	cards = SDL_LoadBMP("../src/images/bigBrownAst.bmp");	
	if(cards==NULL)
		cout << "image loading error: " << SDL_GetError();	
		SDL_Event mainEv;
		while(running)
		{
			while(SDL_PollEvent(&mainEv) !=0)
			{
				if(mainEv.type==SDL_QUIT)
				{
					running=false;
				}
				SDL_UpdateWindowSurface(window);
				SDL_BlitSurface(cards,NULL,screen,NULL);			
			}	
		}
	//if(!(IMG_Init(imgFlags)& imgFlags))
	//	cout << "error intitializing image: "<< IMG_GetError() << endl;
	 //else

	//prevent heap mem leaks.
	//SDL_FreeSurface();	
	SDL_FreeSurface(cards);	
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window); //destroy window created.
	SDL_Quit(); // quit all SDL subsystems.
	return(0);
}	

void createWindow()
{
	if(SDL_Init(SDL_INIT_VIDEO)==-1)							
		cerr << "Video initialiazation failure: " << SDL_GetError() << endl;
	else
	{	
		window=SDL_CreateWindow("ASTEROIDS",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
		if (window==NULL)
		{
			cerr << "Window couldn't be created" << SDL_GetError() << endl;
		}
		else
		{
			screen=SDL_GetWindowSurface(window);
		}
	}
	
}		

