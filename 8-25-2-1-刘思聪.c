#include<stdio.h>

int DealFile();

int main() {
    return DealFile();
}

int DealFile() {
    FILE *fp;
    int cap = 0, low = 0, dig = 0, oth = 0, max = 0, min = 2 << 20, cur = 0, numl = 0;
    int CAP[30] = {0}, LOW[30] = {0};
    //read the file and deal the text
    if ((fp = fopen("file.txt", "r")) == NULL) {
        fprintf(stderr, "File could not be opened\n");
        return -1;
    } else {
        char ch = ' ';
        while  (ch != EOF) {    //"while" for all
            while ((ch = fgetc(fp)) != '\n' && ch != EOF) { //while for each line
                ++cur;
                if ((ch <= 'Z') && (ch >= 'A')) {
					++cap;
					++CAP[ch - 'A' + 1];
				} 
				else if ((ch <= 'z') && (ch >= 'a')) {
					++low;
					++LOW[ch - 'a' + 1];
				} 
				else if ((ch <= '9') && (ch >= '0')) {
					++dig;
				} 
				else {	
					++oth;
				}
			}
            if (cur < min) {
                min = cur;
            }
            if (cur > max) {
                max = cur;
            }
            cur = 0;
            ++numl;
        }
        fclose(fp);
    }   //deal finished
    //output the data to the p1.txt
    if ((fp = fopen("p1.txt", "w")) == NULL) {
        fprintf(stderr, "File could not be writed");
        return -1;
    } else {
        fprintf(fp, "Task 1:\ncapitial:%d\nlowercase:%d\ndigit:%d\nothers:%d\n", 
			cap, low, dig, oth);
        fprintf(fp, "\n\nTask 2:\nline:%d\n%d characters in max line\n%d characters in min line\n",
            numl, max, min);
        fprintf(fp, "\n\nTask 3:\nCAPITAL:\n");
        int i;
        for (i = 1; i <= 26; ++i) {
            fprintf(fp, "%c:%-5d", i + 'A' - 1, CAP[i]);
            if (i % 4 == 0) {
                fprintf(fp, "\n");
            }
        }
        fprintf(fp, "\nLOWERCASE\n");
        for (i = 1; i <= 26; ++i) {
            fprintf(fp, "%c:%-5d", i + 'a' - 1, LOW[i]);
            if (i % 4 == 0) {
                fprintf(fp, "\n");
            }
        }
        fclose(fp);
    }
    return 0;
}