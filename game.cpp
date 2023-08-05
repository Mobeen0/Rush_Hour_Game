//============================================================================
// Name        : .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

const int s=20;
bool obsticl[s][s];
bool structure[s][s]; // 2d array to check if a structure exists or not on the board location
int xI,yI; // car coords
int Cx,Cy;// car cord parameters for the 2D board array


								
const int numObst=7; // total number of obsticles including trees and boxes
int Ox[numObst]={0,};
int Oy[numObst]={0,}; // coordinates for obsticles

const int size=20;
int board_x[size]={0,};
int board_y[size]={0,}; // board cords

bool pickup =false;

int Dx,Dy; // destination of passenger

int points=0;
string DisPoints = "Score=0";
string disTime = ""; //the timer

const int life =3;
int lifeline_x[life];
int lifeline_y[life];
int lives =0;
string liv="Lifeline used = 0";


void initial()
{
	for (int i =0;i<s;i++)
	{
		for (int p =0;p<s;p++)
		{
			structure[i][p] = false;
			obsticl[i][p] = false;
			if (p>=0 and p<life)
			{
				lifeline_x[p] = -1; // initialising all the lifeline cords as 0
				lifeline_y[p] = -1;
			}
		}
	}


}

void board_pos()
{
	board_x[0] = 140;
	board_y[0] = 1150;
	
	for(int i=1;i<size;i++)
	{
		board_x[i]= 140+55*i;
		board_y[i]= 1150-50*i;
	
	}

}

void random_pos()
{
	int x,y;
	
		do{
			x = rand();
			x= x%20;
			Cx=x;
			xI=board_x[Cx] + 10; // to center allign the car horizontally
		
			y = rand();
			y = y%20; 
			Cy=y;
			yI= board_y[Cy] +10; // to center allign the car vertically
			}while(structure[x][y]);
			

}

void obsticle_pos()
{
	int x,y;
	
	for(int i =0; i<numObst;i++)
	{	
			x = rand();
			x= (x%20);
			Ox[i]=board_x[x];
		
	
	
			y = rand();
			y = y%20;
			Oy[i] = board_y[y];
			
			structure[x][y] = true;
			obsticl[x][y]=true;
			
			for(int c=0;c<i and i>0;c++) // checking if the coords of two obsticles are same
			{
				if(Ox[i]==Ox[c] and Oy[i]==Oy[c])
				{
					
					i--;
				}
			}
	}
}

void DrawObsticle()
{

	for(int i =0;i<3;i++)
	{
		
		DrawSquare(Ox[i] +5,Oy[i],30,colors[BURLY_WOOD]);
		
	}
	for (int i =3;i<numObst;i++)
	{
		DrawLine(Ox[i]+20,Oy[i],Ox[i]+20,Oy[i]+25,7,colors[BROWN]);
		DrawCircle(Ox[i]+20,Oy[i]+25,10,colors[DARK_OLIVE_GREEN]);
		
	}
}

const int numBuild = 133; // 35% of 20x20 board
int Bx[numBuild] = {0,};
int By[numBuild] = {0,};

void Building_pos()
{
int z,x,y;
	for(int i =0;i<numBuild;i++)
	{
		
		z= rand();
		z= z%20;
		x=z;
		Bx[i]=board_x[z];
		
		z= rand();
		z= z%20;
		y=z;
		By[i]=board_y[z];
		
		structure[x][y] = true;
		
		for(int c=0;c<i;c++)
		{
			if(Bx[c]==Bx[i] and By[c]==By[i] or (obsticl[x][y]))
			{
				i--; // i loop called again
				break; // c loop breaks
			}		
		}
	}
	
}

void drawBuilding() //random buildings structures drawing
{
	int dont_x,dont_y;
	for(int i =0;i<numBuild;i++)
	{
		for(int c =0;c<life;c++)
		{	
			if(Bx[i]==board_x[lifeline_x[c]] and By[i]==board_y[lifeline_y[c]] and (lifeline_x[c]!=-1 and lifeline_y[c]!=-1))
			{
				structure[lifeline_x[c]][lifeline_y[c]]= false;
				dont_x=Bx[i];
				dont_y=By[i];
			}
		}
		if(!(Bx[i]==dont_x and By[i]==dont_y))
		{
			DrawRectangle(Bx[i],By[i],55,52,colors[BLACK]);
		}
	}
}



