#include "library.h"

#include <iostream>

AVLTree::~AVLTree() {
    delete root;
}

const int *AVLTree::search(const int) const {
    return nullptr;
}

const bool AVLTree::isEmpty() const {
    return false;
}

int AVLTree::add(const int) {
    return 0;
}

int AVLTree::remove(const int) {
    return 0;
}

AVLTree::node *AVLTree::symmetricPrevious() const {
    return nullptr;
}

vector<int> *AVLTree::preorder() const {
    return nullptr;
}

vector<int> *AVLTree::inorder() const {
    return nullptr;
}

vector<int> *AVLTree::postorder() const {
    return nullptr;
}

AVLTree::node::node(const int key, AVLTree::node *prev, AVLTree::node *left, AVLTree::node *right)
        : key(key), prev(prev), left(left), right(right) {
}

AVLTree::node::~node() {
    delete left;
    delete right;
}

void AVLTree::node::upIn() {

}

void AVLTree::node::upOut() {

}

bool AVLTree::node::search(const int) const {
    return false;
}

void AVLTree::node::insert(const int) {

}

void AVLTree::node::remove(const int) {

}

vector<int> *AVLTree::node::preorder() const {
    return nullptr;
}

vector<int> *AVLTree::node::inorder() const {
    return nullptr;
}

vector<int> *AVLTree::node::postorder() const {
    return nullptr;
}

AVLTree::node::node(const int key) : key(key) {

}
