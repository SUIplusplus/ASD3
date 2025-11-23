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
            int choice;
            cout << "1. Inorder traversal\n2. Preorder traversal\n3. Postorder traversal\n4. Bredth-firth traversal\nChoose an option: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Red-Black tree: ";
                    rbtree.inTraverse();
                    cout << endl;
                    break;
                case 2:
                    cout << "Red-Black tree: ";
                    rbtree.preTraverse();
                    cout << endl;
                    break;
                case 3:
                    cout << "Red-Black tree: ";
                    rbtree.postTraverse();
                    cout << endl;
                    break;
                case 4:
                    cout << "Red-Black tree: ";
                    rbtree.bredthTraverse();
                    cout << endl;
                    break;
                default:
                    cout << "Not an option.\n";
            }
        } catch (const std::runtime_error& e) {
            cout << e.what() << endl;
        }
        _getch();
    }
}