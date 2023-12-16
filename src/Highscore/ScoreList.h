#ifndef SCORELIST_H
#define SCORELIST_H

#include "stdint.h"

class ScoreList
{
    class Node
    {
    public:
        int data;
        Node *next;

        Node(int data);
    };

public:
    Node *head;

    ScoreList();

    void insert(int data);

    void deleteLastNode();

    int get(int index);

    ~ScoreList();

    uint8_t size = 0;
};
#endif