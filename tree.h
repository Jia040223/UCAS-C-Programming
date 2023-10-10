#pragma once
struct Tree_Node {
	int x, y; // x,y代表棋盘坐标
	int flag; // flag代表节点是否构建完成
	int sum; // sum代表该节点分数
	int ban; // ban代表是否违反禁手
	int cnt; // cnt代表子节点数目
	struct Tree_Node* son[11]; //子节点地址
}; 


struct Node {
	int x, y;
	int sum;
}; // x,y代表棋盘坐标,sum代表分数

struct AC {
	int fail; //fail指针
	int vis[4]; //字典树的子节点的索引
	int cnt; //cnt代表子节点数目
}; 