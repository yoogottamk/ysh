#include <stdlib.h>

#include "list.h"

Node * newNode(Process proc) {
    Node * ret = (Node *) malloc(sizeof(Node));
    ret->next = 0;
    ret->proc = proc;

    return ret;
}

Node * insert(Node * root, Process proc) {
    if(!root)
        return newNode(proc);

    Node * ret = root,
         *curr = root;

    while(curr->next)
        curr = curr->next;

    curr->next = newNode(proc);

    return ret;
}

Node * delete(Node * root, Process proc) {
    if(!root)
        return 0;

    Node * ret = root,
         *curr = root,
         *prev = 0;

    // if root itself is deleted
    if(curr->proc.pid == proc.pid) {
        ret = curr->next;
        free(curr);

        return ret;
    }

    while(curr && curr->proc.pid != proc.pid) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;

    // free the mem allocated to name the process
    if(curr->proc.name)
        free(curr->proc.name);

    free(curr);

    return ret;
}

Process find(Node * root, Process p) {
    Process nul = { .pid = -1, .name = 0 };

    if(!root)
        return nul;

    Node * curr = root;

    while(curr && curr->proc.pid != p.pid)
        curr = curr->next;

    if(!curr)
        return nul;

    return curr->proc;
}