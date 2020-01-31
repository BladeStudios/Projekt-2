#include "board.h"
#include "block.h"
#include "extern.h"
#include <ctime>
#include <cstdio>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <algorithm>
#include <iterator>
#include <atomic>
#include <chrono>

char tab[windowWidth][windowHeight];
char prevtab[windowWidth][windowHeight];
int positionY = 1;
int positionX = 4;
int level = 0;
//Block bl;
bool fin = false;

using namespace std;

void Board::createBaseWindow(int maxx, int maxy)
{
	for (int j = 0; j < maxy; j++)
	{
		for (int i = 0; i < maxx; i++)
		{
			if (i == 0 && j == 0) //left-top corner
				tab[i][j] = ctopleft;
			else if (i == maxx - 1 && j == 0) //right-top corner
				tab[i][j] = ctopright;
			else if (i == 0 && j == maxy - 1) //left-bottom corner
				tab[i][j] = cbottomleft;
			else if (i == maxx - 1 && j == maxy - 1) //right-bottom corner
				tab[i][j] = cbottomright;
			else if ((j == 0 && i == 11) || (j == 0 && i == 17)) //T-shape-top corners
				tab[i][j] = ctop;
			else if ((j == maxy - 1 && i == 11) || (j == 9 && i == 17)) //T-shape-bottom corners
				tab[i][j] = cbottom;
			else if (i == 11 && (j == 2 || j == 4 || j==9)) //T-shape-left corners
				tab[i][j] = cleft;
			else if (i == 17 && (j == 2 || j == 4)) //middle corners
				tab[i][j] = cmiddle;
			else if (i == maxx - 1 && (j == 2 || j == 4 || j==9)) //T-shape-right corners
				tab[i][j] = cright;
			else if (j == 0 || (j == 2 && i > 11) || (j == 4 && i > 11) || (j == 9 && i > 11) || j == maxy - 1) //horizontal lines
				tab[i][j] = chorizontal;
			else if (i == 0 || i == 11 || (i == 17 && j < 9) || i == maxx - 1) //vertical lines
				tab[i][j] = cvertical;
		}
	}

	//words
	write("SCORE", 12, 1);
	write("SPEED", 12, 3);
	write("NEXT", 12, 6);
	write("BLOCK", 12, 7);
	write("0", 21, 1);
	write("0", 21, 3);
}

void Board::write(string word, int posx, int posy)
{
	for (unsigned int i = posx; i < (word.length() + posx); i++)
	{
		tab[i][posy] = (char)word[i - posx];
	}
}

