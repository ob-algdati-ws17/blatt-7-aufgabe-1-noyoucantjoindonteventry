#include "testAVL.h"

using namespace std;

// empty list

TEST(AVLTest, EmptyTest) { // NOLINT
    auto a = new AVLTree();
    EXPECT_TRUE(a != nullptr);
    EXPECT_TRUE(a->isEmpty());
    EXPECT_EQ(a->height(), 0);
    EXPECT_FALSE(a->search(1));
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;

}

TEST(AVLTest, NotEmptyTest) { // NOLINT
    auto a = new AVLTree();
    a->insert(1);
    EXPECT_TRUE(a != nullptr);
    EXPECT_FALSE(a->isEmpty());
    EXPECT_EQ(a->height(), 1);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertThree_NoRotation) { // NOLINT
    auto a = new AVLTree();
    a->insert(2);
    a->insert(1);
    a->insert(3);
    EXPECT_EQ(a->height(), 2);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertThree_RoatationLeft) { // NOLINT
    auto a = new AVLTree();
    a->insert(1);
    a->insert(2);
    a->insert(3);
    EXPECT_EQ(a->height(), 2);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertThree_RoatationRight) { // NOLINT
    auto a = new AVLTree();
    a->insert(3);
    a->insert(2);
    a->insert(1);
    EXPECT_EQ(a->height(), 2);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertThree_RoatationLeftRight) { // NOLINT
    auto a = new AVLTree();
    a->insert(3);
    a->insert(1);
    a->insert(2);
    EXPECT_EQ(a->height(), 2);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertThree_RoatationRightLeft) { // NOLINT
    auto a = new AVLTree();
    a->insert(1);
    a->insert(3);
    a->insert(2);
    EXPECT_EQ(a->height(), 2);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertRandom_50) { // NOLINT
    auto a = new AVLTree();
    for (int i = 0; i < 50; i++) {
        a->insert(rand() % 100);
    }
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insertRandom_10000) { // NOLINT
    auto a = new AVLTree();
    for (int i = 0; i < 10000; i++) {
        a->insert(rand()); //~32k different values
    }
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

TEST(AVLTest, insert_2Through6_NoRotation_SearchAll) { // NOLINT
    auto a = new AVLTree();
    a->insert(4);
    a->insert(2);
    a->insert(6);
    a->insert(3);
    a->insert(5);
    EXPECT_EQ(a->height(), 3);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    EXPECT_TRUE(a->search(2));
    EXPECT_TRUE(a->search(3));
    EXPECT_TRUE(a->search(4));
    EXPECT_TRUE(a->search(5));
    EXPECT_TRUE(a->search(6));
    delete a;
}

TEST(AVLTest, insertThree_DeleteWithoutChildren) { // NOLINT
    auto a = new AVLTree();
    a->insert(2);
    a->insert(1);
    a->insert(4);
    a->insert(3);
    a->insert(5);
    a->remove(3);
}

TEST(AVLTest, insertRandom_30k_RemoveRandom_15k) { // NOLINT
    auto a = new AVLTree();
    int count = 15000;
    for (int i = 0; i < count*2; i++) {
        a->insert(rand() % (count*2));
    }
    for (int i = 0; i < count; i++) {
        a->remove(rand() % (count*2));
    }
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->isSorted());
    delete a;
}

