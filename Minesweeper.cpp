#include <iostream>
#include "windows.h"
#include <conio.h>
#include<iomanip>
#include<vector>
#include<time.h>
#include <fstream>
#include<string>
#include<cstring>
using namespace std;
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void color(int textColor, int backColor = 0)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
struct cellule
{
	bool flag=false;
	bool bomb=false;
	bool questionMark;
	bool revealedCell=false;
	int numberOfNearbyBombs=0;
	char symbol=178;
};
vector<vector<cellule> > TableMonitor(vector<vector<cellule> > table)//,int row,int col)
{
	system("cls");
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			switch(table[i][j].symbol)
			{
			case '1':color(1,0);break;
			case '2':color(2,0);break;
			case '3':color(4,0);break;
			case '4':color(5,0);break;
			case '5':color(3,0);break;
			case '6':color(9,0);break;
			case '7':color(6,0);break;
			case 'Q':color(0,4);break;
			case 'F':color(0,2);break;
			case 'X':color(0,6);break;
			default:
				color(7,0);break;
			}
			cout<<table[i][j].symbol;
		}
		cout<<endl;
	}
	return table;
}
vector<vector<cellule> > BombPlanting(int row,int col,int numberOfBombs)
{
	vector<vector<cellule> > table(row, vector<cellule>(col));
	srand(time(NULL));
	for(int i=1;i<=numberOfBombs;)
	{
		int rowOfCell=rand()%row;
		int colOfCell=rand()%col;
		if(table[rowOfCell][colOfCell].bomb==false)
		{
			table[rowOfCell][colOfCell].bomb=true;
			i++;
		}
	}
	return table;
}
vector<vector<cellule> > NearbyBombsEstimation(vector<vector<cellule> > table)
{
	for (int i = 0; i < table.size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			if(table[i][j].bomb==false)
			{
				if(i==0)
				{
					if(j==0)
					{
						for (int k = i; k < i+2; k++)
								for (int l = j; l < j+2; l++)	
									if(table[k][l].bomb==true)
										table[i][j].numberOfNearbyBombs++;		
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i; k < i+2; k++)
								for (int l = j-1; l < j+1; l++)	
									if(table[k][l].bomb==true)
										table[i][j].numberOfNearbyBombs++;	
					}
					else
					{
						for (int k = i; k < i+2; k++)
							for (int l = j-1; l < j+2; l++)	
								if(table[k][l].bomb==true)
									table[i][j].numberOfNearbyBombs++;	
					}
				}
				else if(i==table.size()-1)
				{
					if(j==0)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j; l < j+2; l++)	
								if(table[k][l].bomb==true)
									table[i][j].numberOfNearbyBombs++;	
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+1; l++)	
								if(table[k][l].bomb==true)
									table[i][j].numberOfNearbyBombs++;
					}
					else
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+2; l++)	
								if(table[k][l].bomb==true)
									table[i][j].numberOfNearbyBombs++;	
					}
				}
				else if(j==0 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j; l < j+2; l++)	
							if(table[k][l].bomb==true)
								table[i][j].numberOfNearbyBombs++;	
				}
				else if (j==table[0].size()-1 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+1; l++)	
							if(table[k][l].bomb==true)
								table[i][j].numberOfNearbyBombs++;	
				}
				else
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+2; l++)	
							if(table[k][l].bomb==true)
								table[i][j].numberOfNearbyBombs++;	
				}
			}
			else if(table[i][j].bomb==true)
				table[i][j].numberOfNearbyBombs=-1;
		}
	}
	return table;
}

