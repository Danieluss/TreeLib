#include "demo.hpp"
#include "trees/trees.hpp"
#include <gtest/gtest.h>
#include <string>

#define STDBST BSTree< Wrapper< int>>*

void Demo::foreachTree( function< void( STDBST ) > processingFunction ) {
    for ( auto it = treeMap.begin(); it != treeMap.end(); it++ ) {
        processingFunction( it->second );
    }
}

void Demo::displayPrompt() {
    cout<<"$ " + currentTree + " >";
}

void Demo::displayHelp() {
    cout<<"change \"name\""<<endl;//
    cout<<"- changes the current tree"<<endl;
    cout<<"print \"name\""<<endl;//
    cout<<"- prints the current tree on console or the one corresponding to a given name"<<endl;
    cout<<"list"<<endl;//
    cout<<"- prints all available trees"<<endl;
    cout<<"create \"name\" \"type\""<<endl;//
    cout<<"- creates new tree of type \"type\"=\"bs\"|\"rb\"|\"splay\"|\"avl\""<<endl;
    cout<<"delete \"name\""<<endl;//
    cout<<"- deletes the current tree or the one corresponding to a given name"<<endl;
    cout<<"add \"id...\""<<endl;//
    cout<<"- adds new nodes to the current tree"<<endl;
    cout<<"remove \"id...\""<<endl;//
    cout<<"- removes a nodes from the current tree"<<endl;
    cout<<"contains \"id...\""<<endl;//
    cout<<"- checks if the current tree contains nodes corresponding to given ids"<<endl;
    cout<<"span \"name\" \"name\""<<endl;//
    cout<<"- spans two trees"<<endl;
    cout<<"test"<<endl;//
    cout<<"- runs all tests"<<endl;
    cout<<"balance \"name\""<<endl;//
    cout<<"- balances given tree or current"<<endl;
    cout<<"quit"<<endl;//
    cout<<"- exits the programme"<<endl;
}

Demo::Demo() {}

void Demo::start() {
    end = false;
    currentTree = "";
    cout<<"Type in \"help\" for help"<<endl;
    loop();
}

void Demo::loop() {
    while ( !end ) {
        displayPrompt();
        string input;
        getline( cin, input );
        try {
            interpretAndExecute( input );
        } catch ( InvalidInputException &ex ) {
            cout<<ex.getMessage()<<endl;
        }
    }
}

void Demo::stop() {
    end = true;
}

Demo::~Demo() {
    foreachTree( []( STDBST tree ) -> void {
        tree->removeAll();
    } );
}

