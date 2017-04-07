#include<stdio.h>
#include<stdlib.h>

int delete_the_note();

int main() {
	return delete_the_note();
}

int delete_the_note() {
	FILE *input, *output;
	if ((input = fopen("p12in.c", "r")) == NULL) {
		fprintf(stderr, "Can not open the file");
		return -1;	//if can not open the file, return stderr
	} else if ((output = fopen("p12out.c", "w")) == NULL) {
		fprintf(stderr, "Can not write the file");
		return -1;	//if can not write the file, return stderr
	} else {
		int sta = 0;	//0 is ordinary, 1 is //, 2 is /* 3 is "
		char ch1 = '\0', ch2 = '\0';	//ch1 is the processing, ch2 is the least char
		while ((ch1 = fgetc(input)) != EOF) {
			switch (sta) {
				case 0 : 
					if (ch2 == '/' && ch1 == '/') {
						sta = 1;
						ch2 = ch1;
						break;
					}
					if (ch2 == '/' && ch1 == '*') {
						sta = 2;
						ch2 = ch1;
						break;
					}
					if (ch1 == '"') {
						sta = 3;
					}
					if (ch2 != '\0') {
						fprintf(output, "%c", ch2);
					}
					ch2 = ch1;
					break;
				case 1 :
					if (ch1 == '\n') {
						sta = 0;
					}
					ch1 = '\0';
					ch2 = ch1;
					break;
				case 2 :
					if (ch2 == '*' && ch1 == '/') {
						ch1 = '\0';
						sta = 0;
					}
					ch2 = ch1;
					break;
				case 3 :
					if (ch1 == '"') {
						sta = 0;
					}
					fprintf(output, "%c", ch2);
					ch2 = ch1;
					break;
			}
		}
		if (ch2 != '\0') {
			fprintf(output, "%c", ch2);
		}
		if (fclose(input) != 0) {
			fprintf(stderr, "Can not close the input file");
		}
		if (fclose(output) != 0) {
			fprintf(stderr, "Can not close the output file");
		}
	}
	return 0;
}