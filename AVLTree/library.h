#ifndef AVLTREE_LIBRARY_H
#define AVLTREE_LIBRARY_H

#include <iostream>
#include <vector>

using namespace std;

class AVLTree {
private:
    struct node {
        const int key;
        node *prev = nullptr;
        node *left = nullptr;
        node *right = nullptr;

        node(const int);
        node(const int, node *prev, node *left, node *right);
        ~node();

        bool search(const int) const;
        void insert(const int);
        void remove(const int);

        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)

        void upIn();

        void upOut();
    };

    node *root = nullptr;

    node *symmetricPrevious() const;

public:
    ~AVLTree();

    const int *search(const int) const;

    const bool isEmpty() const;

    int add(const int);

    int remove(const int);

    vector<int> *preorder() const;

    vector<int> *inorder() const;

    vector<int> *postorder() const;

    friend ostream &operator<<(ostream &, const AVLTree &);
};

#endif