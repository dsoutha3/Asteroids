#include "funcs.h"

#define TRUE 1
#define FALSE 0

SDL_Window *window=NULL;
SDL_Surface *screen=NULL;

//ASTEROID SURFACES
SDL_Surface *bigAst[3]={NULL};
SDL_Surface *medAst[2]={NULL};
SDL_Surface *smallAst[3]={NULL};
SDL_Rect bigAstPos[3];

//Alien
SDL_Surface *alienShip=NULL;
SDL_Rect alienShipPos;


//StartMenu

int rndVelX[3];
int rndVelY[3];

//FUNCTION DECLARATIONS
void createWindow();
void enableAlienPilot();

//class for player
class player
{
	public:
	player();
	~player();
	int getScore();
	void setScore(int);
	SDL_Surface *playerImg=NULL;
	SDL_Rect playerPos;


	private:
	int playerX, playerY, lives, score;


};

player::player()//constructor for player
{
	playerPos.x=(SCREEN_WIDTH /2);
	playerPos.y=(SCREEN_HEIGHT /2);

	this->lives = 3;
	this->score = 0;

	playerImg=SDL_LoadBMP("../src/images/playerShip.bmp");
	SDL_SetColorKey(playerImg,SDL_TRUE,SDL_MapRGB(playerImg->format,0,128,0));
}

player::~player()
{
}

//class for asteroids and various computer duties
class computer
{
	public:
	computer();
	void getStartPos(void);
	int getVel(void);
	int gameStatus(void);
	SDL_Surface *startImg=NULL;
	SDL_Rect startPos;
	~computer();
};

int player::getScore()
{
	return (this->score);
}

void player::setScore(int value)
{
	this->score = this->score + value;
}

computer::computer() //constructer loads all images, but doesn't blit anything yet.
{

		int i=0;
		startImg=SDL_LoadBMP("../src/images/start.bmp");
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
		alienShip=SDL_LoadBMP("../src/images/alienShip.bmp");

	for(i=0;i<3;i++){
		SDL_SetColorKey(bigAst[i],SDL_TRUE,SDL_MapRGB(bigAst[i]->format,0,238,0));

	}

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

/*
int computer::gameStatus(void)//will later use to determine if another wave will start
{
//	int waveStatus = FALSE;
	private:
	int lives, score;
return (waveStatus);
};
*/


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
	for(i=0; i<3; i++)
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

//start here
	int menu=0,i=0,j=0,k=0,halfK=0,rndVel[6],playerVel=0;
	bool running = true;
	createWindow();
	computer START;
	START.getStartPos();
	player PLAYER;
	//alien start pos	
	alienShipPos.x=SCREEN_HEIGHT;
	alienShipPos.y=-10;
	//start screen
	SDL_BlitSurface(START.startImg, NULL, screen, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Event e;

		while(menu != 1)
		{
			while( SDL_PollEvent( &e) != 0)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_RETURN:
					menu = 1;break;

					default:
					break;
				}
			}
		}


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
				SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));  //re-paint black to prevent smear

				//space ship blit
				SDL_BlitSurface(PLAYER.playerImg, NULL, screen, &PLAYER.playerPos);
					//ship movement
					




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

				//off-screen detection, wrap back around for alienShip
					if (alienShipPos.x>=SCREEN_WIDTH-65)
						alienShipPos.x=20;
					else if (alienShipPos.x<=15)
						alienShipPos.x=SCREEN_WIDTH-80;
					if (alienShipPos.y>=SCREEN_HEIGHT-80)
						alienShipPos.y=22;
					else if(alienShipPos.y<=14)
						alienShipPos.y=SCREEN_HEIGHT-90;							
	
				//off-screen detecion, wrap back around for player
					if (PLAYER.playerPos.x>=SCREEN_WIDTH-65)
						PLAYER.playerPos.x=10;
					else if (PLAYER.playerPos.x<=9)
						PLAYER.playerPos.x=SCREEN_WIDTH-80;
					if (PLAYER.playerPos.y>=SCREEN_HEIGHT)
						PLAYER.playerPos.y=2;
					else if(PLAYER.playerPos.y<=0)
						PLAYER.playerPos.y=SCREEN_HEIGHT-10;	


				
				SDL_Delay(25); //so all key presses are read
				
				if(SDL_PollEvent( &e))
				{
					if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
					{	
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:
							playerVel=-6;
							break;

							case SDLK_ESCAPE:
							exit(0);
							break;

							default:
							break;
						}
					}
								
					else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
					{	
						switch(e.key.keysym.sym)
						{
							case SDLK_UP:					
							playerVel=0;
							break;
						}
					}	
				}				
				//player velocity adjustments
				PLAYER.playerPos.y+=playerVel;

				for (i=0;i<3;i++) //blit first wave of big asteroids		
					SDL_BlitSurface(bigAst[i],NULL,screen,&bigAstPos[i]);

				SDL_BlitSurface(alienShip,NULL,screen,&alienShipPos);//blit alien

				for(halfK=0;halfK<3;halfK++) //to loops velocitys
				{
					bigAstPos[halfK].x+=rndVel[k]; //K increase evey two times that halfk does
					k++;	//cout << "halfk = " << halfK <<" : k = "<< k <<endl;
					bigAstPos[halfK].y+=rndVel[k];
				}
				
				enableAlienPilot();
				
				

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

