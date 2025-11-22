#include "redblacktree.h"
#include "queue.h"
#include <iostream>
 
RBTree::RBTree() {
    root = nullptr;
}

RBTree::~RBTree() {
    clear(root);
}

void RBTree::clear(Node* curr){
    if (!curr) return;
    clear(curr->left);
    clear(curr->right);
    delete curr;
}

void RBTree::inTraverse() {
    Node* curr = root;
    inTraverseRec(curr);
}

void RBTree::inTraverseRec(Node* curr) {
    if (!curr) return;
    inTraverseRec(curr->left);
    if (curr->isRed) std::cout << curr->val << "R ";
    else std::cout << curr->val << "B ";
    inTraverseRec(curr->right);
}

void RBTree::preTraverse() {
    Node* curr = root;
    preTraverseRec(curr);
}

void RBTree::preTraverseRec(Node* curr) {
    if (!curr) return;
    if (curr->isRed) std::cout << curr->val << "R ";
    else std::cout << curr->val << "B ";
    preTraverseRec(curr->left);
    preTraverseRec(curr->right);
}

void RBTree::postTraverse() {
    Node* curr = root;
    postTraverseRec(curr);
}

void RBTree::postTraverseRec(Node* curr) {
    if (!curr) return;
    postTraverseRec(curr->left);
    postTraverseRec(curr->right);
    if (curr->isRed) std::cout << curr->val << "R ";
    else std::cout << curr->val << "B ";
}

void RBTree::bredthTraverse() {
    if (!root) return;
    Queue<Node*> nodes;
    nodes.enqueue(root);
    while (!nodes.isEmpty()) {
        Node* node = nodes.front();
        if (node->isRed) std::cout << node->val << "R ";
        else std::cout << node->val << "B ";
        nodes.dequeue();
        if (node->left) nodes.enqueue(node->left);
        if (node->right) nodes.enqueue(node->right);
    }
}

void RBTree::rotateLeft(Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right) node->right->father = node;

    rightChild->father = node->father;

    if (!rightChild->father) root = rightChild;
    else if (node->father->left == node) node->father->left = rightChild;
    else node->father->right = rightChild;
    
    rightChild->left = node;
    node->father = rightChild;
}

void RBTree::rotateRight(Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (node->left) node->left->father = node;

    leftChild->father = node->father;

    if (!leftChild->father) root = leftChild;
    else if (node->father->left == node) node->father->left = leftChild;
    else node->father->right = leftChild;
    
    leftChild->right = node;
    node->father = leftChild;
}

void RBTree::insert(int data) {
    Node* newNode = new Node(data);
    root = insertRec(root, newNode);
    fixInsertion(newNode);
}

RBTree::Node* RBTree::insertRec(Node* curr, Node* newNode) {
    if (!curr) return newNode;
    if (newNode->val > curr->val) {
        curr->right = insertRec(curr->right, newNode);
        curr->right->father = curr;
    } else if (newNode->val < curr->val) {
        curr->left = insertRec(curr->left, newNode);
        curr->left->father = curr;
    }
    return curr;
}

void RBTree::fixInsertion(Node* node) {
    Node* father = nullptr;
    Node* grandfather = nullptr;
    Node* uncle = nullptr;
    while (node != root && node->isRed && node->father->isRed) {
        father = node->father;
        grandfather = father->father;
        if (father == grandfather->left) {
            uncle = grandfather->right;
            if (uncle && uncle->isRed) {
                grandfather->isRed = true;
                father->isRed = false;
                uncle->isRed = false;
                node = grandfather;
            } else {
                if (father->right == node) {
                    rotateLeft(father);
                    node = father;
                    father = node->father;
                }
                rotateRight(grandfather);
                father->isRed = false;
                grandfather->isRed = true;
            }
        } else {
            uncle = grandfather->left;
            if (uncle && uncle->isRed) {
                grandfather->isRed = true;
                father->isRed = false;
                uncle->isRed = false;
                node = grandfather;
            } else {
                if (father->left == node) {
                    rotateRight(father);
                    node = father;
                    father = node->father;
                }
                rotateLeft(grandfather);
                father->isRed = false;
                grandfather->isRed = true;
            }
        }
    }
    root->isRed = false;
}

void RBTree::remove(int data) {
    Node* node = removeRec(root, data);
    fixRemoval(node);
}

RBTree::Node* RBTree::removeRec(Node* curr, int data) {
    if (!root) return root;
    if (curr->val > data) return removeRec(curr->left, data);
    if (curr->val < data) return removeRec(curr->right, data);
    Node* temp = minNode(curr->right);
    curr->val = temp->val;
    return removeRec(curr->right, temp->val);
}

RBTree::Node* RBTree::minNode(Node* node) {
    if (!node->left) return node;
    return minNode(node->left);
}

void RBTree::fixRemoval(Node* node) {
    if (!node) return;
    if (node == root) {
        root = nullptr;
        return;
    }
    if (node->isRed || (node->left && node->left->isRed) || (node->right && node->right->isRed)) {
        Node* child = nullptr;
        if (node->left) child = node->left;
        else child = node->right;

        if (node == node->father->left) {
            node->father->left = child;
            if (child) child->father = node->father;
            child->isRed = false;
        } else {
            node->father->right = child;
            if (child) child->father = node->father;
            child->isRed = false;
        }
        delete node;
    } else {
        Node* brother = nullptr;
        Node* father = nullptr;
        Node* ptr = node;
        ptr->isRed = false;
        while (ptr != root && !ptr->isRed) {
            father = ptr->father;
            if (ptr == father->left) {
                brother = father->right;
                if (brother->isRed) {
                    brother->isRed = false;
                    father->isRed = true;
                    rotateLeft(father);
                    brother = father->right;
                }
                if ((!brother->left || !brother->left->isRed) && (!brother->right || !brother->right->isRed)) {
                    brother->isRed = true;
                    if (father->isRed) father->isRed = false;
                    ptr = father;
                } else {
                    if (!brother->right || !brother->right->isRed) {
                        brother->left->isRed = false;
                        brother->isRed = true;
                        rotateRight(brother);
                        brother = father->right;
                    }
                    brother->isRed = father->isRed;
                    father->isRed = false;
                    brother->right->isRed = false;
                    rotateLeft(father);
                    break;
                }
            } else {
                brother = father->left;
                if (brother->isRed) {
                    brother->isRed = false;
                    father->isRed = true;
                    rotateLeft(father);
                    brother = father->left;
                }
                if ((!brother->left || !brother->left->isRed) && (!brother->right || !brother->right->isRed)) {
                    brother->isRed = true;
                    if (father->isRed) father->isRed = false;
                    ptr = father;
                } else {
                    if (!brother->left || !brother->left->isRed) {
                        brother->right->isRed = false;
                        brother->isRed = true;
                        rotateLeft(brother);
                        brother = father->left;
                    }
                    brother->isRed = father->isRed;
                    father->isRed = false;
                    brother->left->isRed = false;
                    rotateLeft(father);
                    break;
                }
            }
        }
        if (node == node->father->left) node->father->left = nullptr;
        else node->father->right = nullptr;
        delete node;
        root->isRed = false;
    }
}