#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {
private:
    struct Node {
        int balance = 0;
        const int key;
        Node *prev = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const int);
        Node(const int, Node *prev);
        Node(const int, Node *prev, Node *left, Node *right);
        ~Node();

        bool search(const int) const;

        bool insert(const int);
        bool upIn();

        void remove(const int);
        void upOut();

        void rotateLeft();
        void rotateLeftRight();
        void rotateRight();
        void rotateRightLeft();

        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)

        Node *geometricNext() const;
    };

    Node *root = nullptr;
//    static Node *deleteNode(Node *) const;
    friend Node *Node::geometricNext() const;


public:
    ~AVLTree();

    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    bool isEmpty() const;

    vector<int> *preorder() const;
    vector<int> *inorder() const;
    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);

    //for Tests Only
    bool isBalanced() const;
    bool isBalanced(Node*) const;
    int height() const;
    int height(Node*) const;
    //

};

#endif