#include "ScoreList.h"

ScoreList::ScoreList()
{
    head = nullptr;
    ScoreList::size = 0;
}

ScoreList::Node::Node(int data)
{
    this->data = data;
    this->next = nullptr;
}

void ScoreList::insert(int data)
{
    if (this->size == 10)
    {
        deleteLastNode();
    }

    Node *newNode = new Node(data);

    // If the list is empty, or the new node should be inserted before the head
    if (head == nullptr || data > head->data)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        // Find the node before the point of insertion
        Node *temp = head;
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
    if (head == nullptr)
    {
        return;
    }

    // If the list has only one node
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
        return;
    }

    // Find the second last node
    Node *temp = head;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    // Delete the last node
    delete temp->next;
    temp->next = nullptr;
    this->size--;
}

int ScoreList::get(int index) {
    // If the list is empty or the index is out of bounds, return -1
    if (head == nullptr || index < 0 || index >= size) {
        return -1;
    }

    // Traverse the list until the desired index
    Node* temp = head;
    for (int i = 0; i <= index; i++) {
        temp = temp->next;
    }

    // Return the data of the node at the desired index
    return temp->data;
}

ScoreList::~ScoreList()
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}
