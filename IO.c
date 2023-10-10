#include "chess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int Temp_Board[SIZE][SIZE];

//��ʼ������
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


//��ʾ����
void DisplayBoard()
{
	int i, j;
	char line;
	char ary;

	system("cls");   //����

	for (j = 0, line = 15; j <= SIZE - 1; j++)
	{
		printf("%2d", line);
		line -= 1;
		for (i = 0; i <= SIZE - 1; i++)
		{
			switch (Board[j][i])
			{
			case 1:
				printf("��");
				break;

			case 2:
				printf("��");
				break;

			case 3:
				printf("��");
				break;

			case 4:
				printf("��");
				break;

			case 5:
				printf("��");
				break;

			case 6:
				printf("��");
				break;

			case 7:
				printf("��");
				break;

			case 8:
				printf("��");
				break;

			case 9:
				printf("��");
				break;

			case BLACKtem:      // ������һ��
				printf("��");
				break;

			case WHITEtem:      //������һ��
				printf("��");
				break;

			case BLACK:      //����ͨ��
				printf("��");
				break;

			case WHITE:
				printf("��");  //����ͨ��
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



//�ж��Ƿ�����
int can_chess(const char y, const int x) {
	if (Board[SIZE - x][y] <= 9 && Board[SIZE - x][y] > 0) {
		return 1;
	}
	else {
		return 0;
	}
}



//��������(����)����֧�֡�1A������A1������1a������a1��,�Լ����ܺϷ�������
int DrawBoardArray(char* p_y, int* p_x, int* p_state, int update) {
	if (update) {
		printf("������һ�����ӵ�λ��(��'a1','1a','A1','1A') ���������\n");
	}
	char c;
	while ((c = getchar()) == '\n');

	if (c == 'r' && (c = getchar() == 'e') && (c = getchar() == 'g') && (c = getchar() == 'r') && (c = getchar() == 'e') && (c = getchar() == 't')) {
		return -1;//����-1������Ҫ����
	}

	if (c == 'p' && (c = getchar() == 'r') && (c = getchar() == 'i') && (c = getchar() == 'n') && (c = getchar() == 't')) {
		print_steps();
		return (DrawBoardArray(p_y, p_x, p_state, 1));
	}

	if (c == 'q' && (c = getchar() == 'u') && (c = getchar() == 'i') && (c = getchar() == 't')) {
		getchar();
		printf("���»س���������\n");
		getchar();
		exit(0);
		return;
	}

	if (c >= 'a' && c <= 'o') { //"a1"������
		*p_y = c;
		c = getchar();
		if (c > '0' && c <= '9') {
			*p_x = (int)(c - '0');
			c = getchar();
			if (*p_x == 1 && c >= '0' && c <= '5') {
				*p_x = (*p_x) * 10 + (int)(c - '0');
				if ((c = getchar()) != '\n') {
					while (getchar() != '\n');
					printf("���벻�Ϸ�������������\n");
					int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
					if (return_value == -1) { //�������Ϊ-1��������Ҫ���壬���򷵻�1������Ҫ����״̬
						return -1;
					}
					else {
						return 1;
					}
				}
			}
			else if (c != '\n') {
				while (getchar() != '\n');
				printf("���벻�Ϸ�������������\n");
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
			printf("���벻�Ϸ�������������\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}

		if (can_chess(*p_y - 'a', *p_x)) {
			Board[SIZE - *p_x][*p_y - 'a'] = *p_state - 10;	//�ı������Ӧ����ֵ
		}
		else {
			printf("���λ���Ѿ����ӣ�����������\n");  //�ж��Ƿ�������
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
	}


	else if (c >= 'A' && c <= 'O') {  //"A1"������
		*p_y = c;
		c = getchar();
		if (c > '0' && c <= '9') {
			*p_x = (int)(c - '0');
			c = getchar();
			if (*p_x == 1 && c >= '0' && c <= '5') {
				*p_x = (*p_x) * 10 + (int)(c - '0');
				if ((c = getchar()) != '\n') {
					while (getchar() != '\n');
					printf("���벻�Ϸ�������������\n");
					int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
					if (return_value == -1) { //�������Ϊ-1��������Ҫ���壬���򷵻�1������Ҫ����״̬
						return -1;
					}
					else {
						return 1;
					}
				}
			}
			else if (c != '\n') {
				while (getchar() != '\n');
				printf("���벻�Ϸ�������������\n");
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
			printf("���벻�Ϸ�������������\n");
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
			printf("���λ���Ѿ����ӣ�����������\n");
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
			printf("���벻�Ϸ�������������\n");
			int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
			if (return_value == -1) {
				return -1;
			}
			else {
				return 1;
			}
		}
		if (*p_y >= 'A' && *p_y <= 'O') {  //"1A"������
			if ((c = getchar()) != '\n') {
				while (getchar() != '\n');
				printf("���벻�Ϸ�������������\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) { //�������Ϊ-1��������Ҫ���壬���򷵻�1������Ҫ����״̬
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
				printf("���λ���Ѿ����ӣ�����������\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) {
					return -1;
				}
				else {
					return 1;
				}
			}
		}

		else if (*p_y >= 'a' && *p_y <= 'o') { //"1a"������
			if ((c = getchar()) != '\n') {
				while (getchar() != '\n');
				printf("���벻�Ϸ�������������\n");
				int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
				if (return_value == -1) { //�������Ϊ-1��������Ҫ���壬���򷵻�1������Ҫ����״̬
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
				printf("���λ���Ѿ����ӣ�����������\n");
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
			printf("���벻�Ϸ�������������\n");
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
		printf("���벻�Ϸ�������������\n");
		int return_value = (DrawBoardArray(p_y, p_x, p_state, 0));
		if (return_value == -1) {
			return -1;
		}
		else {
			return 1;
		}
	}

	DisplayBoard();	//��ʾ����
	if (*p_y >= 'a' && *p_y <= 'o') {
		printf("�������:%c%d\n", *p_y, *p_x);
	}
	else {
		printf("�������:%c%d\n", (*p_y + 32), *p_x);
	}

	if (*p_y >= 'a' && *p_y <= 'o') {
		Board[SIZE - *p_x][*p_y - 'a'] = *p_state; //���������ϴ����Ӵ������Ǹĳ�ԲȦ
	}
	else {
		Board[SIZE - *p_x][*p_y - 'A'] = *p_state;
	}

	if (update) {
		if (*p_state == BLACK) {
			*p_state = WHITE; //����state
		}
		else if (*p_state == WHITE) {
			*p_state = BLACK;
		}
	}

	return 0;
}


//�����˻���ս�Ļ��庯��
void AI_regret() { 
	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];
	UpdateV(Steps[Count][0], Steps[Count][1], 5);

	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];
	UpdateV(Steps[Count][0], Steps[Count][1], 5);

	DisplayBoard();
}


//�������˶�ս�Ļ��庯��
void regret() {
	Count--;
	Board[Steps[Count][0]][Steps[Count][1]] = Temp_Board[Steps[Count][0]][Steps[Count][1]];

	DisplayBoard();
}


//��ӡ��ÿһ���µ����λ��
void print_steps() {
	for (int i = 0;i < Count;i++) {
		printf("%d. %s %d %c\n", (i + 1), ((i + 1) % 2 ? "black" : "white"), SIZE - Steps[i][0], (char)('A' + Steps[i][1]));
	}

	printf("successfully print\n");
}