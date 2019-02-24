#include "exceptions.hpp"

namespace Trees {

    Exception::Exception() {
        message = "AN ERROR OCCURED";
    }

    Exception::Exception( string m ) {
        message = m;
    }

    string Exception::getMessage() const {
        return message;
    }

    TreeException::TreeException()
        : Exception( "A TREE ERROR OCCURED" ) {}

    TreeException::TreeException( string m ) : Exception( m ) {}

    TypeException::TypeException()
        : TypeException( "A TYPE ERROR OCCURED" ) {}

    TypeException::TypeException( string m ) : TreeException( m ) {}

    KeyException::KeyException()
        : KeyException( "KEY EXCEPTION OCCURED" ) {}

    KeyException::KeyException( string m ) : TreeException( m ) {}

    KeyNotFoundException::KeyNotFoundException()
        : KeyNotFoundException( "KEY NOT FOUND" ){}

    KeyNotFoundException::KeyNotFoundException( string m ) : KeyException( m ) {}

    InvalidKeyException::InvalidKeyException()
        : KeyException( "INVALID KEY" ) {}

    InvalidKeyException::InvalidKeyException( string m ) : KeyException( m ) {}
}
