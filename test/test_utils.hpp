#ifndef TREES_TESTUTILS_HPP
#define TREES_TESTUTILS_HPP

#include "../src/trees/trees.hpp"
#include <vector>

class TestUtils {

private:

    static vector<int> getRandomSequence( int from, int to );

public:

    static vector< int > getVector( Trees::BSTree< Trees::Wrapper< int>> *tree );

    static void crash( Trees::BSTree< Trees::Wrapper< int>> *tree, int numberOfNodes, int iterations );

    static void testExceptions( Trees::BSTree< Trees::Wrapper< int>> *tree );

    static void testCorrectness( vector< vector< int>> expectedValuesVector, Trees::BSTree<Trees::Wrapper<int>>* tree );

};

#endif //TREES_TESTUTILS_HPP
