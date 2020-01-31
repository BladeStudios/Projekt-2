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

int drawMainMenu()
{
	RenderWindow window(VideoMode(690, 540), "Tetris");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	Texture mainmenu;
	mainmenu.loadFromFile("mainmenu.png");
	Texture button;
	button.loadFromFile("button-bg.png");

	Font font;
	font.loadFromFile("Arial.ttf");

	Text playGame, quit;

	playGame.setFont(font);
	playGame.setFillColor(Color::Red);
	playGame.setString("PLAY GAME");
	playGame.setPosition(260, 250);

	quit.setFont(font);
	quit.setFillColor(Color::White);
	quit.setString("QUIT");
	quit.setPosition(310, 340);

	Sprite sMenu(mainmenu);
	Sprite button1(button);
	Sprite button2(button);

	button1.setPosition(240, 240);
	button2.setPosition(240, 330);

	bool playOption = true;
	bool quitOption = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Down || event.key.code == Keyboard::Up))
			{
				if (quitOption)
				{
					playOption = true;
					quitOption = false;
					playGame.setFillColor(Color::Red);
					quit.setFillColor(Color::White);
				}
				else if (playOption)
				{
					playOption = false;
					quitOption = true;
					playGame.setFillColor(Color::White);
					quit.setFillColor(Color::Red);
				}
			}
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter)
			{
				if (playOption)
					return 1;
				else //quitOption
					return 2;
			}
			if (event.type == Event::MouseMoved)
			{
				if ((Mouse::getPosition(window).x >= button1.getPosition().x) && (Mouse::getPosition(window).x <= button1.getPosition().x + 210)
					&& (Mouse::getPosition(window).y >= button1.getPosition().y) && (Mouse::getPosition(window).y <= button1.getPosition().y + 60)) //playOption
				{
					playOption = true;
					quitOption = false;
					playGame.setFillColor(Color::Red);
					quit.setFillColor(Color::White);
				}
				else if ((Mouse::getPosition(window).x >= button2.getPosition().x) && (Mouse::getPosition(window).x <= button2.getPosition().x + 210)
					&& (Mouse::getPosition(window).y >= button2.getPosition().y) && (Mouse::getPosition(window).y <= button2.getPosition().y + 60)) //playOption
				{
					playOption = false;
					quitOption = true;
					playGame.setFillColor(Color::White);
					quit.setFillColor(Color::Red);
				}
			}
			if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
			{
				if ((Mouse::getPosition(window).x >= button1.getPosition().x) && (Mouse::getPosition(window).x <= button1.getPosition().x + 210)
					&& (Mouse::getPosition(window).y >= button1.getPosition().y) && (Mouse::getPosition(window).y <= button1.getPosition().y + 60)) //playOption
					return 1;
				else if ((Mouse::getPosition(window).x >= button2.getPosition().x) && (Mouse::getPosition(window).x <= button2.getPosition().x + 210)
					&& (Mouse::getPosition(window).y >= button2.getPosition().y) && (Mouse::getPosition(window).y <= button2.getPosition().y + 60)) //playOption
					return 2;
			}

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
*/
}
/*
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

	
	while (1)
	{
		//cleanScreen();
		int res = drawMainMenu();
		if (res == 1)
		{
			//GAME
			Board b;
			bool playAgain = true;
			while (playAgain)
			{
				//clearArray();
				//cleanScreen();
				playAgain = b.game();
			}
		}
		else if (res == 2)
			return 0;
	}
	
	return 0;
}