#define _CRT_SECURE_NO_MARNINGS
#include "game.h"

//此区域负责模块处理

//棋盘初始化
void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			//将内容全部替换为空格
			board[i][j] = ' ';
		}
	}
}


//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//打印数据
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			//过滤一下，免得多打印一个
			if (j < col - 1) {
				printf("|");
			}
		}
		//注意格式
		printf("\n");
		//打印分割信息,与上面的逻辑一样
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("___");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}


//玩家下棋环节
void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;

	while (1)//塞一个死循环，一直到判断输赢为止
	{
		printf("玩家回合>\n");
		printf("请输入坐标:");
		scanf_s("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("该位置已被占用，请重新输入\n");
			}
		}
		else
		{
			printf("该输入不合法，请重新输入\n");
		}
	}
}

//电脑下棋环节，逻辑同理
void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑回合>\n");
	int x = 0;
	int y = 0;
	//生成随机值，注意两个特殊头文件和主函数内的srand函数
	//此时生成的已经是合法的范围,原来rand生成范围是0~32367，用rand%最大范围，可得标准的范围0~2
	while (1)
	{
		x = rand() % row;
		y = rand() % col;
		//判断是否为空坐标
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}
//是否为满判断
int Full(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
	return 1;
}

//输赢判断
char Iswin(char board[ROW][COL], int row, int col)
{
	//行判断,有时间我再来改一下，这硬编码改为双for循环
	int i = 0;
	int j = 0;
	while (1)
	{
		int n = 0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				if (board[i][j] != ' ' && board[i][0] == board[i][j])
					n++;
				if (n == row)
				{
					return board[i][j];
				}

			}
			n = 0;
		}
		break;

	}
	//列判断
	while (1)
	{
		int n = 0;
		for (j = 0; j < col; j++)
		{
			for (i = 0; i < row; i++)
			{
				if (board[i][j] != ' ' && board[0][j] == board[i][j])
					n++;
				if (n == row)
				{
					return board[i][j];
				}

			}
			n = 0;
		}
		break;

	}
	//对角线判断
	while (1)
	{
		int n = 0;
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				if (board[i][j] != ' ' && board[i][j] == board[1][1])
				{
					n++;
					break;
				}
			}
		}
		if (n == row)
		{
			return board[1][1];
		}
		break;
	}
	//平局
	if (Full(board, row, col))
	{
		return 'Q';
	}
	return 'C';
}