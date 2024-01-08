#ifndef SCORELIST_H
#define SCORELIST_H

#include "stdint.h"

/// @brief LinkedList of Nodes, with each Node represented a score
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
    /// @brief The size of the linked list
    uint8_t size = 0;

    /// @brief start of LinkedList, with each Node representing a score
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

private:
    /// @brief The maximum number of highscores the list can hold
    const uint8_t MAX_HIGHSCORES = 5;
};
#endif