#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct commodityData {
	int ID;
	char name[35];
	int num;
	float pri;
};

void printChoice();
void creatBlankRecord();
void inputCommodityRecord();
void updateCommodityRecord();
void deleteCommodityRecord();
void outputCommodityRecord();
void printSingleRecord(FILE *, int);
int converseToInt(char *);
float converseToFloat(char *);

int main() {
	while (1) {
		printChoice();
		int cho;
		fscanf(stdin, "%d", &cho);
		switch (cho) {
		case 1: creatBlankRecord(); break;
		case 2: inputCommodityRecord(); break;
		case 3: updateCommodityRecord(); break;
		case 4: deleteCommodityRecord(); break;
		case 5: outputCommodityRecord(); break;
		case 6: fprintf(stdout, "程序运行结束，再见！"); return 0; break;
		default: fprintf(stdout, "ERROR:Unknow Numner\n"); break;
		}
		fprintf(stdout, "\n");
	}
}

void printChoice() {
	fprintf(stdout, "请输入您的选择：\n1--创建一个100条空记录的文件\n2--输入商品记录\n3--更新商品记录\n4--删除商品记录\n5--输出全部商品记录\n6--退出程序\n");
}

void creatBlankRecord() {
	FILE * fp = NULL;
	if ((fp = fopen("commodity.dat", "wb")) == NULL) {
		fprintf(stderr, "Can not open the file: commodity.dat\n");
		return;
	}
	else {
		int i;
		struct commodityData blankCommodity = { 0, "", 0, 0.0 };
		for (i = 0; i < 100; ++i) {
			fwrite(&blankCommodity, sizeof(struct commodityData), 1, fp);
		}
		fflush(fp);
		if (fclose(fp)) {
			fprintf(stderr, "Can not close the file: commodity,dat\n");
			return;
		}
		else {
			fprintf(stdout, "100条空记录创建完毕\n");
			return;
		}
	}
}

void inputCommodityRecord() {
	FILE *fp;
	if ((fp = fopen("commodity.dat", "rb+")) == NULL) {
		fprintf(stderr, "Can not open the file: commodity.dat\n");
		return;
	}
	else {
		struct commodityData com;
		fprintf(stdout, "请输入商品信息[ID为-1代表输入结束]：\n商品 ID：");
		fscanf(stdin, "%d", &(com.ID));
		while (com.ID != -1) {
			fprintf(stdout, "商品名:");
			fscanf(stdin, "%s", com.name);
			fprintf(stdout, "数量：");
			fscanf(stdin, "%d", &(com.num));
			fprintf(stdout, "价格：");
			fscanf(stdin, "%f", &(com.pri));
			fseek(fp, (com.ID - 1) * sizeof(struct commodityData), SEEK_SET);
			fwrite(&com, sizeof(struct commodityData), 1, fp);
			fprintf(stdout, "请输入商品信息[ID为-1代表输入结束]：\n商品 ID：");
			fscanf(stdin, "%d", &(com.ID));
		}
		fflush(fp);
		if (fclose(fp)) {
			fprintf(stderr, "Can not close the file: commodity.dta\n");
		}
		else {
			fprintf(stdout, "商品信息输入结束\n");
		}
		outputCommodityRecord(fp);
		return;
	}
}

void updateCommodityRecord() {
	FILE *fp;
	if ((fp = fopen("commodity.dat", "rb+")) == NULL) {
		fprintf(stderr, "Can not open the file: commodity.dat\n");
		return;
	}
	else {
		fprintf(stdout, "请输入待更新商品ID[ID为-1代表结束更新]:\n");
		int id, nu = 0;	//ID number
		float pr = 0;	//price
		char str[35] = { 0 };	//name
		fscanf(stdin, "%d", &id);
		while (id != -1) {
			struct commodityData com = { 0 };
			fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
			fread(&com, sizeof(struct commodityData), 1, fp);
			if (com.ID == 0) {
				fprintf(stdout, "对不起，记录号为%d的商品不存在，无法更新\n", id);
			}
			else {
				fprintf(stdout, "原商品信息如下：\n记录号（商品ID）		商品名	        数量	价格\n");
				printSingleRecord(fp, id);
				fprintf(stdout, "请输入更新信息[如某项不更新请直接按回车键]：\n商品名称：");
				getchar();
				gets(str);
				if (strlen(str) != 0) {
					strcpy(com.name, str);
				}
				fprintf(stdout, "数量：");
				gets(str);
				if (strlen(str) != 0) {
					com.num = converseToInt(str);
				}
				fprintf(stdout, "价格：");
				gets(str);
				if (strlen(str) != 0) {
					com.pri = converseToFloat(str);
				}
				//printf("%s\n%d\n%f\n", com.name, com.num, com.pri);
				fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
				fwrite(&com, sizeof(struct commodityData), 1, fp);
			}
			fscanf(stdin, "%d", &id);
		}
		fflush(fp);
		if (close(fp)) {
			fprintf(stderr, "Can not close the file: commodity.dat\n");
		}
		else {
			fprintf(stdout, "更新工作结束\n");
		}
		return;
	}
}

