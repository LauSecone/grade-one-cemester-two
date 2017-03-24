#include<stdio.h>
#include<stdlib.h>

struct node{
    int num;
    struct node *next;
};

void Creat_ChainList(struct node *);
struct node *Sort_ChainList(struct node *);
void Output_ChainList(struct node *);
struct node *FindMaxNum(struct node *);

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    if (head != NULL) {
		int num;
		scanf("%d", &num);
    	head -> next = NULL;
    	head -> num = num;
    }
    Creat_ChainList(head);
    head = Sort_ChainList(head);
    Output_ChainList(head);
    free(head);
    return 0;
}

void Creat_ChainList(struct node *head) {
    struct node *Cur_ptr;
    int num;
    scanf("%d", &num);
    Cur_ptr = head;
    while (num != -1) {
        struct node *new_ptr = (struct node *)malloc(sizeof(struct node));
        if (new_ptr != NULL) {
			new_ptr -> next = NULL;
        	new_ptr -> num = num;
			Cur_ptr -> next = new_ptr;
	    	Cur_ptr = new_ptr;
			scanf("%d", &num);
		}
    }
    return;
}

struct node *Sort_ChainList(struct node *head) {
    struct node *LastSorted_ptr, *MaxNum_ptr = NULL, *PreMaxNum_ptr = NULL;
    struct node *AddAHead = (struct node *)malloc(sizeof(struct node));
    if (AddAHead != NULL) {
    	AddAHead -> next = head;
    	AddAHead -> num = -1;
    	head = AddAHead;
    	LastSorted_ptr = head;
    	while (LastSorted_ptr -> next -> next -> next != NULL) {
        	PreMaxNum_ptr = FindMaxNum(LastSorted_ptr -> next);
        	if (PreMaxNum_ptr != NULL) {
        		MaxNum_ptr = PreMaxNum_ptr -> next;
            	PreMaxNum_ptr -> next = MaxNum_ptr -> next;
            	MaxNum_ptr -> next = LastSorted_ptr -> next;
            	LastSorted_ptr -> next = MaxNum_ptr;
        	}
        	LastSorted_ptr = LastSorted_ptr -> next;
    	}
    }
    return(head -> next);
}

void Output_ChainList(struct node *head) {
    struct node *Cur_ptr;
    Cur_ptr = head;
    while (Cur_ptr != NULL) {
        printf("%d ", Cur_ptr -> num);
        Cur_ptr = Cur_ptr -> next;
    }
    printf("\n");
    return;
}

struct node *FindMaxNum(struct node *head) {
    struct node *pre = NULL, *max = head, *prehead = NULL;
	while (head != NULL) {
		if (head -> num > max -> num) {
			max = head;
			pre = prehead;
		}
		prehead = head;
		head = head -> next;
	}
    return pre;
}
