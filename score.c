#include "chess.h"
#define MAXLEN 10000 
#define CHENG_5_SCORE 5000000
#define HUO_4_SCORE 100000
#define CHONG_4_SCORE 10000
#define DAN_HUO_3_SCORE 8000
#define TIAO_HUO_3_SCORE 7000
#define MIAN_3_SCORE 100
#define HUO_2_SCORE 60
#define MIAN_2_SCORE 10

int SCORE_TABLE[262144]; //分数表：设置为18bit方便进行位操作而减少运行时间
extern struct AC T1[1001], T2[1001], T3[1001], T4[1001], T5[1001], T6[1001], T7[1001], T8[1001];

//对棋子分数评估
int chess_score(int x, int y, int state) {
	int j, k;
	int _state;
	int ret = 0;
	char s[10];

	if (state == WHITE)
		_state = BLACK;
	else
		_state = WHITE;

	for (j = -4, k = 0;j < 5;j++) {
		if (x + j >= 0 && x + j < SIZE) {
			s[k++] = Board[x + j][y];
		}
		else {
			s[k++] = _state;
		}
	}
	s[k] = '\0';
	ret += get_val(s, state);

	for (j = -4, k = 0;j < 5;j++) {
		if (y + j >= 0 && y + j < SIZE) {
			s[k++] = Board[x][y + j];
		}
		else {
			s[k++] = _state;
		}
	}
	s[k] = '\0';
	ret += get_val(s, state);

	for (j = -4, k = 0;j < 5;j++) {
		if (x + j >= 0 && x + j < SIZE && y + j >= 0 && y + j < SIZE) {
			s[k++] = Board[x + j][y + j];
		}
		else {
			s[k++] = _state;
		}
	}
	s[k] = '\0';
	ret += get_val(s, state);

	for (j = -4, k = 0;j < 5;j++) {
		if (x + j >= 0 && x + j < SIZE && y - j >= 0 && y - j < SIZE) {
			s[k++] = Board[x + j][y - j];
		}
		else {
			s[k++] = _state;
		}
	}
	s[k] = '\0';
	ret += get_val(s, state);

	return ret;
}


int get_val(char* s, int state) { // 直接查分数表，降低复杂度
	int index = 0;

	if (state == BLACK) {
		for (int i = 0;s[i] != '\0';i++) {
			if (s[i] > 0 && s[i] <= 9) {
				index |= 0; //位操作加快运行时间
				index <<= 2;
			}
			else if (s[i] == BLACK || s[i] == BLACKtem) {
				index |= 1;
				index <<= 2;
			}
			else {
				index |= 2;
				index <<= 2;
			}
		}
		index >>= 2;
	}

	if (state == WHITE) {
		for (int i = 0;s[i] != '\0';i++) {
			if (s[i] > 0 && s[i] <= 9) {
				index |= 0; //位操作加快运行时间
				index <<= 2;
			}
			else if (s[i] == WHITE || s[i] == WHITEtem) {
				index |= 1;
				index <<= 2;
			}
			else {
				index |= 2;
				index <<= 2;
			}
		}
		index >>= 2;
	}

	return SCORE_TABLE[index];

}


//对棋子的分数评估
int score(int x, int y, int state) {
	int _state;
	int score;
	int nowx, nowy;
	score = 0;
	nowx = nowy = 0;
	int Dir_X[8] = { 1,1,0,-1,-1,-1,0,1 };
	int Dir_Y[8] = { 0,1,1,1,0,-1,-1,-1 };

	if (state == WHITE)
		_state = BLACK;
	else
		_state = WHITE;

	for (int dir = 0;dir < 4;dir++) {
		for (int i = -4;i < 5;i++) {
			nowx = x + Dir_X[dir] * i;
			nowx = y + Dir_X[dir] * i;
			score += chess_score(nowx, nowy, state);
		}
	}

	return score;
}


// 分数表的初始化
void score_init(void) { 
	for (int i = 0;i <= 262143;i++) {
		int x = i;
		char s[10];
		int flag = 1;
		for (int i = 0;i < 9;++i) {
			int now = x & 3;
			if (now == 3)flag = 0;
			x >>= 2;
		}
		if (flag == 0)continue;
		x = i;
		for (int i = 0;i < 9;++i) {
			int now = x & 3;
			if (now == 0)s[i] = '0';
			if (now == 1)s[i] = '1';
			if (now == 2)s[i] = '2';
			x >>= 2; //位操作加快运行时间
		}
		s[9] = '\0';
		SCORE_TABLE[i] = value_init(s);
	}
}


//用于score_init，用AC自动机进行多模式匹配
int value_init(char s[]) { 
	int ret = 0;

	if (quary(s, T8)) {
		ret += MIAN_2_SCORE;
	}
	if (quary(s, T7)) {
		ret += HUO_2_SCORE;
	}
	if (quary(s, T6)) {
		ret += MIAN_3_SCORE;
	}
	if (quary(s, T5)) {
		ret += TIAO_HUO_3_SCORE;
	}
	if (quary(s, T4)) {
		ret += DAN_HUO_3_SCORE;
	}
	if (quary(s, T3)) {
		ret += CHONG_4_SCORE;
	}
	if (quary(s, T2)) {
		ret += HUO_4_SCORE;
	}
	if (quary(s, T1)) {
		ret += CHENG_5_SCORE;
	}

	return ret;
}
