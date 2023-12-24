#include "Tetris.h"

#include <time.h>
#include <stdlib.h>

const int SPEED_NORMAL = 500; //ms
const int SPEED_QUICK = 50; //ms

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
	this->rows = rows;
	this->cols = cols;
	this->leftMargin = left;
	this->topMargin = top;
	this->blockSize = blockSize;

	for (int i = 0; i < rows; i++)
	{
		std::vector<int> mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}

	//imgBg;
}

void Tetris::init()
{
	delay = SPEED_NORMAL;

	// 配置随机种子
	srand((unsigned int)time(NULL));

	// 创建游戏窗口
	initgraph(938, 896);

	// 加载背景图片
	loadimage(&imgBg, "res/bg2.png");

	// 初始化游戏区中的数据  ************************************
	//char data[20][10];
	//for (int i = 0; i < rows; i++)
	//{
	//	for (int j = 0; j < cols; j++)
	//	{
	//		map[i][j] = 0;
	//	}
	//}
	for (std::vector<std::vector<int>>::iterator it = map.begin(); it != map.end(); it++)
	{
		for (std::vector<int>::iterator t = it->begin(); t != it->end(); t++)
		{
			*t = 0;
		}
	}


}

void Tetris::play()
{
	init();

	nextBlock = new Block;
	curBlock = nextBlock;
	nextBlock = new Block;

	int timer = 0;
	while (1)
	{
		//接收用户输入
		keyEvent();

		timer += getDelay();
		if (timer >= delay)
		{
			timer = 0;
			drop();
			update = true; //是否更新
		}

		if (update)
		{
			update = false;

			//渲染游戏画面
			updateWindow();

			//更新游戏数据
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{

}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg); //绘制背景图片

	IMAGE** imgs = Block::getImage();

	BeginBatchDraw();
	/*for (std::vector<std::vector<int>>::iterator it = map.begin(), int i = 0; it != map.end() && i < rows; it++, i++)
	{
		for (std::vector<int>::iterator t = it->begin(), int j = 0; t != it->end() && j < cols; t++, j++)
		{
			if (*t == 0)
			{
				continue;
			}
			else
			{
				int x = leftMargin + j * blockSize;
				int y = topMargin + i * blockSize;
				putimage(x, y, imgs[(*t) - 1]);
			}
		}
	}*/

	for (int i = 0; i < rows; i++)
	{
		for ( int j = 0; j < cols; j++)
		{
			if (map[i][j] == 0)
			{
				continue;
			}
			else
			{
				int x = leftMargin + j * blockSize;
				int y = topMargin + i * blockSize;
				putimage(x, y, imgs[map[i][j] - 1]);
			}
		}
	}

	//测试方块
	//Block block;
	//block.draw(leftMargin, topMargin);

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);

	EndBatchDraw();
}

// 第一次调用返回0, 之后返回距离上一次调用间隔了多少毫秒
int Tetris::getDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();

	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void Tetris::drop()
{
	bakBlock = *curBlock;
	curBlock->drop();

	if (!curBlock->blockInMap(map))
	{
		//把这个方块固化
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}
}

void Tetris::clearLine()
{
}
