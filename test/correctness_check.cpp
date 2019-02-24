#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include "../src/trees/trees.hpp"
#include "test_utils.hpp"

using namespace testing;
using namespace Trees;

TEST( correctness, RBT ) {
    vector< vector< int>> expectedValuesVectors =
            {{3,  1,  0,  2,  7,  5,  4,  6,  9,  8,  11, 10, 13, 12, 14},
             {3,  1,  0,  2,  6,  5,  4,  13, 14},
             {3,  1,  0,  2,  6,  5,  4,  13, 14},
             {6,  13, 14},
             {14, 6,  13, 31, 30, 33, 32, 34, 35},
             {5,  3,  1,  0,  2,  4,  14, 6,  13, 31, 30, 33, 32, 34, 35},
             {13, 3,  1,  0,  2,  5,  4,  6,  32, 30, 14, 31, 34, 33, 35}};
    auto tree = new RBTree< Wrapper< int >>();
    TestUtils::testCorrectness( expectedValuesVectors, tree );
    ASSERT_EQ( tree->areColorsViolated(), 0 );
    for ( int i = 100; i < 10000; ++i ) {
        tree->insert( new Wrapper< int >( i ));
    }
    ASSERT_EQ( tree->areColorsViolated(), 0 );
    for ( int i = 4000; i < 6000; ++i ) {
        tree->remove( new Wrapper< int >( i ));
    }
    ASSERT_EQ( tree->areColorsViolated(), 0 );
    tree->removeAll();
    delete tree;
}

TEST( correctness, AVL ) {
    auto tree = new AVLTree< Wrapper< int >>();
    vector< vector< int>> expectedValuesVector =
            {{7,  3,  1, 0,  2,  5,  4,  6,  11, 9,  8,  10, 13, 12, 14},
             {6,  3,  1, 0,  2,  5,  4,  13, 14},
             {6,  3,  1, 0,  2,  5,  4,  13, 14},
             {13, 6,  14},
             {30, 13, 6, 14, 32, 31, 34, 33, 35},
             {30, 5,  3, 1,  0,  2,  4,  13, 6,  14, 32, 31, 34, 33, 35},
             {13, 3,  1, 0,  2,  5,  4,  6,  32, 30, 14, 31, 34, 33, 35}};
    TestUtils::testCorrectness( expectedValuesVector, tree );
    tree->removeAll();
    delete tree;
}

TEST( correctness, BST ) {
    auto tree = new BSTree< Wrapper< int >>();
    vector< vector< int>> expectedValuesVector =
            {{0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14},
             {0,  1,  2,  3,  4,  5,  6,  13, 14},
             {0,  1,  2,  3,  4,  5,  6,  13, 14},
             {6,  13, 14},
             {6,  13, 14, 30, 31, 32, 33, 34, 35},
             {6,  5,  4,  3,  2,  1,  0,  13, 14, 30, 31, 32, 33, 34, 35},
             {13, 3,  1,  0,  2,  5,  4,  6,  32, 30, 14, 31, 34, 33, 35}};
    TestUtils::testCorrectness( expectedValuesVector, tree );
    tree->removeAll();
    delete tree;
}

TEST( correctness, SPLAY ) {
    auto tree = new SplayTree< Wrapper< int >>();
    vector< vector< int>> expectedValuesVector =
            {{14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
             {14, 6,  5,  4,  3,  2,  1,  0,  13},
             {5,  4,  3,  2,  1,  0,  14, 6,  13},
             {14, 6,  13},
             {35, 34, 33, 32, 31, 30, 14, 6,  13},
             {0,  1,  2,  3,  4,  5,  34, 32, 30, 6,  14, 13, 31, 33, 35},
             {13, 3,  1,  0,  2,  5,  4,  6,  32, 30, 14, 31, 34, 33, 35}};
    TestUtils::testCorrectness( expectedValuesVector, tree );
    tree->removeAll();
    delete tree;
}