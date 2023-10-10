#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define SIZE 15
#define BLACKtem 10
#define WHITEtem 11
#define BLACK 20
#define WHITE 21

#define DEPTH 10
#define MAXSTEP 15*15+1


int Steps[MAXSTEP][2];//�洢ÿһ���µ����λ��
int Board[SIZE][SIZE];//����
int Value_Board[SIZE][SIZE];//��ֵ���̣����ڼ�������ʱ�ĸ��Ӷ�
int Count, X, Y; //Count�������ӵĴ�����X��Y�����µ�����
int now_sum; //�������ڵ�AI�������

void InitBoardArray();  //��ʼ��������
void DisplayBoard();	//��ʾ����
int DrawBoardArray(char* y, int* x, int* p_state, int update); ////��������(����)����֧�֡�1A������A1������1a������a1�����Լ����ܺϷ�������

void AI_regret();//�����˻���ս�Ļ��庯��
void regret();//�������˶�ս�Ļ��庯��(ֻ��һ��)
void print_steps();//��ӡ��ÿһ���µ����λ��

void player_to_player(); // ���˶�ս������
void computer_to_player(); // �˻���ս������

int can_chess(char y, int x); //�ж��Ƿ�����
int Whe_win(char y, int x); //�ж���Ϸ�Ƿ�����������
int Whe_full();//�ж������Ƿ�����
int Whe_forbidden(const char y, const int x, int state);//�жϽ���
int keypoint_forbidden(const char y, const int x, int ad_black, int direction);//�жϹؼ����Ƿ�Ϊ����(�����жϽ���ʱ�ĵݹ�)

int AI_Whe_forbidden(const char x, const int y, int state);//����AI�Ľ��֣����ڽ��͸��Ӷ�
int AI_Whe_chengwu(const int x, const int y, int now_player);//����AI���ж��Ƿ�����5�ĺ��������ڽ��͸��Ӷ�
struct Node Min_Max(int alpha, int beta, int player, int dep, struct Tree_Node* nowNode);//alpha-beta��֦ + Min_Max����
void UpdateV(int x, int y, int state); //���·�ֵ���̵ķ���
int Whe_drop(int i, int j, int state); //�ж��ܷ�����
void Tree_DFS(struct Tree_Node* now); //�ͷ�tree�ڵ�

void Build_AC(); // �������������ֵ�����AC�Զ���
void build_fail(struct AC T[]); //����AC�Զ�����failָ��
void insert(char s[], struct AC T[]); //����AC�Զ������ֵ���
int quary(char s[], struct AC T[]); //ƥ��AC�Զ���

int get_val(char* s, int state); // ���ڻ��ָ���������з���������chess_score��
int chess_score(int y, int x, int state); //���ڻ�õ������ӵķ���
int score(int x, int y, int state);
void score_init(); // ���ڳ�ʼ�����������͸��Ӷ�
int value_init(char s[]); // ����score_init
