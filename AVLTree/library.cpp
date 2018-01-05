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
            if (this->balance == EQUAL) {
                this->balance = LEFT;
                return this->upIn();
            } else {
                this->balance = EQUAL;
            }
        } else if (left->insert(value)) {
            return this->upIn();
        }
    } else {
        if (right == nullptr) {
            right = new AVLTree::Node(value, this);
            //inserted node on the right, check balance
            if (this->balance == EQUAL) {
                this->balance = RIGHT;
                return this->upIn();
            } else {
                this->balance = EQUAL;
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
            case RIGHT:
                prev->balance = EQUAL;
                return false;
            case EQUAL:
                prev->balance = LEFT;
                return true;
            case LEFT:
                switch (this->balance) {
                    case RIGHT: {
                        Balance startBalance = right->balance;
                        right->rotateLeftRight();
                        prev->balance = EQUAL;
                        if (startBalance == LEFT) {
                            balance = EQUAL;
                            prev->right->balance = RIGHT;
                        } else if (startBalance == RIGHT) {
                            balance = LEFT;
                            prev->right->balance = EQUAL;
                        } else {
                            balance = EQUAL;
                            prev->right->balance = EQUAL;
                        }
                        break;
                    }
                    case LEFT:
                        rotateRight();
                        balance = EQUAL;
                        right->balance = EQUAL;
                        break;
                    default:
                        throw "Illegal Balance!";
                }
                return false;
            default:
                throw "Illegal Balance!";
        }
    } else {
        //right child
        switch (prev->balance) {
            case LEFT:
                prev->balance = EQUAL;
                return false;
            case EQUAL:
                prev->balance = RIGHT;
                return true;
            case RIGHT:
                switch (this->balance) {
                    case RIGHT:
                        rotateLeft();
                        balance = EQUAL;
                        left->balance = EQUAL;
                        break;
                    case LEFT: {
                        Balance startBalance = left->balance;
                        left->rotateRightLeft();
                        prev->balance = EQUAL;
                        if (startBalance == LEFT) {
                            balance = RIGHT;
                            prev->left->balance = EQUAL;
                        } else if (startBalance == RIGHT) {
                            balance = EQUAL;
                            prev->left->balance = LEFT;
                        } else {
                            balance = EQUAL;
                            prev->left->balance = EQUAL;
                        }
                        break;
                    }
                    default:
                        throw "Illegal Balance!";
                }
                return false;
            default:
                throw "Illegal Balance!";
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
}

void AVLTree::Node::rotateLeftRight() {
    rotateLeft();
    rotateRight();
}

void AVLTree::Node::rotateRightLeft() {
    rotateRight();
    rotateLeft();
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

bool AVLTree::isSorted(AVLTree::Node *node) const {
    bool r;
    if (node == nullptr) {
        r = true;
    } else {
        r = !(node->left != nullptr && node->left->key >= node->key ||
              node->right != nullptr && node->right->key <= node->key);
    }
    return r;
}

bool AVLTree::isSorted() const {
    return isSorted(root);
}

bool AVLTree::isBalanced() const {
    return isBalanced(root);
}

bool AVLTree::isBalanced(Node *node) const {
    bool r;
    if (node == nullptr) {
        r = true;
    } else {
        int heightDif = height(node->right) - height(node->left);
        Balance actualBalance;
        switch (heightDif) {
            case -1:
                actualBalance = LEFT;
                break;
            case 0:
                actualBalance = EQUAL;
                break;
            case 1:
                actualBalance = RIGHT;
                break;
            default:
                throw "Illegal Balance";
        }
        if ((abs(heightDif) > 1) || (actualBalance != node->balance)) {
            r = false;
        } else {
            r = isBalanced(node->left) && isBalanced(node->right);
        }
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