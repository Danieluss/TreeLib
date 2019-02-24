#ifndef BRTREE_AVL_HPP
#define BRTREE_AVL_HPP

#include "bst.hpp"

#define null nullptr
#define TNode TreeNode<Value>
#define KNode KeyNode<Value>


namespace Trees {


    template< class Value >
    class AVLTree
            : public BSTree< Value > {

    protected:

        int heightOf( TNode *node ) const {
            if ( !node )
                return 0;
            return keyCast( node )->key;
        }

        int balanceOf( TNode *node ) const {
            return heightOf( node->left ) - heightOf( node->right );
        }

        void setHeightOf( TNode *node ) {
            keyCast( node )->key = heightOf( node->left ) > heightOf( node->right ) ?
                               heightOf( node->left ) + 1 :
                               heightOf( node->right ) + 1;
        }

        virtual void rotateLeft( TNode *node ) override {

            this->BSTree< Value >::rotateLeft( node );

            setHeightOf( node );
            setHeightOf( node->parent );
        }

        virtual void rotateRight( TNode *node ) override {

            this->BSTree< Value >::rotateRight( node );

            setHeightOf( node );
            setHeightOf( node->parent );

        }

        virtual bool validateRemoval( TNode *originalNode, TNode *replacementNode ) override {
            while ( originalNode ) {
                setHeightOf( originalNode );
                int balance = balanceOf( originalNode );
                if ( balance > 1 && balanceOf( originalNode->left ) >= 0 ) {
                    rotateRight( originalNode );
                } else if ( balance < -1 && balanceOf( originalNode->right ) <= 0 ) {
                    rotateLeft( originalNode );
                } else if ( balance > 1 && balanceOf( originalNode->left ) < 0 ) {
                    rotateLeft( originalNode->left );
                    rotateRight( originalNode );
                } else if ( balance < -1 && balanceOf( originalNode->right ) > 0 ) {
                    rotateRight( originalNode->right );
                    rotateLeft( originalNode );
                }
                originalNode = originalNode->parent;
            }
            return true;
        }

        virtual bool validateInsertion( TNode *node ) override {

            TNode *parent = node->parent;

            int rot = 0;
            while ( parent && rot < 2 ) {
                setHeightOf( parent );
                int balance = balanceOf( parent );
                if ( balance == 0 ) {

                } else if ( balance > 1 && ( parent->left == null || *node->data < *parent->left->data )) {
                    rotateRight( parent );
                    rot++;
                } else if ( balance < -1 && ( parent->right == null || *node->data > *parent->right->data )) {
                    rotateLeft( parent );
                    rot++;
                } else if ( balance > 1 && ( parent->left == null || *node->data > *parent->left->data )) {
                    rotateLeft( parent->left );
                    rotateRight( parent );
                    rot += 2;
                } else if ( balance < -1 && ( parent->right == null || *node->data < *parent->right->data )) {
                    rotateRight( parent->right );
                    rotateLeft( parent );
                    rot += 2;
                }
                parent = parent->parent;
            }
            return true;

        }

        static KNode *keyCast( TNode *node ) {
            return static_cast<KNode *>( node );
        }

        virtual TNode *instantiateNode( Value *data ) override {
            return new KNode( data );
        }

        virtual void printNode( TNode *node, ostream& output ) const override {
            BSTree< Value >::printNode( node, output );
            output<<":"<<balanceOf( node );
        }

    public:

    };

}

#undef TNode
#undef KNode
#undef null

#endif //BRTREE_AVL_HPP
