#include "chess.h"
#include "tree.h" 
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>//INT_MIN表式负无穷，INT_MAX表示正无穷

int T = 0;//用于记时
extern int Limit1[13];
extern int Limit2[13];
extern int Limit3[13];
extern int(*Limit)[13];

int main(int argc, char* argv[]) {
	if (argc == 1) { //直接运行exe，没有参数
		char c, y = 'a';
		int x = 0;
		int state = BLACK;
		int gamemode = 1;
		int	Whe_right = 1;//判断DrawBoardArray是否因为格式问题而执行多次
		int winner = 0;
		int forbid = 0;//判断有无禁手

		InitBoardArray();
		DisplayBoard();

		printf("输入1进行人人对战，输入0进行人机对战\n");
		gamemode = getchar();

		while (gamemode != '0' && gamemode != '1') {
			printf("请输入正确的格式\n");
			while (getchar() != '\n');
			gamemode = getchar();
		}
		while (getchar() != '\n');

		if (gamemode == '1') {
			player_to_player();
		}
		else {
			computer_to_player();
		}

		return 0;
	}
	else if (argc == 2) { //运行exe，有参数（pvp代表人人对战，pvc代表人机对战）
		char c, y = 'a';
		int x = 0;
		int state = BLACK;
		int gamemode = 1;
		int	Whe_right = 1;//判断DrawBoardArray是否因为格式问题而执行多次
		int winner = 0;
		int forbid = 0;//判断有无禁手

		InitBoardArray();
		DisplayBoard();

		if (!strcmp(argv[1], "pvp") || !strcmp(argv[1], "PVP")) { //pvp代表人人对战
			player_to_player();
		}
		else if (!strcmp(argv[1], "pvc") || !strcmp(argv[1], "PVC")) { //pvc代表人机对战
			computer_to_player();
		}
		else { //参数错误
			printf("unknown command\n");
		}

		return 0;
	}
	else { //参数过多
		printf("unknown command: too many argument\n");
		return 0;
	}
}


