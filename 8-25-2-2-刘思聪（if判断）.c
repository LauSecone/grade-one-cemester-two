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
		int t1n = 0, t2n = 0, quo = 0;	//t1n is type 1 of note status, t2n is type 2 of note status, quo is quotation mark status
		char ch1 = '\0', ch2 = '\0';	//ch1 is the processing, ch2 is the least char
		while ((ch1 = fgetc(input)) != EOF) {	//read until EOF
			if (ch1 == '"' && t1n == 0 && t2n == 0) {
				quo ^= 1;
			}
			if (ch1 == '/' && ch2 == '/' && quo == 0 && t2n == 0) {
				t1n = 1;
			}
			if (ch1 == '*' && ch2 == '/' && quo == 0 && t1n == 0) {
				t2n = 1;
			}
			if (ch1 == '/' && ch2 == '*') {
				t2n = 0;
				ch2 = '\0';
				ch1 = '\0';
			}
			if (ch1 == '\n' && t1n == 1) {
				ch1 = '\0';
				t1n = 0;
			}
			if (!t1n && !t2n && ch2 != '\0') {
				fprintf(output, "%c", ch2);
			}
			ch2 = ch1;
		}
		fprintf(output, "%c", ch2);
		if (fclose(input) != 0) {
			fprintf(stderr, "Can not close the input file");
		}
		if (fclose(output) != 0) {
			fprintf(stderr, "Can not close the output file");
		}
	}
	return 0;
}