vector<vector<cellule> > GameplayResponse(vector<vector<cellule> > table)
{
	for(int i=0;i<table.size();i++)
	for(int j=0;j<table[0].size();j++)
	{
	if(table[i][j].revealedCell==false && table[i][j].flag==true)
	{
		table[i][j].symbol='F';
	}
	else if(table[i][j].revealedCell==false && table[i][j].flag==false)
	{
		table[i][j].symbol=178;
	}
	if(table[i][j].revealedCell==true && table[i][j].flag==false)
	{
		switch(table[i][j].numberOfNearbyBombs)
		{
			case -1:
					table[i][j].symbol='Q';
					table[i][j].bomb=true;
					break;
			case 0:
					table[i][j].symbol=177;
					break;
					
			case 1:
					table[i][j].symbol=49;
					break;
			case 2:
					table[i][j].symbol=50;
					break;
			case 3:
					table[i][j].symbol=51;
					break;
			case 4:
					table[i][j].symbol=52;
					break;
			case 5:
					table[i][j].symbol=53;
					break;
			case 6:
					table[i][j].symbol=54;
					break;
			case 7:
					table[i][j].symbol=55;
					table[i][j].revealedCell=true;
					break;
			case 8:
					table[i][j].symbol=56;
					break;
			//default:
			//	table[i][j].symbol=178;
		}
	}
}
	//TableMonitor(table);
	return table;
}

