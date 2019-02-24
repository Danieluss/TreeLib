#ifndef BRTREE_NODES_HPP
#define BRTREE_NODES_HPP
#define null nullptr


namespace Trees {

    template< class Value >
    class TreeNode {

        void initRel() {
            left = null;
            right = null;
            parent = null;
        }

    public:

        Value *data;
        TreeNode< Value > *parent, *left, *right;

        TreeNode( Value *data ) {
            this->data = data;
            initRel();
        }

        TreeNode() {
            initRel();
        }

        virtual ~TreeNode() {}

    };


    template< class Value >
    class ColorNode
            : public TreeNode< Value > {

    public:

        enum Color {
            RED, BLACK
        };
        Color color;

        ColorNode( Value *data ) : TreeNode< Value >( data ) {
            color = RED;
        }

    };

    template< class Value >
    class KeyNode
            : public TreeNode< Value > {

    public:

        int key;

        KeyNode( Value *data ) : TreeNode< Value >( data ) {
            key = 1;
        }

    };

}

#undef null
#endif //BRTREE_NODES_HPP
