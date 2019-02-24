#ifndef TREES_COLLECTION_HPP
#define TREES_COLLECTION_HPP

template<class Value>
class Collection {

public:

    virtual bool insert( Value* value ) = 0;

    virtual bool remove( Value *value ) = 0;

    virtual void popAll() = 0;

    virtual Value* pop( Value* value ) = 0;

    virtual Value* get( Value *value ) = 0;

    virtual void removeAll() = 0;

};

#endif //TREES_COLLECTION_HPP
