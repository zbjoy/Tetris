#pragma once
#include <vector>
#include <graphics.h>

#include "Block.h"

class Tetris
{
public:

	//我是大傻子:::::Tetris(int row, int cols, int left, int top, int blockSize);
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();


private:

	void keyEvent(); //接收用户输入
	void updateWindow(); //渲染游戏画面

	//返回距离上一次调用该函数， 间隔了多少毫秒（ms)
	//第一次调用该函数, 返回0
	int getDelay(); 
	void drop();
	void clearLine();
	void moveLeftRight(int offset);

private:

	int delay; //延时时间
	bool update; //是否更新

	std::vector<std::vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //预告方块
	Block bakBlock; //备用方块  当前方块降落过程中备份上一个合法位置
};

