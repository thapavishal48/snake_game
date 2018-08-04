#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include"mmsystem.h"
using namespace std;

int life=3,level=0;
bool gameOver;
const int width = 50;
const int height = 15;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
int m,i,j;
string oname = "1name"; 

class snake
{
	public:
	void StdColor()
	{
    	 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	}

	void CPos(int i, int j)
	{
    	COORD cPos;
     	cPos.X = j;
    	cPos.Y = i;
    	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
	}

	void Menu()
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); cout << (char)1; //for green color
     	CPos(7,35); cout <<" Welcome to the ' S N A K E - - - G A M E '";
     	CPos(12,10); cout<<" How To Control:";
     	CPos(14,10); cout<<" Press 'a' for 'Left','d' for 'Right','w' for 'Up' and 's' for 'Down'"; 
     	CPos(17,10); cout << " Creating players:";
     	CPos(19,10); cout << " Enter Player's name: "; cin >> oname;
	 	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); cout << (char)1; //for green color
	 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); cout << (char)1;	  //for red color
	}

	void Setup(int sc)
	{
		gameOver = false;
		dir = STOP;
		x = width / 2;
		y = height / 2;
		fruitX = rand() % width;
		fruitY = rand() % height;
		score = sc;
	}

	void Draw(int life,int level)
	{	
	
     	COORD cPos;
     	cPos.X = 1;
     	cPos.Y = 3;
     	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos); 
		CPos(4,55); cout<<"' S N A K E - - - - - - - - G A M E '";
		for(m=0;m<5;m++)
		{
			cout<<endl;
		}
	
		for (i = 0; i < width+2; i++)
		{
			if(i==0)
			{
				cout <<"                                              "<<char(178);
			}
			else
			{
				cout<< char(178);
			}
		}
			cout << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (j == 0)
				cout <<"                                              "<<char(178);
				if (i == y && j == x)
				cout << "0";
				else if (i == fruitY && j == fruitX)
				{
					cout << char(1);
				}
				else
				{
					bool print = false;
					for (int k = 0; k < nTail; k++)
					{
						if (tailX[k] == j && tailY[k] == i)
						{
							cout << "O";
							print = true;
						}
					}
					if (!print)
					cout << " ";
				}				
				if (j == width - 1)
				cout << char(178);
			}
			cout << endl;
		}

		for(int p = 0; p < width+2; p++)
		{
			if(p==0)
			{
				cout <<"                                              "<<char(178);
			}
			else
			{
				cout<< char(178);
			}
		}
		
		cout << endl;
		cout<<endl;
		cout<<endl;
		cout << "                                                                    SCORE: " << score << endl;
		cout << "                                                                    LIFE: " << life << endl;
		cout << "                                                                    LEVEL: " << level << endl;
	}

	void Input()
	{
		if (_kbhit())
		{
			switch (_getch())
			{	
				case 'a':
					dir = LEFT;
					break;
				case 'd':
					dir = RIGHT;
					break;
				case 'w':
					dir = UP;
					break;
				case 's':
					dir = DOWN;
					break;
				case 'x':
					gameOver = true;
					break;
			}
		}
	}

	void Logic()
	{
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = x;
		tailY[0] = y;
		
		for (int i = 1; i < nTail; i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
		
		switch (dir)
		{
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			case UP:
				y--;
				break;
			case DOWN:
				y++;
				break;
			default:
				break;
		}
		
		//if (x > width || x < 0 || y > height || y < 0)
		//	gameOver = true;
		if (x >= width) x = 0; else if (x < 0) x = width - 1;
		if (y >= height) y = 0; else if (y < 0) y = height - 1;

		for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
		gameOver = true;

		if (x == fruitX && y == fruitY)
		{
			score += 10;
			fruitX = rand() % width;
			fruitY = rand() % height;
			nTail++;
		}
	}
};

int main()
{
	snake s1;
	int n=0,sc=0,l;
	PlaySound(TEXT("C:\\Users\\vishal\\Desktop\\snake project\\Nightcore - River Flows In You.wav"),NULL,SND_ASYNC); //for game sound
    SetConsoleTitle("S N A K E  G A M E");
    s1.StdColor();
    s1.Menu();
     cout<<endl;
     cout<<"           choose the level of difficulty from level 1-3: ";
     cin>>l;
     
	 switch(l)
     {
	 	 case 1:	
	 	 	{		     
				start1:
				PlaySound(TEXT("C:\\Users\\vishal\\Desktop\\snake project\\Nightcore - River Flows In You.wav"),NULL,SND_ASYNC); 
				if(score>=10)
				goto start2;
				while(n!=3)
   				{
   					life=life-1;
   					sc=score;
   					nTail=0;
    				s1.Setup(sc);
   					system("cls");
					while (!gameOver)
					{
						s1.Draw(life,1);
						s1.Input();
						s1.Logic();
						Sleep(100);		
					}
					n++;
					goto start1;
					getch();
				}
				break;
			}
	 	 	
			case 2:
	 	 	{ 
				start2:
				PlaySound(TEXT("C:\\Users\\vishal\\Desktop\\snake project\\Nightcore - River Flows In You.wav"),NULL,SND_ASYNC); 
				if(score>=100)
				goto start3;
				while(n!=3)
   				{
   					life=life-1;
   					sc=score;
   					nTail=0;
    				s1.Setup(sc);
   					system("cls");
					while (!gameOver)
					{
						s1.Draw(life,2);
						s1.Input();
						s1.Logic();	
						Sleep(50); //sleep(10);		
					}
					n++;
					goto start2;
					getch();
				}
				break;
			}
	 	 	
			case 3:
	 	 	{ 
	 	 	
				start3:
				PlaySound(TEXT("C:\\Users\\vishal\\Desktop\\snake project\\Nightcore - River Flows In You.wav"),NULL,SND_ASYNC);
				while(n!=3)
   				{
   					life=life-1;
   					sc=score;
   					nTail=0;
    				s1.Setup(sc);
   					system("cls");
					while (!gameOver)
					{
						s1.Draw(life,3);
						s1.Input();
						s1.Logic();
						Sleep(15); //sleep(10);		
					}
					n++;
					goto start3;
					getch();
				}
				break;
			}
		}
		
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); cout << (char)1; //for lightblue color
	cout<<endl;
	cout<<endl;
	cout<<endl;
	cout<<"                   ' G A M E - - - O V E R '"<<endl;
	cout<<endl;
	cout<<"                   Congratulations "<<oname<<", you have made score: "<<score<<endl;
	getch();
    return 0;
}

