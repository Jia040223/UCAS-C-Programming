#include "chess.h"
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>

#define MAXLEN 10000 
#define CHENG_5_SCORE 5000000
#define HUO_4_SCORE 100000
#define CHONG_4_SCORE 10000
#define DAN_HUO_3_SCORE 8000
#define TIAO_HUO_3_SCORE 7000
#define MIAN_3_SCORE 500
#define HUO_2_SCORE 50
#define MIAN_2_SCORE 10

char CHANG_LIAN[10] = "111111";
char CHENG_5[10] = "11111";
char HUO_4[10] = "011110";
char DAN_HUO_3_1[10] = "001110";
char DAN_HUO_3_2[10] = "011100";
char TIAO_HUO_3_1[10] = "010110";
char TIAO_HUO_3_2[10] = "011010";
char HUO_2_1[10] = "001100";
char HUO_2_2[10] = "010100";
char HUO_2_3[10] = "001010";
char CHONG_4_1[10] = "011112";
char CHONG_4_2[10] = "211110";
char CHONG_4_3[10] = "10111";
char CHONG_4_4[10] = "11101";
char CHONG_4_5[10] = "11011";
char MIAN_3_1[10] = "001112";
char MIAN_3_2[10] = "211100";
char MIAN_3_3[10] = "010112";
char MIAN_3_4[10] = "211010";
char MIAN_3_5[10] = "011012";
char MIAN_3_6[10] = "210110";
char MIAN_3_7[10] = "10011";
char MIAN_3_8[10] = "11001";
char MIAN_3_9[10] = "10101";
char MIAN_3_10[10] = "2011102";
char MIAN_2_1[10] = "000112";
char MIAN_2_2[10] = "211000";
char MIAN_2_3[10] = "001012";
char MIAN_2_4[10] = "210100";
char MIAN_2_5[10] = "010012";
char MIAN_2_6[10] = "210010";
char MIAN_2_7[10] = "10001";
char SHUANGCHONG_4_1[10] = "1011101";
char SHUANGCHONG_4_2[10] = "11011011";
char SHUANGCHONG_4_3[10] = "111010111";

struct AC {
    int fail;
    int vis[4];
    int cnt;
}T1[1001], T2[1001], T3[1001], T4[1001], T5[1001], T6[1001], T7[1001], T8[1001];
int ACcnt = 0;//字典树节点下标


//构建AC自动机的字典树
void insert(char s[], struct AC T[]) {
    int len = strlen(s);
    int idx = 0;
    for (int i = 0;i < len;i++) {
        if (!T[idx].vis[s[i] - '0']) {//没有子节点就建立节点
            T[idx].vis[s[i] - '0'] = ++ACcnt;
            idx = ACcnt;
        }
        else {//有子节点直接跳转
            idx = T[idx].vis[s[i] - '0'];
        }
    }
    T[idx].cnt++;
}


//构建AC自动机的fail指针
void build_fail(struct AC T[]) {
    int q[MAXLEN];
    int head = 0;
    int tail = -1;
    for (int i = 0;i < 3;i++) {
        if (T[0].vis[i]) {
            T[0].fail = 0;
            q[++tail] = T[0].vis[i];
        }
    }
    while (head <= tail) { // head赶上tail代表所有节点都构建了fail指针
        int x = q[head];
        head++;
        for (int i = 0;i < 3;i++) {
            if (T[x].vis[i]) {
                T[T[x].vis[i]].fail = T[T[x].fail].vis[i];
                q[++tail] = T[x].vis[i];
            }
            else
                T[x].vis[i] = T[T[x].fail].vis[i];
        }
    }
}


//匹配AC自动机
int quary(char s[], struct AC T[]) {
    int len = strlen(s);
    int idx = 0;
    for (int i = 0;i < len;i++) {
        idx = T[idx].vis[s[i] - '0'];
        for (int j = idx;j && T[j].cnt != -1;j = T[j].fail) {//没找到通过fail指针跳转
            if (T[j].cnt > 0)
                return 1;
        }
    }
    return 0;
}



