#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int Temp_Board[SIZE][SIZE];

//初始化棋盘
void InitBoardArray()
{
	int j, i;

	Board[0][0] = 1;
	Board[0][SIZE - 1] = 2;
	Board[SIZE - 1][SIZE - 1] = 3;
	Board[SIZE - 1][0] = 4;

	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][0] = 5;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[0][i] = 6;
	}

	for (j = 1; j <= SIZE - 2; j++)
	{
		Board[j][SIZE - 1] = 7;
	}

	for (i = 1; i <= SIZE - 2; i++)
	{
		Board[SIZE - 1][i] = 8;
	}

	for (j = 1; j <= SIZE - 2; j++)
	{
		for (i = 1; i <= SIZE - 2; i++)
		{
			Board[j][i] = 9;
		}
	}
	memcpy(Temp_Board, Board, SIZE * SIZE * sizeof(int));
}


//显示棋盘
void DisplayBoard()
{
	int i, j;
	char line;
	char ary;

	system("cls");   //清屏

	for (j = 0, line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d", line);
		line -= 1;
		for (i = 0; i <= SIZE - 1; i++)
		{
			switch (Board[j][i])
			{
			case 1:
				printf("┏");
				break;

			case 2:
				printf("┓");
				break;

			case 3:
				printf("┛");
				break;

			case 4:
				printf("┗");
				break;

			case 5:
				printf("┠");
				break;

			case 6:
				printf("┯");
				break;

			case 7:
				printf("┨");
				break;

			case 8:
				printf("┷");
				break;

			case 9:
				printf("┼");
				break;

			case BLACKtem:      // 黑子上一步
				printf("▲");
				break;

			case WHITEtem:      //白子上一步
				printf("△");
				break;

			case BLACK:      //黑子通常
				printf("●");
				break;

			case WHITE:
				printf("○");  //白子通常
				break;
			}
			if (i == SIZE - 1)
			{
				printf("\n");
			}

		}
	}

	printf("   ");
	for (ary = 'A'; ary < 'A' + SIZE; ary++)
		printf("%c ", ary);

	printf("\n");
}



//判断是否落子
int can_chess(const char y, const int x) {
	if (Board[SIZE - x][y] <= 9 && Board[SIZE - x][y] > 0) {
		return 1;
	}
	else {
		return 0;
	}
}



