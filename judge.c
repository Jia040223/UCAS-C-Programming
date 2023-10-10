#include "chess.h"
#include <stdio.h>

//�ж���Ϸ�Ƿ�����������
int Whe_win(const char y, const int x) {
	int start_positionx, start_positiony;
	int b_score, w_score;
	b_score = w_score = 0;

	for (int i = 0;i < 5;i++) {  //�����ж�
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
				return 1; //����1�������Ӯ
			}
			else if (w_score == 5) {
				return 2;  //����2�������Ӯ
			}

			b_score = w_score = 0;
		}
	}


	for (int i = 0;i < 5;i++) { //�����ж�
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

	for (int i = 0;i < 5;i++) { //б���ж�1
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

	for (int i = 0;i < 5;i++) { //б���ж�2
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

	return 0; //����0����˫����ûӮ
}



//�ж������Ƿ�����
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



//�жϽ���
int Whe_forbidden(const char y, const int x, int state) {
	int ad_black[8];//��¼��x��yλ�����ڵĺ�����(������±������)
	int ad_empty[8];//��¼ad_black�����ڵĿ�λ����
	int gap_black[8];//��¼ad_empty�����ڵĺ�����
	int gap_empty[8];//��¼��gap_black�����ڵĿ�λ����
	int gap_gap_black[8];//��¼gap_empty�����ڵĺ�����
	if (state == BLACK) {
		return 0; //���岻����(�������ڸı�state���жϵģ����������жϵ��Ƿ�ΪBLACK)
	}
	int i;
	for (i = 0;i < 8;i++) {
		ad_black[i] = ad_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
	}

	int _y, _x;

	//��������(����x��y�Ķ��׾���)
	for (_y = y - 1;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, ad_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, ad_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, gap_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_gap_black[0]++);

	//��������
	for (_y = y - 1, _x = x + 1;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, ad_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, ad_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, gap_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_gap_black[1]++);

	//��������
	for (_x = x + 1; _x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, ad_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, ad_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, gap_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, gap_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x++, gap_gap_black[2]++);

	//��������
	for (_y = y + 1, _x = x + 1;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, ad_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, ad_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, gap_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_gap_black[3]++);

	//��������
	for (_y = y + 1;y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, ad_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, ad_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, gap_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_gap_black[4]++);

	//��������
	for (_y = y + 1, _x = x - 1;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, ad_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, ad_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, gap_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_gap_black[5]++);

	//��������
	for (_x = x - 1; _x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, ad_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, ad_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, gap_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, gap_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x--, gap_gap_black[6]++);

	//��������
	for (_y = y - 1, _x = x - 1;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, ad_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, ad_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, gap_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_gap_black[7]++);

	//������н��ַ���
	int three_num = 0;
	int four_num = 0;
	int is_four, is_three;

	for (i = 0;i < 4;i++) { //�����5������������ʧЧ��ֱ�ӷ���0
		if (ad_black[i] + ad_black[i + 4] == 4) {
			return 0; //����0����Υ������
		}
	}

	//������Զ���û��5�����������
	for (i = 0;i < 4;i++) {
		if (ad_black[i] + ad_black[i + 4] >= 5) { //5����������
			return 3;//����3����������
		}

		else if (ad_black[i] + ad_black[i + 4] == 3) { //4������
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

		else if (ad_black[i] + ad_black[i + 4] == 2) { //3������
			//��4����4���
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

			//��3���
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

		else if (ad_black[i] + ad_black[i + 4] == 1) { //2������
			//��4����4���
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

			//��3���
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

		else if (ad_black[i] + ad_black[i + 4] == 0) { //����һ����
			//��4����4���
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

			//��3���
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

	//�����жϽ���
	if (four_num > 1) { //һ�����ϵĻ�4���߳�4
		return 2;//����2����Υ�����Ľ���
	}
	if (three_num > 1) { //һ�����ϵĻ�3
		return 1; //����1����Υ����������
	}

	return 0; //����0����Υ������
}



//�жϹؼ����Ƿ�Ϊ����(�����жϽ���ʱ�ĵݹ�)
int keypoint_forbidden(const char y, const int x, int ad_black, int direction) {  //�жϹؼ����Ƿ�Ϊ����(�����жϽ���ʱ�ĵݹ�)
	int _x, _y;
	int value;

	ad_black++;
	//��ȡ�ؼ�������
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

	//���ؼ�����Ϊ����
	value = Board[_x][_y];
	Board[_x][_y] = BLACK;

	//�жϹؼ����Ƿ�Ϊ����
	int forbidden = Whe_forbidden(_y, _x, WHITE);

	//��ԭ����
	Board[_x][_y] = value;

	return forbidden;
}



//����AI�Ľ��֣����ڽ��͸��Ӷ�
int AI_Whe_forbidden(const char x, const int y, int state) {
	int ad_black[8];//��¼��x��yλ�����ڵĺ�����(������±������)
	int ad_empty[8];//��¼ad_black�����ڵĿ�λ����
	int gap_black[8];//��¼ad_empty�����ڵĺ�����
	int gap_empty[8];//��¼��gap_black�����ڵĿ�λ����
	int gap_gap_black[8];//��¼gap_empty�����ڵĺ�����
	if (state == WHITE) {
		return 0; //���岻����(�������ڸı�state���жϵģ����������жϵ��Ƿ�ΪBLACK)
	}
	int i;
	for (i = 0;i < 8;i++) {
		ad_black[i] = ad_empty[i] = gap_black[i] = gap_empty[i] = gap_gap_black[i] = 0;
	}

	int _y, _x;

	//��������(����x��y�Ķ��׾���)
	for (_y = y - 1;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, ad_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, ad_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_black[0]++);
	for (;_y >= 0 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y--, gap_empty[0]++);
	for (;_y >= 0 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y--, gap_gap_black[0]++);

	//��������
	for (_y = y - 1, _x = x + 1;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, ad_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, ad_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_black[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x++, gap_empty[1]++);
	for (;_y >= 0 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x++, gap_gap_black[1]++);

	//��������
	for (_x = x + 1; _x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, ad_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, ad_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x++, gap_black[2]++);
	for (;_x < 15 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x++, gap_empty[2]++);
	for (;_x < 15 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x++, gap_gap_black[2]++);

	//��������
	for (_y = y + 1, _x = x + 1;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, ad_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, ad_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_black[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x++, gap_empty[3]++);
	for (;_y < 15 && _x < 15 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x++, gap_gap_black[3]++);

	//��������
	for (_y = y + 1;y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, ad_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, ad_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_black[4]++);
	for (;_y < 15 && (Board[x][_y] > 0 && Board[x][_y] <= 9);_y++, gap_empty[4]++);
	for (;_y < 15 && (Board[x][_y] == BLACK || Board[x][_y] == BLACKtem);_y++, gap_gap_black[4]++);

	//��������
	for (_y = y + 1, _x = x - 1;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, ad_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, ad_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_black[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y++, _x--, gap_empty[5]++);
	for (;_y < 15 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y++, _x--, gap_gap_black[5]++);

	//��������
	for (_x = x - 1; _x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, ad_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, ad_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem); _x--, gap_black[6]++);
	for (;_x >= 0 && (Board[_x][y] > 0 && Board[_x][y] <= 9); _x--, gap_empty[6]++);
	for (;_x >= 0 && (Board[_x][y] == BLACK || Board[_x][y] == BLACKtem);_x--, gap_gap_black[6]++);

	//��������
	for (_y = y - 1, _x = x - 1;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, ad_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, ad_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_black[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] > 0 && Board[_x][_y] <= 9);_y--, _x--, gap_empty[7]++);
	for (;_y >= 0 && _x >= 0 && (Board[_x][_y] == BLACK || Board[_x][_y] == BLACKtem);_y--, _x--, gap_gap_black[7]++);

	//������н��ַ���
	int three_num = 0;
	int four_num = 0;
	int is_four, is_three;

	for (i = 0;i < 4;i++) { //�����5������������ʧЧ��ֱ�ӷ���0
		if (ad_black[i] + ad_black[i + 4] == 4) {
			return 0; //����0����Υ������
		}
	}

	//������Զ���û��5�����������
	for (i = 0;i < 4;i++) {
		if (ad_black[i] + ad_black[i + 4] >= 5) { //5����������
			return 3;//����3����������
		}

		else if (ad_black[i] + ad_black[i + 4] == 3) { //4������
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

		else if (ad_black[i] + ad_black[i + 4] == 2) { //3������
			//��4����4���
			if (ad_empty[i] == 1 && gap_black[i] == 1) { // ?000+0?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1) {// ?0+000?
				four_num++;
			}

			//��3���
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

		else if (ad_black[i] + ad_black[i + 4] == 1) { //2������
			//��4����4���
			if (ad_empty[i] == 1 && gap_black[i] == 2) { // ?00+00?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2) {// ?00+00?
				four_num++;
			}

			//��3���
			if (ad_empty[i] == 1 && gap_black[i] == 1 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+00+0+?
				three_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 1 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+0+00+?
				three_num++;
			}
		}

		else if (ad_black[i] + ad_black[i + 4] == 0) { //����һ����
			//��4����4���
			if (ad_empty[i] == 1 && gap_black[i] == 3) { // ?0+000?
				four_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 3) {// ?000+0?
				four_num++;
			}

			//��3���
			if (ad_empty[i] == 1 && gap_black[i] == 2 && (gap_empty[i] > 1 || (gap_empty[i] == 1 || gap_gap_black[i] == 0)) && (ad_empty[i + 4] > 1 || ad_empty[i + 4] == 1 && gap_black[i + 4] == 0)) {// ?+0+00+?
				three_num++;
			}
			if (ad_empty[i + 4] == 1 && gap_black[i + 4] == 2 && (gap_empty[i + 4] > 1 || (gap_empty[i + 4] == 1 || gap_gap_black[i + 4] == 0)) && (ad_empty[i] > 1 || ad_empty[i] == 1 && gap_black[i] == 0)) {// ?+00+0+?
				three_num++;
			}
		}
	}

	//�����жϽ���
	if (four_num > 1) { //һ�����ϵĻ�4���߳�4
		return 2;//����2����Υ�����Ľ���
	}
	if (three_num > 1) { //һ�����ϵĻ�3
		return 1; //����1����Υ����������
	}

	return 0; //����0����Υ������
}


int AI_Whe_chengwu(const int x, const int y, int now_player) {//����AI���ж��Ƿ�����5�ĺ��������ڽ��͸��Ӷ�
	int ad_black[8];//��¼��x��yλ�����ڵĺ�����(������±������)
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
		for (i = 0;i < 4;i++) { //���ں��������5��������ֱ�ӷ���1
			if (ad_black[i] + ad_black[i + 4] == 4) {
				return 1;
			}
		}

		return 0;
	}
	else if (now_player == WHITE)
	{
		for (i = 0;i < 4;i++) { //���ڰ�������г��������5��������ֱ�ӷ���1
			if (ad_black[i] + ad_black[i + 4] >= 4) {
				return 1;
			}
		}

		return 0;
	}
}