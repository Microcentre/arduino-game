#include "ScoreList.h"

ScoreList::ScoreList()
{
    this->head = nullptr;
    ScoreList::size = 0;
}

ScoreList::Node::Node(uint16_t data)
{
    this->data = data;
    this->next = nullptr;
}

ScoreList::Node::~Node()
{
    delete this->next;
    this->next = nullptr;
}

void ScoreList::insert(uint16_t data)
{
    if (this->size == MAX_HIGHSCORES)
    {
        deleteLastNode();
    }

    Node *newNode = new Node(data);

    // If the list is empty, or the new node should be inserted before the head
    if (this->head == nullptr || data > this->head->data)
    {
        newNode->next = this->head;
        this->head = newNode;
    }
    else
    {
        // Find the node before the point of insertion
        Node *temp = this->head;
        while (temp->next != nullptr && temp->next->data >= data)
        {
            temp = temp->next;
        }

        // Insert the new node after temp
        newNode->next = temp->next;
        temp->next = newNode;
    }

    this->size++;
}

void ScoreList::deleteLastNode()
{
    // If the list is empty, there's nothing to delete
    if (this->head == nullptr)
    {
        return;
    }

    // If the list has only one node
    if (this->head->next == nullptr)
    {
        delete this->head;
        this->head = nullptr;
        return;
    }

    // Find the second last node
    Node *temp = this->head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    // Delete the last node
    delete temp->next;
    temp->next = nullptr;
    this->size--;
}

uint16_t ScoreList::get(uint8_t index)
{
    // If the list is empty or the index is out of bounds, return -1
    if (this->head == nullptr || index >= size)
    {
        return 0;
    }

    // Traverse the list until the desired index
    Node *temp = this->head;
    for (int i = 0; i < index; i++)
    {
        temp = temp->next;
    }

    // Return the data of the node at the desired index
    return temp->data;
}

ScoreList::~ScoreList()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
}
