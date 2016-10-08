#ifndef _MATELIB_EXCEPTION_HPP_
#define _MATELIB_EXCEPTION_HPP_

#include <string>

namespace Mate {

    class Exception : public std::exception {
    public:
        Exception() { }
        virtual ~Exception() throw () { }
    };

    class TextualException : public Exception {
    public:
        TextualException(const char *msg) : msg(msg) { }
        TextualException(const std::string& msg) : msg(msg) { }
        virtual ~TextualException() throw () { }

        virtual const char *what() const throw () { return msg.c_str(); }

    private:
        std::string msg;
    };

}

#endif