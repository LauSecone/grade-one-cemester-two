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
		case 6: fprintf(stdout, "�������н������ټ���"); return 0; break;
		default: fprintf(stdout, "ERROR:Unknow Numner\n"); break;
		}
		fprintf(stdout, "\n");
	}
}

void printChoice() {
	fprintf(stdout, "����������ѡ����\n1--����һ��100���ռ�¼���ļ�\n2--������Ʒ��¼\n3--������Ʒ��¼\n4--ɾ����Ʒ��¼\n5--����ȫ����Ʒ��¼\n6--�˳�����\n");
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
			fprintf(stdout, "100���ռ�¼��������\n");
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
		fprintf(stdout, "��������Ʒ��Ϣ[IDΪ-1������������]��\n��Ʒ ID��");
		fscanf(stdin, "%d", &(com.ID));
		while (com.ID != -1) {
			fprintf(stdout, "��Ʒ��:");
			fscanf(stdin, "%s", com.name);
			fprintf(stdout, "������");
			fscanf(stdin, "%d", &(com.num));
			fprintf(stdout, "�۸���");
			fscanf(stdin, "%f", &(com.pri));
			fseek(fp, (com.ID - 1) * sizeof(struct commodityData), SEEK_SET);
			fwrite(&com, sizeof(struct commodityData), 1, fp);
			fprintf(stdout, "��������Ʒ��Ϣ[IDΪ-1������������]��\n��Ʒ ID��");
			fscanf(stdin, "%d", &(com.ID));
		}
		fflush(fp);
		if (fclose(fp)) {
			fprintf(stderr, "Can not close the file: commodity.dta\n");
		}
		else {
			fprintf(stdout, "��Ʒ��Ϣ��������\n");
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
		fprintf(stdout, "��������������ƷID[IDΪ-1������������]:\n");
		int id, nu = 0;	//ID number
		float pr = 0;	//price
		char str[35] = { 0 };	//name
		fscanf(stdin, "%d", &id);
		while (id != -1) {
			struct commodityData com = { 0 };
			fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
			fread(&com, sizeof(struct commodityData), 1, fp);
			if (com.ID == 0) {
				fprintf(stdout, "�Բ��𣬼�¼��Ϊ%d����Ʒ�����ڣ��޷�����\n", id);
			}
			else {
				fprintf(stdout, "ԭ��Ʒ��Ϣ���£�\n��¼�ţ���ƷID��		��Ʒ��	        ����	�۸�\n");
				printSingleRecord(fp, id);
				fprintf(stdout, "������������Ϣ[��ĳ�������ֱ�Ӱ��س���]��\n��Ʒ���ƣ�");
				getchar();
				gets(str);
				if (strlen(str) != 0) {
					strcpy(com.name, str);
				}
				fprintf(stdout, "������");
				gets(str);
				if (strlen(str) != 0) {
					com.num = converseToInt(str);
				}
				fprintf(stdout, "�۸���");
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
			fprintf(stdout, "���¹�������\n");
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
		fprintf(stdout, "��������ɾ����ƷID[��¼��Ϊ-1��������ɾ��]:\n");
		fscanf(stdin, "%d", &id);
		while (id != -1) {
			struct commodityData com = { 0 };
			fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
			fread(&com, sizeof(struct commodityData), 1, fp);
			if (com.ID == 0) {
				fprintf(stdout, "�Բ��𣬼�¼��Ϊ%d����Ʒ�����ڣ��޷�����ɾ������\n", id);
			}
			else {
				fprintf(stdout, "��Ʒ��Ϣ���£�\n��¼�ţ���ƷID��		��Ʒ��	        ����	�۸�\n");
				printSingleRecord(fp, id);
				fprintf(stdout, "�Ƿ�ȷʵɾ����ȷ�ϰ�Y��ȡ����N)��\n");
				char ch;
				getchar();
				fscanf(stdin, "%c", &ch);
				if (ch == 'Y') {
					fseek(fp, (id - 1) * sizeof(struct commodityData), SEEK_SET);
					fwrite(&blankCommodity, sizeof(struct commodityData), 1, fp);
				}
				if (ch == 'N') {
					fprintf(stdout, "��ѡ����ɾ����¼��Ϊ%d����Ʒ\n", id);
				}
				fflush(fp);
				outputCommodityRecord();
			}
			fprintf(stdout, "��������ɾ����ƷID[��¼��Ϊ-1��������ɾ��]:\n");
			fscanf(stdin, "%d", &id);
		}
		fflushi(fp);
		if (fclose(fp)) {
			fprintf(stderr, "Can not close the file: commodity.dat\n");
		}
		else {
			fprintf(stdout, "ɾ����������\n");
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
		fprintf(stdout, "��Ʒ��Ϣ���£�\n��¼�ţ���ƷID��		��Ʒ��	        ����	�۸�\n");
		for (i = 1; i <= 100; ++i) {
			printSingleRecord(fp, i);
		}
		fclose(fp);
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