bool Board::game()
{
	size_t time = 0;
	int score = 0;
	int speed = 150;
	size_t sleepTime = 60000 / speed;
	int speedChanger = 0;
	bool gameOver = false;
	int nextBlockType = getBlockType();
	int nextRotation = getRotation();
	int fin = false;
	bool spaceBlocked = false;
	bool arrowDownBlocked = false;

	Block bl;
	bl.blockType = 0;
	bl.rotation = 1;

	createBaseWindow(windowWidth, windowHeight);
	cleanBoard();
	drawBoard(windowWidth, windowHeight);
	copy(&tab[0][0], &tab[windowWidth-1][windowHeight-1], &prevtab[0][0]);

		while (!gameOver)
		{
			writeScore(score);
			writeSpeed(speed);
			bl.setBlockType(nextBlockType);
			bl.setRotation(nextRotation);
			//bl.blockType = 1; //nextBlockType;
			//bl.rotation = nextRotation;
			nextBlockType = getBlockType();
			nextRotation = getRotation();
			//rysowanie nastepnego klocka
			drawNextBlock(nextBlockType, nextRotation);
			//rysowanie aktualnego klocka
			//Block bl;
			positionY = 4;
			positionX = 4;
			bool breaked = false;
			//narysowanie figury w ustawieniu poczatkowym
			int i2, j2;
			for (int i = positionX; i < positionX+4; i++)
			{
				i2 = i - positionX;
				for (int j = positionY; j > positionY-4; j--)
				{
					j2 = j - positionY + 3;
					if (bl.getTile(bl.blockType, bl.rotation, j2, i2) == 1)
					{
						tab[i][j] = square;
						prevtab[i][j] = square;
						draw(square, i, j);
					}
					else
					{
						tab[i][j] = nothing;
						prevtab[i][j] = nothing;
						draw(nothing, i, j);
					}
				}
			}
			while (!breaked)
			{
				//ustawienie co ma byc narysowane
				/*for (int i = 0; i < 4; i++)
				{
					if (positionY < 5 && bl.getTile(bl.blockType, bl.rotation, 4 - positionY, i) == 1)
						tab[i + positionX][1] = square;
					else
						tab[i + positionX][1] = nothing;
				}*/
				//rysowanie
				for (int i = 1; i <= 10; i++)
				{
					if (tab[i][1] == square)
					{
						draw(square, i, 1);
					}
					else if (tab[i][1] != solid)
					{
						draw(nothing, i, 1);
					}
				}
				
				//sprawdzenie kolizji
				for (int j = positionY; ((j >= 1) && j >= (positionY - 4)); j--)
				{
					for (int i = 1; i < 11; i++)
					{
						if (tab[i][j] == square && collision("down", i, j))
						{
							breaked = true;
						}
					}
				}
				copy(&tab[0][0], &tab[windowWidth-1][windowHeight-1], &prevtab[0][0]);

				//obsluga klawiatury
				while (time < sleepTime)
				{
					if (GetKeyState(VK_SPACE)>=0 && GetKeyState(VK_UP)>=0 && spaceBlocked==true) 
						spaceBlocked = false;
					if (GetKeyState(VK_DOWN) >= 0)
						arrowDownBlocked = false;
					if (_kbhit())
						keys(bl, spaceBlocked, arrowDownBlocked, time, sleepTime);
					time++;
					Sleep(1);
				}
				time = 0;

				if (!breaked)
				{
					copyx(positionY);
				}
				positionY++;
			}

			arrowDownBlocked = true; //po dojechaniu klocka do dolu, strzalka w dol jest blokowana aby niechcacy nie przejechac w dol kilkoma kolejnymi figurami
			speedChanger++;
			if (speedChanger >= 1)
			{
				speed++;
				speedChanger = 0;
			}
			//zamiana wszystkich klockow na wyglad juz ulozonych (aby potem odrozniac od nich latajace)
			for (int j = 1; j <= 16; j++)
			{
				for (int i = 1; i < 11; i++)
				{
					if (tab[i][j] == square)
					{
						tab[i][j] = solid;
						prevtab[i][j] = solid;
						draw(solid, i, j);
					}
				}
			}
			//dodanie pkt
			score += countPoints();
			//usuniecie rzedow
			deleteRows();
			gameOver = isOver();
		}
		fin = drawResult(score);
		return fin;
}

void Board::copyx(int posy)
{
	for (int j = posy; j >= 1; j--)
	{
		for (int i = 1; i <= 10; i++)
		{
			if (tab[i][j] == square)
			{
				tab[i][j + 1] = tab[i][j];
				tab[i][j] = nothing;

				draw(tab[i][j + 1], i, j + 1);
				draw(nothing, i, j);

			}
		}
	}
}

void Board::drawBoard(int maxx, int maxy)
{
	for (int j = 0; j < maxy; j++)
	{
		for (int i = 0; i < maxx; i++)
		{
			cout << tab[i][j];
		}
		cout << endl;
	}
}

int Board::getBlockType()
{
	srand((int)time(NULL));
	return (rand() % 7);
}

int Board::getRotation()
{
	srand((int)time(NULL));
	return (rand() % 4);
}

bool Board::collision(string dir, int posx, int posy)
{
	if (dir.compare("left") == 0 && (posx == 1 || tab[posx - 1][posy] == solid))
		return true;
	else if (dir.compare("right") == 0 && (posx == 10 || tab[posx + 1][posy] == solid))
		return true;
	else if (dir.compare("down") == 0 && (posy == 16 || tab[posx][posy + 1] == solid))
		return true;
	else
		return false;
}

void Board::setCursorPosition(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	csbi.dwCursorPosition.X = x;
	csbi.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hStdout, csbi.dwCursorPosition);
}

void Board::draw(char a, int x, int y)
{
	if (a == square || a == solid)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 22);
	else if (a == nothing)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	setCursorPosition(x, y);
	cout << a;
}

void Board::keys(Block &bl, bool &spaceBlocked, bool &arrowDownBlocked, size_t &time, size_t sleepTime)
{
	int key;

	//while (1)
	//{
		key = 0;
		switch (key = _getch())
		{
			case 32: //space
			case 72: //arrow up
			{
				if (!spaceBlocked)
				{
					rotate(bl.blockType, bl.rotation, bl);
					spaceBlocked = true;
				}
				break;
			}
			case 75: //left arrow
			{
				moveleft();
				break;
			}
			case 77: //right arrow
			{
				moveright();
				break;
			}
			case 80: //down arrow
			{
				if (!arrowDownBlocked)
				{
					time = sleepTime;
				}
				break;
			}
		}
	//}
}

