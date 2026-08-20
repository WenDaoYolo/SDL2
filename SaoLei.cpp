#define _CRT_SECURE_NO_WARNINGS 1
#include "SaoLei.h"

void PrintMenu() {
	printf("=================================================\n");
	printf("  Menu：                                         \n");
	printf("                   1:开始游戏                     \n");
	printf("                   2:游戏规则                     \n");
	printf("                   3:退出游戏                     \n");
	printf("                                                 \n");
	printf("=================================================\n");
}

void Reboard(char board[ROW][COL],char flag) {
	int i = 0, j = 0;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			board[i][j] = flag;
}

void PrintBoard(char board[ROW][COL]){
	int i = 0, j = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);	//将控制台输出字符的颜色更改为绿色
	for (int k = (ROW - row) / 2 - 1; k <= row; k++)
		printf("%d ",k);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//将控制台输出字符的颜色还原为白色
	putchar('\n');
	for (i = (ROW - row)/2; i <=row; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);	//将控制台输出字符的颜色更改为绿色
		printf("%d ", i);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);	//将控制台输出字符的颜色还原为白色
		for (j =(COL-col)/2; j <=col; j++)
			printf("%c ", board[i][j]);
		putchar('\n');
	}
	printf("Mines:%d\n", MINES);
}

char GetMessageForMines(char real[ROW][COL],int PlayerX,int PlayerY) {
	int count=0,i=0,j=0;
	for(i=PlayerX-1;i<=PlayerX+1;i++)
		for (j = PlayerY-1; j <=PlayerY+1; j++)
		{
			if (real[i][j] == 'a')
				count++;
		}
	return count + '0';
}

void LayMines(char board[ROW][COL]) {
	int randX, randY;
	for(int count=0;count<MINES;count++)
	while (1) {
		randX = rand() % row + 1;
		randY = rand() % col + 1;
		if (board[randX][randY] == 'A')
		{
			board[randX][randY] = 'a';
			break;
		}
	}
}

 GAMESTATUS GetGameStatus(char real[ROW][COL],char show[ROW][COL],int x,int y) {
	 int i = 0,j = 0;
	 if (real[x][y] == 'a')
	 {
		 show[x][y] = 'x';
		 return GAMEOVER;
	 }
	 else
		 real[x][y] = 'N';

	 for(i=(ROW-row)/2;i<=row;i++)
		 for (j = (COL - col); j <= col; j++)
		 {
			 if (real[i][j] == 'A')
				 return CONTINUE;
		 }
	 return WIN;
}

