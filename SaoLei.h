#include<stdio.h>
#include<windows.h>
#include<time.h>

#define row 9							    //展示大小
#define col 9
#define ROW row+2						    //实际大小
#define COL col+2
#define MINES 30						    //地雷个数
enum GAMESTATUS{CONTINUE,GAMEOVER,WIN};		//定义游戏状态

/*

棋盘符号
real :A-无雷 a-有雷  N-已排雷
show :*-未知 x-有雷  数字-已排雷

游戏状态
CONTINUE:继续
GAMEOVER:游戏失败
WIN:游戏胜利

*/

void PrintMenu();																				 //打印游戏菜单
void Reboard(char board[ROW][COL], char flag);													 //初始化棋盘
void PrintBoard(char board[ROW][COL]);															 //打印棋盘
char GetMessageForMines(char real[ROW][COL],int PlayerX,int PlayerY);							 //获取排雷信息
void LayMines(char board[ROW][COL]);															 //随机布雷
GAMESTATUS GetGameStatus(char real[ROW][COL],char show[ROW][COL],int x,int y);                   //获取游戏状态