// 构建五子棋评分的AC完整自动机
void Build_AC(void)
{
    insert(CHENG_5, T1);
    ACcnt = 0;
    build_fail(T1);//建立失败指针

    insert(HUO_4, T2);
    ACcnt = 0;
    build_fail(T2);//建立失败指针

    insert(CHONG_4_1, T3);
    insert(CHONG_4_2, T3);
    insert(CHONG_4_3, T3);
    insert(CHONG_4_4, T3);
    insert(CHONG_4_5, T3);
    ACcnt = 0;
    build_fail(T3);//建立失败指针

    insert(DAN_HUO_3_1, T4);
    insert(DAN_HUO_3_2, T4);
    ACcnt = 0;
    build_fail(T4);//建立失败指针

    insert(TIAO_HUO_3_1, T5);
    insert(TIAO_HUO_3_2, T5);
    ACcnt = 0;
    build_fail(T5);//建立失败指针

    insert(MIAN_3_1, T6);
    insert(MIAN_3_2, T6);
    insert(MIAN_3_3, T6);
    insert(MIAN_3_4, T6);
    insert(MIAN_3_5, T6);
    insert(MIAN_3_6, T6);
    //insert(MIAN_3_7, root, MIAN_3_SCORE);
    //insert(MIAN_3_8, root, MIAN_3_SCORE);
    insert(MIAN_3_9, T6);
    insert(MIAN_3_10, T6);
    ACcnt = 0;
    build_fail(T6);//建立失败指针

    insert(HUO_2_1, T7);
    insert(HUO_2_2, T7);
    insert(HUO_2_3, T7);
    ACcnt = 0;
    build_fail(T7);//建立失败指针

    insert(MIAN_2_1, T8);
    insert(MIAN_2_2, T8);
    insert(MIAN_2_3, T8);
    insert(MIAN_2_4, T8);
    insert(MIAN_2_5, T8);
    insert(MIAN_2_6, T8);
    insert(MIAN_2_7, T8);
    ACcnt = 0;
    build_fail(T8);//建立失败指针
}

/*
void Build_AC(void)
{
    int i;
    Node* ptr = (Node*)malloc(sizeof(Node));
    root = ptr;
    for (i = 0; i < 3; i++)
        root->next[i] = 0;
    root->count = 0;

    insert(CHENG_5, root, CHENG_5_SCORE);

    insert(HUO_4, root, HUO_4_SCORE);

    insert(CHONG_4_1, root, CHONG_4_SCORE);
    insert(CHONG_4_2, root, CHONG_4_SCORE);
    insert(CHONG_4_3, root, CHONG_4_SCORE);
    insert(CHONG_4_4, root, CHONG_4_SCORE);
    insert(CHONG_4_5, root, CHONG_4_SCORE);

    insert(DAN_HUO_3_1, root, DAN_HUO_3_SCORE);
    insert(DAN_HUO_3_2, root, DAN_HUO_3_SCORE);

    insert(TIAO_HUO_3_1, root, TIAO_HUO_3_SCORE);
    insert(TIAO_HUO_3_2, root, TIAO_HUO_3_SCORE);

    insert(MIAN_3_1, root, MIAN_3_SCORE);
    insert(MIAN_3_2, root, MIAN_3_SCORE);
    insert(MIAN_3_3, root, MIAN_3_SCORE);
    insert(MIAN_3_4, root, MIAN_3_SCORE);
    insert(MIAN_3_5, root, MIAN_3_SCORE);
    insert(MIAN_3_6, root, MIAN_3_SCORE);
    //insert(MIAN_3_7, root, MIAN_3_SCORE);
    //insert(MIAN_3_8, root, MIAN_3_SCORE);
    insert(MIAN_3_9, root, MIAN_3_SCORE);
    insert(MIAN_3_10, root, MIAN_3_SCORE);

    insert(HUO_2_1, root, HUO_2_SCORE);
    insert(HUO_2_2, root, HUO_2_SCORE);
    insert(HUO_2_3, root, HUO_2_SCORE);

    insert(MIAN_2_1, root, MIAN_2_SCORE);
    insert(MIAN_2_2, root, MIAN_2_SCORE);
    insert(MIAN_2_3, root, MIAN_2_SCORE);
    insert(MIAN_2_4, root, MIAN_2_SCORE);
    insert(MIAN_2_5, root, MIAN_2_SCORE);
    insert(MIAN_2_6, root, MIAN_2_SCORE);
    insert(MIAN_2_7, root, MIAN_2_SCORE);

    build_fail(root);//建立失败指针
}*/