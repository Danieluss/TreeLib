#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "../src/trees/trees.hpp"
#include "test_utils.hpp"

#define MAXNODES 1<<14
#define ITERATIONS 1<<18

using namespace Trees;
using namespace std;

TEST( crash, BST ) {
    auto tree = new BSTree<Wrapper<int>>();
    TestUtils::crash( tree, MAXNODES, ITERATIONS );
    tree->removeAll();
    delete tree;
}

TEST( crash, AVL ) {
    auto tree = new AVLTree<Wrapper<int>>();
    TestUtils::crash( tree, MAXNODES, ITERATIONS );
    tree->removeAll();
    delete tree;
}

TEST( crash, RBT ) {
    auto tree = new RBTree<Wrapper<int>>();
    TestUtils::crash( tree, MAXNODES, ITERATIONS );
    ASSERT_EQ(tree->areColorsViolated(), 0);
    tree->removeAll();
    delete tree;
}

TEST( crash, SPLAY ) {
    auto tree = new SplayTree<Wrapper<int>>();
    TestUtils::crash( tree, MAXNODES, ITERATIONS );
    tree->removeAll();
    delete tree;
}