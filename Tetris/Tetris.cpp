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

	// �����������
	srand((unsigned int)time(NULL));

	// ������Ϸ����
	initgraph(938, 896);

	// ���ر���ͼƬ
	loadimage(&imgBg, "res/bg2.png");

	// ��ʼ����Ϸ���е�����  ************************************
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
		//�����û�����
		keyEvent();

		timer += getDelay();
		if (timer >= delay)
		{
			timer = 0;
			drop();
			update = true; //�Ƿ����
		}

		if (update)
		{
			update = false;

			//��Ⱦ��Ϸ����
			updateWindow();

			//������Ϸ����
			clearLine();
		}
	}
}

void Tetris::keyEvent()
{

}

void Tetris::updateWindow()
{
	putimage(0, 0, &imgBg); //���Ʊ���ͼƬ

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

	//���Է���
	//Block block;
	//block.draw(leftMargin, topMargin);

	curBlock->draw(leftMargin, topMargin);
	nextBlock->draw(689, 150);

	EndBatchDraw();
}

// ��һ�ε��÷���0, ֮�󷵻ؾ�����һ�ε��ü���˶��ٺ���
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
		//���������̻�
		bakBlock.solidify(map);
		delete curBlock;
		curBlock = nextBlock;
		nextBlock = new Block;
	}
}

void Tetris::clearLine()
{
}