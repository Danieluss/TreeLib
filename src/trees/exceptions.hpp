#ifndef BRTREE_EXCEPT_HPP
#define BRTREE_EXCEPT_HPP

#include<string>

using namespace std;

namespace Trees {

    class Exception
            :exception {

        string message;

    public:

        Exception();

        Exception( string m );

        string getMessage() const;

    };

    class TreeException
            : public Exception {

    public:

        TreeException();

        TreeException( string m );

    };

    class TypeException
            : public TreeException {

    public:

        TypeException();

        TypeException( string m );

    };

    class KeyException
            : public TreeException {

    public:

        KeyException();

        KeyException( string m );

    };

    class KeyNotFoundException
            : public KeyException {

    public:

        KeyNotFoundException();

        KeyNotFoundException( string m );

    };

    class InvalidKeyException
            : public KeyException {

    public:

        InvalidKeyException();

        InvalidKeyException( string m );

    };

}
#endif //BRTREE_EXCEPT_HPP
