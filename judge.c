#include "chess.h"
#include <stdio.h>

//判断游戏是否有五子相连
int Whe_win(const char y, const int x) {
	int start_positionx, start_positiony;
	int b_score, w_score;
	b_score = w_score = 0;

	for (int i = 0;i < 5;i++) {  //横向判断
		start_positionx = x;
		start_positiony = y - i;
		if (start_positiony < 0 || start_positiony + 5>SIZE) {
			continue;
		}
		else {
			for (int j = 0;j < 5;j++) {
				if (Board[start_positionx][start_positiony + j] == BLACK || Board[start_positionx][start_positiony + j] == BLACKtem) {
					b_score++;
				}
				else if (Board[start_positionx][start_positiony + j] == WHITE || Board[start_positionx][start_positiony + j] == WHITEtem) {
					w_score++;
				}
			}

			if (b_score == 5) {
				return 1; //返回1代表黑棋赢
			}
			else if (w_score == 5) {
				return 2;  //返回2代表白棋赢
			}

			b_score = w_score = 0;
		}
	}


	for (int i = 0;i < 5;i++) { //竖向判断
		start_positionx = x - i;
		start_positiony = y;
		if (start_positionx < 0 || start_positionx + 5>SIZE) {
			continue;
		}
		else {
			for (int j = 0;j < 5;j++) {
				if (Board[start_positionx + j][start_positiony] == BLACK || Board[start_positionx + j][start_positiony] == BLACKtem) {
					b_score++;
				}
				else if (Board[start_positionx + j][start_positiony] == WHITE || Board[start_positionx + j][start_positiony] == WHITEtem) {
					w_score++;
				}
			}

			if (b_score == 5) {
				return 1;
			}
			else if (w_score == 5) {
				return 2;
			}

			b_score = w_score = 0;
		}
	}

	for (int i = 0;i < 5;i++) { //斜向判断1
		start_positionx = x - i;
		start_positiony = y - i;
		if (start_positionx < 0 || start_positionx + 5>SIZE || start_positiony < 0 || start_positiony + 5>SIZE) {
			continue;
		}
		else {
			for (int j = 0;j < 5;j++) {
				if (Board[start_positionx + j][start_positiony + j] == BLACK || Board[start_positionx + j][start_positiony + j] == BLACKtem) {
					b_score++;
				}
				else if (Board[start_positionx + j][start_positiony + j] == WHITE || Board[start_positionx + j][start_positiony + j] == WHITEtem) {
					w_score++;
				}
			}

			if (b_score == 5) {
				return 1;
			}
			else if (w_score == 5) {
				return 2;
			}

			b_score = w_score = 0;
		}
	}

	for (int i = 0;i < 5;i++) { //斜向判断2
		start_positionx = x - i;
		start_positiony = y + i;
		if (start_positionx < 0 || start_positionx + 5>SIZE || start_positiony - 4 < 0 || start_positiony >= SIZE) {
			continue;
		}
		else {
			for (int j = 0;j < 5;j++) {
				if (Board[start_positionx + j][start_positiony - j] == BLACK || Board[start_positionx + j][start_positiony - j] == BLACKtem) {
					b_score++;
				}
				else if (Board[start_positionx + j][start_positiony - j] == WHITE || Board[start_positionx + j][start_positiony - j] == WHITEtem) {
					w_score++;
				}
			}

			if (b_score == 5) {
				return 1;
			}
			else if (w_score == 5) {
				return 2;
			}

			b_score = w_score = 0;
		}
	}

	return 0; //返回0代表双方都没赢
}



//判断棋盘是否下满
int Whe_full() {
	for (int i = 0;i < SIZE;i++) {
		for (int j = 0;j < SIZE;j++) {
			if (Board[i][j] <= 9 && Board[i][j] > 0) {
				return 0;
			}
		}
	}

	return 1;
}