bool Board::check() //sprawdzenie czy cos sie zmienilo na planszy i trzeba rysowac
{
	return true;
}

void Board::moveleft()
{
	bool breaked = false;
	for (int j = 1; j <= positionY; j++)
	{
		for (int i = 1; i < 11; i++)
		{
			if (tab[i][j] == square)
			{
				if (!collision("left", i, j))
				{
					tab[i - 1][j] = tab[i][j];
					tab[i][j] = nothing;
				}
				else
				{
					breaked = true;
					break;
				}
			}
		}
	}
	if (breaked)
		copy(&prevtab[0][0], &prevtab[windowWidth-1][windowHeight-1], &tab[0][0]);
	else
	{
		positionX--;
		for (int j = 1; j <= positionY; j++)
		{
			for (int i = 1; i < 11; i++)
			{
				if (tab[i][j] != prevtab[i][j])
				{

					if (tab[i][j] == square)
						draw(square, i, j);
					else if (tab[i][j] == nothing)
						draw(nothing, i, j);

				}
			}
		}
		copy(&tab[0][0], &tab[windowWidth-1][windowHeight-1], &prevtab[0][0]);
	}
}

void Board::moveright()
{
	bool breaked = false;
	for (int j = 1; j <= positionY; j++)
	{
		for (int i = 10; i > 0; i--)
		{
			if (tab[i][j] == square)
			{
				if (!collision("right", i, j))
				{
					tab[i + 1][j] = tab[i][j];
					tab[i][j] = nothing;
				}
				else
				{
					breaked = true;
					break;
				}
			}
		}
	}
	if (breaked)
		copy(&prevtab[0][0], &prevtab[windowWidth-1][windowHeight-1], &tab[0][0]);
	else
	{
		positionX++;
		for (int j = 1; j <= positionY; j++)
		{
			for (int i = 1; i < 11; i++)
			{
				if (tab[i][j] != prevtab[i][j])
				{

					if (tab[i][j] == square)
						draw(square, i, j);
					else if (tab[i][j] == nothing)
						draw(nothing, i, j);

				}
			}
		}
		copy(&tab[0][0], &tab[windowWidth-1][windowHeight-1], &prevtab[0][0]);
	}
}

void Board::cleanBoard()
{
	/*for (int j = 0; j < windowHeight; j++)
	{
		for (int i = 0; i < windowWidth; i++)
		{
			//if (tab[i][j] == NULL || tab[i][j] == solid)
				tab[i][j] = nothing;
			prevtab[i][j] = nothing;
		}
	}*/
	
	for (int j = 1; j <= 16; j++)
	{
		for (int i = 1; i <=10; i++)
		{
			//if (tab[i][j] == NULL || tab[i][j] == solid)
			tab[i][j] = nothing;
			prevtab[i][j] = nothing;
		}
	}
}

void Board::writeScore(int sc)
{
	string strScore = to_string(sc);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	if (sc / 1000 > 0)
	{
		setCursorPosition(18, 1);
		cout << strScore;
	}
	else if (sc / 100 > 0)
	{
		setCursorPosition(19, 1);
		cout << strScore;
	}
	else if (sc / 10 > 0)
	{
		setCursorPosition(20, 1);
		cout << strScore;
	}
	else
	{
		setCursorPosition(21, 1);
		cout << strScore;
	}

}

void Board::writeSpeed(int sp)
{
	string strSpeed = to_string(sp);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	if (sp / 1000 > 0)
	{
		setCursorPosition(18, 3);
		cout << strSpeed;
	}
	else if (sp / 100 > 0)
	{
		setCursorPosition(19, 3);
		cout << strSpeed;
	}
	else if (sp / 10 > 0)
	{
		setCursorPosition(20, 3);
		cout << strSpeed;
	}
	else
	{
		setCursorPosition(21, 3);
		cout << strSpeed;
	}

}