void Demo::interpretAndExecute( string input ) throw( InvalidInputException& ) {
    vector< string > tokens = getTokens( input );
    bool valid = false;
    if ( tokens.size() == 0 )
        throw ( InvalidInputException());
    if ( tokens[0] == "help" ) {
        displayHelp();
        valid = true;
    } else if ( tokens[0] == "print" ) {
        if ( tokens.size() == 2 && containsTree( tokens[1] )) {
            treeMap[tokens[1]]->print( cout );
        } else if ( tokens.size() == 1 && containsTree( currentTree )) {
            treeMap[currentTree]->print( cout );
        }
        valid = true;
    } else if ( tokens[0] == "balance" ) {
        if ( tokens.size() == 2 && containsTree( tokens[1] )) {
            treeMap[tokens[1]]->balance();
        } else if ( tokens.size() == 1 && containsTree( currentTree )) {
            treeMap[currentTree]->balance();
        }
        valid = true;
    } else if ( tokens[0] == "change" ) {
        if ( tokens.size() == 2 && containsTree( tokens[1] )) {
            currentTree = tokens[1];
            valid = true;
        }
    } else if ( tokens[0] == "create" ) {
        if ( tokens.size() == 3 && !containsTree( tokens[1] )) {
            if ( tokens[2] == "bst" )
                treeMap[tokens[1]] = new BSTree< Wrapper< int>>();
            else if ( tokens[2] == "rb" )
                treeMap[tokens[1]] = new RBTree< Wrapper< int>>();
            else if ( tokens[2] == "avl" )
                treeMap[tokens[1]] = new AVLTree< Wrapper< int>>();
            else if ( tokens[2] == "splay" )
                treeMap[tokens[1]] = new SplayTree< Wrapper< int>>();
            if ( !containsTree( currentTree ))
                interpretAndExecute( "change " + tokens[1] );
            valid = true;
        }
    } else if ( tokens[0] == "delete" ) {
        string name = "";
        if ( tokens.size() == 2 ) {
            name = tokens[1];
        } else if ( tokens.size() == 1 ) {
            name = currentTree;
        }
        if ( name == currentTree )
            currentTree = "";
        if ( containsTree( name )) {
            treeMap[name]->removeAll();
            delete treeMap[name];
            treeMap.erase( name );
            valid = true;
        }
    } else if ( tokens[0] == "add" ) {
        if ( tokens.size() >= 2 && containsTree( currentTree )) {
            for ( int i = 1; i < tokens.size(); i++ ) {
                int number = stoi( tokens[i] );
                try {
                    treeMap[currentTree]->insert( new Wrapper< int >( number ));
                } catch ( InvalidKeyException &ex ) {
                    cout<<number<<" "<<ex.getMessage()<<endl;
                }
            }
            valid = true;
        }
    } else if ( tokens[0] == "remove" ) {
        if ( tokens.size() >= 2 && containsTree( currentTree )) {
            for ( int i = 1; i < tokens.size(); i++ ) {
                int number = stoi( tokens[i] );
                auto removalTmp = new Wrapper< int >( number );
                try {
                    treeMap[currentTree]->remove( removalTmp );
                } catch ( KeyNotFoundException &ex ) {
                    cout<<number<<" "<<ex.getMessage()<<endl;
                }
                delete removalTmp;
            }
            valid = true;
        }
    } else if ( tokens[0] == "contains" ) {
        if ( tokens.size() >= 2 && containsTree( currentTree )) {
            for ( int i = 1; i < tokens.size(); i++ ) {
                int number = stoi( tokens[i] );
                auto containsTmp = new Wrapper< int >( number );
                bool contains = false;
                contains = treeMap[currentTree]->contains( containsTmp );
                if ( contains )
                    cout<<number<<" YES"<<endl;
                else
                    cout<<number<<" NO"<<endl;
                delete containsTmp;
            }
            valid = true;
        }
    } else if ( tokens[0] == "quit" ) {
        stop();
        valid = true;
    } else if ( tokens[0] == "span" ) {
        if ( tokens.size() == 3 ) {
            if ( containsTree( tokens[1] ) && containsTree( tokens[2] )) {
                auto tmpVector = treeMap[tokens[2]]->toVector( PREORDER );
                treeMap[tokens[1]]->insert( tmpVector );
                treeMap[tokens[2]]->popAll();
                delete treeMap[tokens[2]];
                treeMap.erase(tokens[2]);
                if( currentTree == tokens[2] )
                    currentTree = "";
            }
            valid = true;
        }
    } else if ( tokens[0] == "test" ) {
        RUN_ALL_TESTS();
        valid = true;
    } else if ( tokens[0] == "list" ) {
        for ( auto it = treeMap.begin(); it != treeMap.end(); ++it ) {
            cout<<" |"<<it->first<<"| ";
        }
        valid = true;
        cout<<endl;
    }
    if ( !valid )
        throw InvalidInputException();
}

bool Demo::containsTree( string treeName ) {
    return treeMap.count( treeName );
}

vector< string > Demo::getTokens( string input ) {
    vector< string > returnVector;
    int index, previousIndex = 0;
    while (( index = input.find( " ", previousIndex )) != string::npos ) {
        returnVector.push_back( input.substr( previousIndex, index - previousIndex ));
        previousIndex = index + 1;
    }
    returnVector.push_back( input.substr( previousIndex, input.length()));
    return returnVector;
}


InvalidInputException::InvalidInputException()
        : Exception( "Invalid input" ) {}

InvalidInputException::InvalidInputException( string message )
        : Exception( message ) {}
