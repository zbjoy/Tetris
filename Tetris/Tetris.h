#pragma once
#include <vector>
#include <graphics.h>

#include "Block.h"

class Tetris
{
public:

	//���Ǵ�ɵ��:::::Tetris(int row, int cols, int left, int top, int blockSize);
	Tetris(int rows, int cols, int left, int top, int blockSize);
	void init();
	void play();


private:

	void keyEvent(); //�����û�����
	void updateWindow(); //��Ⱦ��Ϸ����

	//���ؾ�����һ�ε��øú����� ����˶��ٺ��루ms)
	//��һ�ε��øú���, ����0
	int getDelay(); 
	void drop();
	void clearLine();
	void moveLeftRight(int offset);

private:

	int delay; //��ʱʱ��
	bool update; //�Ƿ����

	std::vector<std::vector<int>> map;
	int rows;
	int cols;
	int leftMargin;
	int topMargin;
	int blockSize;
	
	IMAGE imgBg;

	Block* curBlock;
	Block* nextBlock; //Ԥ�淽��
	Block bakBlock; //���÷���  ��ǰ���齵������б�����һ���Ϸ�λ��
};

