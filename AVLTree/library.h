#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {
private:
    enum Balance {
        LEFT,EQUAL,RIGHT
    };
    struct Node {
        Balance balance = EQUAL;
        const int key;
        Node *prev = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;

        explicit Node(int);
        Node(int, Node *prev);
        Node(int, Node *prev, Node *left, Node *right);
        ~Node();

        bool search(int) const;

        bool insert(int);
        bool upIn();

        void remove(int);
        void remove0Children();
        void remove1Child();
        void remove2Children();
        void upOut();

        void rotateLeft();
        void rotateLeftRight();
        void rotateRight();
        void rotateRightLeft();
    };

    Node *root = nullptr;


public:
    ~AVLTree();

    bool search(int) const;
    void insert(int);
    void remove(int);

    bool isEmpty() const;

//    friend ostream &operator<<(ostream &, const AVLTree &);

////////////////    //for Tests Only
    bool isSorted() const;
    bool isSorted(Node *) const;
    bool isBalanced() const;
    bool isBalanced(Node*) const;
    int height() const;
    int height(Node*) const;
////////////////    //

};

#endif