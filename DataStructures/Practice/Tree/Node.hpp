#pragma once

template <typename E>
class Node
{
public:
    E data;
    Node *parent;
    Node *head;
    Node *tail;
};
