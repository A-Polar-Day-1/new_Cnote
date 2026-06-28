#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//这里我们在创建格子的时候，要注意把操作格和实际格都同时创建

//难度调整
#define EASY_COUNT 5
#define NOMAL 10
#define HARD 15

//操作格
#define ROW 9
#define COL 9

//实际格
//注意创建的时候直接加2，可以在上面进行直接i需改而不用重复修改
#define ROWS ROW+2
#define COLS COL+2

//初始化，注意我们这里多进入一个参数，在后期函数实现的时候能直接调用需要的符号
void Initboard(char board[ROWS][COLS], int rows, int cols, char set);

//格子打印
//无论在失败还是继续游戏时，都要打印一次
void DisplayBoard(char board[ROWS][COLS],int row, int col);

//雷设置
void SetMine(char board[ROWS][COLS], int row, int col);

//雷统计与判断
void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], char visited[ROWS][COLS] ,int row, int col);