//判断禁手
int Whe_forbidden(const char y, const int x, int state) {
	int ad_black[8];//记录与x，y位置相邻的黑子数(数组的下标代表方向)
	int ad_empty[8];//记录ad_black后相邻的空位置数
	int gap_black[8];//记录ad_empty后相邻的黑子数
	int gap_empty[8];//记录与gap_black后相邻的空位置数
	int gap_gap_black[8];//记录gap_empty后相邻的黑子数
	if (state == BLACK) {
		return 0; //白棋不考虑(由于是在改变state后判断的，所以这里判断的是否为BLACK)
	}
	int i;
	for (i = 0;i < 8;i++) {
		ad_black[i] = ad_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
	}

	int _y, _x;

	//向下搜索(对于x，y的二阶矩阵)
	for (_y = y - 1;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, ad_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, ad_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, gap_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_gap_black[0]++);

	//右下搜索
	for (_y = y - 1, _x = x + 1;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, ad_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, ad_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, gap_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_gap_black[1]++);

	//向右搜索
	for (_x = x + 1; _x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, ad_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, ad_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, gap_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, gap_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x++, gap_gap_black[2]++);

	//右上搜索
	for (_y = y + 1, _x = x + 1;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, ad_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, ad_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, gap_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_gap_black[3]++);

	//向上搜索
	for (_y = y + 1;y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, ad_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, ad_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, gap_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_gap_black[4]++);

	//左上搜索
	for (_y = y + 1, _x = x - 1;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, ad_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, ad_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, gap_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_gap_black[5]++);

	//向左搜素
	for (_x = x - 1; _x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, ad_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, ad_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, gap_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, gap_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x--, gap_gap_black[6]++);

	//左下搜索
	for (_y = y - 1, _x = x - 1;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, ad_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, ad_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, gap_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_gap_black[7]++);

	//下面进行禁手分析
	int three_num = 0;
	int four_num = 0;
	int is_four, is_three;

	for (i = 0;i < 4;i++) { //如果有5子相连，禁手失效，直接返回0
		if (ad_black[i] + ad_black[i + 4] == 4) {
			return 0; //返回0代表不违反禁手
		}
	}

	//下面针对对于没有5子相连的情况
	for (i = 0;i < 4;i++) {
		if (ad_black[i] + ad_black[i + 4] >= 5) { //5子以上相连
			return 3;//返回3代表长连禁手
		}

		else if (ad_black[i] + ad_black[i + 4] == 3) { //4子相连
			is_four = 0;
			if (ad_empty[i] > 0) { // ?0000+?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					is_four = 1;
				}
			}
			if (ad_empty[i + 4] > 0) { // ?+0000?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					is_four = 1;
				}
			}

			if (is_four) {
				four_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 2) { //3子相连
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 1) { // ?000+0?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					four_num++;
				}
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1) {// ?0+000?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					four_num++;
				}
			}

			//活3检查
			is_three = 0;
			if ((ad_empty[i] > 2 || ad_empty[i] == 2 && gap_black[i] == 0) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+000++?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					is_three = 1;
				}
			}
			if ((ad_empty[i + 4] > 2 || ad_empty[i + 4] == 2 && gap_black[i + 4] == 0) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?++000+?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					is_three = 1;
				}
			}

			if (is_three) {
				three_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 1) { //2子相连
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 2) { // ?00+00?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					four_num++;
				}
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2) {// ?00+00?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					four_num++;
				}
			}

			//活3检查
			if (ad_empty[i] == 1 && gap_black[i] == 1 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+00+0+?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					three_num++;
				}
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+0+00+?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					three_num++;
				}
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 0) { //单独一个子
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 3) { // ?0+000?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					four_num++;
				}
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 3) {// ?000+0?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					four_num++;
				}
			}

			//活3检查
			if (ad_empty[i] == 1 && gap_black[i] == 2 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+0+00+?
				if (keypoint_forbidden(y, x, ad_black[i], i) == 0) {
					three_num++;
				}
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+00+0+?
				if (keypoint_forbidden(y, x, ad_black[i + 4], i + 4) == 0) {
					three_num++;
				}
			}
		}
	}

	//禁手判断结束
	if (four_num > 1) { //一个以上的活4或者冲4
		return 2;//返回2代表违反四四禁手
	}
	if (three_num > 1) { //一个以上的活3
		return 1; //返回1代表违反三三禁手
	}

	return 0; //返回0代表不违反禁手
}



