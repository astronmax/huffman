#pragma once

#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include <node.hpp>

// Function builds Huffman tree for unordered map with symbols frequency
auto build_huffman_tree(std::unordered_map<char, size_t> freq_map) -> std::shared_ptr<node>
{
    // for a shorter code
    using node_vector = std::vector<std::shared_ptr<node>>;
    using node_ptr = std::shared_ptr<node>;

    // create priority queue and fill it with values from map
    std::priority_queue<node_ptr, node_vector, node_comparator> queue;
    node_ptr tmp;

    for (const auto& [symbol, freq] : freq_map) {
        tmp = std::make_shared<node>(symbol, freq);
        queue.push(tmp);
    }

    // check to avoid errors
    if (queue.size() == 0)
        return nullptr;

    while (queue.size() != 1) {
        tmp = std::make_shared<node>(); // allocate memory for new node

        // take first two items from queue
        tmp->left = queue.top();
        queue.pop();
        tmp->right = queue.top();
        queue.pop();

        // initialize frequency and symbol in new node
        tmp->freq = tmp->left->freq + tmp->right->freq;
        tmp->symbol = 0;

        queue.push(tmp); // push new node into queue
    }

    return queue.top();
}

/** 
 * Tool that provide you hashmap with codes for each symbol
 * builded by using Huffman tree. It's better to use hashmap 
 * while encoding text instead of just a tree, because access 
 * to code by symbol (key) can occur in constant time. That 
 * fact accelerates encoding
 * 
 * Note: If text contain only one symbol we encode it using '0'
 */
class encoder {

    std::unordered_map<char, std::string> m_codes;

    // Method analyzes Huffman tree recursively and fills hashmap
    void init(const std::shared_ptr<node> huffman_tree, std::string code = "")
    {
        if (huffman_tree->left && huffman_tree->right) {
            // it's not a leaf, go deeper
            init(huffman_tree->left, code + "0");
            init(huffman_tree->right, code + "1");
        } else if (code == "") {
            // text have only one symbol
            m_codes[huffman_tree->symbol] = "0";
            return;
        } else {
            // we found leaf, add code into hashmap
            m_codes[huffman_tree->symbol] = code;
        }
    }

public:
    encoder(const std::shared_ptr<node> huffman_tree) { init(huffman_tree); }
    ~encoder() = default;

    // Method returns hashmap with codes
    auto& codes() noexcept { return m_codes; }
};

/** 
 * Tool that provide you searching for symbol in Huffman tree 
 * using it's code
 */
class decoder {

    std::shared_ptr<node> m_huffman_tree;

    // Method searchs for symbol with needed code in Huffman tree
    char walk(std::shared_ptr<node> tree, std::string code) const
    {        
        while (tree->left && tree->right) {
            // it's not a leaf, but code is over
            if (code.size() == 0)
                return 0;
            
            // '0' means that we need left subtree, 
            // '1' - right subtree.
            if (code.at(0) == '0') {
                code.erase(code.begin());
                tree = tree->left;
            } else {
                code.erase(code.begin());
                tree = tree->right;
            }
        }

        // it's leaf, but code isn't over
        if (code.size() != 0)
            return 0;

        return tree->symbol;
    }

public:
    decoder(std::shared_ptr<node> huffman_tree)
        : m_huffman_tree { huffman_tree }
    {
    }

    char find(std::string code) const
    {
        if (!m_huffman_tree->left && !m_huffman_tree->right)
            return m_huffman_tree->symbol; // text contains only one symbol

        auto tree = m_huffman_tree; // make copy
        return walk(tree, code);
    }
};
