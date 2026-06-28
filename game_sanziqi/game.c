#define _CRT_SECURE_NO_MARNINGS
#include "game.h"//主动包含自己写的头文件，链接上去

//在开头写一下整个项目的基本逻辑：
//把每一个过程都分开进行判断，分别是：棋盘打印（每一次结束后进行），玩家回合，电脑回合
//输赢上有行，列，对角判断，分别对应：输，赢，平局
//该区域为主函数，用来调用各种函数
void menu()//棋盘打印区域
{
	printf("***************************************************\n");
	printf("*******************1. piay  0. exit****************\n");
	printf("***************************************************\n");
}
void game()//函数调用目录
{
	char ret = 0;
	char board[ROW][COL] = { 0 };
	//传入数组地址和行列数
	//将函数写在game.h中，可以随取随用的同时还方便
	//初始化棋盘函数
	InitBoard(board, ROW, COL);
	//不断地打印新的棋盘
	DisplayBoard(board, ROW, COL);
	//开始下棋
	while (1)//放一个死循环，反正后面判断输赢了会过去
	{
		//玩家回合
		PlayerMove(board, ROW, COL);
		//玩家是否继续判断，此时如果不为“c”则继续游戏
		ret = Iswin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);//把棋盘打印过去
		//电脑回合
		ComputerMove(board, ROW, COL);
		//电脑是否继续判断，逻辑同理
		ret = Iswin(board, ROW, COL);
		if (ret != 'C')
		{
			break;
		}
		DisplayBoard(board, ROW, COL);//同理

	}
	//输赢判断
	if (ret == '*')
	{
		printf("玩家胜利\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢了\n");
	}
	else
	{
		printf("平局\n");
	}
	//再打印一次棋盘，显示对局结果
	DisplayBoard(board, ROW, COL);
}
int main()
{
	srand((unsigned int)time(NULL));//生成随机的生成起点，这是一个重点
	//time函数不能传空指针，用NULL，生成一个时间戳，同时强制改为 int 类型\

	int input = 0;
	//使用do while 可以至少运行一次，把菜单打印出来
	//注意选择语句case使用的是“：（冒号）”而不是“；（分号）”
	do
	{
		menu();
		printf("请选择:");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			printf("三子棋\n");
			//封装一个game函数，这样就不会很累赘
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("该输入不合法\n");
			break;
		}
	} while (input);         //这里选择0时，则表示语句不成立，直接跳出
	return 0;
}
//该游戏已通过