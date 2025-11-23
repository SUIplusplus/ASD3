#include "bintree.h"
#include "redblacktree.h"
#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>
using namespace std;

int main() {
    while (true) {
        system("cls");
        BinTree tree;
        bool choice;
        cout << "0. Exit\n1. Proceed\nChoose an option: ";
        cin >> choice;
        if (!choice) return 0;
        string s;
        cout << "Enter parenth expression: ";
        cin >> s;
        try {
            stringstream ss;
            tree.parseParenthExp(s);
            cout << "Binary tree (pre-order traversal): ";
            tree.preTraverse();
            tree.preTraverse(ss);
            cout << "\n";
            int n;
            RBTree rbtree;
            while (ss >> n) { 
                rbtree.insert(n);
            }
            cout << "In-order traversal: ";
            rbtree.inTraverse();
            cout << endl;
            cout << "Pre-order traversal: ";
            rbtree.preTraverse();
            cout << endl;
            cout << "Post-order traversal: ";
            rbtree.postTraverse();
            cout << endl;
            cout << "Bredth-first traversal: ";
            rbtree.bredthTraverse();
            cout << endl;
        } catch (const std::runtime_error& e) {
            cout << e.what() << endl;
        }
        _getch();
    }
}