vector<vector<cellule> > ExpandingSafeArea(vector<vector<cellule> > table)
{

	for (int i=0;i<table.size();i++)
		for (int j=0;j<table[0].size();j++)	
		{
			if(table[i][j].numberOfNearbyBombs==0 && table[i][j].revealedCell==true)
			{
				if(i==0)
				{
					if(j==0)
					{
						for (int k = i; k < i+2; k++)
							for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i; k < i+2; k++)
							for (int l = j-1; l < j+1; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else
					{
						for (int k = i; k < i+2; k++)
							for (int l = j-1; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
				}
				else if(i==table.size()-1)
				{
					if(j==0)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+1; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
				}
				else if(j==0 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
				}
				else if (j==table[0].size()-1 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+1; l++)	
						{
							if(table[k][l].flag==false)
							{
								table[k][l].revealedCell=true;
								table=GameplayResponse(table);
							}
						}
				}
				else
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+2; l++)	
						{
							if(table[k][l].flag==false)
							{
								table[k][l].revealedCell=true;
								table=GameplayResponse(table);
							}
						}
				}
			}
		}
	for (int i=table.size()-1;i>=0;i--)
		for (int j=table[0].size()-1;j>=0;j--)	
		{
			if(table[i][j].numberOfNearbyBombs==0 && table[i][j].revealedCell==true)
			{
				if(i==0)
				{
					if(j==0)
					{
						for (int k = i; k < i+2; k++)
							for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i; k < i+2; k++)
							for (int l = j-1; l < j+1; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else
					{
						for (int k = i; k < i+2; k++)
							for (int l = j-1; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
				}
				else if(i==table.size()-1)
				{
					if(j==0)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else if(j==table[0].size()-1)
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+1; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
					else
					{
						for (int k = i-1; k < i+1; k++)
							for (int l = j-1; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
					}
				}
				else if(j==0 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j; l < j+2; l++)	
							{
								if(table[k][l].flag==false)
								{
									table[k][l].revealedCell=true;
									table=GameplayResponse(table);
								}
							}
				}
				else if (j==table[0].size()-1 && i!=table.size()-1 && i!=0)
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+1; l++)	
						{
							if(table[k][l].flag==false)
							{
								table[k][l].revealedCell=true;
								table=GameplayResponse(table);
							}

						}
				}
				else
				{
					for (int k = i-1; k < i+2; k++)
						for (int l = j-1; l < j+2; l++)	
						{
							if(table[k][l].flag==false)
							{
								table[k][l].revealedCell=true;
								table=GameplayResponse(table);
							}
						}
				}
			}
		}		
	return table;
}
bool Loose(vector<vector<cellule> > table)
{
	for (int i = 0; i < table.size(); i++)
		for (int j = 0; j < table[i].size(); j++)
			if(table[i][j].bomb==true && table[i][j].revealedCell==true)
			{
				return true;
			}
}
int BombCounter(vector<vector<cellule> >table)
{
	int counter=0;
	for (int i = 0; i < table.size(); i++)
		for (int j = 0; j < table[i].size(); j++)
			if(table[i][j].bomb==true)
			counter++;
	return counter;
}
bool Win(vector<vector<cellule> > table)
{
	int totalBombs=BombCounter(table);
	int counter=0,Counter=0;
	for (int i = 0; i < table.size(); i++)
		for (int j = 0; j < table[i].size(); j++)
		{
			if(table[i][j].bomb==true && table[i][j].flag==true)
				counter++;
			if(table[i][j].revealedCell==true && table[i][j].bomb==false)
				Counter++;
		}
	if(counter==totalBombs || (table.size()*table[0].size()-Counter==totalBombs))
	{
		return true;
	}
	else
		return false;
}
vector<vector<cellule> > Preloading(int row,int col,int numberOfBombs)
{
	vector<vector<cellule> > table=BombPlanting(row,col,numberOfBombs);
	table=NearbyBombsEstimation(table);
	return table;
}
int Minesweeper(vector<vector<cellule> > table)
{
	if(Win(table)==true)
		return 1;
	else if(Loose(table)==true)
		return -1;
	else
		return 0;
}
void Game(vector<vector<cellule> > table)
{
	if(Win(table)==true)
	{
		cout<<endl<<endl<<"Fantastic.  ";
	}
 	if(Loose(table)==true)
	{
		for (int i = 0; i < table.size(); i++)
			for (int j = 0; j < table[i].size(); j++)
			{
				if(table[i][j].bomb==true && table[i][j].flag==false)
				{
					table[i][j].symbol='Q';
				}
				else if(table[i][j].bomb==false && table[i][j].flag==true)
				{
					table[i][j].symbol='X';
				}
			}
		TableMonitor(table);
		cout<<"\n\aOh, Went of the target !!  ";	
		
	}
}
bool PrivacyAndPolicy()
{
	char userAgreement;
	cin>>userAgreement;
	while(userAgreement<48 || userAgreement>53)
	{
		cout<<"Try again: ";
		cin>>userAgreement;
	}
	if(userAgreement=='3')
	{
		cout<<"1.Enter inputs correctly.\n2.We ARE NOT responsible for any crash after entering incorrect input.\n3.You must not copy this interface unless you mention our designer:\"Saeed All Gharaee\".\n4.All Rights Reserved.";
		cout<<endl<<"Do you Agree?  1.YES  2.NO \n";
		cin>>userAgreement;
	}
	if(userAgreement=='1')
	{
		system("cls");
		cout<<"Thanks, Enjoy The Best Game We \'ve Ever Made."<<endl;
		return true;
	}
	if(userAgreement=='2')
	{
		cout<<"Sorry. We admire stubborn guys.";
		return false;
	}
} 

vector<vector<cellule> > Menu(char userResponseToMenu)
{
	int col=1,row=1,totalBombs=0;
	switch(userResponseToMenu)
	{
		case '1':
		{
			char level;
			cout<<"1.Easy  2.Medium  3.Hard  4.Exreme  ";
			cin>>level;
			if(level=='1')
			{
				col=9;
				row=9;
				totalBombs=10;
			}
			else if(level=='2')
			{
				col=16;
				row=16;
				totalBombs=40;
			}
			else if(level=='3')
			{
				col=30;
				row=16;
				totalBombs=99;
			}
			else if(level=='4')
			{
				col=30;
				row=24;
				totalBombs=180;
			}
			else
			{
				system("cls");
				cout<<"Sorry,You ignored our terms.";
			}
			break;
		}
		case '2':
		{
			ifstream record;
			record.open("leaderboard.txt", ios::in);
			if (record)
			{
				system("cls");
				string leaderBoard;
				while(getline(record, leaderBoard))
					cout << leaderBoard<<endl;
			}
			else 
				cout<<"You should play at least once to see your scores!!";
			break;
		}
		case '3':
		{
			system("cls");
			cout<<"User Guide:"<<endl<<"1.Revealing a cell(ENTER)	2.Put or remove a flag(F)\na)Bomb container cell 'Q'	b)No bomb but flag 'X'\n";
		}
		case '4':
			cout<<"Contact us on telegram: @SaeedAG.";break;
		default:
			cout<<"Sorry,You ignored our terms.";
			break;
	}
	return Preloading(row,col,totalBombs);
}
int main() 
{
	cout<<"Autorized by Saeed";
	Sleep(1000);
	system("cls");
	cout<<"Minesweeper"<<endl;
	Sleep(1000);
	cout<<"You should agree with our terms of use:"<<"  1.Agree  2.Disagree  3.Terms of use  :";
	bool userAgreementResponse=PrivacyAndPolicy();
	if(userAgreementResponse==false)
		return 0;	
	while(true)
	{
			//system("cls");
			cout<<"Menu"<<endl<<"1.New Game"<<endl<<"2.Leaderboard"<<endl<<"3.Use Guide"<<endl<<"4.About us"<<endl;
			char userResponseMenuInput;
			cin>>userResponseMenuInput;
			vector<vector<cellule> > table=Menu(userResponseMenuInput);
			clock_t time=clock()/1000;
			TableMonitor(table);
			//Minesweeper(table);
				
			char key = 0;
			int x = 0, y = 0;
			gotoxy(y, x);
			char carsor=248;
			cout << carsor;
			int gameContinue=1;
			while (gameContinue==1) 
			{
				if(Minesweeper(table)!=0)
					{
						clock_t ExtraTime=clock()/1000;
						time=ExtraTime-time;
						Game(table);
						cout<<"TIME: "<<time;
						cout<<endl<<"1.Menu		2.Finish\n";
						ofstream leaderBoard;
						leaderBoard.open("leaderboard.txt", ios::app);
						if (leaderBoard)
						{
							//string level=BombCounter(table)==10?"Easy":(BombCounter(table)==40?"Medium":(BombCounter(table)==99?"Hard":(BombCounter(table)==10?"Extreme":"")));
							string level="";
							if(BombCounter(table)==10)
								level="Easy";
							if(BombCounter(table)==40)
								level="Medium";
							if(BombCounter(table)==99)
								level="Hard";
						if(BombCounter(table)==180)
								level="Extreme";
							if(Minesweeper(table)==1)
							{
								string text=" secounds ";
								text+=level;
								leaderBoard<<"Win: "<<time<<text<<endl;
							}
							if(Minesweeper(table)==-1)
							{
								string text=" secounds ";
								text+=level;
								leaderBoard<<"Loose: "<<time<<text<<endl;
							}
								
						}
						char userResponseAfterGame;
						cin>>userResponseAfterGame;
						if(userResponseAfterGame=='1')
						{
							gameContinue=0;
						}
						else if(userResponseAfterGame=='2')
						{
							false;
							return 0;
						}
						else 
						{
							cout<<"Sorry, You ignored our terms.";
							false;
							return 0;
						}
					}
				else
				{
					key = _getch();
					switch (key)
					{
						case 77:
							gotoxy(y, x);
							cout << table[x][y].symbol;
							gotoxy(y = y<table[0].size()-1? y+1 : y,x);
							cout << carsor;
							break;
						case 80:
							gotoxy(y, x);
							cout << table[x][y].symbol;
							gotoxy(y,x = x<table.size()-1? x+1 : x);
							cout << carsor;
							break;
						case 75:
							gotoxy(y, x);
							cout << table[x][y].symbol;
							gotoxy(y = y>0 ? y-1 : y, x);
							cout << carsor;
							break;
						case 72:
							gotoxy(y, x);
							cout << table[x][y].symbol;
							gotoxy(y,x = x>0 ? x-1 : x);
							cout << carsor;
					
							break;
						case 'F':
						case 'f':
								gotoxy(y, x);
								if(table[x][y].flag==false)
									table[x][y].flag=true;
								else
									table[x][y].flag=false;
								table=GameplayResponse(table);
								TableMonitor(table);
								gotoxy(y = y>0 ? y-1 : y, x);
							    cout<<carsor;
							    break;
							
						case 13:
							if(table[x][y].revealedCell==true || table[x][y].flag==true)
								break;
							else
							{
								table[x][y].revealedCell=true;
								table=ExpandingSafeArea(table);
								table=GameplayResponse(table);
								TableMonitor(table);
								gotoxy(y = y>0 ? y-1 : y, x);
								cout<<carsor;
								break;
							}
						default:
							break;
						}
				}
			}
	}
	system("pause>0");
}
