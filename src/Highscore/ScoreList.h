#ifndef SCORELIST_H
#define SCORELIST_H

#include "stdint.h"

class ScoreList
{
    /// @brief A node in the linked list
    class Node
    {
    public:
        /// @brief The data stored in the node
        uint16_t data;

        /// @brief The next node in the linked list
        Node *next;

        Node(uint16_t data);
        ~Node();
    };

public:
    Node *head;

    /// @brief Creates a new Linked list
    ScoreList();

    /// @brief Inserts a new node into the linked list
    void insert(uint16_t data);

    /// @brief Deletes the last node in the linked list
    void deleteLastNode();

    /// @brief Gets the data at the given index
    uint16_t get(uint8_t index);

    ~ScoreList();

    /// @brief The size of the linked list
    uint8_t size = 0;

private:
    /// @brief The maximum number of highscores the list can hold
    const uint8_t MAX_HIGHSCORES = 5;
};
#endif