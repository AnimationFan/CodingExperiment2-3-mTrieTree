#include "MTrie.h"
#include"common.h"

TrieNode::TrieNode(int m) {
	this->itemEnd = false;
	this->next = new TrieNode* [m];
	for (int i = 0; i < m; i++) {
		this->next[i] = nullptr;
	}
}

//checked
//mΪ��Ӧ�Ĳ���
//bits��Ϊ2^bits = m
MTrie::MTrie(int m) {
	this->m = m;
	int k = 1;
	while ((m >> k)>0) {
		k++;
	}
	this->bits = k - 1;
	this->root = new TrieNode(this->m);
}

int MTrie::getm() {
	return this->m;
}

int MTrie::getbits() {
	return this->bits;
}

/*����*/
void MTrie::put(char* str) {
	return this->put(str,0,this->root);
}


//deepthΪ��ǰ�㴦�ڵ�λ�ã��ӵ�0�㿪ʼ����
//node��Ϊ��ǰ���Ӧ�Ľ��
//��ʱ�����ǿ������
void MTrie::put(char* str, int deepth, TrieNode* node) {
	int beginBit = deepth * this->bits; //��ʼλ�õ�bit���
	int branch = this->getBranch(str,beginBit);
	if (branch == -1) {
		node->itemEnd = true;
		return;
	}
	else {
		if (node->next[branch] == nullptr)
			node->next[branch] = new TrieNode(this->m);
		return this->put(str, deepth + 1, node->next[branch]);
	}
}

int MTrie::getBranch(char* str, int beginBit) {
	int len = strlen(str);
	int beginChar = beginBit >> 3;
	if (beginChar>= len)
		return -1;
	int mask = this->m - 1;
	int branch = (str[beginChar]>>(beginBit%8)) & mask;
	return branch;
}

bool MTrie::get(char* str) {
	int len = strlen(str);
	TrieNode* node = this->root;
	for (int beginBit = 0; beginBit < (len << 3); beginBit += this->bits) {
		int branch = this->getBranch(str, beginBit);
		if (node->next[branch] == nullptr)
			return false;
		else
			node = node->next[branch];
	}
	if (node->itemEnd == true)
		return true;
	else
		return false;
}

