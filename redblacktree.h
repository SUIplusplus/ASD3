#pragma once

class RBTree {
private:
    struct Node {
        int val;
        bool isRed;
        Node* left;
        Node* right;
        Node* father;
        Node() : val(0), left(nullptr), right(nullptr), father(nullptr), isRed(false) {}
        Node(int data) : val(data), isRed(true), left(nullptr), right(nullptr), father(nullptr) {}
        Node(int data, bool color) : val(data), isRed(color), left(nullptr), right(nullptr), father(nullptr) {}
    };
    Node* root;
    void rotateLeft(Node* node); 
    void rotateRight(Node* node); 
    void inTraverseRec(Node* curr);
    void preTraverseRec(Node* curr);
    void postTraverseRec(Node* curr);
    Node* minNode(Node* node);
    Node* insertRec(Node* curr, Node* newNode);
    Node* removeRec(Node* curr, int data);
    void fixInsertion(Node* node); 
    void fixRemoval(Node* node); 
    void clear(Node* curr);
public:
    RBTree();
    ~RBTree();
    void inTraverse();
    void preTraverse();
    void postTraverse();
    void bredthTraverse();
    void insert(int data); 
    void remove(int data); 
};