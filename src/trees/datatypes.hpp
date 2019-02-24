#ifndef BRTREE_DATATYPES_HPP
#define BRTREE_DATATYPES_HPP

#include <iostream>


namespace Trees {


    class Comparable {

    public:

        virtual int compare( const Comparable &obj ) const = 0;

        bool operator<( const Comparable &object ) const;

        bool operator==( const Comparable &object ) const;

        bool operator!=( const Comparable &object ) const;

        bool operator>( const Comparable &object ) const;

    };


    template< class Number >
    class Wrapper :
            public Comparable {

        Number key;

    public:

        Wrapper( Number key ) {
            this->key = key;
        }

        virtual int compare( const Comparable &object ) const {
            const Wrapper<Number> *wrapperObject = dynamic_cast<const Wrapper<Number> *>( &object );
            return key - wrapperObject->getKey();
        }

        Number getKey() const {
            return key;
        }

    };

    template<class Number>
    std::ostream &operator<<( std::ostream &output, const Wrapper<Number> &wrapper ) {
        return output << wrapper.getKey();
    }

}
#endif //BRTREE_DATATYPES_HPP