int Board::countPoints()
{
	int pts = 0; //przechowuje ilosc pkt za dany ruch
	int rows = 0; //zlicza ile pelnych rzedow udalo sie skasowac danym ruchem
	int counter = 0; //zlicza ile w danym rzedzie jest klockow typu solid
	for (int j = 16; j >= 1; j--)
	{
		counter = 0;
		for (int i = 1; i <= 10; i++)
		{
			if (tab[i][j] == solid)
				counter++;
		}
		if (counter == 10)
			rows++;
		if (rows == 4)
			break;
	}
	switch (rows)
	{
	case 0: pts = 0; break;
	case 1: pts = 1; break;
	case 2: pts = 4; break;
	case 3: pts = 9; break;
	case 4: pts = 16; break;
	default: pts = 0;
	}
	return pts;
}

void Board::deleteRows()
{
	int counter = 0; //zlicza ile w danym rzedzie jest klockow typu solid
	for (int j = 16; j >= 1; j--)
	{
		counter = 0;
		for (int i = 1; i <= 10; i++)
		{
			if (tab[i][j] == solid)
				counter++;
		}
		if (counter == 10) //zliczono 10 solidow w 1 rzedzie wiec go kasujemy
		{
			for (int i = 1; i <= 10; i++) //kasowanie rzedu
			{
				tab[i][j] = deleted;
				prevtab[i][j] = deleted;

				draw(tab[i][j], i, j);

			}
		}

	}
	bool finished = false;
	while (!finished)
	{
		for (int j = 1; j <= 16; j++)
		{
			if (tab[1][j] == deleted)
			{
				for (int k = j; k > 1; k--)
				{
					for (int i = 1; i <= 10; i++)
					{
						tab[i][k] = tab[i][k - 1];
						prevtab[i][k] = prevtab[i][k - 1];

						draw(tab[i][k], i, k);

					}
				}
			}
		}
		finished = true;
	}

}

bool Board::isOver()
{
	for (int i = 1; i <= 10; i++)
	{
		if (tab[i][4] == solid)
			return true;
	}
	return false;
}

void Board::writeAndDraw(string word, int posx, int posy)
{
	for (unsigned int i = posx; i < (word.length() + posx); i++)
	{
		tab[i][posy] = (char)word[i - posx];

		draw2(tab[i][posy], i, posy);

	}
}

void Board::draw2(char a, int x, int y)
{
	setCursorPosition(x, y);
	cout << a;
}

bool Board::drawResult(int sc)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	string strScore = to_string(sc);
	draw2(ctopleft, 5, 5);
	for (int i = 6; i <= 16; i++)
		draw2(chorizontal, i, 5);
	draw2(ctopright, 17, 5);
	draw2(cvertical, 5, 6);
	draw2(nothing, 6, 6);
	writeAndDraw("GAME OVER", 7, 6);
	draw2(nothing, 16, 6);
	draw2(cvertical, 17, 6);
	draw2(cleft, 5, 7);
	for (int i = 6; i <= 16; i++)
		draw2(chorizontal, i, 7);
	draw2(cright, 17, 7);

	draw2(cvertical, 5, 8);
	writeAndDraw("SCORE:", 6, 8);
	int len = strScore.length();
	for (int i = 12; i < ((5 - len) + 12); i++)
		draw2(nothing, i, 8);
	writeAndDraw(strScore, (5 - len) + 12, 8);
	draw2(cvertical, 17, 8);

	draw2(cvertical, 5, 9);
	for (int i = 6; i <= 16; i++)
		draw2(nothing, i, 9);
	draw2(cvertical, 17, 9);

	//play again
	draw2(cvertical, 5, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
	writeAndDraw("PLAY AGAIN ", 6, 10);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	draw2(cvertical, 17, 10);

	//exit
	draw2(cvertical, 5, 11);
	writeAndDraw("MAIN MENU  ", 6, 11);
	draw2(cvertical, 17, 11);

	draw2(cbottomleft, 5, 12);
	for (int i = 6; i <= 16; i++)
		draw2(chorizontal, i, 12);
	draw2(cbottomright, 17, 12);

	int option = 0;
	int key;
	bool goToMainMenu = false;
	while (!goToMainMenu)
	{
		key = 0;
		switch (key = _getch())
		{
		case 13: //enter
		{
			goToMainMenu = true;
			if (option == 0)
				return true;
			else
				return false;
		}break;
		case 72: //up
		{
			if (option == 0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				writeAndDraw("PLAY AGAIN ", 6, 10);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				writeAndDraw("MAIN MENU  ", 6, 11);
				option = 1;
			}
			else if (option == 1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				writeAndDraw("PLAY AGAIN ", 6, 10);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				writeAndDraw("MAIN MENU  ", 6, 11);
				option = 0;
			}
		}break;
		case 80: //down
		{
			if(option==0)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				writeAndDraw("PLAY AGAIN ", 6, 10);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				writeAndDraw("MAIN MENU  ", 6, 11);
				option = 1;
			}
			else if (option==1)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				writeAndDraw("PLAY AGAIN ", 6, 10);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				writeAndDraw("MAIN MENU  ", 6, 11);
				option = 0;
			}

		}break;
		default: break;
		}
	}
	return true; //na wszelki wypadek, funkcja i tak tutaj nie powinna nigdy dojsc
}

