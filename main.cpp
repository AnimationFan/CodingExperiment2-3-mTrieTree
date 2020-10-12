#include"common.h"
#include"MTrie.h"
#include"FileOption.h"

void testMTrieBuild() {
	MTrie* t1 = new MTrie(2);
	MTrie* t2 = new MTrie(4);
	MTrie* t3 = new MTrie(16);
	printf("2叉MTrie: 分叉数 %d 判定比特数 %d\n", t1->getm(), t1->getbits());
	printf("4叉MTrie: 分叉数 %d 判定比特数 %d\n", t2->getm(), t2->getbits());
	printf("16叉MTrie: 分叉数 %d 判定比特数 %d\n", t3->getm(), t3->getbits());
}

void testGetBranch() {
	MTrie* t1 = new MTrie(16);
	char* test = { "Hello World" };
	for (int i = 0; i < strlen(test); i++) {
		printf("%X ", test[i]);
	}
	printf("\n");
	printf("逐个截取得到的结果为:");
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
	//构造MTrie树

	MTrie* tree = new MTrie(4);
	FileReader* sourceFile = new FileReader();
	bool openRe = sourceFile->openFile(sourceFileLoc, "r");
	if (openRe == false) {
		printf("源文件打开错误\n");
		return 0;
		}

	//写入MTrie
	char* data = new char[BUFFER_SIZE];
	memset(data, 0x00, BUFFER_SIZE);
	while (sourceFile->getline(data))
	{
		tree->put(data);
		memset(data, 0x00, BUFFER_SIZE);
	}
	sourceFile->closeFile();
	delete sourceFile;


	//打开待匹配字符串文件
	FileReader* targetFile = new FileReader();
	openRe = targetFile->openFile(targetFileLoc, "r");
	if (openRe == false) {
		printf("目标文件打开错误\n");
		return 0;
	}
	//打开匹配结果文件准备写入
	FileWriter* fileWriter = new FileWriter();
	openRe = fileWriter->openFile(resultFileLoc, "w");
	if (openRe == false) {
		printf("打开结果文件错误\n");
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
				//printf("存在%d: %s \n",i,data);
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