//判断关键点是否为禁手(用于判断禁手时的递归)
int keypoint_forbidden(const char y, const int x, int ad_black, int direction) {  //判断关键点是否为禁手(用于判断禁手时的递归)
	int _x, _y;
	int value;

	ad_black++;
	//获取关键点坐标
	switch (direction) {
	case 0:
		_x = x;
		_y = y - ad_black;
		break;
	case 1:
		_x = x + ad_black;
		_y = y - ad_black;
		break;
	case 2:
		_x = x + ad_black;
		_y = y;
		break;
	case 3:
		_x = x + ad_black;
		_y = y + ad_black;
		break;
	case 4:
		_x = x;
		_y = y + ad_black;
		break;
	case 5:
		_x = x - ad_black;
		_y = y + ad_black;
		break;
	case 6:
		_x = x - ad_black;
		_y = y;
		break;
	case 7:
		_x = x - ad_black;
		_y = y - ad_black;
		break;
	default:
		printf("error\n");
		break;
	}

	//将关键点视为黑子
	value = Board[_x][_y];
	Board[_x][_y] = BLACK;

	//判断关键点是否为禁手
	int forbidden = Whe_forbidden(_y, _x, WHITE);

	//还原棋盘
	Board[_x][_y] = value;

	return forbidden;
}