void deleteCommodityRecord() {
	FILE *fp;
	if ((fp = fopen("commodity.dat", "rb+")) == NULL) {
		fprintf(stderr, "Can not open the file: commodity.dat\n");
		return;
	}
	else {
		struct commodityData blankCommodity = { 0, "", 0, 0.0 };
		int id;
		fprintf(stdout, "请输入待删除商品ID[记录号为-1代表结束删除]:\n");
		fscanf(stdin, "%d", &id);
		while (id != -1) {
			struct commodityData com = { 0 };
			fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
			fread(&com, sizeof(struct commodityData), 1, fp);
			if (com.ID == 0) {
				fprintf(stdout, "对不起，记录号为%d的商品不存在，无法进行删除操作\n", id);
			}
			else {
				fprintf(stdout, "商品信息如下：\n记录号（商品ID）		商品名	        数量	价格\n");
				printSingleRecord(fp, id);
				fprintf(stdout, "是否确实删除（确认按Y，取消按N)？\n");
				char ch;
				getchar();
				fscanf(stdin, "%c", &ch);
				if (ch == 'Y') {
					fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
					fwrite(&blankCommodity, sizeof(struct commodityData), 1, fp);
				}
				if (ch == 'N') {
					fprintf(stdout, "您选择不删除记录号为%d的商品\n", id);
				}
				fflush(fp);
				outputCommodityRecord();
			}
			fprintf(stdout, "请输入待删除商品ID[记录号为-1代表结束删除]:\n");
			fscanf(stdin, "%d", &id);
		}
		fflush(fp);
		if (fclose(fp)) {
			fprintf(stderr, "Can not close the file: commodity.dat\n");
		}
		else {
			fprintf(stdout, "删除工作结束\n");
		}
	}
	return;
}

void outputCommodityRecord() {
	FILE *fp;
	if ((fp = fopen("commodity.dat", "rb")) == NULL) {
		fprintf(stderr, "Can not open the file: commodity.dat\n");
		return;
	}
	else {
		int i;
		fprintf(stdout, "商品信息如下：\n记录号（商品ID）		商品名	        数量	价格\n");
		for (i = 1; i <= 100; ++i) {
			printSingleRecord(fp, i);
		}
		if (close(fp)) {
			fprintf(stdout, "Can not close the file: commodity.dat");
		}
		return;
	}
}

void printSingleRecord(FILE *fp, int id) {
	struct commodityData co;
	fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
	fread(&co, sizeof(struct commodityData), 1, fp);
	if (co.ID != 0) {
		fprintf(stdout, "%5d%40s%5d%7.2f\n", co.ID, co.name, co.num, co.pri);
	}
	return;
}

int converseToInt(char * str) {
	int l = strlen(str), i, num = 0;
	for (i = 1; i <= l; ++i) {
		num *= 10;
		num += str[i - 1] - '0';
	}
	return num;
}

float converseToFloat(char *str) {
	float pri = 0;
	int i, l = strlen(str), flag = 0;
	for (i = 1; i <= l - 3; ++i) {
		pri *= 10.0;
		pri += (float)(str[i - 1] - '0');
	}
	pri += (float)(str[l - 2] - '0') / 10;
	pri += (float)(str[l - 1] - '0') / 100;
	return pri;
}
