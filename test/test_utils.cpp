#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "test_utils.hpp"
#include <vector>
#include <random>

using namespace Trees;

vector< int > TestUtils::getVector( Trees::BSTree< Trees::Wrapper< int>> *tree ) {
    vector< int > returnVector;
    tree->process(
            [ &returnVector ]( Trees::Wrapper< int > *node ) -> void {
                returnVector.push_back( node->getKey());
            }, PREORDER );
    return returnVector;
}

void TestUtils::crash( Trees::BSTree< Trees::Wrapper< int>> *tree, int numberOfNodes, int iterations ) {
    mt19937 randomNumberGenerator;
    randomNumberGenerator.seed( time( 0 ));
    uniform_int_distribution< int > uniformDistribution0_255( 0, 255 );
    uniform_int_distribution< int > uniformDistribution0_1000000( 0, 1000000 );
    vector< int > removedNodesVector = TestUtils::getRandomSequence( 0, numberOfNodes - 1 );
    vector< int > addedNodesVector;
    for ( int i = 0; i < iterations; ++i ) {
        int steer = uniformDistribution0_255( randomNumberGenerator );
        if ( steer < 96 && addedNodesVector.size() > 0 ) {
            int count = uniformDistribution0_1000000( randomNumberGenerator )%addedNodesVector.size();
            for ( int j = 0; j < count; ++j ) {
                int removeValue = addedNodesVector.back();
                auto wrapper = new Wrapper< int >( removeValue );
                bool returnedFlag = tree->remove( wrapper );
                delete wrapper;
                addedNodesVector.pop_back();
                ASSERT_EQ( returnedFlag, 1);
            }
        } else if ( steer < 192 && removedNodesVector.size() > 0 ) {
            int count = uniformDistribution0_1000000( randomNumberGenerator )%removedNodesVector.size();
            for ( int j = 0; j < count; ++j ) {
                int insertValue = removedNodesVector.back();
                bool returnedFlag = tree->insert( new Wrapper<int>( insertValue ) );
                removedNodesVector.pop_back();
                ASSERT_EQ( returnedFlag, 1);
            }
        } else if ( steer < 255 && addedNodesVector.size() > 0 ) {
            int count = uniformDistribution0_1000000( randomNumberGenerator )%addedNodesVector.size();
            for ( int j = 0; j < count; ++j ) {
                int searchValue = addedNodesVector.back();
                auto wrapper = new Wrapper< int >( searchValue );
                bool returnedFlag = tree->contains( wrapper );
                delete wrapper;
                addedNodesVector.pop_back();
                ASSERT_EQ( returnedFlag, 1);
            }
        } else if ( steer < 256 ) {
            //tree->balance();//costly for RBT
        }
    }
    ASSERT_NO_THROW( tree->removeAll(); );
}

void TestUtils::testExceptions( Trees::BSTree< Trees::Wrapper< int>> *tree ) {
    tree->insert( new Trees::Wrapper< int >( 1 ));
    ASSERT_THROW( tree->insert( new Trees::Wrapper< int >( 1 ));, Trees::InvalidKeyException );
    ASSERT_THROW( tree->get( new Trees::Wrapper< int >( 10 ));, Trees::KeyNotFoundException );
    ASSERT_THROW( tree->remove( new Trees::Wrapper< int >( 10 ));, Trees::KeyNotFoundException );
    ASSERT_THROW( tree->pop( new Trees::Wrapper< int >( 10 ));, Trees::KeyNotFoundException );
}

void TestUtils::testCorrectness( vector< vector< int>> expectedValuesVector,
                                 Trees::BSTree< Trees::Wrapper< int>> *tree ) {
    vector< int > actualValuesVector;
    for ( int i = 0; i < 15; ++i )
        tree->insert( new Wrapper< int >( i ));
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[0] ));
    for ( int i = 7; i < 13; ++i ) {
        auto rem = new Wrapper< int >( i );
        tree->remove( rem );
        delete rem;
    }
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[1] ));
    bool f = 1;
    for ( int i = 0; i < 6; ++i ) {
        auto rem = new Wrapper< int >( i );
        f &= tree->contains( rem );
        delete rem;
    }
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_EQ( f, 1 );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[2] ));
    for ( int i = 0; i < 6; ++i ) {
        auto rem = new Wrapper< int >( i );
        tree->remove( rem );
        delete rem;
    }
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[3] ));
    for ( int i = 30; i < 36; ++i ) {
        tree->insert( new Wrapper< int >( i ));
    }
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[4] ));
    for ( int i = 5; i >= 0; --i ) {
        tree->insert( new Wrapper< int >( i ));
    }
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[5] ));
    tree->balance();
    actualValuesVector = TestUtils::getVector( tree );
    ASSERT_THAT( actualValuesVector, testing::ElementsAreArray( expectedValuesVector[6] ));
}

vector< int > TestUtils::getRandomSequence( int from, int to ) {
    int range = to - from + 1;
    int returnArray[range];
    mt19937 randomNumberGenerator;
    randomNumberGenerator.seed( time( 0 ));
    uniform_int_distribution< int > distribution( 0, range - 1 );
    for ( int i = 0; i < range; ++i ) {
        returnArray[i] = i + from;
    }
    for ( int i = 0; i < range*4; ++i ) {
        swap( returnArray[distribution( randomNumberGenerator )], returnArray[distribution( randomNumberGenerator )] );
    }
    vector< int > vec;
    for ( int i = 0; i < range; ++i ) {
        vec.push_back( returnArray[i] );
    }
    return vec;
}
