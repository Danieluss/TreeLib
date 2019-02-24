#ifndef BRTREE_BST_HPP
#define BRTREE_BST_HPP

#include "nodes.hpp"
#include "order.hpp"
#include "exceptions.hpp"
#include "datatypes.hpp"
#include "collection.hpp"
#include <queue>
#include <functional>
#include <fstream>
#include <cmath>

#define null nullptr
#define TNode TreeNode<Value>


namespace Trees {


    template< class Value >
    class BSTree
            : public Collection< Value > {

        std::function< void( TNode * ) > processingFunction;
        std::function< void( Value * ) > safeProcessingFunction;

        void processTree( TNode *from, Order order ) {
            if ( order == PREORDER )
                processingFunction( from );
            if ( from->left != null )
                processTree( from->left, order );
            if ( order == INORDER )
                processingFunction( from );
            if ( from->right != null )
                processTree( from->right, order );
            if ( order == POSTORDER )
                processingFunction( from );
        }

        void processTreeSafely( TNode *from, Order order ) {
            if ( order == PREORDER )
                safeProcessingFunction( from->data );
            if ( from->left != null )
                processTreeSafely( from->left, order );
            if ( order == INORDER )
                safeProcessingFunction( from->data );
            if ( from->right != null )
                processTreeSafely( from->right, order );
            if ( order == POSTORDER )
                safeProcessingFunction( from->data );
        }

    protected:

        int size;
        TNode *root;
        bool removalDirection;

        TNode *sibling( TNode *node, TNode *parent ) {
            TNode *ret = null;
            if ( parent != null )
                ret = parent->left == node ? parent->right : parent->left;
            return ret;
        }

        TNode *grandparent( TNode *node, TNode *parent ) {
            TNode *ret = null;
            if ( parent != null )
                ret = parent->parent;
            return ret;
        }

        TNode *uncle( TNode *node, TNode *parent ) {
            TNode *ret = null;
            if ( parent != null )
                ret = sibling( parent );
            return ret;
        }

        TNode *sibling( TNode *node ) {
            TNode *ret = null;
            if ( node != null && node != this->root )
                ret = node->parent->left == node ? node->parent->right : node->parent->left;
            return ret;
        }

        TNode *grandparent( TNode *node ) {
            TNode *ret = null;
            if ( node != null && node != this->root )
                ret = node->parent->parent;
            return ret;
        }

        TNode *uncle( TNode *node ) {
            TNode *ret = null;
            if ( node != null && node != this->root )
                ret = sibling( node->parent );
            return ret;
        }

        void process( std::function< void( TNode * ) > processingFunction, Order order ) {
            if ( root != null ) {
                this->processingFunction = processingFunction;
                processTree( root, order );
            }
        }

        virtual void rotateLeft( TNode *node ) {
            TNode *rightChild = node->right;
            node->right = rightChild->left;
            if ( node->right != null )
                node->right->parent = node;
            rightChild->parent = node->parent;

            if ( node->parent == null )
                this->root = rightChild;
            else if ( node == node->parent->left )
                node->parent->left = rightChild;
            else
                node->parent->right = rightChild;

            rightChild->left = node;
            node->parent = rightChild;
        }

        virtual void rotateRight( TNode *node ) {
            TNode *leftChild = node->left;
            node->left = leftChild->right;
            if ( node->left != null )
                node->left->parent = node;
            leftChild->parent = node->parent;
            if ( node->parent == null )
                this->root = leftChild;
            else if ( node == node->parent->right )
                node->parent->right = leftChild;
            else
                node->parent->left = leftChild;

            leftChild->right = node;
            node->parent = leftChild;
        }

        virtual TNode *instantiateNode( Value *data ) {
            return new TNode( data );
        }

        virtual void printNode( TNode *node, ostream &output ) const {
            output<<"+--"<<*node->data;
        }

        virtual void print( TNode *node, string indent, int level, bool isLastChild, ostream &output ) {
            output<<indent;
            indent += isLastChild ? "   " : "|  ";
            printNode( node, output );
            output<<endl;
            if ( node->left && !node->right )
                print( node->left, indent, level + 1, true, output );
            else if ( node->left )
                print( node->left, indent, level + 1, false, output );
            if ( node->right )
                print( node->right, indent, level + 1, true, output );
        }

        virtual void breadthFirstSearch( std::function< void( TNode *, int ) > processingFunction ) const {
            auto currentLevel = new std::queue< TNode * >();
            auto nextLevel = new std::queue< TNode * >();
            std::queue< TNode * > *tmp;
            int i = 0;
            if ( root != null )
                currentLevel->push( root );
            while ( !currentLevel->empty()) {
                i++;
                while ( !currentLevel->empty()) {
                    processingFunction( currentLevel->front(), i );
                    if ( currentLevel->front()->left != null ) {
                        nextLevel->push( currentLevel->front()->left );
                    }
                    if ( currentLevel->front()->right != null ) {
                        nextLevel->push( currentLevel->front()->right );
                    }
                    currentLevel->pop();
                }
                swap( currentLevel, nextLevel );
            }
            delete currentLevel;
            delete nextLevel;
        }

        virtual bool validateInsertion( TNode *node ) {
            return true;
        }

        virtual bool validateRemoval( TNode *originalNode, TNode *replacement ) {
            return true;
        }

    public:

        BSTree() throw( TypeException& ) {
            if ( !std::is_base_of< Comparable, Value >::value)
                throw TypeException( "BSTree<T>: T must extend Comparable" );
            size = 0;
            root = null;
            removalDirection = true;
        }

        BSTree( vector< Value * > &vec ) throw( TypeException&, InvalidKeyException& ) {
            BSTree< Value >();
            insert( vec );
        }

        virtual void breadthFirstSearch( std::function< void( Value *, int ) > processingFunction ) const {
            auto currentLevel = new std::queue< TNode * >();
            auto nextLevel = new std::queue< TNode * >();
            std::queue< TNode * > *tmp;
            int i = 0;
            if ( root != null )
                currentLevel->push( root );
            while ( !currentLevel->empty()) {
                i++;
                while ( !currentLevel->empty()) {
                    processingFunction( currentLevel->front()->data, i );
                    if ( currentLevel->front()->left != null ) {
                        nextLevel->push( currentLevel->front()->left );
                    }
                    if ( currentLevel->front()->right != null ) {
                        nextLevel->push( currentLevel->front()->right );
                    }
                    currentLevel->pop();
                }
                swap( currentLevel, nextLevel );
            }
            delete currentLevel;
            delete nextLevel;
        }

        void process( std::function< void( Value * ) > processingFunction, Order order ) {
            if ( root != null ) {
                safeProcessingFunction = processingFunction;
                processTreeSafely( root, order );
            }
        }

        int getSize() const {
            return size;
        }

        virtual bool insert( Value &data ) throw( InvalidKeyException& ) {
            Value *dataP = &data;
            return insert( dataP );
        }

        virtual bool insert( Value *data ) throw( InvalidKeyException& ) {
            auto node = instantiateNode( data );
            if ( this->root == null ) {
                this->root = node;
            } else {
                TNode *parentNode = this->root;
                bool f = true;
                while ( f ) {
                    while ( *parentNode->data < *node->data ) {
                        if ( parentNode->right != null )
                            parentNode = parentNode->right;
                        else {
                            parentNode->right = node;
                            node->parent = parentNode;
                            f = false;
                            break;
                        }
                    }
                    while ( *parentNode->data > *node->data ) {
                        if ( parentNode->left != null )
                            parentNode = parentNode->left;
                        else {
                            parentNode->left = node;
                            node->parent = parentNode;
                            f = false;
                            break;
                        }
                    }
                    if ( *parentNode->data == *node->data ) {
                        throw InvalidKeyException();
                    }
                }
            }

            this->size++;
            if ( validateInsertion( node ))
                return true;
        }

        virtual bool insert( vector< Value * > *dataVector ) throw( InvalidKeyException& ) {
            return insert( *dataVector );
        }

        virtual bool insert( vector< Value * > &dataVector ) throw( InvalidKeyException& ) {
            bool ret = 1;
            for ( auto it = dataVector.begin(); it != dataVector.end(); it++ ) {
                ret = ret && insert( *it );
            }
            return ret;
        }

        virtual Value *get( Value *data ) throw( KeyNotFoundException& ) {
            TNode *walkthroughNode = root;
            while ( walkthroughNode != null && *walkthroughNode->data != *data ) {
                walkthroughNode = *walkthroughNode->data < *data ? walkthroughNode->right : walkthroughNode->left;
            }
            if ( walkthroughNode == null )
                throw KeyNotFoundException();
            return walkthroughNode->data;
        }

        virtual bool contains( Value *data ) {
            try {
                get( data );
            } catch ( KeyNotFoundException &ex ) {
                return false;
            }
            return true;
        }

        //
        virtual bool remove( vector< Value * > &dataVector ) throw( KeyNotFoundException& ) {
            bool ret = 1;
            for ( auto it = dataVector.begin(); it != dataVector.end(); it++ ) {
                Value *v = pop( *it );
                ret = ret && v == null;
                delete v;
            }
            return ret;
        }

        virtual bool remove( vector< Value * > *dataVector ) throw( KeyNotFoundException& ) {
            remove( *dataVector );
        }

        virtual bool remove( Value &data ) throw( KeyNotFoundException& ) {
            Value *dt = &data;
            Value *v = pop( dt );
            if ( v != null ) {
                delete v;
                return true;
            }
            return false;
        }

        virtual bool remove( Value *data ) throw( KeyNotFoundException& ) {
            Value *v = pop( data );
            if ( v != null ) {
                delete v;
                return true;
            }
            return false;
        }
        //

        virtual bool pop( vector< Value * > &dataVector ) throw( KeyNotFoundException& ) {
            bool ret = 1;
            for ( auto it = dataVector.begin(); it != dataVector.end(); it++ ) {
                ret = ret && pop( *it );
            }
            return ret;
        }

        virtual bool pop( vector< Value * > *dataVector ) throw( KeyNotFoundException& ) {
            return pop( *dataVector );
        }

        virtual Value *pop( Value &data ) throw( KeyNotFoundException& ) {
            Value *dt = &data;
            return pop( dt );
        }

        virtual Value *pop( Value *data ) throw( KeyNotFoundException& ) {
            bool properDeletionFlag = false;
            TNode *node = this->root;
            Value *returnValue = null;
            while ( node != null ) {
                if ( *node->data > *data ) {
                    node = node->left;
                } else if ( *node->data < *data ) {
                    node = node->right;
                } else {
                    properDeletionFlag = true;
                    this->size--;
                    if ( node->left == null || node->right == null ) {
                        TNode *singleChild = node->right ? node->right : node->left;
                        if ( node->parent != null ) {
                            if ( node->parent->left == node )
                                node->parent->left = singleChild;
                            else
                                node->parent->right = singleChild;
                        }
                        if ( singleChild != null )
                            singleChild->parent = node->parent;
                        if ( this->root == node )
                            this->root = singleChild;
                        validateRemoval( node, singleChild );
                        returnValue = node->data;
                        delete node;
                    } else {
                        if ( BSTree< Value >::removalDirection ) {
                            TNode *greaterMinimumNode = node->right;
                            while ( greaterMinimumNode->left != null ) {
                                greaterMinimumNode = greaterMinimumNode->left;
                            }
                            returnValue = node->data;
                            node->data = greaterMinimumNode->data;
                            if ( greaterMinimumNode->parent->left == greaterMinimumNode ) {
                                greaterMinimumNode->parent->left = greaterMinimumNode->right;
                                if ( greaterMinimumNode->right != null )
                                    greaterMinimumNode->right->parent = greaterMinimumNode->parent;
                            } else {
                                greaterMinimumNode->parent->right = greaterMinimumNode->right;
                                if ( greaterMinimumNode->right != null )
                                    greaterMinimumNode->right->parent = greaterMinimumNode->parent;
                            }
                            validateRemoval( greaterMinimumNode, greaterMinimumNode->right );
                            delete greaterMinimumNode;
                            BSTree< Value >::removalDirection = false;
                        } else {
                            TNode *lesserMaximumNode = node->left;
                            while ( lesserMaximumNode->right != null ) {
                                lesserMaximumNode = lesserMaximumNode->right;
                            }
                            returnValue = node->data;
                            node->data = lesserMaximumNode->data;
                            if ( lesserMaximumNode->parent->left == lesserMaximumNode ) {
                                lesserMaximumNode->parent->left = lesserMaximumNode->left;
                                if ( lesserMaximumNode->left != null )
                                    lesserMaximumNode->left->parent = lesserMaximumNode->parent;
                            } else {
                                lesserMaximumNode->parent->right = lesserMaximumNode->left;
                                if ( lesserMaximumNode->left != null )
                                    lesserMaximumNode->left->parent = lesserMaximumNode->parent;
                            }
                            validateRemoval( lesserMaximumNode, lesserMaximumNode->left );
                            delete lesserMaximumNode;
                            BSTree< Value >::removalDirection = true;
                        }
                    }
                    break;
                }
            }
            if ( !properDeletionFlag )
                throw KeyNotFoundException();
            return returnValue;
        }

        virtual bool balance() {
            TNode *walkthroughNode = root;
            TNode *childNode;
            if ( root != null ) {
                while ( walkthroughNode != null ) {
                    while ( walkthroughNode->left != null ) {
                        childNode = walkthroughNode->left;
                        if ( walkthroughNode == root )
                            root = childNode;
                        rotateRight( walkthroughNode );
                        walkthroughNode = childNode;
                    }
                    walkthroughNode = walkthroughNode->right;
                }

                int m = 1;
                for ( int i = size + 1; i > 1; i >>= 1 ) {
                    m <<= 1;
                }

                walkthroughNode = root;
                for ( int i = size + 1 - m; i > 0; i-- ) {
                    childNode = walkthroughNode->right;
                    if ( walkthroughNode == root )
                        root = childNode;
                    rotateLeft( walkthroughNode );
                    walkthroughNode = childNode->right;
                }

                m -= 1;
                while ( m > 1 ) {
                    m >>= 1;
                    walkthroughNode = root;
                    for ( int i = 0; i < m; i++ ) {
                        childNode = walkthroughNode->right;
                        if ( walkthroughNode == root )
                            root = childNode;
                        rotateLeft( walkthroughNode );
                        walkthroughNode = childNode->right;
                    }
                }
            }
            return true;
        }

        virtual void print( ostream &output ) {
            if(root != null)
                print( root, "", 0, 1, output );
        }

        std::vector< Value * > toVector( Order order ) {
            std::vector< Value * > returnVector;
            auto collect = [ &returnVector ]( Value *data ) -> void { returnVector.push_back( data ); };
            process( collect, order );
            return returnVector;
        }

        std::vector< Value * > toVector() {
            return toVector( INORDER );
        }

        Value *getMax() const throw( KeyNotFoundException& ) {
            if ( root != null ) {
                TNode *walkthroughNode = root;
                while ( walkthroughNode->right != null ) {
                    walkthroughNode = walkthroughNode->right;
                }
                return walkthroughNode->data;
            }
            throw KeyNotFoundException();
        }

        Value *getMin() const throw( KeyNotFoundException& ) {
            if ( root != null ) {
                TNode *walkthroughNode = root;
                while ( walkthroughNode->left != null ) {
                    walkthroughNode = walkthroughNode->left;
                }
                return walkthroughNode->data;
            }
            throw KeyNotFoundException();
        }

        virtual void removeAll() override {
            process( []( TNode *node ) -> void {
                delete node->data;
                delete node;
            }, POSTORDER );
            root = null;
        }

        virtual void popAll() {
            process( []( TNode *node ) -> void {
                delete node;
            }, POSTORDER );
            root = null;

        }

        ~BSTree() {
            popAll();
        }

    };


}

#undef TNode
#undef null
#endif //BRTREE_BST_HPP
