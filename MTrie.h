#pragma once
class TrieNode {
public:
	/*���캯����mΪ�����*/
	TrieNode(int m);
	/*��ʾ��ǰ����Ƿ�Ϊһ�ַ����Ľ����Ľ��*/
	bool itemEnd;
	/*�洢�����������*/
	TrieNode** next;
	
	
};

class MTrie
{

protected:
	/*����*/
	int m;
	/*�������Ӧ�ı���λ��*/
	int bits;
	/*����*/
	TrieNode* root;
public:
	/*���캯��*/
	MTrie(int m);
	int getm();
	int getbits();
	
	/*����ַ���*/
	void put(char* str);
	/*���ַ��������Զ�Ӧ�Ľ��Ϊ����������put()��ʵ��ִ�к���*/
	void put(char* str, int deepth, TrieNode* node);
	/*�����ַ�������ȷ�����ʱ���Ӧ�ķ�֧*/
	int getBranch(char*str, int beginBit);
	/*�ж��ַ����Ƿ����������*/
	bool get(char*);
};

