#include <SFML/Graphics.hpp>
#include <cmath>
#include <time.h>
#include <iostream>
#include <string>
#include <windows.h> //console size
#include <cstdio>
#include <conio.h>
#include <ctime>
#include "board.h"
#include "block.h"
#include "extern.h"

//OTHERS
using namespace std;
using namespace sf;

void setFontSize(int FontSize)
{
	/*CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize;
	info.dwFontSize.X = FontSize;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);*/
}

void cleanScreen()
{
	system("cls");
}
/*
int drawMainMenu()
{
	cleanScreen();
	int tetris[9][23] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
		{0,1,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0},
		{0,1,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,1,0,0,1,1,1},
		{0,1,0,0,1,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,1},
		{0,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,1,1,0,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,0,1,1,1,0,0,0,1},
		{1,1,1,1,0,1,1,0,1,1,1,0,0,1,1,0,0,1,0,0,1,1,1}
	};
	Board br;
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 34);
	for (int i = 0; i < 23; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (tetris[j][i] == 1)
			{
				br.setCursorPosition(i, j);
				cout << 'X';
			}
		}
	}
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
	for (int i = 0; i < 23; i++)
	{
		for (int j = 6; j < 9; j++)
		{
			if (tetris[j][i] == 1)
			{
				br.setCursorPosition(i, j);
				cout << 'X';
			}
		}
	}
	bool play = true;
	bool quit = false;
	int key;

	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
	br.setCursorPosition(7, 10);
	cout << "PLAY GAME";
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	br.setCursorPosition(10, 11);
	cout << "QUIT";

	while (1)
	{
		key = 0;
		switch (key = _getch())
		{
		case 13: //enter
		{
			if (play)
				return 1;
			else if (quit)
				return 2;
		}break;
		case 72: //up
		{
			if (quit)
			{
				play = true;
				quit = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				br.setCursorPosition(7, 10);
				cout << "PLAY GAME";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				br.setCursorPosition(10, 11);
				cout << "QUIT";
			}
			else if (play)
			{
				play = false;
				quit = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				br.setCursorPosition(7, 10);
				cout << "PLAY GAME";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				br.setCursorPosition(10, 11);
				cout << "QUIT";
			}
		}break;
		case 80: //down
		{
			if (quit)
			{
				play = true;
				quit = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				br.setCursorPosition(7, 10);
				cout << "PLAY GAME";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				br.setCursorPosition(10, 11);
				cout << "QUIT";
			}
			else if (play)
			{
				play = false;
				quit = true;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				br.setCursorPosition(7, 10);
				cout << "PLAY GAME";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 244);
				br.setCursorPosition(10, 11);
				cout << "QUIT";
			}
		}break;
		default: break;
		}
	}

}

void clearArray()
{
	for (int i = 0; i < windowWidth; i++)
	{
		for (int j = 0; j < windowHeight; j++)
		{
			tab[i][j] = nothing;
		}
	}
}
*/
int main()
{
	RenderWindow window(sf::VideoMode(690, 540), "Tetris");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture mainmenu;
	mainmenu.loadFromFile("mainmenu.png");
	Texture button;
	button.loadFromFile("button-bg.png");
	Texture blocks;
	blocks.loadFromFile("texture.png");

	Font font;
	font.loadFromFile("Arial.ttf");

	Text playGame, quit;
	playGame.setFont(font);
	playGame.setFillColor(Color::White);
	playGame.setString("PLAY GAME");
	playGame.setPosition(260, 250);

	quit.setFont(font);
	quit.setFillColor(Color::White);
	quit.setString("QUIT");
	quit.setPosition(310, 340);
	
	Sprite sMenu(mainmenu);
	Sprite button1(button);
	Sprite button2(button);
	Sprite s(blocks);

	button1.setPosition(240, 240);
	button2.setPosition(240, 330);

	s.setTextureRect(IntRect(0, 0, 30, 30));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		} //while
		//window.clear(Color::White);
		window.draw(sMenu);
		window.draw(button1);
		window.draw(playGame);
		window.draw(button2);
		window.draw(quit);

		window.display();
	} //while

	/*
	//SETTING FONT SIZE
	int fontSize = 32;
	setFontSize(fontSize);

	//SETTING WINDOW SIZE AND PLACE
	HWND hDesktop = GetDesktopWindow();
	HWND hConsole = GetConsoleWindow();
	RECT r;
	GetWindowRect(hDesktop, &r);
	int consoleWidth = windowWidth * fontSize + 65;
	int consoleHeight = windowHeight * fontSize + 100;
	int middleX = (r.right / 2) - (consoleWidth / 2);
	int middleY = (r.bottom / 2) - (consoleHeight / 2);
	SetWindowPos(hConsole, 0, middleX, middleY, consoleWidth, consoleHeight, 0);

	//REMOVING CURSOR
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);*/

	/* TODO
	while (1)
	{
		cleanScreen();
		//SETTING FONT COLOR
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
		int res = drawMainMenu();
		if (res == 1)
		{
			//GAME
			Board b;
			bool playAgain = true;
			while (playAgain)
			{
				clearArray();
				//SETTING FONT COLOR
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
				cleanScreen();
				playAgain = b.game();
			}
			//thread th2(doKeys, &b);
			//th1.join();
			//th2.join();
		}
		else if (res == 2)
			return 0;
	}
	*/
	return 0;
}