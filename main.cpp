#include"common.h"
#include"MTrie.h"
#include"FileOption.h"

void testMTrieBuild() {
	MTrie* t1 = new MTrie(2);
	MTrie* t2 = new MTrie(4);
	MTrie* t3 = new MTrie(16);
	printf("2��MTrie: �ֲ��� %d �ж������� %d\n", t1->getm(), t1->getbits());
	printf("4��MTrie: �ֲ��� %d �ж������� %d\n", t2->getm(), t2->getbits());
	printf("16��MTrie: �ֲ��� %d �ж������� %d\n", t3->getm(), t3->getbits());
}

void testGetBranch() {
	MTrie* t1 = new MTrie(16);
	char* test = { "Hello World" };
	for (int i = 0; i < strlen(test); i++) {
		printf("%X ", test[i]);
	}
	printf("\n");
	printf("�����ȡ�õ��Ľ��Ϊ:");
	int beginBit = 0;
	while (true) {
		if (beginBit % 4 == 0)
			printf("\n");
		int result = t1->getBranch(test,beginBit);
		if (result >= 0) {
			beginBit += t1->getbits();
			printf("%X ", result);
		}
		else
			break;
	}
	printf("\n");
}

void testMTrie() {
	testMTrieBuild();
}


char* sourceFileLoc = { "dict.txt" };
char* targetFileLoc = { "string.txt" };
char* resultFileLoc = { "bupt_18_3.txt" };

int main() {
	time_t start, finish;
	start = clock();
	int count = 0;
	//����MTrie��

	MTrie* tree = new MTrie(4);
	FileReader* sourceFile = new FileReader();
	bool openRe = sourceFile->openFile(sourceFileLoc, "r");
	if (openRe == false) {
		printf("Դ�ļ��򿪴���\n");
		return 0;
		}

	//д��MTrie
	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		tree->put(data);
		memset(data, 0x00, BUFFER_SIZE);
	}
	sourceFile->closeFile();
	delete sourceFile;


	//�򿪴�ƥ���ַ����ļ�
	FileReader* targetFile = new FileReader();
	openRe = targetFile->openFile(targetFileLoc, "r");
	if (openRe == false) {
		printf("Ŀ���ļ��򿪴���\n");
		return 0;
	}
	//��ƥ�����ļ�׼��д��
	FileWriter* fileWriter = new FileWriter();
	openRe = fileWriter->openFile(resultFileLoc, "w");
	if (openRe == false) {
		printf("�򿪽���ļ�����\n");
		return 0;
	}
	memset(data, 0x00, BUFFER_SIZE);
	int i = 0;
	while (targetFile->getline(data))
	{
		int length = strlen(data);
		if (length == 0) continue;
		int getRe = tree->get(data);
		if (getRe == 1) {
				//printf("����%d: %s \n",i,data);
				fileWriter->putline(data);
				i++;
		}
		memset(data, 0x00, BUFFER_SIZE);
	}

	finish = clock();
	delete targetFile;
	delete[] data;
	delete fileWriter;
	delete tree;
	count++;
	

	printf("string_march: %d  runtime: %d\n",i, (finish - start) );
	system("pause");
	_sleep(3000);
	return 0;
}