void drawCar() {
	
	
	DrawCircle(xI, yI, 5,colors[BLACK]);
	DrawCircle(xI+30,yI,5,colors[BLACK]);
	DrawCircle(xI,yI+25,5,colors[BLACK]);
	DrawCircle(xI+30, yI+25, 5,colors[BLACK]);
	DrawRoundRect(xI, yI, 30, 25,colors[RED]);

	glutPostRedisplay();
}
void DrawBorder()
{

	int width = 1243;
	int height = 1200;
	int x_start, y_start;
	
		
		DrawRectangle(140,190,1103,1010,colors[SLATE_GRAY]);
		
	 	x_start=140+55;
		y_start=190;
		
	
		for(int count =0;x_start<width;x_start+=55)
		{
			DrawLine(x_start , y_start , x_start , height , 1 , colors[BLACK] );
			
		}

}

void DrawBoardLines()
{
	for(int i =0;i<20;i++)
	{
		for (int c=0;c<20;c++)
		{
			DrawLine(board_x[i]+30,board_y[c]+15,board_x[i]+30,board_y[c],2,colors[WHITE]);
		}
	}

}


const int pasize =5;
int passenger_x[pasize]={0,};
int passenger_y[pasize]={0,};
int passnum =-1;

void Passenger_pos()
{
	int x,y;

	if (passnum==-1)
	{
		for (int i =0;i<pasize;i++)
		{
			do{
				x= rand();	
				x=x%20;
				y= rand();
				y=y%20;
			}while(structure[x][y] or structure[x][y+1]); // clear top and bottom for passenger so can be visible on board
		
			passenger_x[i]=x;
			passenger_y[i]=y;
		
		}
	}
	else
	{
			do{
				x= rand();	
				x=x%20;
				y= rand();
				y=y%20;
			}while(structure[x][y] or structure[x][y+1]); // clear top and bottom for passenger so can be visible on board
		
			passenger_x[passnum]=x;
			passenger_y[passnum]=y;
	}

}

void DrawPassenger()
{

	for (int i =0; i< pasize;i++)
	{
		if(i!=passnum)
		{
			DrawLine(board_x[passenger_x[i]]+10,board_y[passenger_y[i]],board_x[passenger_x[i]]+10,board_y[passenger_y[i]]+15,4,colors[BLUE]);
			DrawCircle(board_x[passenger_x[i]]+10,board_y[passenger_y[i]]+15,5,colors[BLUE]);
			DrawLine(board_x[passenger_x[i]],board_y[passenger_y[i]]-10,board_x[passenger_x[i]]+10,board_y[passenger_y[i]],4,colors[BLUE]);
			DrawLine(board_x[passenger_x[i]]+20,board_y[passenger_y[i]]-10,board_x[passenger_x[i]]+10,board_y[passenger_y[i]],4,colors[BLUE]);
			DrawLine(board_x[passenger_x[i]]+20,board_y[passenger_y[i]]+13,board_x[passenger_x[i]]+10,board_y[passenger_y[i]]+10,3,colors[BLUE]);
			DrawLine(board_x[passenger_x[i]],board_y[passenger_y[i]],board_x[passenger_x[i]]+10,board_y[passenger_y[i]] +10,4,colors[BLUE]);
			structure[passenger_x[i]][passenger_y[i]]= true;	
		}
	}
	
}

void Destination_pos()
{
	int x,y;
	do{
		x= rand();
		x=x%20;
		y = rand();
		y=y%20;
		}while(structure[x][y] or structure[x+1][y] or structure[x-1][y] or structure[x][y+1] or structure[x][y-1]);

	Dx= board_x[x];
	Dy= board_y[y];
}

void DrawDestination()
{
	DrawRectangle(Dx,Dy,55,52,colors[GREEN]);
}

int droped=0;
string drops;
double speed=1000;
void check_drop()
{
	if(abs(xI-Dx)<30 and abs(yI-Dy)<30 and (pickup))
	{
		pickup = false;
		points+=10;
		Destination_pos();
		Passenger_pos();
		droped++;
		if (droped%2==0)
		{
			speed-=200;
		}
	}
	
	stringstream d; // for conversion of drop int to string
	
	d<<droped;
	d>>drops;
	drops = "Total Drops= " + drops;

}

const int cars=2;
int OCx[cars]={0,};
int OCy[cars]={0,};
void OtherCar_pos()
{
	int x,y;
	
	for(int i =0;i<cars;i++)
	{
		do{
		x= rand();
		x=x%20;
		y=rand();
		y=y%20;
		}while(structure[x][y]);
		
		OCx[i]=x;
		OCy[i]=y;
		
		if(OCx[1]==OCx[2] and OCy[1]==OCy[2])
		{
			i--; // loop called again
		}
	}
}

