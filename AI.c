#include "chess.h"
#include "tree.h" 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>//INT_MIN表式负无穷，INT_MAX表示正无穷

int Limit1[13] = { 9,9,9,9,9,9,9,9,9,9,9,9,9 };
int Limit2[13] = { 9,9,9,9,9,8,8,8,8,8,8,8,8 };
int Limit3[13] = { 8,8,8,7,7,7,7,7,6,6,6,6,6 };
int(*Limit)[13];

#define SUM 10
#define CHENG_5_SCORE 500000000

//判断能否落子
int Whe_drop(int i, int j, int state) {
	if (Board[i][j] <= 9 && Board[i][j] > 0 && (AI_Whe_forbidden(i, j, state) == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}


//更新分值棋盘的分数
void UpdateV(int x, int y, int state) {
	int j;
	if (Board[x][y] > 9) {//棋盘上该点不为空
		Value_Board[x][y] = chess_score(x, y, state);
	}
	else {
		Value_Board[x][y] = 0;
	}

	for (j = -4;j < 5;j++) {
		if (j == 0) {
			continue;
		}
		if (x + j >= 0 && x + j < SIZE && Board[x + j][y]>9) {
			Value_Board[x + j][y] = chess_score(x + j, y, Board[x + j][y]);
		}
	}
	for (j = -4;j < 5;j++) {
		if (j == 0) {
			continue;
		}
		if (x + j >= 0 && x + j < SIZE && Board[x + j][y]>9) {
			Value_Board[x + j][y + j] = chess_score(x + j, y + j, Board[x + j][y]);
		}
	}
	for (j = -4;j < 5;j++) {
		if (j == 0) {
			continue;
		}
		if (x + j >= 0 && x + j < SIZE && Board[x + j][y]>9) {
			Value_Board[x][y + j] = chess_score(x, y + j, Board[x + j][y]);
		}
	}
	for (j = -4;j < 5;j++) {
		if (j == 0) {
			continue;
		}
		if (x + j >= 0 && x + j < SIZE && Board[x + j][y]>9) {
			Value_Board[x + j][y - j] = chess_score(x + j, y - j, Board[x + j][y]);
		}
	}
}


//alpha-beta剪枝 + Min_Max搜索
struct Node Min_Max(int alpha, int beta, int player, int dep, struct Tree_Node* nowNode) {
	struct Node ret = { -1,-1,INT_MIN };
	int cnt = 0;
	int _player;
	int value = 0;

	int Dir_X[8] = { 1,1,0,-1,-1,-1,0,1 };
	int Dir_Y[8] = { 0,1,1,1,0,-1,-1,-1 };

	if (player == WHITE) {
		_player = BLACK;
	}
	else if (player == BLACK) {
		_player = WHITE;
	}
	else {
		printf("error\n");
	}

	if (dep == 0) {
		int now = INT_MIN;
		for (int i = 0;i < SIZE;i++) {
			for (int j = 0;j < SIZE;j++) {
				int sum = 0;
				if (Board[i][j] > 0 && Board[i][j] <= 9) {//如果棋盘上点是空的，评估该位置分数
					value = Board[i][j];
					Board[i][j] = player;
					int My_score = chess_score(i, j, player);
					Board[i][j] = _player;
					int Op_score = chess_score(i, j, _player);
					Board[i][j] = value;
					sum = My_score + Op_score;//评估该位置分数
					/*
					排出价值最大的N个点
					*/
					if (cnt < SUM - 1) {
						cnt++;
						nowNode->son[cnt] = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
						memset(nowNode->son[cnt], 0, sizeof(struct Tree_Node));
						nowNode->son[cnt]->x = i;
						nowNode->son[cnt]->y = j;
						nowNode->son[cnt]->sum = sum;
						for (int i = cnt - 1;i >= 1;i--) {
							if ((nowNode->son[i]->sum) < (nowNode->son[i + 1]->sum)) {//如果大于直接交换
								struct Tree_Node* tmp = nowNode->son[i + 1];
								nowNode->son[i + 1] = nowNode->son[i];
								nowNode->son[i] = tmp;
							}
						}
					}
					else {
						if (nowNode->son[cnt]->sum < sum) {
							memset(nowNode->son[cnt], 0, sizeof(struct Tree_Node));
							nowNode->son[cnt]->x = i;
							nowNode->son[cnt]->y = j;
							nowNode->son[cnt]->sum = sum;
							for (int i = cnt - 1;i >= 1;i--) {//如果大于直接交换
								if ((nowNode->son[i]->sum) < (nowNode->son[i + 1]->sum)) {
									struct Tree_Node* tmp = nowNode->son[i + 1];
									nowNode->son[i + 1] = nowNode->son[i];
									nowNode->son[i] = tmp;
								}
							}
						}
					}
				}
			}
		}
		nowNode->cnt = cnt;


		if ((player == BLACK && (dep % 2 == 0)) || (player == WHITE && (dep % 2 == 1))) {//判断禁手
			for (int i = 1;i <= cnt;i++) {
				nowNode->son[i]->ban = AI_Whe_forbidden(nowNode->son[i]->x, nowNode->son[i]->y, BLACK);
			}
		}
		nowNode->flag = 1;//flag=1代表树节点构建完成


		int tot = 0;
		for (int i = 1;i <= nowNode->cnt;i++) {
			if (nowNode->son[i] == NULL) {
				continue;
			}
			++tot;
			if (tot > (*Limit)[DEPTH - dep]) {
				break;
			}
			if (((player == BLACK && (dep % 2 == 0)) || (player == WHITE && (dep % 2 == 1))) && nowNode->son[i]->ban) {
				continue;
			}

			int sum = 0;
			int x = nowNode->son[i]->x;
			int y = nowNode->son[i]->y;
			int now_player = (dep % 2 == 1) ? _player : player;
			int _now_player = (dep % 2 == 1) ? player : _player;
			int My_score = INT_MIN;
			int Op_score = INT_MIN;
			if (AI_Whe_chengwu(x, y, now_player)) {
				sum = CHENG_5_SCORE;
			}
			else {
				value = Board[x][y];
				Board[x][y] = now_player;
				UpdateV(x, y, now_player);
				for (int u = 0;u < SIZE;u++) {
					for (int v = 0;v < SIZE;v++) {
						if (Board[u][v] == now_player) {
							My_score = max(My_score, Value_Board[u][v]);
						}
						if (Board[u][v] == _now_player) {
							Op_score = max(Op_score, Value_Board[u][v]);
						}
					}
				}
				Board[x][y] = value;
				UpdateV(x, y, now_player);
				sum = My_score - ((now_player == WHITE && now_sum <= 2000) ? 4 : 1) * Op_score; //评分规则

			}
			if (sum > now) {
				now = sum;
				ret.x = x;
				ret.y = y;
				ret.sum = sum;
			}
		}
		return ret;
	}

	if (Count == 1 && dep == DEPTH) { //AI后手第一次评判
		for (int direction = 0;direction < 8;++direction) {
			int now_x = X + Dir_X[direction];
			int now_y = Y + Dir_Y[direction];
			if (now_x >= 0 && now_x < SIZE && now_y >= 0 && now_y < SIZE && Board[now_x][now_y] <= 9 && Board[now_x][now_y]>0) {
				cnt++;
				nowNode->son[cnt] = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
				memset(nowNode->son[cnt], 0, sizeof(struct Tree_Node));
				nowNode->son[cnt]->x = now_x;
				nowNode->son[cnt]->y = now_y;
			}
		}
		nowNode->cnt = cnt;
		nowNode->flag = 1;
	}

	else {
		if ((nowNode->flag) != 1) {
			int now_player = (dep % 2 == 1) ? _player : player;
			for (int i = 0;i < SIZE;i++) {
				for (int j = 0;j < SIZE;j++) {
					int sum = 0;
					if (Board[i][j] <= 9 && Board[i][j] > 0) {//如果棋盘上点是空的，评估该位置分数
						value = Board[i][j];
						Board[i][j] = player;
						int My_score = chess_score(i, j, player);
						Board[i][j] = _player;
						int Op_score = chess_score(i, j, _player);
						Board[i][j] = value;
						sum = My_score + Op_score; //评估该位置分数
						/*
						排出价值最大的N个点
						*/
						if (cnt < SUM - 1) {
							cnt++;
							nowNode->son[cnt] = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
							memset(nowNode->son[cnt], 0, sizeof(struct Tree_Node));
							nowNode->son[cnt]->x = i;
							nowNode->son[cnt]->y = j;
							nowNode->son[cnt]->sum = sum;
							for (int i = cnt - 1;i >= 1;i--) {//如果大于直接交换
								if ((nowNode->son[i]->sum) < (nowNode->son[i + 1]->sum)) {
									struct Tree_Node* tmp = nowNode->son[i + 1];
									nowNode->son[i + 1] = nowNode->son[i];
									nowNode->son[i] = tmp;
								}
							}
						}
						else {
							if (nowNode->son[cnt]->sum < sum) {
								memset(nowNode->son[cnt], 0, sizeof(struct Tree_Node));
								nowNode->son[cnt]->x = i;
								nowNode->son[cnt]->y = j;
								nowNode->son[cnt]->sum = sum;
								for (int i = cnt - 1;i >= 1;i--) {//如果大于直接交换
									if ((nowNode->son[i]->sum) < (nowNode->son[i + 1]->sum)) {
										struct Tree_Node* tmp = nowNode->son[i + 1];
										nowNode->son[i + 1] = nowNode->son[i];
										nowNode->son[i] = tmp;
									}
								}
							}
						}
					}
				}
			}
			nowNode->cnt = cnt;
			if ((player == BLACK && (dep % 2 == 0)) || (player == WHITE && (dep % 2 == 1))) {
				for (int i = 1;i <= cnt;i++) {
					nowNode->son[i]->ban = AI_Whe_forbidden(nowNode->son[i]->x, nowNode->son[i]->y, BLACK); //禁手判断
				}
			}
			nowNode->flag = 1;//flag=1代表树节点构建完成
		}
	}


	//alpha-beta剪枝 + Min_Max搜索
	if (dep % 2 == 1) {
		ret.sum = beta;
	}
	else ret.sum = alpha;

	int tot = 0;
	for (int i = 1;i <= nowNode->cnt;i++) {
		if (nowNode->son[i] == NULL) {
			continue;
		}
		++tot;
		if (tot > (*Limit)[DEPTH - dep]) {
			break;
		}
		int x = nowNode->son[i]->x;
		int y = nowNode->son[i]->y;
		if (((player == BLACK && (dep % 2 == 0)) || (player == WHITE && (dep % 2 == 1))) && nowNode->son[i]->ban) {
			continue;
		}

		if (dep % 2 == 0) {//max节点
			value = Board[x][y];
			Board[x][y] = player;
			UpdateV(x, y, player);
			if (AI_Whe_chengwu(x, y, player)) {// 如果五连不向下搜索
				ret.x = x;
				ret.y = y;
				ret.sum = CHENG_5_SCORE;
				alpha = CHENG_5_SCORE;
			}
			else {
				struct Node now = Min_Max(alpha, beta, player, dep - 1, nowNode->son[i]);
				if (now.sum > ret.sum) {
					ret.x = x;
					ret.y = y;
					ret.sum = now.sum;
					alpha = now.sum;
				}
				if (dep == DEPTH) {
					printf("%d%c sum=%d\n", 15 - x, (char)('A' + y), now.sum);
				}
			}
			Board[x][y] = value;
			UpdateV(x, y, player);
			if (beta <= alpha) {
				break;
			}
		}
		else {//min节点
			value = Board[x][y];
			Board[x][y] = _player;
			UpdateV(x, y, _player);
			if (AI_Whe_chengwu(x, y, _player)) {// 如果五连不向下搜索
				ret.x = x;
				ret.y = y;
				ret.sum = 0 - CHENG_5_SCORE;
				beta = 0 - CHENG_5_SCORE;
			}
			else {
				struct Node now = Min_Max(alpha, beta, player, dep - 1, nowNode->son[i]);
				if (now.sum < ret.sum) {
					ret.x = x;
					ret.y = y;
					ret.sum = now.sum;
					beta = now.sum;
				}
			}
			Board[x][y] = value;
			UpdateV(x, y, _player);
			if (beta <= alpha) {
				break;
			}
		}
	}
	return ret;
}


//释放tree节点
void Tree_DFS(struct Tree_Node* now) {//释放tree node
	if (now == NULL)return;
	for (int i = 1;i <= now->cnt;i++) {
		if (now->son[i] != NULL) {
			Tree_DFS(now->son[i]);
		}
	}
	free(now);
}
