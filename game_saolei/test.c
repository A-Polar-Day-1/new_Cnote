#define _CRT_SECURE_NO_MARNING
#include"game.h"

//该区域负责函数实现

//初始化格子，用set而不用具体的符号
void Initboard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int count = 0;
	int count_0 = 0;
	for (count = 0; count < rows; count++)
	{
		for (count_0 = 0; count_0 < cols; count_0++)
		{
			board[count][count_0] = set;
		}
	}
}

//格子打印
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int count = 0;
	int count_0 = 0;
	printf("-------------------------------------------------\n");
	for (count_0 = 0; count_0 <= col; count_0++)//列的提示打印,注意初始化为0这样就能做到坐标提示
	{
		printf("%d ", count_0);
	}
	printf("\n");
	for (count = 1; count <= row; count++)
	{
		printf("%d ", count);//行的提示打印
		for (count_0 = 1; count_0 <= col; count_0++)
		{
			printf("%c ", board[count][count_0]);

		}
		printf("\n");
	}
	printf("-------------------------------------------------\n");
}

//雷设置
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int count = 0;
	//横纵坐标范围是1~9
	//设置随机数的起点

	while (1)//当所有的雷布置结束后跳出循环
	{
		int x = rand() % row + 1;//rand（）%row之后的余数在0~8，需要再加上1，这时候就设置好了横坐标
		int y = rand() % col + 1;//设置纵坐标

		//设置完坐标后开始判断
		//我在这里进行了一点点优化，直接判断最后的个数可以有效限制10个雷，不会多放或者少放
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count++;
		}
		if (count == EASY_COUNT)
		{
			break;
		}
	}
}

//雷统计
int Get_mine_count(char board[ROWS][COLS], int x, int y, int count)
{
	int X = 0;
	int Y = 0;
	//可以使用ASCII码来进行快速判断，这样可以更节省空间和时间
	//因为'1'的ASCII码为49，'0'的ASCII码为48，所以用两个来分别减去'0'，就得到了整形1和0
	//实际上，由于我们只统计有1的个数，所以即使把x,y塞进去也没有问题，x,y一定是0，所以不用设置跳过

	for (X = x - 1; X <= x + 1; X++)
	{
		for (Y = y - 1; Y <= y + 1; Y++)
		{
			if (board[X][Y] - '0' == 1)
			{
				count++;
			}
		}
	}
	//这里仅做对于ASCII码的操作示范，其实可以不用这么麻烦
	//如果要更小的空间复杂度和时间复杂度，可以直接把八个循环放上去，对于小判断来说，直接写的复杂度低
	return count;
}


//雷标记
void MarkMine(char show[ROWS][COLS], int x, int y)
{
	show[x][y] = '%';
	DisplayBoard(show, ROW, COL);
	//在插入标记后，由于插入标记本身只是显示，不进行操作，所以会让函数又来一次，让我们选择标记或排查
	//因此需要一个开头的提示
	printf("请选择排查或标记\n");
}
//空白处统计（胜利条件）
int Speace(char show[ROWS][COLS], int row, int col)
{
	int count = 0;
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j++) {
			if (show[i][j] == '*')
				count++;
		}
	}
	return count;
}

//空白处展开
void ControlSpeace(char mine[ROWS][COLS], char show[ROWS][COLS], char visited[ROWS][COLS], int x, int y, int row , int col )
{
	//先进行边界排查
	if (x < 1 || x > row || y < 1 || y > col) return;  //超出范围
	if (visited[x][y] == '1') return;                    //出现已访问区域
	if (show[x][y] != '*') return;   // 已揭开（可选，与visited重复保护）

	//注意标记去过的格子
	visited[x][y] = '1';


	//统计周围
	int mineCount = Get_mine_count(mine, x, y, 0);

	if (mineCount == 0)
		show[x][y] = ' ';              // 空白，显示空格
	else
		show[x][y] = '0' + mineCount;  // 数字，显示对应字符

	//确认可以用
	if (mineCount == 0) {
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				if (dx == 0 && dy == 0) continue;
				ControlSpeace(mine, show, visited, x + dx, y + dy, row, col);
			}
		}
	}
}

//雷判断

void Findmine(char mine[ROWS][COLS], char show[ROWS][COLS], char visited[ROWS][COLS] , int row, int col)
{
	int count = 0;
	int x = 0;
	int y = 0;
	int input = 1;
	//初始化
	Initboard(visited, ROWS, COLS, '0');

	while (1)
	{
		//该模块用于选择操作
		do {
			printf("请选择 1:输入坐标或 2:进行标记\n");
			scanf_s("%d", &input);
			switch (input)
			{
			case 1://排查
				printf("请输入排查的坐标\n");
				scanf_s("%d%d", &x, &y);
				//排重

				if (show[x][y] != '*' && show[x][y] != '%')
				{
					printf("输入了重复坐标，请重新输入\n");
					input = 1;
					continue;
				}
				input = 0;
				break;
			case 2://标记
				printf("请输入标记的坐标\n");
				scanf_s("%d%d", &x, &y);
				//排重
				if (show[x][y] != '*' && show[x][y] != '%')
				{
					printf("输入了重复坐标，请重新输入\n");
					input = 1;
					continue;
				}
				MarkMine(show, x, y);
				input = 1;
				break;
			default://错误选择
				printf("输入错误，请重新输入\n");
				input = 1;
				break;
			}
		} while (input);
		if (x >= 1 && y >= 1 && x <= ROWS && y <= COLS)
		{
			//如果是雷的判断
			if (mine[x][y] == '1')
			{
				printf("该区域为雷区，游戏结束\n");
				//在显示失败后，再把棋盘打印一下.这个直接把函数拿过来就可以打印了
				DisplayBoard(mine, ROW, COL);
				break;
			}
			//如果不是的判断
			else
			{
				//进入展开函数,它将同时负责展开+雷计数
				ControlSpeace(mine, show, visited , x, y, row,col);
				DisplayBoard(show, ROW, COL);
				//进入空白处判断
				if (Speace(show, row, col) == EASY_COUNT)
				{
					printf("通关！\n");
					DisplayBoard(mine, ROW, COL);
					break;
				}
			}
		}
		else
		{
			printf("该输入不合法，请重新输入\n");
		}
	}
}