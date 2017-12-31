#include "testAVL.h"
#include <memory>

using namespace std;

// empty list

TEST(AVLTest, EmptyTest) { // NOLINT
    auto a = new AVLTree();
    EXPECT_TRUE(a != nullptr);
    EXPECT_TRUE(a->isEmpty());
    EXPECT_EQ(a->height(),0);
    EXPECT_TRUE(a->isBalanced());
    delete a;

}TEST(AVLTest, NotEmptyTest) { // NOLINT
    auto a = new AVLTree();
    a->insert(1);
    EXPECT_TRUE(a != nullptr);
    EXPECT_FALSE(a->isEmpty());
    EXPECT_EQ(a->height(),1);
    EXPECT_TRUE(a->isBalanced());
    delete a;
}

TEST(AVLTest, insertThree_NoRotation) { // NOLINT
    auto a = new AVLTree();
    a->insert(2);
    a->insert(1);
    a->insert(3);
    EXPECT_EQ(a->height(),2);
    EXPECT_TRUE(a->isBalanced());
    delete a;
}

TEST(AVLTest, insertThree_WithRoatationLeft) { // NOLINT
    auto a = new AVLTree();
    a->insert(1);
    a->insert(2);
    a->insert(3);
    EXPECT_EQ(a->height(),2);
    EXPECT_TRUE(a->isBalanced());
    delete a;
}

TEST(AVLTest, insertThree_WithRoatationRight) { // NOLINT
    auto a = new AVLTree();
    a->insert(3);
    a->insert(2);
    a->insert(1);
    EXPECT_EQ(a->height(),2);
    EXPECT_TRUE(a->isBalanced());
    delete a;
}

TEST(AVLTest, insert2Through6_NoRotationAndSearchAll) { // NOLINT
    auto a = new AVLTree();
    a->insert(4);
    a->insert(2);
    a->insert(6);
    a->insert(3);
    a->insert(5);
    cout << *a;
    EXPECT_EQ(a->height(),3);
    EXPECT_TRUE(a->isBalanced());
    EXPECT_TRUE(a->search(2));
    EXPECT_TRUE(a->search(3));
    EXPECT_TRUE(a->search(4));
    EXPECT_TRUE(a->search(5));
    EXPECT_TRUE(a->search(6));
    delete a;
}