#include "chess.h"
#include "tree.h" 
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>//INT_MIN��ʽ�����INT_MAX��ʾ������

int T = 0;//���ڼ�ʱ
extern int Limit1[13];
extern int Limit2[13];
extern int Limit3[13];
extern int(*Limit)[13];

int main(int argc, char* argv[]) {
	if (argc == 1) { //ֱ������exe��û�в���
		char c, y = 'a';
		int x = 0;
		int state = BLACK;
		int gamemode = 1;
		int	Whe_right = 1;//�ж�DrawBoardArray�Ƿ���Ϊ��ʽ�����ִ�ж��
		int winner = 0;
		int forbid = 0;//�ж����޽���

		InitBoardArray();
		DisplayBoard();

		printf("����1�������˶�ս������0�����˻���ս\n");
		gamemode = getchar();

		while (gamemode != '0' && gamemode != '1') {
			printf("��������ȷ�ĸ�ʽ\n");
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
	else if (argc == 2) { //����exe���в�����pvp�������˶�ս��pvc�����˻���ս��
		char c, y = 'a';
		int x = 0;
		int state = BLACK;
		int gamemode = 1;
		int	Whe_right = 1;//�ж�DrawBoardArray�Ƿ���Ϊ��ʽ�����ִ�ж��
		int winner = 0;
		int forbid = 0;//�ж����޽���

		InitBoardArray();
		DisplayBoard();

		if (!strcmp(argv[1], "pvp") || !strcmp(argv[1], "PVP")) { //pvp�������˶�ս
			player_to_player();
		}
		else if (!strcmp(argv[1], "pvc") || !strcmp(argv[1], "PVC")) { //pvc�����˻���ս
			computer_to_player();
		}
		else { //��������
			printf("unknown command\n");
		}

		return 0;
	}
	else { //��������
		printf("unknown command: too many argument\n");
		return 0;
	}
}


void player_to_player() {
	char c, y = 'a';
	int x = 0;
	int state = BLACK;
	int	Whe_right = 1;//�ж�DrawBoardArray�Ƿ���Ϊ��ʽ�����ִ�ж��
	int winner = 0;
	int forbid = 0;//�ж����޽���

	InitBoardArray();
	DisplayBoard();


	while (1) {
		Whe_right = DrawBoardArray(&y, &x, &state, 1);
		if (Whe_right == 1) {
			if (state == BLACK) {
				state = WHITE;  //����Ǹ�ʽ������ٴ��������ڴ˸���state
			}
			else if (state == WHITE) {
				state = BLACK;
			}
		}
		else if (Whe_right == -1) {
			if (Count > 0) {
				regret();//���˶�ս����ֻ��һ������Ҫ����state
				if (state == BLACK) {
					state = WHITE;
				}
				else if (state == WHITE) {
					state = BLACK;
				}
				printf("����ɹ�\n");
				if (Count != 0) {
					printf("�������һ����: %s %d %c\n", (Count % 2 ? "black" : "white"), SIZE - Steps[Count - 1][0], (char)('A' + Steps[Count - 1][1]));
				}
			}
			else {
				printf("��һ���޷�����\n");
			}
			continue;
		}

		if (y >= 'a' && y <= 'o') {  //����Steps
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

		if (y >= 'a' && y <= 'o') {  //�ж��Ƿ�Υ������
			forbid = Whe_forbidden(y - 'a', SIZE - x, state);
		}
		else {
			forbid = Whe_forbidden(y - 'A', SIZE - x, state);
		}
		if (forbid > 0) {
			printf("����Υ�����֣������ʤ\n");
			getchar();
			break;
		}

		if (y >= 'a' && y <= 'o') {  //�ж��Ƿ���ʤ���߲���
			winner = Whe_win(y - 'a', SIZE - x);
		}
		else {
			winner = Whe_win(y - 'A', SIZE - x);
		}
		if (winner == 1) {
			printf("�����ʤ\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("�����ʤ\n");
			getchar();
			break;
		}


		if (Whe_full()) { //�ж������Ƿ�����
			printf("�����Ѿ���������Ϸƽ��\n");
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
	int	Whe_right = 1;//�ж�DrawBoardArray�Ƿ���Ϊ��ʽ�����ִ�ж��
	int winner = 0;
	int forbid = 0;//�ж����޽���

	printf("����1�����֣�����0�����\n");

	InitBoardArray();
	Build_AC();
	score_init();

	int player;
	scanf("%d", &player);
	Limit = Limit3;

	if (player == 0) {//�������ֵĻ�����һ������H8
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
		DisplayBoard();//������֣���һ���հ�����
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
				state = WHITE;  //����Ǹ�ʽ������ٴ��������ڴ˸���state
			}
			else if (state == WHITE) {
				state = BLACK;
			}
		}
		else if (Whe_right == -1) {//����-1������Ҫ����
			if (Count > 1) {
				AI_regret();
				Tree_DFS(head);
				head = malloc(sizeof(struct Tree_Node));
				memset(head, 0, sizeof(struct Tree_Node));
				printf("����ɹ�\n");
				if (Count != 0) {
					printf("�������һ����: %s %d %c\n", (Count % 2 ? "black" : "white"), SIZE - Steps[Count - 1][0], (char)('A' + Steps[Count - 1][1]));
				}
			}
			else {
				printf("��һ���޷�����\n");
			}
			continue;
		}

		if (y >= 'a' && y <= 'o') {  //����Steps
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

		if (y >= 'a' && y <= 'o') {  //�ж��Ƿ�Υ������
			forbid = Whe_forbidden(y - 'a', SIZE - x, state);
		}
		else {
			forbid = Whe_forbidden(y - 'A', SIZE - x, state);
		}
		if (forbid > 0) {
			printf("����Υ�����֣������ʤ\n");
			getchar();
			break;
		}

		if (y >= 'a' && y <= 'o') {  //�ж��Ƿ���ʤ���߲���
			winner = Whe_win(y - 'a', SIZE - x);
		}
		else {
			winner = Whe_win(y - 'A', SIZE - x);
		}
		if (winner == 1) {
			printf("�����ʤ\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("�����ʤ\n");
			getchar();
			break;
		}

		if (Whe_full()) { //�ж������Ƿ�����
			printf("�����Ѿ���������Ϸƽ��\n");
			getchar();
			break;
		}


		int findson = 0;
		struct Tree_Node* temp = head;

		//����ҵ��ӽڵ㣬ֱ�Ӱ��ӽڵ㸳ֵ��head����
		if (head->flag)
			for (int i = 1;i <= head->cnt;++i) {
				if (head->son[i] != NULL && head->son[i]->x == X && head->son[i]->y == Y) {
					temp = head->son[i];
					findson = 1;
				}
				else { // ����ֱ���ͷ���������ռ���ڴ�
					if (head->son[i] != NULL) {
						Tree_DFS(head->son[i]);
					}
				}
			}
		head = temp;
		//û�ҵ��ӽڵ㣬����һ���µ���
		if (!findson) {
			head = (struct Tree_Node*)malloc(sizeof(struct Tree_Node));
			memset(head, 0, sizeof(struct Tree_Node));
		}


		T = clock(); //��ʱ
		struct Node tmp;

		tmp = Min_Max(INT_MIN, INT_MAX, state, DEPTH, head);

		now_sum = tmp.sum;
		Board[tmp.x][tmp.y] = state -10;
		UpdateV(tmp.x, tmp.y, state);//����steps
		X = tmp.x;
		Y = tmp.y;
		Steps[Count][0] = X;
		Steps[Count][1] = Y;
		Count++;

		temp = head;
		for (int i = 1;i <= head->cnt;++i) { //����ҵ��ӽڵ㣬ֱ�Ӱ��ӽڵ㸳ֵ��head����
			if (head->son[i] != NULL && head->son[i]->x == tmp.x && head->son[i]->y == tmp.y) {
				temp = head->son[i];
				printf("success in\n");
			}
			else { // �ͷ������ӽڵ������ڴ�
				if (head->son[i] != NULL) {
					Tree_DFS(head->son[i]);
				}
			}
		}
		head = temp;

		DisplayBoard();
		printf("��������: %d%c %dms\n", 15 - tmp.x, 'A' + tmp.y, (clock() - T) / 1000);
		Board[tmp.x][tmp.y] = state; //�����̴����Ӵ������Ǹĳ�ԲȦ

		//�ж�ʤ����
		winner = Whe_win(tmp.y, tmp.x);
		if (winner == 1) {
			printf("�����ʤ\n");
			getchar();
			break;
		}
		else if (winner == 2) {
			printf("�����ʤ\n");
			getchar();
			break;
		}

		if (state == BLACK) {
			state = WHITE;  //�ڴ˸���state
		}
		else if (state == WHITE) {
			state = BLACK;
		}
	}
}