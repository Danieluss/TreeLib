#ifndef BRTREE_RB_HPP
#define BRTREE_RB_HPP

#include "bst.hpp"
#include <queue>

#define null nullptr
#define TNode TreeNode<Value>
#define RED CNode::RED
#define BLACK CNode::BLACK
#define CNode ColorNode<Value>

namespace Trees {


    template< class Value >
    class RBTree
            : public BSTree< Value > {

        TNode *originalNode, *replacementNode, *originalSiblingNode;

    protected:

        static CNode *cCast( TNode *node ) {
            return static_cast<CNode *>( node );
        }

        static typename CNode::Color getColorOf( TNode *node ) {
            if ( node == null )
                return BLACK;
            return static_cast<CNode *>( node )->color;
        }

        virtual bool validateInsertion( TNode *node ) override {
            cCast( node )->color = RED;
            while ( true ) {
                if ( node == this->root ) {
                    cCast( node )->color = BLACK;
                    break;
                } else if ( cCast( node->parent )->color == BLACK ) {
                    break;
                } else if ( getColorOf( this->uncle( node )) == RED ) {
                    cCast( node->parent )->color = BLACK;
                    cCast( this->uncle( node ))->color = BLACK;
                    cCast( this->grandparent( node ))->color = RED;
                    node = this->grandparent( node );
                } else {
                    if (( this->grandparent( node ) != null )
                        && ( this->grandparent( node )->left != null )
                        && ( node == this->grandparent( node )->left->right )) {
                        this->rotateLeft( node->parent );
                        node = node->left;
                    } else if (( this->grandparent( node ) != null )
                               && ( this->grandparent( node )->right != null )
                               && ( node == this->grandparent( node )->right->left )) {
                        this->rotateRight( node->parent );
                        node = node->right;
                    }

                    TNode *grandpa = this->grandparent( node ), *papa = node->parent;
                    if ( node == node->parent->left )
                        this->rotateRight( this->grandparent( node ));
                    else
                        this->rotateLeft( this->grandparent( node ));
                    cCast( papa )->color = BLACK;
                    cCast( grandpa )->color = RED;
                    break;
                }
            }
            return true;
        }

        virtual bool validateRemoval( TNode *originalNode, TNode *replacementNode ) override {
            this->replacementNode = replacementNode;
            this->originalNode = originalNode;
            if ( getColorOf( originalNode ) == BLACK ) {
                if ( getColorOf( replacementNode ) == RED )
                    cCast( replacementNode )->color = BLACK;
                else
                    removalCase1();
            }
            return true;
        }

        virtual void removalCase1() {
            if ( this->root != replacementNode ) {
                removalCase2();
            }
        }

        virtual void removalCase2() {
            originalSiblingNode = this->sibling( replacementNode, originalNode );
            if (( getColorOf( originalSiblingNode ) == RED )
                && ( cCast( originalNode )->color == BLACK )
                && ( getColorOf( originalSiblingNode->left ) == BLACK )
                && ( getColorOf( originalSiblingNode->right ) == BLACK )) {
                cCast( originalNode )->color = RED;
                cCast( originalSiblingNode )->color = BLACK;
                if ( replacementNode == originalNode->left )
                    this->rotateLeft( originalNode );
                else
                    this->rotateRight( originalNode );
            }
            removalCase3();
        }

        virtual void removalCase3() {
            originalSiblingNode = this->sibling( replacementNode, originalNode );
            if ( originalSiblingNode != null
                 && ( cCast( originalNode )->color == BLACK )
                 && ( cCast( originalSiblingNode )->color == BLACK )
                 && ( getColorOf( originalSiblingNode->left ) == BLACK )
                 && ( getColorOf( originalSiblingNode->right ) == BLACK )) {
                cCast( originalSiblingNode )->color = RED;
                replacementNode = originalNode;
                originalNode = originalNode->parent;
                removalCase1();
            } else
                removalCase4();
        }

        virtual void removalCase4() {
            originalSiblingNode = this->sibling( replacementNode, originalNode );
            if ( originalSiblingNode
                 && ( cCast( originalNode )->color == RED )
                 && ( cCast( originalSiblingNode )->color == BLACK )
                 && ( getColorOf( originalSiblingNode->left ) == BLACK )
                 && ( getColorOf( originalSiblingNode->right ) == BLACK )) {
                cCast( originalSiblingNode )->color = RED;
                cCast( originalNode )->color = BLACK;
            } else
                removalCase5();
        }

        virtual void removalCase5() {
            originalSiblingNode = this->sibling( replacementNode, originalNode );
            if ( originalSiblingNode
                 && cCast( originalSiblingNode )->color == BLACK ) {
                if (( replacementNode == originalNode->left )
                    && ( getColorOf( originalSiblingNode->right ) == BLACK )
                    && ( getColorOf( originalSiblingNode->left ) == RED )) {
                    cCast( originalSiblingNode )->color = RED;
                    cCast( originalSiblingNode->left )->color = BLACK;
                    this->rotateRight( originalSiblingNode );
                } else if (( replacementNode == originalNode->right )
                           && ( cCast( originalSiblingNode->right )->color == RED )
                           && ( cCast( originalSiblingNode->left )->color == BLACK )) {
                    cCast( originalSiblingNode )->color = RED;
                    cCast( originalSiblingNode->right )->color = BLACK;
                    this->rotateLeft( originalSiblingNode );
                }
            }
            removalCase6();
        }

        virtual void removalCase6() {
            originalSiblingNode = this->sibling( replacementNode, originalNode );
            if ( originalSiblingNode )
                if (( replacementNode == originalNode->left )
                    && ( cCast( originalSiblingNode )->color == BLACK )
                    && ( getColorOf( originalSiblingNode->right ) == RED )) {
                    cCast( originalSiblingNode->right )->color = BLACK;
                    cCast( originalSiblingNode )->color = cCast( originalNode )->color;
                    cCast( originalNode )->color = BLACK;
                    this->rotateLeft( originalNode );
                } else if ( replacementNode == originalNode->right
                            && ( cCast( originalSiblingNode )->color == BLACK )
                            && ( getColorOf( originalSiblingNode->left ) == RED )) {
                    cCast( originalSiblingNode->left )->color = BLACK;
                    cCast( originalSiblingNode )->color = cCast( originalNode )->color;
                    cCast( originalNode )->color = BLACK;
                    this->rotateRight( originalNode );
                }
        }

        virtual TNode *instantiateNode( Value *data ) override {
            return new CNode( data );
        }

        virtual void printNode( TNode *node, ostream &output ) const override {
            BSTree< Value >::printNode( node, output );
            if ( cCast( node )->color == RED )
                cout<<":R";
            else
                cout<<":B";
        }

    public:

        virtual bool areColorsViolated() { //for debug only
            bool flag = false;
            this->process( [ &flag ]( TNode *node ) -> void {
                if ( getColorOf( node ) == RED && ( getColorOf( node->right ) == RED || getColorOf( node->left ) == RED )) {
                    flag = true;
                }
            }, INORDER );
            return flag;
        }

        virtual bool balance() override {
            this->BSTree< Value >::balance();
            typename CNode::Color levelColor = BLACK;
            /*auto curLevel = new std::queue<TNode*, std::deque<TNode*> >();
            auto nextLevel = new std::queue<TNode*, std::deque<TNode*> >();
            std::queue<TNode*, std::deque<TNode*> >*tmp;
            if ( this->root != null )
                curLevel->push( this->root );
            while ( !curLevel->empty()) {
                while ( !curLevel->empty()) {
                    if ( curLevel->front()->left != null ) {
                        nextLevel->push( curLevel->front()->left );
                    }
                    if ( curLevel->front()->right != null ) {
                        nextLevel->push( curLevel->front()->right );
                    }
                    cCast( curLevel->front())->color = clr;
                    curLevel->pop();
                }
                clr = clr == BLACK ? RED : BLACK;
                tmp = curLevel;
                curLevel = nextLevel;
                nextLevel = tmp;
            }
            delete curLevel;
            delete nextLevel;*/
            int currentLevel = 1;
            this->breadthFirstSearch( [ &levelColor, &currentLevel ]( TNode *node, int nextLevel ) -> void {
                if ( nextLevel != currentLevel && getColorOf( node ) != levelColor ) {
                    currentLevel = nextLevel;
                    levelColor = levelColor == BLACK ? levelColor = RED : levelColor = BLACK;
                }
                cCast( node )->color = levelColor;
            } );
        }

    };


}

#undef null
#undef TNode
#undef RED
#undef BLACK
#undef CNode
#endif //BRTREE_RB_HPP
