// Code by Caleb Fernandes and Jadon Orr

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include <map>
#include <string>
#include <stack>
using namespace std;

// this method will take in a string and compress it down to the binary representation
/*
STEPS:
    ~ Generate a list of the frequency in which characters appear in the string using a map
    · Inserting the characters and their frequencies into a priority queue (sorted first by the lowest
    frequency and then lexicographically)
    · Until there is one element left in the priority queue
    · Remove two characters/frequencies pairs from the priority queue
    · Turn them into leaf nodes on a binary tree
    · Create an intermediate node to be their parent using the sum of the frequencies for those
    children
    · Put that intermediate node back in the priority queue
    · The last pair in the priority queue is the root node of the tree
    · Using this new tree, encode the characters in the string using a map with their prefix code by
    traversing the tree to find where the character’s leaf is. When traversal goes left, add a 0 to
    the code, when it goes right, add a 1 to the code
    · With this encoding, replace the characters in the string with their new variable-length prefix
    codes
*/

// Constructor: Initializes an empty Huffman tree
HuffmanTree::HuffmanTree() : root(nullptr) {}

// Destructor: Calls helper function to free memory
HuffmanTree::~HuffmanTree()
{
    deleteTree(root);
}

// Recursive helper function to deallocate all nodes
void HuffmanTree::deleteTree(HuffmanNode *node)
{
    if (!node)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

string HuffmanTree::compress(const string &inputStr)
{
    // generate the freq map and make the queue
    map<char, size_t> freqMap;
    for (char c : inputStr)
    {
        freqMap[c]++;
    }
    // this takes in the freq map and generate the Heap Queue
    /*
    HuffmanNode(char c, size_t f, HuffmanNode *p, HuffmanNode *l, HuffmanNode *r) : character(c), frequency(f), parent(p), left(l), right(r) {};
    HuffmanNode(char c, size_t f) : HuffmanNode(c, f, nullptr, nullptr, nullptr) {};
    */
    HeapQueue<HuffmanNode *, HuffmanNode::Compare> queue;
    for (const auto &pair : freqMap)
    {
        HuffmanNode *node = new HuffmanNode(pair.first, pair.second);
        queue.insert(node);
    };
    // Build the tree
    while (queue.size() != 1)
    {
        // get the first two nodes
        HuffmanNode *u = queue.min();
        queue.removeMin();
        HuffmanNode *v = queue.min();
        queue.removeMin();
        // generate the combined node dependent on if it the root or not
        HuffmanNode *w = new HuffmanNode('\0', (u->getFrequency() + v->getFrequency()), nullptr, u, v);
        // insert the node back into the PQ
        queue.insert(w);
    }
    root = queue.min();
    queue.removeMin();

    // generate the Huffman Codes using Preorder
    generateCodes(root, "");

    // replace the characters in the string with their new binary counterparts
    string finalString = "";
    for (char c : inputStr)
    {
        finalString = finalString + huffmanCodes[c];
    }
    return finalString;
};
// function that will generate the huffman codes using PreOrder in a recursive way
void HuffmanTree::generateCodes(HuffmanNode *node, const string &prefix)
{
    // for empty tree
    if (!node)
        return;

    if (node->isLeaf())
    {
        huffmanCodes[node->getCharacter()] = prefix; // This is a leaf
        return;
    }
    // post order recursive part of function
    if (!node->isLeaf())
        generateCodes(node->left, prefix + "0");
    if (!node->isLeaf())
        generateCodes(node->right, prefix + "1");
}

// Serialization Step:
/*
    Tree serialization will organize the characters associated with the nodes using post order.
    During the post order when you visit a node,
    · if it the node is a leaf (external node) then you add a L plus the character to the serialize tree
    string
    · if it is a branch (internal node) then you add a B to the serialize tree string
*/
void postOrder(HuffmanNode *node, string &output)
{
    // for empty tree
    if (!node)
        return;

    // post order recursive part of function
    if (!node->isLeaf())
        postOrder(node->left, output);
    if (!node->isLeaf())
        postOrder(node->right, output);

    // part that will update the output string
    if (node->isLeaf())
        output = output + "L" + node->getCharacter();
    if (!node->isLeaf())
        output = output + "B";
}

std::string HuffmanTree::serializeTree() const
{
    string finalStr = compressedString;
    postOrder(root, finalStr);
    return finalStr; // placeholder
}

// decompressing the tree
/*
    For decompression, two input arguments will be needed. The Huffman Code that was generated
    by your compress method and the serialized tree string from your serializeTree method. Your
    Huffman tree will have to be built by deserializing the tree string by using the leaves and
    branches indicators. After you have your tree back, you can decompress the Huffman Code by
    tracing the tree to figure out what variable length codes represent actual characters from the
    original string.
*/
std::string HuffmanTree::decompress(const std::string &inputCode, const std::string &serializedTree)
{
    // Rebuild tree from serialized string
    stack<HuffmanNode *> s;
    for (size_t i = 0; i < serializedTree.size(); i++)
    {
        char c = serializedTree[i];
        if (c == 'L')
        {
            char leaf = serializedTree[++i];
            s.push(new HuffmanNode(leaf, 0));
        }
        else if (c == 'B')
        {
            HuffmanNode *rightChild = s.top();
            s.pop();
            HuffmanNode *leftChild = s.top();
            s.pop();
            s.push(new HuffmanNode('\0', 0, nullptr, leftChild, rightChild));
        }
    }
    root = s.top();
    s.pop();

    // Now decode using the tree
    std::string output;
    HuffmanNode *current = root;

    for (char bit : inputCode)
    {
        if (bit == '0')
            current = current->left;
        else if (bit == '1')
            current = current->right;

        // If it's a leaf node
        if (!current->left && !current->right)
        {
            output += current->getCharacter();
            current = root; // reset to root for next symbol
        }
    }

    return output;
}

HuffmanNode *deserializeTree(const std::string &serializedTree, int &index)
{
    if (index >= serializedTree.size())
    {
        return nullptr;
    }

    // If we reach a '#' marker, return nullptr (leaf's child)
    if (serializedTree[index] == '#')
    {
        index++; // Move to next character
        return nullptr;
    }

    // Extract character and create a node
    char character = serializedTree[index++];
    HuffmanNode *node = new HuffmanNode(character, 0); // Frequency is unknown at deserialization

    // Recursively build left and right subtrees
    node->left = deserializeTree(serializedTree, index);
    node->right = deserializeTree(serializedTree, index);

    return node;
}
