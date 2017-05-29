#ifndef _MATELIB_REFCOUNT_HPP_
#define _MATELIB_REFCOUNT_HPP_

#include <MateLib/Mutex.hpp>

namespace Mate {

    class RefCount {
    public:
        RefCount();
        virtual ~RefCount();

    public:
        void add_ref();
        void release();

        virtual void on_destroy();

    private:
        int cnt;

        Mutex mtx;
    };

}

#endif
