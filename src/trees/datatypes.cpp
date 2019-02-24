#include "datatypes.hpp"


namespace Trees {

    bool Comparable::operator<( const Comparable &object ) const {
        return compare( object ) < 0;
    }

    bool Comparable::operator==( const Comparable &object ) const {
        return compare( object ) == 0;
    }

    bool Comparable::operator!=( const Comparable &object ) const {
        return compare( object ) != 0;
    }

    bool Comparable::operator>( const Comparable &object ) const {
        return compare( object ) > 0;
    }

}