int movement[cars]={-1,-1};
void MoveOtherCars()
{
	
		for(int i=0;i<cars;i++)
		{
			if((structure[OCx[i]][OCy[i]]) or movement[i]==-1)
			{
			movement[i]= rand();
			movement[i] = movement[i]%4; // 4 differnt values can be obtained. which can be used to move up,down,left and right.
			}
			if(movement[i]==0)
			{
				OCx[i]--;
				if(structure[OCx[i]][OCy[i]])
				{
					OCx[i]++;
					movement[i] = -1;
				}
				if(OCx[i]<=0)
				{
					movement[i]=-1;
					OCx[i]=0;
				}
			}
			if(movement[i]==1)
			{
				OCx[i]++;
				if(structure[OCx[i]][OCy[i]])
				{
					movement[i]=-1;
					OCx[i]--;
				}
				if(OCx[i]>=19)
				{
					movement[i]=-1;
					OCx[i]= 19;
				}				
			}
			if(movement[i]==2)
			{
				OCy[i]++;
				if(structure[OCx[i]][OCy[i]])
				{
					movement[i]=-1;
					OCy[i]--;
				}				
				if(OCy[i]>=19)
				{
					movement[i]=-1;
					OCy[i]=19;
				}
			}
			if(movement[i]==3)
			{
				OCy[i]--;
				if(structure[OCx[i]][OCy[i]])
				{
					movement[i]=-1;
					OCy[i]++;
				}	
				if(OCy[i]<=0)
				{
					movement[i]=-1;
					OCy[i]=0;
				}			
			}
		}
}

void DrawOtherCars()
{

	for(int i=0;i<cars;i++)
	{
		DrawCircle(board_x[OCx[i]]+10, board_y[OCy[i]]+10, 5,colors[BLACK]);
		DrawCircle(board_x[OCx[i]]+40,board_y[OCy[i]]+10,5,colors[BLACK]);
		DrawCircle(board_x[OCx[i]]+10,board_y[OCy[i]]+35,5,colors[BLACK]);
		DrawCircle(board_x[OCx[i]]+40, board_y[OCy[i]]+35, 5,colors[BLACK]);
		DrawRoundRect(board_x[OCx[i]]+10, board_y[OCy[i]]+10, 30, 25,colors[BLUE]);
	}

	glutPostRedisplay();
}

void check_point()
{
	stringstream scores;

	scores<< points;
	scores>> DisPoints;
	DisPoints = "Score=" + DisPoints;
}


const int show=10;
int menu_x[show]={0,};
int menu_x1[show]={0,};
int menu_y[show]={0,};
int menu_y1[show] = {0,};


void menu_move()
{
	bool flagx = false;
	bool flagy=false;
	int y =1000,x;
	int x2=1300;

	for(int i =0;i<10;i++)
	{
		menu_y[i]= y-i*100;
		menu_x1[i]= x2-i*200;
		x = rand();
		x= (x%1300) + 100;
		menu_x[i]= x;
		menu_y1[i]=x;
	


	if (menu_x[i] > 10 && flagx) {
		menu_x[i] -= 30;
		if(menu_x[i] < 1000)
			
			flagx = false;

	}
	else if (menu_x[i] < 1300 && !flagx) {
		menu_x[i] += 10;
		if (menu_x[i] > 1300)
			flagx = true;
	}
	if (menu_y1[i] > 10 && flagy) {
		menu_y1[i] -= 30;
		if(menu_y1[i] < 1000)
			
			flagy = false;

	}
	else if (menu_y1[i] < 1300 && !flagy) {
		menu_y1[i] += 10;
		if (menu_y1[i] > 1300)
			flagy = true;
	}
	}

	glutPostRedisplay();


}

/*
 * Main Canvas drawing function.
 * */

