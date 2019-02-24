#include "src/trees/trees.hpp"
#include <gtest/gtest.h>
#include "src/demo.hpp"
using namespace std;
using namespace Trees;

int main( int argc, char **argv ) {
    srand( time( 0 ));
    // TESTING {
//    testing::InitGoogleTest(&argc, argv);
//    RUN_ALL_TESTS();
    // } TESTING
    Demo* demo = new Demo();
    demo->start();
    delete demo;
    return 0;
}