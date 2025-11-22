#pragma once
#include <string>
#include <iostream>

class BinTree {
private:
    struct Node {
        int val;
        Node* left;
        Node* right;
        Node() : val(0), left(nullptr), right(nullptr) {}
        Node(int data) : val(data), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void inTraverseRec(Node* curr, std::ostream& out = std::cout);
    void preTraverseRec(Node* curr, std::ostream& out = std::cout);
    void postTraverseRec(Node* curr, std::ostream& out = std::cout);
    void clear(Node* curr);
    Node* parseRec(const std::string &s, int &pointer);
public:
    BinTree();
    ~BinTree();
    void inTraverse(std::ostream& out = std::cout);
    void preTraverse(std::ostream& out = std::cout);
    void postTraverse(std::ostream& out = std::cout);
    void parseParenthExp(std::string s);
};