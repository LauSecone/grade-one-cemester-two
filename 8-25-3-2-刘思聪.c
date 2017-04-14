#include<stdio.h>

int main() {
	FILE *fp;
	fp = fopen("2.txt", "r");
	int sta = 2;	//status, 0 is start, 1 is class, 2 is variable's first, 3 is variable, 4 is equal, 5 is value, 6 is error, 7 is end;
	int flag = 1, i;
	char ch;
	for (i = 1; i <= 4; ++i) {
		fgetc(fp);
	}
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == ' ') continue;
		//printf("%d %d\n", sta, ch);
		switch (sta) {
			case 2:
				if (isalpha(ch) || (ch == '_')) {
					sta = 3;
				}
				else {
					flag = 0;
					sta = 6;
				}
				break;
			case 3:
				if (isalpha(ch) || isdigit(ch) || (ch == '_')) {
					sta = 3;
				}
				else if (ch == '=') {
					sta = 4;
				}
				else if (ch == ';') {
					sta = 7;
				}
				else if (ch == ',') {
					sta = 2;
				}
				else {
					flag = 0;
					sta = 6;
				}
				break;
			case 4:
				if (isdigit(ch)) {
					sta = 5;
				}
				else {
					flag = 0;
					sta = 6;
				}
				break;
			case 5:
				if (isdigit(ch)) {
					sta = 5;
				} else if (ch == ';') {
					sta = 7;
				} else if (ch == ',') {
					sta = 2;
				}
				else {
					flag = 0;
					sta = 6;
				}
				break;
			case 6:
				break;
			case 7:
				if (ch != ';' || ch != '\n') {
					flag = 0;
					sta = 6;
				}
				break;
			default : printf("Unknow status");
		}
	}
	fclose(fp);
	if (flag) {
		printf("YES");
	}
	else {
		printf("NO");
	}
	return 0;
}