//更新棋盘(输入)——支持“1A”、“A1”、“1a”、“a1”,以及接受合法的命令
int DrawBoardArray(char* p_y, int* p_x, int* p_state, int update) {
	if (update) {
		printf("输入下一步落子的位置(如'a1','1a','A1','1A') 或相关命令\n");
	}
	char c;
	while ((c = getchar()) == '\n');

	if (c == 'r' && (c = getchar() == 'e') && (c = getchar() == 'g') && (c = getchar() == 'r') && (c = getchar() == 'e') && (c = getchar() == 't')) {
		return -1;//返回-1代表需要悔棋
	}

	if (c == 'p' && (c = getchar() == 'r') && (c = getchar() == 'i') && (c = getchar() == 'n') && (c = getchar() == 't')) {
		print_steps();
		return (DrawBoardArray(p_y, p_x, p_state, 1));
	}

	if (c == 'q' && (c = getchar() == 'u') && (c = getchar() == 'i') && (c = getchar() == 't')) {
		getchar();
		printf("按下回车结束程序\n");
		getchar();
		exit(0);
		return;
	}

	if (c >= 'a' && c <= 'o') { //"a1"型输入
		*p_y = c;
		c = getchar();
		if (c > '0' && c <= '9') {
			*p_x = (int)(c - '0');
			c = getchar();
			if (*p_x == 1 && c >= '0' && c <= '5') {
				*p_x = (*p_x) * 10 + (int)(c - '0');
				if ((c = getchar()) != '\n') {
					while (getchar() != '\n');
					printf("输入不合法，请重新输入\n");
					int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
					if (return_value == -1) { //如果返回为-1，代表需要悔棋，否则返回1代表需要更新状态
						return -1;
					}
					else {
						return 1;
					}
				}
			}
			else if (c != '\n') {
				while (getchar() != '\n');
				printf("输入不合法，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) {
					return -1;
				}
				else {
					return 1;
				}
			}
		}
		else {
			if (c != '\n') {
				while (getchar() != '\n');
			}
			printf("输入不合法，请重新输入\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}

		if (can_chess(*p_y - 'a', *p_x)) {
			Board[SIZE - *p_x][*p_y - 'a'] = *p_state - 10;	//改变数组对应的数值
		}
		else {
			printf("这个位置已经落子，请重新输入\n");  //判断是否能落子
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}


	else if (c >= 'A' && c <= 'O') {  //"A1"型输入
		*p_y = c;
		c = getchar();
		if (c > '0' && c <= '9') {
			*p_x = (int)(c - '0');
			c = getchar();
			if (*p_x == 1 && c >= '0' && c <= '5') {
				*p_x = (*p_x) * 10 + (int)(c - '0');
				if ((c = getchar()) != '\n') {
					while (getchar() != '\n');
					printf("输入不合法，请重新输入\n");
					int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
					if (return_value == -1) { //如果返回为-1，代表需要悔棋，否则返回1代表需要更新状态
						return -1;
					}
					else {
						return 1;
					}
				}
			}
			else if (c != '\n') {
				while (getchar() != '\n');
				printf("输入不合法，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) {
					return -1;
				}
				else {
					return 1;
				}
			}
		}

		else {
			if (c != '\n') {
				while (getchar() != '\n');
			}
			printf("输入不合法，请重新输入\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}

		if (can_chess(*p_y - 'A', *p_x)) {
			Board[SIZE - *p_x][*p_y - 'A'] = *p_state - 10;
		}
		else {
			printf("这个位置已经落子，请重新输入\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}


	else if (c >= '1' && c <= '9') {
		*p_x = (int)(c - '0');
		c = getchar();
		if (*p_x == 1 && c >= '0' && c <= '5') {
			*p_x = (*p_x) * 10 + (int)(c - '0');
			scanf("%c", p_y);
		}
		else {
			*p_y = c;
		}
		if (*p_y == '\n') {
			printf("输入不合法，请重新输入\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
		if (*p_y >= 'A' && *p_y <= 'O') {  //"1A"型输入
			if ((c = getchar()) != '\n') {
				while (getchar() != '\n');
				printf("输入不合法，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) { //如果返回为-1，代表需要悔棋，否则返回1代表需要更新状态
					return -1;
				}
				else {
					return 1;
				}
			}
			if (can_chess(*p_y - 'A', *p_x)) {
				Board[SIZE - *p_x][*p_y - 'A'] = *p_state - 10;
			}
			else {
				printf("这个位置已经落子，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) {
					return -1;
				}
				else {
					return 1;
				}
			}
		}

		else if (*p_y >= 'a' && *p_y <= 'o') { //"1a"型输入
			if ((c = getchar()) != '\n') {
				while (getchar() != '\n');
				printf("输入不合法，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) { //如果返回为-1，代表需要悔棋，否则返回1代表需要更新状态
					return -1;
				}
				else {
					return 1;
				}
			}
			if (can_chess(*p_y - 'a', *p_x)) {
				Board[SIZE - *p_x][*p_y - 'a'] = *p_state - 10;
			}
			else {
				printf("这个位置已经落子，请重新输入\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) {
					return -1;
				}
				else {
					return 1;
				}
			}
		}
		else {
			while (getchar() != '\n');
			printf("输入不合法，请重新输入\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}
	else {
		if (c != '\n') {
			while (getchar() != '\n');
		}
		printf("输入不合法，请重新输入\n");
		int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
		if (return_value == -1) {
			return -1;
		}
		else {
			return 1;
		}
	}

	DisplayBoard();	//显示棋盘
	if (*p_y >= 'a' && *p_y <= 'o') {
		printf("最后落子:%c%d\n", *p_y, *p_x);
	}
	else {
		printf("最后落子:%c%d\n", (*p_y + 32), *p_x);
	}

	if (*p_y >= 'a' && *p_y <= 'o') {
		Board[SIZE - *p_x][*p_y - 'a'] = *p_state; //将棋盘上上次落子处的三角改成圆圈
	}
	else {
		Board[SIZE - *p_x][*p_y - 'A'] = *p_state;
	}

	if (update) {
		if (*p_state == BLACK) {
			*p_state = WHITE; //更新state
		}
		else if (*p_state == WHITE) {
			*p_state = BLACK;
		}
	}

	return 0;
}


//用于人机对战的悔棋函数
void AI_regret() { 
	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];
	UpdateV(Steps[Count][0], Steps[Count][1], 5);

	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];
	UpdateV(Steps[Count][0], Steps[Count][1], 5);

	DisplayBoard();
}


//用于人人对战的悔棋函数
void regret() {
	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];

	DisplayBoard();
}


//打印出每一步下的棋的位置
void print_steps() {
	for (int i = 0;i < Count;i++) {
		printf("%d. %s %d %c\n", (i + 1), ((i + 1) % 2 ? "black" : "white"), SIZE - Steps[i][0], (char)('A' + Steps[i][1]));
	}

	printf("successfully print\n");
}