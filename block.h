#pragma once

class Block
{
public:
	Block();
	int getTile(int blockType, int rotation, int y, int x);
	int rotation;
	int blockType;
	void setRotation(int r);
	void setBlockType(int t);
};