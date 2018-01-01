#include "library.h"
#include <functional>
#include <iostream>

bool AVLTree::isEmpty() const {
    return root == nullptr;
}

AVLTree::Node::Node(const int key)
        : key(key) {
}

AVLTree::Node::Node(const int key, AVLTree::Node *prev)
        : key(key), prev(prev) {
}

AVLTree::Node::Node(const int key, AVLTree::Node *prev, AVLTree::Node *left, AVLTree::Node *right)
        : key(key), prev(prev), left(left), right(right) {
}

AVLTree::~AVLTree() {
    delete root;
}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

/********************************************************************
 * Search
 *******************************************************************/
bool AVLTree::search(const int value) const {
    return root == nullptr ? false : root->search(value);
}

bool AVLTree::Node::search(const int value) const {
    if (value == this->key) {
        return true;
    }
    if (value < this->key) {
        return left == nullptr ? false : left->search(value);
    } else {
        return right == nullptr ? false : right->search(value);
    }
}

/********************************************************************
 * insert
 *******************************************************************/

void AVLTree::insert(const int value) {
    if (root == nullptr) {
        root = new AVLTree::Node(value);
    } else {
        root->insert(value);
        while (root->prev != nullptr) {
            root = root->prev;
        };
    }
}

bool AVLTree::Node::insert(const int value) {
    if (value == key) { return false; }
    if (value < key) {
        if (left == nullptr) {
            left = new AVLTree::Node(value, this);
            //inserted node on the left, check balance
            if (this->balance == 0) {
                this->balance = -1;
                return this->upIn();
            } else {
                this->balance = 0;
            }
        } else if (left->insert(value)) {
            return this->upIn();
        }
    } else {
        if (right == nullptr) {
            right = new AVLTree::Node(value, this);
            //inserted node on the right, check balance
            if (this->balance == 0) {
                this->balance = 1;
                return this->upIn();
            } else {
                this->balance = 0;
            }
        } else if (right->insert(value)) {
            return this->upIn();
        }
    }
    return false;
}

bool AVLTree::Node::upIn() {

    if (prev == nullptr) {
        return false;
    }
    if (this == prev->left) {
        //left child
        switch (prev->balance) {
            case 1:
                prev->balance = 0;
                return false;
            case 0:
                prev->balance = -1;
                return true;
            case -1:
                switch (this->balance) {
                    case 1:
                        right->rotateLeftRight();
                        //(calc new balances)
                        break;
                    case -1:
                        rotateRight();
                        //(calc new balances)
                        break;
                }
                return false;
        }
    } else {
        //right child
        switch (prev->balance) {
            case -1:
                prev->balance = 0;
                return false;
            case 0:
                prev->balance = 1;
                return true;
            case 1:
                switch (this->balance) {
                    case 1:
                        rotateLeft();
                        //(calc new balances)
                        break;
                    case -1:
                        left->rotateRightLeft();
                        //(calc new balances)
                        break;
                }
                return false;
        }
    }
}

/********************************************************************
 * remove
 *******************************************************************/

void AVLTree::remove(const int) {
}

void AVLTree::Node::remove(const int) {

}

void AVLTree::Node::upOut() {

}

AVLTree::Node *AVLTree::Node::geometricNext() const {
    return nullptr;
}

/********************************************************************
 * rotations
 *******************************************************************/

void AVLTree::Node::rotateLeft() {
    if (prev->prev != nullptr) {
        if (prev == prev->prev->right) {
            prev->prev->right = this;
        } else {
            prev->prev->left = this;
        }
    }
    auto prePreTmp = prev->prev;
    if (left != nullptr) {
        left->prev = prev;
    }
    prev->right = left;
    left = prev;
    prev->prev = this;
    prev = prePreTmp;
    balance = 0;
    left->balance = 0;
}

void AVLTree::Node::rotateLeftRight() {
    int startBalance = this->balance;
    rotateLeft();
    rotateRight();
    if (startBalance == -1) {
        right->balance = 1;
    } else if (startBalance == 1) {
        left->balance = -1;
    }
}

void AVLTree::Node::rotateRight() {
    if (prev->prev != nullptr) {
        if (prev == prev->prev->right) {
            prev->prev->right = this;
        } else {
            prev->prev->left = this;
        }
    }
    auto prePreTmp = prev->prev;
    if (right != nullptr) {
        right->prev = prev;
    }
    prev->left = right;
    right = prev;
    prev->prev = this;
    prev = prePreTmp;
    balance = 0;
    right->balance = 0;
}

void AVLTree::Node::rotateRightLeft() {
    int startBalance = this->balance;
    rotateRight();
    rotateLeft();
    if (startBalance == -1) {
        right->balance = 1;
    } else if (startBalance == 1) {
        left->balance = -1;
    }
}

/********************************************************************
 * traversal
 *******************************************************************/

vector<int> *AVLTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AVLTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AVLTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AVLTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AVLTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AVLTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

/********************************************************************
 * operator<< (output)
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AVLTree &tree) {
    function<void(std::ostream &, const int, const AVLTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AVLTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}

//<For Testing Only>

bool AVLTree::isBalanced() const {
    return isBalanced(root);
}

bool AVLTree::isBalanced(Node *node) const {
    bool r;
    if (node == nullptr) {
        r = true;
    } else if (abs(height(node->left) - height(node->right)) > 1) {
        r = false;
    } else {
        r = isBalanced(node->left) && isBalanced(node->right);
    }
    return r;
}

int AVLTree::height() const {
    return height(root);
}

int AVLTree::height(Node *node) const {
    int r;
    if (node == nullptr) {
        r = 0;
    } else {
        r = 1 + max(height(node->left), height(node->right));
    }
    return r;
}
//</For Testing Only>