void enableAlienPilot()
{
	
	//start moving
	alienShipPos.x+=3;
	alienShipPos.y-=2;
	int l=0;	
	for(l=0;l<3;l++)
	{						
				
					//Asteroid coming down towards top left corner of ship.		
		if (((bigAstPos[l].y>=alienShipPos.y-80)&&(bigAstPos[l].y<=alienShipPos.y))&&((bigAstPos[l].x>=alienShipPos.x-80)&&(bigAstPos[l].x<=alienShipPos.x)))
		{									
			alienShipPos.x+=4;
			alienShipPos.y+=4;
		}
					//Asteroid coming up towards bottom left corner of ship.
		else if (((bigAstPos[l].y<=alienShipPos.y+180)&&(bigAstPos[l].y>=alienShipPos.y+100))&&((bigAstPos[l].x>=alienShipPos.x-80)&&(bigAstPos[l].x<=alienShipPos.x)))
		{	
			alienShipPos.x+=4;
			alienShipPos.y-=4;
		}
					//Asteroid coming down towards top right corner of ship.
		else if(((bigAstPos[l].x<=alienShipPos.x+180)&&(bigAstPos[l].x>=alienShipPos.x+100))&&((bigAstPos[l].y<=alienShipPos.y+80)&&(bigAstPos[l].y>=alienShipPos.y)))
		{
			alienShipPos.x-=4;
			alienShipPos.y+=4;
		}
					//Asteroid coming up toward bottom right corner of ship.
		else if(((bigAstPos[l].x<=alienShipPos.x+180)&&(bigAstPos[l].x>=alienShipPos.x+100))&&((bigAstPos[l].y<=alienShipPos.y+180)&&(bigAstPos[l].y>=alienShipPos.y+100)))
		{
			alienShipPos.x-=10;
			alienShipPos.y+=7;
		}
					//Asteroid coming toward left side of ship.
		else if(((bigAstPos[l].y>=alienShipPos.y+5)&&(bigAstPos[l].y<=alienShipPos.y+95))&&((bigAstPos[l].x>=alienShipPos.x-80)&&(bigAstPos[l].x<=alienShipPos.x)))
		{
			alienShipPos.x+=7;
		}						
					//Asteroid coming toward mid right of ship.
		else if(((bigAstPos[l].y>=alienShipPos.y+5)&&(bigAstPos[l].y<=alienShipPos.y+95))&&((bigAstPos[l].x>=alienShipPos.x+180)&&(bigAstPos[l].x<=alienShipPos.x)))
		{
			alienShipPos.x-=10;
		}
					//Asteroid coming toward top side of ship.
		else if(((bigAstPos[l].y>=alienShipPos.y-80)&&(bigAstPos[l].y<=alienShipPos.y))&&((bigAstPos[l].x>=alienShipPos.x+5)&&(bigAstPos[l].x<=alienShipPos.x+95)))
		{
			alienShipPos.y+=14;
			alienShipPos.x-=10;
		}
					//Asteroid coming from back side.
		else if(((bigAstPos[l].y<=alienShipPos.y+180)&&(bigAstPos[l].y>=alienShipPos.y+100))&&((bigAstPos[l].x>=alienShipPos.x+5)&&(bigAstPos[l].x<=alienShipPos.x+95)))
		{
			alienShipPos.y+=7;
			alienShipPos.x+=7;
		}
	}						
}
