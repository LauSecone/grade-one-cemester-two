#include<stdio.h>

struct node {
    int num;
    struct node *next;
};

void creat(struct node *);
struct node *insert(struct node *, int);
void output(struct node *);

int main() {
    struct node *head1 = NULL, *head2 = NULL;
    creat(head1);
    creat(head2);
    struct node *cur_node;
    cur_node = head2;
    while (cur_node -> next != NULL) {
        insert(head1, cur_node -> num);
        cur_node = cur_node -> next;
    }
    output(head1);
    free(head1);
    free(head2);
    return 0;
}

void creat(struct node *head) {
    int num = 0;
    scanf("%d", &num);
    while(num != -1) {
        insert(head, num);
        scanf("%d", &num);
    }
    return;
}

struct node *insert(struct node *head, int num) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node != NULL) {
        new_node -> num = num;
        new_node -> next = NULL;
        if (head == NULL) {
            head = new_node;
            return head;
        }
        if (new_node -> num < head -> num) {
            new_node -> next = head;
            head = new_node;
            return head;
        }
        if (head -> next = NULL) {
            head -> next = new_node;
            return head;
        }
        struct node *small, *big;
        small = head;
        big = head -> next;
        while ((big -> num < new_node -> num)||(big -> next == NULL)) {
            small = big;
            big = big -> next;
        }
        if (big -> num >= new_node -> num) {
            small -> next = new_node;
            new_node -> next = big;
        }
        else {
            new_node -> next = big -> next;
            big -> next = new_node;
        }
        return head;
    }
}

void output(struct node *head) {
    while (head != NULL) {
        printf("%d ", head -> num);
        head = head -> next;
    }
    return;
}