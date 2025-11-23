#include "bintree.h"
#include "queue.h"
#include <iostream>
#include <stdexcept>

BinTree::BinTree() {
    root = nullptr;
}

BinTree::~BinTree() {
    clear(root);
}

void BinTree::clear(Node* curr){
    if (!curr) return;
    clear(curr->left);
    clear(curr->right);
    delete curr;
}

void BinTree::inTraverse(std::ostream& out) {
    Node* curr = root;
    inTraverseRec(curr, out);
}

void BinTree::inTraverseRec(Node* curr, std::ostream& out) {
    if (!curr) return;
    inTraverseRec(curr->left, out);
    out << curr->val << " ";
    inTraverseRec(curr->right, out);
}

void BinTree::preTraverse(std::ostream& out) {
    Node* curr = root;
    preTraverseRec(curr, out);
}

void BinTree::preTraverseRec(Node* curr, std::ostream& out) { 
    if (!curr) return;
    out << curr->val << " ";
    preTraverseRec(curr->left, out);
    preTraverseRec(curr->right, out);
}

void BinTree::postTraverse(std::ostream& out) {
    Node* curr = root;
    postTraverseRec(curr, out);
}

void BinTree::postTraverseRec(Node* curr, std::ostream& out) {
    if (!curr) return;
    postTraverseRec(curr->left, out);
    postTraverseRec(curr->right, out);
    out << curr->val << " ";
}

void BinTree::parseParenthExp(std::string s) {
    if (root) clear(root);
    int pointer = 0;
    root = parseRec(s, pointer);
    if (pointer != s.size()) {
        throw std::runtime_error("Extra characters in expression");
    }
}

BinTree::Node* BinTree::parseRec(const std::string &s, int &p) {
    if (p >= s.size() || s[p] != '(') {
        throw std::runtime_error("Expected '('.");
    }
    p++; 
    if (p >= s.size() || !std::isdigit(s[p])) {
        throw std::runtime_error("Expected number.");
    }
    int val = 0;
    while (p < s.size() && std::isdigit(s[p])) {
        val = val * 10 + (s[p] - '0');
        p++;
    }
    Node* node = new Node(val);
    if (p < s.size() && s[p] == ')') {
        p++;
        return node;
    }
    node->left = parseRec(s, p);
    if (p < s.size() && s[p] == ')') {
        p++;
        return node;
    }
    node->right = parseRec(s, p);
    if (p >= s.size() || s[p] != ')') {
        throw std::runtime_error("Expected ')'.");
    }
    p++;
    return node;
}