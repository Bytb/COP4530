// Code by Caleb Fernandes and Jadon Orr

#pragma once
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"
#include <map>
#include <string>
using namespace std;
class HuffmanTree : public HuffmanTreeBase
{
public:
    HuffmanTree();  // Constructor
    ~HuffmanTree(); // Destructor to free memory

    std::string compress(const std::string &inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string &inputCode, const std::string &serializedTree);

private:
    HuffmanNode *root;                        // Root node of Huffman Tree
    std::map<char, std::string> huffmanCodes; // Stores char → Huffman Code
    string compressedString;

    void generateCodes(HuffmanNode *node, const std::string &prefix);
    void deleteTree(HuffmanNode *node);
    HuffmanNode *deserializeTree(const std::string &serializedTree, int &index);
};
