#pragma once

#include <memory>

/**
 * Struct of binary tree's nodes (need for Huffman's tree building)
 * left subtree adds '0' to the code
 * right subtree adds '1' to the code
 */
struct node
{
    char symbol;
    size_t freq; // count of symbol repeating
    std::shared_ptr<node> left; // left subtree pointer
    std::shared_ptr<node> right; // right subtree pointer

    node() = default;
    ~node() = default;

    node(char _symbol, int _freq)
        : symbol { _symbol }
        , freq { _freq }
    {
        left = nullptr;
        right = nullptr;
    }
};

/**
 * Comparator for priority queue
 * makes it possible to push items in queue from less to high
 */
struct node_comparator
{
    bool operator() (std::shared_ptr<node> n1, std::shared_ptr<node> n2)
    { 
        return (n1->freq > n2->freq);
    }
};