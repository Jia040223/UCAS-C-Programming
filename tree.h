#pragma once
struct Tree_Node {
	int x, y; // x,y������������
	int flag; // flag����ڵ��Ƿ񹹽����
	int sum; // sum����ýڵ����
	int ban; // ban�����Ƿ�Υ������
	int cnt; // cnt�����ӽڵ���Ŀ
	struct Tree_Node* son[11]; //�ӽڵ��ַ
}; 


struct Node {
	int x, y;
	int sum;
}; // x,y������������,sum�������

struct AC {
	int fail; //failָ��
	int vis[4]; //�ֵ������ӽڵ������
	int cnt; //cnt�����ӽڵ���Ŀ
}; 