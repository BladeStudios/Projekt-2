#pragma once
#include <string>
#include <iostream>
#include "block.h"
using namespace std;
using namespace sf;

class Board
{
public:
	void createBaseWindow(int maxx, int maxy);
	void write(string word, int posx, int posy);
	bool game();
	void copyx(int posy);
	void drawBoard(int maxx, int maxy);
	int getBlockType();
	int getRotation();
	bool collision(string dir, int posx, int posy);
	void setCursorPosition(int x, int y);
	void draw(char a, int x, int y);
	void keys(Block& bl, bool& spaceBlocked, bool& arrowDownBlocked, size_t& time, size_t sleepTime);
	bool check();
	void moveleft();
	void moveright();
	void cleanBoard();
	void writeScore(int sc, Text &text);
	void writeSpeed(int sp, Text &text);
	int countPoints();
	void deleteRows();
	bool isOver();
	void writeAndDraw(string word, int posx, int posy);
	void draw2(char a, int x, int y);
	bool drawResult(int sc);
	void drawNextBlock(int type, int rotation);
	void rotate(int type, int rot, Block &bl);
	bool canRorate(int type, int rot);
	int getMinX(int type, int rotation);
	int getMaxX(int type, int rotation);
	int getMaxY(int type, int rotation);
};