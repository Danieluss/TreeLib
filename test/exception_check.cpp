#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "../src/trees/trees.hpp"
#include "test_utils.hpp"

using namespace Trees;

TEST( exception, RBT ) {
    vector<int> retC;
    auto tree = new RBTree< Wrapper< int >>();
    ASSERT_THROW( new RBTree<int>();, Trees::TypeException);
    TestUtils::testExceptions( tree );
    tree->removeAll();
    delete tree;
}


TEST( exception, AVL ) {
    vector<int> retC;
    auto tree = new AVLTree< Wrapper< int >>();
    ASSERT_THROW( new AVLTree<int>();, Trees::TypeException);
    TestUtils::testExceptions( tree );
    tree->removeAll();
    delete tree;
}


TEST( exception, SPLAY ) {
    vector<int> retC;
    auto tree = new SplayTree< Wrapper< int >>();
    ASSERT_THROW( new SplayTree<int>();, Trees::TypeException);
    TestUtils::testExceptions( tree );
    tree->removeAll();
    delete tree;
}

TEST( exception, BST ) {
    vector<int> retC;
    auto tree = new BSTree< Wrapper< int >>();
    ASSERT_THROW( new BSTree<int>();, Trees::TypeException);
    TestUtils::testExceptions( tree );
    tree->removeAll();
    delete tree;
}