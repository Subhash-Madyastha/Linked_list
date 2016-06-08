#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    char c;
    struct Node *next;
} Node;

void printOutput(Node *head)
{
    Node *node;
    Node *freeme;

    printf("Sorted output:\n");
    node = head;
    while (node) {
        printf("%c", node->c);
        freeme = node;
        node = node->next;
        free(freeme);
    }
    printf("\n");
}

void sortAndInsertNode(Node **head, char c)
{
    Node *n;
    Node *lhead;
    Node *prev;

    if (c == ' ' || c == '\n') {
        return;
    }

    lhead = *head;

    n = (Node *) malloc(sizeof(Node));
    if (n) {
        prev = NULL;
        n->next = NULL;
        n->c = c;

        if (lhead) {
            do {
                if (c < lhead->c) {
                    n->next = lhead;
                    if (prev) {
                        prev->next = n;
                    }
                    else {
                        *head = n;
                    }
                    break;
                }

                if (lhead->next) {
                    prev = lhead;
                    lhead = lhead->next;
                }
                else {
                    /* reached end of the linked list */
                    lhead->next = n;
                    break;
                }
            }
            while (1);
        }
        else {
            *head = n;
        }
    }
    else {
        printf("Can't allocate memory. Aborting...\n");
        abort();
    }
}

int main(int argc, char *argv[])
{
    char str[32];
    char *s;
    int i;
    int slen;
    bool done = false;
    Node *head = NULL;

    slen = sizeof(str);

    printf("Enter your input:\n");

    while (!done) {
        s = fgets(str, slen, stdin);
        printf("\n");
        if (!s) {
            continue;
        }
        for (i = 0; i < slen; i++) {
            sortAndInsertNode(&head, str[i]);
            if (str[i] == '\n') {
                printOutput(head);
                done = true;
                break;
            }
        }
    }
}