void Board::drawNextBlock(int type, int rotation)
{
	Block nextB;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{

			if (nextB.getTile(type, rotation, j, i) == 1)
				draw(square, i + 18, j + 5);
			else
				draw(nothing, i + 18, j + 5);

		}
	}
}

void Board::rotate(int type, int rot, Block &bl)
{
	rot++;
	if (rot > 3)
		rot -= 4;

	bl.setRotation(rot);

	//obsluzenie sytuacji, kiedy niemozliwy jest obrot z powodu ograniczenia przez boczna lub dolna ramke planszy
	if ((getMinX(type, rot) + positionX < 1) || (getMaxX(type, rot) + positionX > 10) || (getMaxY(type,rot) + positionY > 19))
	{
		rot--;
		if (rot < 0)
			rot += 4;
		bl.setRotation(rot);
		return;
	}

	int i2, j2;

	//obsluzenie sytuacji, kiedy niemozliwy jest obrot z powodu ograniczenia przez inne juz ulozone figury
	for (int i = positionX; i < positionX + 4; i++)
	{
		i2 = i - positionX;
		for (int j = positionY; j > positionY - 4; j--)
		{
			j2 = 3 + j - positionY;
			if (tab[i][j] == solid)
				return;
		}
	}

	//USTAWIENIE KLOCKA PO OBROCIE BEZ UWZGLEDNIENIA CZY WYSTAJE ZA PLANSZE
	//i oraz j - wspolrzedne na planszy
	//i2 oraz j2 - wspolrzedne z tablicy 4x4 odpowiadajacej danemy klockowi
	
	for (int i = (positionX); i < positionX + 4; i++)
	{
		i2 = i - positionX;
		for (int j = positionY; j > positionY - 4; j--)
		{
			j2 = 3 + j - positionY;
			if (bl.getTile(type,rot,j2,i2) == 1)
			{
				tab[i][j] = square;
				prevtab[i][j] = square;
				draw(square, i, j);
			}
			else if (i>=1 && i<=10 && j<=16)
			{
				tab[i][j] = nothing;
				prevtab[i][j] = nothing;
				draw(nothing, i, j);
			}
		}
	}
}

bool Board::canRorate(int type, int rot)
{
	bool can = true;
	rot++;
	if (rot > 3)
		rot -= 4;

	int blockPosX = 0;
	for (int i = 3; i <= 3; i++)
	{
		for (int j = 0; j <= 3; j++)
		{

		}
	}
	return can;
}

//zwraca pozycjê od 0 do 3, na ktorej w danym kwadracie zaczyna siê klocek
int Board::getMinX(int type, int rotation)
{
	int minX = 4;
	Block temp;
	for (int x = 0; x <= 3; x++)
	{
		for (int y = 0; y <= 3; y++)
		{
			if (temp.getTile(type, rotation, y, x) == 1)
			{
				minX = x;
				return minX;
			}
		}
	}
	return minX;
}

//zwraca pozycjê od 0 do 3, na ktorej w danym kwadracie konczy siê klocek
int Board::getMaxX(int type, int rotation)
{
	int maxX = -1;
	Block temp;
	for (int x = 3; x >= 0; x--)
	{
		for (int y = 0; y <= 3; y++)
		{
			if (temp.getTile(type, rotation, y, x) == 1)
			{
				maxX = x;
				return maxX;
			}
		}
	}
	return maxX;
}

int Board::getMaxY(int type, int rotation)
{
	int maxY = -1;
	Block temp;
	for (int y = 3; y >= 0; y--)
	{
		for (int x = 0; x <= 3; x++)
		{
			if (temp.getTile(type, rotation, y, x) == 1)
			{
				maxY = y;
				return maxY;
			}
		}
	}
	return maxY;
}