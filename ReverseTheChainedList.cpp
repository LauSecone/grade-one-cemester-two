ptr* ReverseTheChainedList(ptr* head) {
    ptr *p1, *p2;
    if (head == NULL) {
        return head;
    }
    if (head -> next == NULL) {
        head -> next -> next = head;
        head -> next -> next = NULL;
        return head;
    }
    p1 = head;
    p1 -> next = NULL;
    p2 = head -> next;
    head = head -> next -> next;
    while (head != NULL) {
        p2 -> next = p1;
        p1 = p2;
        p2 = head;
        head = head -> next;
    }
    p2 -> next = p1;
    head -> next = p2;
    return head;
}