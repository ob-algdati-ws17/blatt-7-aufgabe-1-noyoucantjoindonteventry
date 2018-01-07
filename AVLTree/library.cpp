#include "library.h"
//#include <functional>

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
                    case LEFT:
                        rotateRight();
                        balance = EQUAL;
                        right->balance = EQUAL;
                        break;
                    case RIGHT: {
                        Balance startBalance = right->balance;
                        right->rotateLeftRight();
                        prev->balance = EQUAL;
                        switch (startBalance) {
                            case LEFT:
                                balance = EQUAL;
                                prev->right->balance = RIGHT;
                                break;
                            case EQUAL:
                                balance = EQUAL;
                                prev->right->balance = EQUAL;
                                break;
                            case RIGHT:
                                balance = LEFT;
                                prev->right->balance = EQUAL;
                                break;
                            default:
                                throw "Illegal Balance!";
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
                        switch (startBalance) {
                            case LEFT:
                                balance = RIGHT;
                                prev->left->balance = EQUAL;
                                break;
                            case EQUAL:
                                balance = EQUAL;
                                prev->left->balance = EQUAL;
                                break;
                            case RIGHT:
                                balance = EQUAL;
                                prev->left->balance = LEFT;
                                break;
                            default:
                                throw "Illegal Balance!";
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

void AVLTree::remove(const int value) {
    if (root != nullptr) {
        if (root->key == value) {
            if (root->right == nullptr && root->left == nullptr) {
                root->remove(value);
                root = nullptr;
            } else {
                auto rootTmp = root->left != nullptr ? root->left : root->right;
                root->remove(value);
                root = rootTmp;
            }
        }
        if (root != nullptr) {
            while (root->prev != nullptr) {
                root = root->prev;
            }
        }
    }
}

void AVLTree::Node::remove(const int value) {
    if (value < key) {
        if (left != nullptr) {
            left->remove(value);
        }
    } else if (value > key) {
        if (right != nullptr) {
            right->remove(value);
        }
    } else {
        if (left == nullptr && right == nullptr) {
            remove0Children();
        } else if (left == nullptr || right == nullptr) {
            remove1Child();
        } else {
            remove2Children();
        }
        delete this;
    }
}

void AVLTree::Node::remove0Children() {
    if (prev == nullptr) { return; }
    if (this == prev->left) {
        //left child of prev
        prev->left = nullptr;
        switch (prev->balance) {
            case LEFT:
                prev->balance = EQUAL;
                prev->upOut();
                break;
            case EQUAL:
                prev->balance = RIGHT;
                break;
            case RIGHT:
                if (prev->right->right == nullptr) {
                    prev->right->left->rotateRightLeft();
                    prev->prev->right->balance = EQUAL;
                    prev->prev->balance = EQUAL;
                    prev->prev->upOut();
                } else if (prev->right->left == nullptr) {
                    prev->right->rotateLeft();
                    prev->prev->balance = EQUAL;
                    prev->prev->upOut();
                } else {
                    prev->right->rotateLeft();
                    prev->prev->right->balance = RIGHT;
                }
                prev->balance = EQUAL;
                break;
        }
    } else {
        //right child of prev
        prev->right = nullptr;
        switch (prev->balance) {
            case RIGHT:
                prev->balance = EQUAL;
                prev->upOut();
                break;
            case EQUAL:
                prev->balance = LEFT;
                break;
            case LEFT:
                if (prev->left->left == nullptr) {
                    prev->left->left->rotateLeftRight();
                    prev->prev->left->balance = EQUAL;
                    prev->prev->balance = EQUAL;
                    prev->prev->upOut();
                } else if (prev->left->right == nullptr) {
                    prev->left->rotateRight();
                    prev->prev->balance = EQUAL;
                    prev->prev->upOut();
                } else {
                    prev->left->rotateRight();
                    prev->prev->left->balance = LEFT;
                }
                prev->balance = EQUAL;
                break;
        }
    }
}

void AVLTree::Node::remove1Child() {
    if (prev == nullptr) { return; }
    AVLTree::Node *b;
    if (left != nullptr) {
        b = left;
    } else {
        b = right;
    }
    if (this == prev->left) {
        //left child
        prev->left = b;
    } else {
        //right child
        prev->right = b;
    }
    b->prev = prev;
    left = nullptr;
    right = nullptr;
    prev->upOut();
}

void AVLTree::Node::remove2Children() {
    auto geoNext = right;
    while (geoNext->left != nullptr) {
        geoNext = geoNext->left;
    }

    auto geoNextCopy = new Node(geoNext->key, prev, left, right);
    geoNextCopy->balance = balance;
    if (prev != nullptr) {
        if (this == prev->right) {
            prev->right = geoNextCopy;
        } else {
            prev->left = geoNextCopy;
        }
    }
    right->prev = geoNextCopy;
    left->prev = geoNextCopy;

    right->remove(geoNext->key);
    right = nullptr;
    left = nullptr;
}

void AVLTree::Node::upOut() {
    if (prev == nullptr) { return; }
    if (this == prev->left) {
        //left child
        switch (prev->balance) {
            case LEFT:
                prev->balance = EQUAL;
                prev->upOut();
                break;
            case EQUAL:
                prev->balance = RIGHT;
                break;
            case RIGHT:
                switch (prev->right->balance) {
                    case LEFT: {
                        Balance startBalance = prev->right->left->balance;
                        prev->right->left->rotateRightLeft();
                        prev->prev->balance = EQUAL;
                        switch (startBalance) {
                            case LEFT:
                                prev->balance = EQUAL;
                                prev->prev->right->balance = RIGHT;
                                break;
                            case EQUAL:
                                prev->balance = EQUAL;
                                prev->prev->right->balance = EQUAL;
                                break;
                            case RIGHT:
                                prev->balance = LEFT;
                                prev->prev->right->balance = EQUAL;
                                break;
                            default:
                                throw "Illegal Balance!";
                        }
                        prev->prev->upOut();
                        break;
                    }
                    case EQUAL:
                        prev->right->rotateLeft();
                        prev->prev->balance = LEFT;
                        break;
                    case RIGHT:
                        prev->right->rotateLeft();
                        prev->balance = EQUAL;
                        prev->prev->balance = EQUAL;
                        break;
                    default:
                        throw "Illegal Balance!";
                }
                break;
            default:
                throw "Illegal Balance!";
        }
    } else {
        //right child
        switch (prev->balance) {
            case LEFT:
                switch (prev->left->balance) {
                    case LEFT:
                        prev->left->rotateRight();
                        prev->balance = EQUAL;
                        prev->prev->balance = EQUAL;
                        break;
                    case EQUAL:
                        prev->left->rotateRight();
                        prev->prev->balance = RIGHT;
                        break;
                    case RIGHT: {
                        Balance startBalance = prev->left->right->balance;
                        prev->left->right->rotateLeftRight();
                        prev->prev->balance = EQUAL;
                        switch (startBalance) {
                            case LEFT:
                                prev->balance = RIGHT;
                                prev->prev->left->balance = EQUAL;
                                break;
                            case EQUAL:
                                prev->balance = EQUAL;
                                prev->prev->left->balance = EQUAL;
                                break;
                            case RIGHT:
                                prev->balance = EQUAL;
                                prev->prev->left->balance = LEFT;
                                break;
                            default:
                                throw "Illegal Balance!";
                        }
                        prev->prev->upOut();
                        break;
                    }
                    default:
                        throw "Illegal Balance!";
                }
                break;
            case EQUAL:
                prev->balance = LEFT;
                break;
            case RIGHT:
                prev->balance = EQUAL;
                prev->upOut();
                break;
            default:
                throw "Illegal Balance!";
        }
    }
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

///********************************************************************
// * operator<< (output)
// *******************************************************************/
//std::ostream &operator<<(std::ostream &os, const AVLTree &tree) {
//    function<void(std::ostream &, const int, const AVLTree::Node *, const string)> printToOs
//            = [&](std::ostream &os, const int value, const AVLTree::Node *node, const string l) {
//
//                static int nullcount = 0;
//
//                if (node == nullptr) {
//                    os << "    null" << nullcount << "[shape=point];" << endl;
//                    os << "    " << value << " -> null" << nullcount
//                       << " [label=\"" << l << "\"];" << endl;
//                    nullcount++;
//                } else {
//                    os << "    " << value << " -> " << node->key
//                       << " [label=\"" << l << "\"];" << endl;
//
//                    printToOs(os, node->key, node->left, "l");
//                    printToOs(os, node->key, node->right, "r");
//                }
//            };
//    os << "digraph tree {" << endl;
//    if (tree.root == nullptr) {
//        os << "    null " << "[shape=point];" << endl;
//    } else {
//        printToOs(os, tree.root->key, tree.root->left, "l");
//        printToOs(os, tree.root->key, tree.root->right, "r");
//    }
//    os << "}" << endl;
//    return os;
//}

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
                throw "Illegal Balance!";
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