#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define SIZE 15
#define BLACKtem 10
#define WHITEtem 11
#define BLACK 20
#define WHITE 21

#define DEPTH 10
#define MAXSTEP 15*15+1


int Steps[MAXSTEP][2];//存储每一步下的棋的位置
int Board[SIZE][SIZE];//棋盘
int Value_Board[SIZE][SIZE];//分值棋盘，用于减少搜索时的复杂度
int Count, X, Y; //Count代表下子的次数，X，Y代表下的坐标
int now_sum; //代表现在的AI局面分数

void InitBoardArray();  //初始化空棋盘
void DisplayBoard();	//显示棋盘
int DrawBoardArray(char* y, int* x, int* p_state, int update); ////更新棋盘(输入)——支持“1A”、“A1”、“1a”、“a1”，以及接受合法的命令

void AI_regret();//用于人机对战的悔棋函数
void regret();//用于人人对战的悔棋函数(只悔一步)
void print_steps();//打印出每一步下的棋的位置

void player_to_player(); // 人人对战主程序
void computer_to_player(); // 人机对战主程序

int can_chess(char y, int x); //判断是否落子
int Whe_win(char y, int x); //判断游戏是否有五子相连
int Whe_full();//判断棋盘是否下满
int Whe_forbidden(const char y, const int x, int state);//判断禁手
int keypoint_forbidden(const char y, const int x, int ad_black, int direction);//判断关键点是否为禁手(用于判断禁手时的递归)

int AI_Whe_forbidden(const char x, const int y, int state);//用于AI的禁手：用于降低复杂度
int AI_Whe_chengwu(const int x, const int y, int now_player);//用于AI的判断是否连成5的函数，用于降低复杂度
struct Node Min_Max(int alpha, int beta, int player, int dep, struct Tree_Node* nowNode);//alpha-beta剪枝 + Min_Max搜索
void UpdateV(int x, int y, int state); //更新分值棋盘的分数
int Whe_drop(int i, int j, int state); //判断能否落子
void Tree_DFS(struct Tree_Node* now); //释放tree节点

void Build_AC(); // 构建五子棋评分的完整AC自动机
void build_fail(struct AC T[]); //构建AC自动机的fail指针
void insert(char s[], struct AC T[]); //构建AC自动机的字典树
int quary(char s[], struct AC T[]); //匹配AC自动机

int get_val(char* s, int state); // 用于获得指定棋子序列分数（用于chess_score）
int chess_score(int y, int x, int state); //用于获得单个棋子的分数
int score(int x, int y, int state);
void score_init(); // 用于初始化分数表，降低复杂度
int value_init(char s[]); // 用于score_init