bool username =false;
bool start = false;
int menu =1;
string name="";

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	if (!start)
	{
		DrawRectangle(0,0,1400,1350,colors[WHITE]);
		DrawString(board_x[4],board_y[0],"***** ****WELCOME TO RUSH HOUR***** *****", colors[BLACK]);
		DrawString(board_x[6],board_y[8],"Menu",colors[BLACK]);
		DrawString(board_x[6],board_y[14],"LeaderBoards",colors[BLACK]);
		if(menu==1)
		{
			DrawTriangle(board_x[6],board_y[8]+10,board_x[5],board_y[7],board_x[5],board_y[9]+10,colors[BLACK]);
		}
		else
		{
			DrawTriangle(board_x[6],board_y[14]+10,board_x[5],board_y[13],board_x[5],board_y[15]+10,colors[BLACK]);
		}
		
		menu_move();
		for (int i =0;i<10;i++)
		{
			DrawRectangle(menu_x[i],menu_y[i],30,10,colors[GOLD]);
			DrawRectangle(menu_x1[i],menu_y1[i],10,30,colors[RED]);
		}
	}
	else
	{
		if(username)
		{
			menu_move();
			for (int i =0;i<10;i++)
		{
			DrawRectangle(menu_x[i],menu_y[i],30,10,colors[LIME]);
			DrawRectangle(menu_x1[i],menu_y1[i],10,30,colors[LIME]);
		}
		
			DrawString( board_x[1], 800, "Enter your username = ", colors[IVORY]);
			DrawString(board_x[5]+20,800,name,colors[WHITE]);
		}
		else
		{
			//Display the game
			DrawString( 20, 1300, DisPoints, colors[CHART_REUSE]);
			DrawString( 10, 1250, drops, colors[DARK_CYAN]);
			DrawString( board_x[9], 1270, disTime, colors[LIGHT_CORAL]);
			DrawString (1000,150,"Press W: to remove upper building",colors[WHITE]);
			DrawString (1000,120,"Press A: to remove left building",colors[WHITE]);
			DrawString (1000,90,"Press S: to remove lower building",colors[WHITE]);
			DrawString (1000,60,"Press D: to remove right building",colors[WHITE]);
			DrawString (1000,20,liv,colors[WHITE]);
		
			
			DrawBorder();
			DrawBoardLines();
			DrawObsticle();
			drawBuilding();
			check_point();
			DrawPassenger();
			DrawOtherCars();
			
			if (!pickup)
			{
					// do nothing
			}
			else
			{
				DrawDestination();
			}
				drawCar();	
		}

	}
	
	glutSwapBuffers(); // do not modify this line..

}




/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {	

	
	if(!start and key == GLUT_KEY_DOWN)
	{
		menu =2;
	}
	if(!start and key==GLUT_KEY_UP)
	{
		menu=1;
	}


/***************************************MOVING THE CAR***********************************/

	if(start)
	{
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		Cx--;
		xI = board_x[Cx]+10;
		
		if (Cx<=0)
		{
			Cx = 0;
			xI = board_x[Cx] +10; // left boundary
		}

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		Cx++;	
		xI = board_x[Cx]+10;
		
		if(Cx>=19)
		{
			Cx=19; // right boundary
			xI= board_x[Cx] +10;
		}
		
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
			Cy--;
		yI = board_y[Cy]+10;
		
		if(Cy<=0)
		{
			Cy=0;
			yI=board_y[Cy]+10; // dont let car cross lower boundary
		}
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
			Cy++;
		yI = board_y[Cy]+10;
		
		if(Cy>=19)
		{
			Cy=19;
			yI=board_y[Cy]+10; // dont let car cross lower boundary
		}
	}
/*************************************************************************************/		
	
	
/*****************************CHECKING FOR POINTS DEDUCTION****************************/		
	
	bool done = false;
	
	if(key == GLUT_KEY_LEFT and structure[Cx][Cy])
	{
	
		if(obsticl[Cx][Cy])
		{
			points= points - 3;
		}
		else
		{
			for(int i =0;i<pasize;i++)
			{
				if(Cx==passenger_x[i] and Cy==passenger_y[i])
				{
					points = points -5;
					done = true;
				}
			}

					if (!done)
					{
						Cx++;
						xI= board_x[Cx]+10;
					}
		}
	}


	if(key == GLUT_KEY_RIGHT and structure[Cx][Cy])
	{
		if(obsticl[Cx][Cy])
		{
			points= points - 3;
		}
		else
		{
			for(int i =0;i< pasize;i++)
			{
				if(Cx==passenger_x[i] and Cy==passenger_y[i])
				{
					points = points -5;
					done = true;
				}	
			}	

					if(!done)
					{
						Cx--;
						xI= board_x[Cx]+10;
					}

		}
		
	}
	if(key == GLUT_KEY_UP and structure[Cx][Cy])
	{
		
	if(obsticl[Cx][Cy])
		{
			points= points - 3;
		}
		else
		{
			for(int i=0;i<pasize;i++)
			{
				if(Cx==passenger_x[i] and Cy==passenger_y[i])
				{
					points = points -5;
					done = true;
				}
			}			
					if(!done)
					{
						Cy++;
						yI= board_y[Cy]+10;
					}
		}
	}
	if(key == GLUT_KEY_DOWN and structure[Cx][Cy])
	{
	
		if(obsticl[Cx][Cy])
		{
			points= points - 3;
		}
		else
		{
			for(int i=0;i<pasize;i++)
			{
				if(Cx==passenger_x[i] and Cy==passenger_y[i])
				{
					points = points -5;
					done = true;
				}	
			}		
			
					if (!done)
					{
						Cy--;
						yI= board_y[Cy]+10;
					}
		}
		
	}
	}
