#ifndef _MATELIB_MEMORY_HPP_
#define _MATELIB_MEMORY_HPP_

#include <MateLib/Exception.hpp>
#include <MateLib/AutoPtr.hpp>

namespace Mate {

    class MemoryException : public Exception {
    public:
        const char *what() const throw () { return "Not enough memory."; }
    };

    template<typename T> inline T *alloc(size_t sz) throw (MemoryException) {
        try {
            return new T[sz];
        } catch (const std::bad_alloc&) {
            throw MemoryException();
        }
    }

    template<typename T> inline void dealloc(T *obj) {
        delete[] obj;
    }

    template<typename T> class ScopeAllocator : public AutoPtr<T[]> {
    public:
        ScopeAllocator(size_t sz) : AutoPtr<T[]>(allocate<T>(sz)) { }
    };

}

#endif