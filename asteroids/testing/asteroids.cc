#include "funcs.h"

#define TRUE 1
#define FALSE 0

SDL_Window *window=NULL;
SDL_Surface *screen=NULL;

//ASTEROID SURFACES
SDL_Surface *bigAst[3]={NULL};
SDL_Surface *medAst[2]={NULL};
SDL_Surface *smallAst[3]={NULL};
SDL_Rect bigAstPos[2];
//Alien
SDL_Surface * alien=NULL;

int rndVelX[3]; 
int rndVelY[3];

//FUNCTION DECLARATIONS
void createWindow();
void cleanUp();

//class for player
class player
{
	public:
	player();
	~player();

	private:
	int lives, score;
};

//class for asteroids and various computer duties
class computer
{
	public:
	computer();
	void getStartPos(void);
	int getVel(void);	
	int gameStatus(void);
	~computer();
};

computer::computer() //constructer loads all images, but doesn't blit anything yet.
{	

		int i=0;		
		bigAst[0]=SDL_LoadBMP("../src/images/bigBrownAst1.bmp");
		bigAst[1]=SDL_LoadBMP("../src/images/bigGreyAst1.bmp");
		bigAst[2]=SDL_LoadBMP("../src/images/bigGreyAst2.bmp");		
		medAst[0]=SDL_LoadBMP("../src/images/medBrownAst1.bmp");
		medAst[1]=SDL_LoadBMP("../src/images/medGreyAst1.bmp");
		medAst[2]=SDL_LoadBMP("../src/images/medGreyAst2.bmp");
		smallAst[0]=SDL_LoadBMP("../src/images/smallGreyAst1.bmp");	
		smallAst[1]=SDL_LoadBMP("../src/images/smallGreyAst2.bmp");
		smallAst[2]=SDL_LoadBMP("../src/images/smallBrowAst1.bmp");
		smallAst[3]=SDL_LoadBMP("../src/images/smallBrownAst2.bmp");
		for(i=0;i<3;i++)		
			SDL_SetColorKey(bigAst[i],SDL_TRUE,SDL_MapRGB(bigAst[i]->format,0,238,0));		
}

computer::~computer() //destructor frees all images and their memory, then quits SDL.
{
	//prevent heap mem leaks.	
	int i=0;	
	while (i<3)
	{	
		SDL_FreeSurface(bigAst[i]);
		SDL_FreeSurface(medAst[i]);
		SDL_FreeSurface(smallAst[i]);		
		i++;
	}
	while(i<4){
	SDL_FreeSurface(smallAst[i]);
	i++; }
	

	SDL_DestroyWindow(window); //destroy window created.
	SDL_Quit(); // quit all SDL subsystems.
}

int computer::gameStatus(void)//will later use to determine if another wave will start
{
	int waveStatus=FALSE;	

return (waveStatus);
}


//to get rnd Velocity
int computer::getVel(void)
{
int rndVel,rndVel2,vel, posOrNeg;
posOrNeg=rand() % 2;
if (posOrNeg==0)
{			
	rndVel=3;
	rndVel2=3;
}
else
{		
	rndVel=-3;
	rndVel2=-4;
}
	vel=rand() %rndVel+rndVel2;
	cout << "velocity is " << vel << endl;
	return(vel);
}

//to get a rnd start pos
void computer::getStartPos(void)
{		
	int i=0;	
	int rndXStart;
	int rndYStart;	
	srand(static_cast<unsigned int>(time(0)));	
	for(i=0;i<3;i++)	
	{	
		rndXStart=rand() % (SCREEN_WIDTH); 
		rndYStart=rand() % (SCREEN_HEIGHT); //start them in or near screen.
		bigAstPos[i].x=rndXStart;
		bigAstPos[i].y=rndYStart; //for start positions
		cout << "bigAstPosx"<<i<<" = "<<bigAstPos[i].x << endl;
		cout << "bigAstPosy"<<i<<" = "<<bigAstPos[i].y << endl;			
	}
}

int main(int argc,char* argv[])
{
	int i=0,j=0,k=0,halfK=0,rndVel[6];		
	bool running = true;	
	createWindow();
	computer START;	
	START.getStartPos();	
	//To get several velocitys for differnt images 
	for (j=0;j<6;j++)
	{					
		rndVel[j]=START.getVel();
	}
			
	SDL_Event mainEv;
		while(running)
		{
						
			j=k=0; //loop back to 0 to keep loops active in event.	
			while(SDL_PollEvent(&mainEv) !=0)
			{
				if(mainEv.type==SDL_QUIT)
				{
					running=false;
				}	
			}				
				
				SDL_UpdateWindowSurface(window);			
				SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));  //re-paint balck to prevent smear	

				for(j=0;j<3;j++) //off-screen detection, wrap back around for all images
				{					
					if (bigAstPos[j].x>=SCREEN_WIDTH)
						bigAstPos[j].x=0;
					else if	(bigAstPos[j].x<=0)
						bigAstPos[j].x=SCREEN_WIDTH;
					if (bigAstPos[j].y>=SCREEN_HEIGHT)
						bigAstPos[j].y=0;
					else if(bigAstPos[j].y<=0)
						bigAstPos[j].y=SCREEN_HEIGHT;
				}
				for (i=0;i<3;i++) //blit first wave of big asteroids			{
					SDL_BlitSurface(bigAst[i],NULL,screen,&bigAstPos[i]);

				for(halfK=0;halfK<3;halfK++) //to loops velocitys
				{
					bigAstPos[halfK].x+=rndVel[k]; //K increase evey two times that halfk does 
					k++;	//cout << "halfk = " << halfK <<" : k = "<< k <<endl;			
					bigAstPos[halfK].y+=rndVel[k];
				}
		
				//bigAstPos[k].y+=rndVel[3];
				//bigAstPos[k].x+=rndVel[4];
				//bigAstPos[k].y+=rndVel[5];		
				SDL_Delay(20);		
		}
 
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





