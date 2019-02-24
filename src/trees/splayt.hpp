#ifndef SPLAYT_HPP
#define SPLAYT_HPP

#include "bst.hpp"

#define null nullptr
#define TNode TreeNode<Value>

namespace Trees {


    template< class Value >
    class SplayTree
            : public BSTree< Value > {

    protected:

        virtual void splay( TNode *node ) {
            if ( node )
                while ( node->parent ) {
                    if ( !node->parent->parent ) {
                        if ( node->parent->left == node )
                            this->rotateRight( node->parent );
                        else
                            this->rotateLeft( node->parent );
                    } else if ( node->parent->left == node && node->parent->parent->left == node->parent ) {
                        this->rotateRight( node->parent->parent );
                        this->rotateRight( node->parent );
                    } else if ( node->parent->right == node && node->parent->parent->right == node->parent ) {
                        this->rotateLeft( node->parent->parent );
                        this->rotateLeft( node->parent );
                    } else if ( node->parent->left == node && node->parent->parent->right == node->parent ) {
                        this->rotateRight( node->parent );
                        this->rotateLeft( node->parent );
                    } else {
                        this->rotateLeft( node->parent );
                        this->rotateRight( node->parent );
                    }
                }
        }

        virtual bool validateInsertion( TNode *node ) override {
            splay( node );
            return true;
        }

        virtual bool validateRemoval( TNode *originalNode, TNode *replacedNode ) override {
            splay( replacedNode );
            return true;
        }

    public:

        virtual Value *get( Value *data ) throw( KeyNotFoundException& ) override {
            TNode *walkthroughNode = this->root;
            TNode *parent;
            while ( walkthroughNode != null && *walkthroughNode->data != *data ) {
                parent = walkthroughNode;
                walkthroughNode = *walkthroughNode->data < *data ? walkthroughNode->right : walkthroughNode->left;
            }
            if ( this->root == null )
                return null;
            if ( walkthroughNode == null ) {
                splay( parent );
                throw KeyNotFoundException();
            }
            splay( walkthroughNode );
            return walkthroughNode->data;
        }

    };

}
#undef null
#endif //SPLAYT_HPP