//用于AI的禁手：用于降低复杂度
int AI_Whe_forbidden(const char x, const int y, int state) {
	int ad_black[8];//记录与x，y位置相邻的黑子数(数组的下标代表方向)
	int ad_empty[8];//记录ad_black后相邻的空位置数
	int gap_black[8];//记录ad_empty后相邻的黑子数
	int gap_empty[8];//记录与gap_black后相邻的空位置数
	int gap_gap_black[8];//记录gap_empty后相邻的黑子数
	if (state == WHITE) {
		return 0; //白棋不考虑(由于是在改变state后判断的，所以这里判断的是否为BLACK)
	}
	int i;
	for (i = 0;i < 8;i++) {
		ad_black[i] = ad_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
	}

	int _y, _x;

	//向下搜索(对于x，y的二阶矩阵)
	for (_y = y - 1;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, ad_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, ad_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, gap_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_gap_black[0]++);

	//右下搜索
	for (_y = y - 1, _x = x + 1;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, ad_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, ad_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, gap_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_gap_black[1]++);

	//向右搜索
	for (_x = x + 1; _x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, ad_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, ad_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, gap_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, gap_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x++, gap_gap_black[2]++);

	//右上搜索
	for (_y = y + 1, _x = x + 1;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, ad_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, ad_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, gap_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_gap_black[3]++);

	//向上搜索
	for (_y = y + 1;y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, ad_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, ad_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, gap_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_gap_black[4]++);

	//左上搜索
	for (_y = y + 1, _x = x - 1;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, ad_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, ad_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, gap_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_gap_black[5]++);

	//向左搜素
	for (_x = x - 1; _x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, ad_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, ad_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, gap_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, gap_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x--, gap_gap_black[6]++);

	//左下搜索
	for (_y = y - 1, _x = x - 1;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, ad_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, ad_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, gap_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_gap_black[7]++);

	//下面进行禁手分析
	int three_num = 0;
	int four_num = 0;
	int is_four, is_three;

	for (i = 0;i < 4;i++) { //如果有5子相连，禁手失效，直接返回0
		if (ad_black[i] + ad_black[i + 4] == 4) {
			return 0; //返回0代表不违反禁手
		}
	}

	//下面针对对于没有5子相连的情况
	for (i = 0;i < 4;i++) {
		if (ad_black[i] + ad_black[i + 4] >= 5) { //5子以上相连
			return 3;//返回3代表长连禁手
		}

		else if (ad_black[i] + ad_black[i + 4] == 3) { //4子相连
			is_four = 0;
			if (ad_empty[i] > 0) { // ?0000+?
				is_four = 1;
			}
			if (ad_empty[i + 4] > 0) { // ?+0000?
				is_four = 1;
			}

			if (is_four) {
				four_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 2) { //3子相连
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 1) { // ?000+0?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1) {// ?0+000?
				four_num++;
			}

			//活3检查
			is_three = 0;
			if ((ad_empty[i] > 2 || ad_empty[i] == 2 && gap_black[i] == 0) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+000++?
				is_three = 1;
			}
			if ((ad_empty[i + 4] > 2 || ad_empty[i + 4] == 2 && gap_black[i + 4] == 0) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?++000+?
				is_three = 1;
			}

			if (is_three) {
				three_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 1) { //2子相连
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 2) { // ?00+00?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2) {// ?00+00?
				four_num++;
			}

			//活3检查
			if (ad_empty[i] == 1 && gap_black[i] == 1 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+00+0+?
				three_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+0+00+?
				three_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 0) { //单独一个子
			//冲4、活4检查
			if (ad_empty[i] == 1 && gap_black[i] == 3) { // ?0+000?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 3) {// ?000+0?
				four_num++;
			}

			//活3检查
			if (ad_empty[i] == 1 && gap_black[i] == 2 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+0+00+?
				three_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+00+0+?
				three_num++;
			}
		}
	}

	//禁手判断结束
	if (four_num > 1) { //一个以上的活4或者冲4
		return 2;//返回2代表违反四四禁手
	}
	if (three_num > 1) { //一个以上的活3
		return 1; //返回1代表违反三三禁手
	}

	return 0; //返回0代表不违反禁手
}


int AI_Whe_chengwu(const int x, const int y, int now_player) {//用于AI的判断是否连成5的函数，用于降低复杂度
	int ad_black[8];//记录与x，y位置相邻的黑子数(数组的下标代表方向)
	int i;
	for (i = 0;i < 8;i++) {
		ad_black[i] = 0;
	}

	int _y, _x;

	for (_y = y - 1;_y >= 0 && (Board[x][_y] == now_player || Board[x][_y] == now_player - 10);_y--, ad_black[0]++);
	for (_y = y - 1, _x = x + 1;_y >= 0 && _x < 15 && (Board[_x][_y] == now_player || Board[_x][_y] == now_player - 10);_y--, _x++, ad_black[1]++);
	for (_x = x + 1; _x < 15 && (Board[_x][y] == now_player || Board[_x][y] == now_player - 10); _x++, ad_black[2]++);
	for (_y = y + 1, _x = x + 1;_y < 15 && _x < 15 && (Board[_x][_y] == now_player || Board[_x][_y] == now_player - 10);_y++, _x++, ad_black[3]++);
	for (_y = y + 1;y < 15 && (Board[x][_y] == now_player || Board[x][_y] == now_player - 10);_y++, ad_black[4]++);
	for (_y = y + 1, _x = x - 1;_y < 15 && _x >= 0 && (Board[_x][_y] == now_player || Board[_x][_y] == now_player - 10);_y++, _x--, ad_black[5]++);
	for (_x = x - 1; _x >= 0 && (Board[_x][y] == now_player || Board[_x][y] == now_player - 10); _x--, ad_black[6]++);
	for (_y = y - 1, _x = x - 1;_y >= 0 && _x >= 0 && (Board[_x][_y] == now_player || Board[_x][_y] == now_player - 10);_y--, _x--, ad_black[7]++);

	if (now_player == BLACK) {
		for (i = 0;i < 4;i++) { //对于黑子如果有5子相连，直接返回1
			if (ad_black[i] + ad_black[i + 4] == 4) {
				return 1;
			}
		}

		return 0;
	}
	else if (now_player == WHITE)
	{
		for (i = 0;i < 4;i++) { //对于白字如果有超过或等于5子相连，直接返回1
			if (ad_black[i] + ad_black[i + 4] >= 4) {
				return 1;
			}
		}

		return 0;
	}
}