void player_to_player() {
	char c, y = 'a';
	int x = 0;
	int state = BLACK;
	int	Whe_right = 1;//判断DrawBoardArray是否因为格式问题而执行多次
	int winner = 0;
	int forbid = 0;//判断有无禁手

	InitBoardArray();
	DisplayBoard();


	while (1) {
		Whe_right = DrawBoardArray(&y, &x, &state, 1);
		if (Whe_right == 1) {
			if (state == BLACK) {
				state = WHITE;  //如果是格式出错后再次输入则在此更新state
			}
			else if (state == WHITE) {
				state = BLACK;
			}
		}
		else if (Whe_right == -1) {
			if (Count > 0) {
				regret();//人人对战悔棋只悔一步，需要更新state
				if (state == BLACK) {
					state = WHITE;
				}
				else if (state == WHITE) {
					state = BLACK;
				}
				printf("悔棋成功\n");
				if (Count != 0) {
					printf("悔棋后上一步是: %s %d %c\n", (Count % 2 ? "black" : "white"), SIZE - Steps[Count - 1][0], (char)('A' + Steps[Count - 1][1]));
				}
			}
			else {
				printf("第一步无法悔棋\n");
			}
			continue;
		}

		if (y >= 'a' && y <= 'o') {  //更新Steps
			UpdateV(y - 'a', SIZE - x, (state == BLACK ? WHITE : BLACK));
			X = SIZE - x;
			Y = y - 'a';
			Steps[Count][0] = X;
			Steps[Count][1] = Y;
			Count++;
		}
		else {
			UpdateV(y - 'A', SIZE - x, (state == BLACK ? WHITE : BLACK));
			Count++;
			X = SIZE - x;
			Y = y - 'A';
			Steps[Count][0] = X;
			Steps[Count][1] = Y;
			Count++;
		}

		if (y >= 'a' && y <= 'o') {  //判断是否违反禁手
			forbid = Whe_forbidden(y - 'a', SIZE - x, state);
		}
		else {
			forbid = Whe_forbidden(y - 'A', SIZE - x, state);
		}
		if (forbid > 0) {
			printf("黑棋违反禁手，白棋获胜\n");
			getchar();
			break;
		}

		if (y >= 'a' && y <= 'o') {  //判断是否有胜利者产生
			winner = Whe_win(y - 'a', SIZE - x);
		}
		else {
			winner = Whe_win(y - 'A', SIZE - x);
		}
		if (winner == 1) {
			printf("黑棋获胜\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("白棋获胜\n");
			getchar();
			break;
		}


		if (Whe_full()) { //判断棋盘是否下满
			printf("棋盘已经下满，游戏平局\n");
			getchar();
			break;
		}
	}
}


void computer_to_player() {
	char c, y = 'a';
	int x = 0;
	int state = BLACK;
	int gamemode = 1;
	int	Whe_right = 1;//判断DrawBoardArray是否因为格式问题而执行多次
	int winner = 0;
	int forbid = 0;//判断有无禁手

	printf("输入1你先手，输入0你后手\n");

	InitBoardArray();
	Build_AC();
	score_init();

	int player;
	scanf("%d", &player);
	Limit = Limit3;

	if (player == 0) {//电脑先手的话，第一步先下H8
		Board[7][7] = BLACK;
		UpdateV(7, 7, state);
		X = 7;
		Y = 7;
		Steps[Count][0] = X;
		Steps[Count][1] = Y;
		DisplayBoard();
		state = WHITE;
		Count++;
	}
	else if (player == 1) {
		DisplayBoard();//玩家先手，给一个空白棋盘
	}

	struct Tree_Node* head;
	head = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
	memset(head, 0, sizeof(struct Tree_Node));

	while (1) {
		if (Count >= 4) {
			Limit = Limit1;
		}

		Whe_right = DrawBoardArray(&y, &x, &state, 1);
		if (Whe_right == 1) {
			if (state == BLACK) {
				state = WHITE;  //如果是格式出错后再次输入则在此更新state
			}
			else if (state == WHITE) {
				state = BLACK;
			}
		}
		else if (Whe_right == -1) {//返回-1代表需要悔棋
			if (Count > 1) {
				AI_regret();
				Tree_DFS(head);
				head = malloc(sizeof(struct Tree_Node));
				memset(head, 0, sizeof(struct Tree_Node));
				printf("悔棋成功\n");
				if (Count != 0) {
					printf("悔棋后上一步是: %s %d %c\n", (Count % 2 ? "black" : "white"), SIZE - Steps[Count - 1][0], (char)('A' + Steps[Count - 1][1]));
				}
			}
			else {
				printf("第一步无法悔棋\n");
			}
			continue;
		}

		if (y >= 'a' && y <= 'o') {  //更新Steps
			UpdateV(y - 'a', SIZE - x, (state == BLACK ? WHITE : BLACK));
			X = SIZE - x;
			Y = y - 'a';
			Steps[Count][0] = X;
			Steps[Count][1] = Y;
			Count++;
		}
		else {
			UpdateV(y - 'A', SIZE - x, (state == BLACK ? WHITE : BLACK));
			X = SIZE - x;
			Y = y - 'A';
			Steps[Count][0] = X;
			Steps[Count][1] = Y;
			Count++;
		}

		if (y >= 'a' && y <= 'o') {  //判断是否违反禁手
			forbid = Whe_forbidden(y - 'a', SIZE - x, state);
		}
		else {
			forbid = Whe_forbidden(y - 'A', SIZE - x, state);
		}
		if (forbid > 0) {
			printf("黑棋违反禁手，白棋获胜\n");
			getchar();
			break;
		}

		if (y >= 'a' && y <= 'o') {  //判断是否有胜利者产生
			winner = Whe_win(y - 'a', SIZE - x);
		}
		else {
			winner = Whe_win(y - 'A', SIZE - x);
		}
		if (winner == 1) {
			printf("黑棋获胜\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("白棋获胜\n");
			getchar();
			break;
		}

		if (Whe_full()) { //判断棋盘是否下满
			printf("棋盘已经下满，游戏平局\n");
			getchar();
			break;
		}


		int findson = 0;
		struct Tree_Node* temp = head;

		//如果找到子节点，直接把子节点赋值给head即可
		if (head->flag)
			for (int i = 1;i <= head->cnt;++i) {
				if (head->son[i] != NULL && head->son[i]->x == X && head->son[i]->y == Y) {
					temp = head->son[i];
					findson = 1;
				}
				else { // 否则直接释放搜索树所占的内存
					if (head->son[i] != NULL) {
						Tree_DFS(head->son[i]);
					}
				}
			}
		head = temp;
		//没找到子节点，建立一个新的树
		if (!findson) {
			head = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
			memset(head, 0, sizeof(struct Tree_Node));
		}


		T = clock(); //计时
		struct Node tmp;

		tmp = Min_Max(INT_MIN, INT_MAX, state, DEPTH, head);

		now_sum = tmp.sum;
		Board[tmp.x][tmp.y] = state -10;
		UpdateV(tmp.x, tmp.y, state);//更新steps
		X = tmp.x;
		Y = tmp.y;
		Steps[Count][0] = X;
		Steps[Count][1] = Y;
		Count++;

		temp = head;
		for (int i = 1;i <= head->cnt;++i) { //如果找到子节点，直接把子节点赋值给head即可
			if (head->son[i] != NULL && head->son[i]->x == tmp.x && head->son[i]->y == tmp.y) {
				temp = head->son[i];
				printf("success in\n");
			}
			else { // 释放其它子节点树的内存
				if (head->son[i] != NULL) {
					Tree_DFS(head->son[i]);
				}
			}
		}
		head = temp;

		DisplayBoard();
		printf("电脑落子: %d%c %dms\n", 15 - tmp.x, 'A' + tmp.y, (clock() - T) / 1000);
		Board[tmp.x][tmp.y] = state; //将棋盘次落子处的三角改成圆圈

		//判断胜利者
		winner = Whe_win(tmp.y, tmp.x);
		if (winner == 1) {
			printf("黑棋获胜\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("白棋获胜\n");
			getchar();
			break;
		}

		if (state == BLACK) {
			state = WHITE;  //在此更新state
		}
		else if (state == WHITE) {
			state = BLACK;
		}
	}
}