/*****************************************************************************/	


	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	
	for(int i =0;i<25;i++) // what
	{
		if(key == 65+i) // upper case characters
		{
			name = name+ char(65+i);
		}
		if(key == 97+i)// lower case characters;
		{
			name = name+ char(97+i);
		}
		if(key ==32) // spacebar
		{
			name = name+ char(32);
		}
		
	}
	
	
	
	
	
	for(int i =0;i<pasize;i++)
	{
		if (key == ' ' and (abs(xI-board_x[passenger_x[i]]) <=50) and (abs(yI-board_y[passenger_y[i]]) <=50) and (!pickup)) // if taxi is close and spacebar is pressed and no passenger is on the taxi
		{
			structure[passenger_x[i]][passenger_y[i]]= false; // passenger removed so it doesnt occupy space
			passnum = i; // checking which passenger was removed
			Passenger_pos();
			 
			pickup =true;
		}
	}
		
	if (key== ' ' and (board_x[Cx]==Dx) and (board_y[Cy]==Dy) and (pickup))
	{
		check_drop();
	}
		
	
	if(key==13) // ascii value for enter
	{
		if(menu==1)
		{
			start=true;
			username = !username;
		}
	
	}
	
	stringstream l;
	if((key=='w' or key =='W') and structure[Cx][Cy-1] and !(obsticl[Cx][Cy-1]) and lives<life and (start and !username)) // the block on the top is removed
	{
		lifeline_x[lives] = Cx;
		lifeline_y[lives] = Cy-1;
		lives++;
		liv="";
		l<<lives;
		l>>liv;
		liv = "Lifelines Used= " + liv;
	}
	if((key=='s' or key =='S') and structure[Cx][Cy+1] and !(obsticl[Cx][Cy+1])and lives<life and (start and !username)) // the block on the bottom is removed
	{
		lifeline_x[lives] = Cx;
		lifeline_y[lives] = Cy+1;
		lives++;
		l<<lives;
		liv="";
		l>>liv;	
		liv = "Lifelines Used= " + liv;	
	}
	if((key=='a' or key =='A') and structure[Cx-1][Cy] and !(obsticl[Cx-1][Cy]) and lives<life and (start and !username)) // the block on the left is removed
	{
		lifeline_x[lives] = Cx-1;
		lifeline_y[lives] = Cy;
		lives++;
		liv="";
		l<<lives;
		l>>liv;	
		liv = "Lifelines Used= " + liv;	
	}
	if((key=='d' or key =='D') and structure[Cx+1][Cy] and !(obsticl[Cx+1][Cy]) and lives<life and (start and !username)) // the block on the right is removed
	{
		lifeline_x[lives] = Cx+1;
		lifeline_y[lives] = Cy;
		lives++;
		liv="";
		l<<lives;
		l>>liv;	
		liv = "Lifelines Used= " + liv;	
	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
double timer=0;
void Timer(int m) {
	double minutes,seconds;
	if(start and !username)
	{
	string min,sec;
	
	stringstream mi;
	stringstream se;
	
		timer+=(speed/1000);
		
		minutes = timer/60;
		mi<<int(minutes);
		mi>>min; // int to string
		seconds = int(timer)%60; // converting seconds to minute and seconds
		se<< int(seconds);
		se>>sec; // int to string
		
		string che = "Timer= ";
		if(seconds<10)
		{
			disTime= che + "0"+min + " : "+ "0" +sec;
		}
		else
		{
			disTime= che + "0"+min + " : "+ sec;
		}
		
		if(minutes>=3)
		{
		 exit(1); // when minutes are 3, the time for playing is up and game closes.
		}
	// once again we tell the library to call our Timer function after next 1000/FPS
		MoveOtherCars();
		}
	glutTimerFunc(speed, Timer, 0); // function called after every fifth of a second as this function is also being used to move cars and moving cars every second is too slow.

}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1400, height = 1350; // my custom window size

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Muhammad Mobeen. Roll Number : I21-0444"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	initial();
	board_pos();
	obsticle_pos();
	Building_pos();
	Passenger_pos();
	random_pos();
	OtherCar_pos();
	Destination_pos();
	

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
