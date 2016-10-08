#ifndef _MATELIB_THREAD_HPP_
#define _MATELIB_THREAD_HPP_

#ifdef __unix__
#include <pthread.h>
#include <signal.h>
#elif _WIN32
#include "Win.hpp"
#endif

namespace Mate {

    class Thread {
    private:
        Thread(const Thread&);
        Thread& operator=(const Thread&);

    public:
        Thread();
        virtual ~Thread();

    protected:
        bool thread_start();
        void thread_join();
        void thread_detach();
        virtual void thread() = 0;

    private:
    #ifdef __unix__
        pthread_t t;
    #else
        HANDLE t;
    #endif

        static void *thread_helper(void *o);
    };

}

#endif