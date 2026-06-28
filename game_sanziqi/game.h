//头文件站
#pragma once
#include<stdio.h>
#include<stdlib.h>//<-用上随机数需要的时间戳头文件
#include<time.h>//<-同理，如果要用随机数需要的头文件
//当我们使用定义常量时，可以更方便的修改
#define ROW 3
#define COL 3

//初始化棋盘
void InitBoard(char board[ROW][COL], int row, int col);//行row  列col

//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);

//玩家回合
void PlayerMove(char board[ROW][COL], int row, int col);

//电脑回合
//找空白的位置随机下
void ComputerMove(char board[ROW][COL], int row, int col);

//输赢判断，总共有四种状态：玩家赢(*)，电脑赢(#)，平局(q)，继续(C)
char Iswin(char board[ROW][COL], int row, int col);

