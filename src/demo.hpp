#ifndef TREES_DEMO_HPP
#define TREES_DEMO_HPP

#include <map>
#include "trees/trees.hpp"

using namespace Trees;

class InvalidInputException
        :public Exception {

public:

    InvalidInputException();

    InvalidInputException( string message );

};

class Demo {

    map< string, BSTree< Wrapper< int>> * > treeMap;

    string currentTree;

    bool containsTree( string treeName );

    bool end;

    void foreachTree( function< void( BSTree< Wrapper< int>> * ) > processingFunction );

    void displayHelp();

    void displayPrompt();

    vector<string> getTokens( string input );

    void interpretAndExecute( string input ) throw( InvalidInputException& );

public:

    Demo();

    void start();

    void loop();

    void stop();

    ~Demo();

};

#endif //TREES_DEMO_HPP
