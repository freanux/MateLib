#ifndef _MATELIB_MUTEX_HPP_
#define _MATELIB_MUTEX_HPP_

#include <MateLib/Exception.hpp>

#ifdef __unix__
#include <pthread.h>
#elif _WIN32
#include "Win.hpp"
#endif

namespace Mate {

    class MutexException : public TextualException {
    public:
        MutexException(const char *msg) : TextualException(msg) { }
        MutexException(std::string msg) : TextualException(msg) { }
    };

    class Mutex {
    private:
        Mutex(const Mutex& rhs);
        Mutex& operator=(const Mutex& rhs);

        typedef struct {
    #ifdef __unix__
            pthread_mutex_t h_mutex;
    #else
            HANDLE h_mutex;
    #endif
        } mutex_t;

    public:
        Mutex() throw (MutexException);
        virtual ~Mutex();

        void lock();
        void unlock();

        void scope_enter();
        void scope_leave();

    private:
        mutex_t *mutex;
    };

    // -------------------------------------------------------------------------
    class ReadWriteMutex {
    private:
        ReadWriteMutex(const ReadWriteMutex&);
        ReadWriteMutex& operator=(const ReadWriteMutex&);

    public:
        ReadWriteMutex() throw (MutexException);

        void lock_write();
        void lock_read();
        void unlock();

    private:
        pthread_rwlock_t lock_rw = PTHREAD_RWLOCK_INITIALIZER;
    };

    class ScopeReadLock {
    private:
        ScopeReadLock(const ScopeReadLock&);
        ScopeReadLock& operator=(const ScopeReadLock&);

    public:
        ScopeReadLock(ReadWriteMutex& m) : m(m) { m.lock_read(); }
        ~ScopeReadLock() { m.unlock(); }

    private:
        ReadWriteMutex& m;
    };

    class ScopeWriteLock {
    private:
        ScopeWriteLock(const ScopeWriteLock&);
        ScopeWriteLock& operator=(const ScopeWriteLock&);

    public:
        ScopeWriteLock(ReadWriteMutex& m) : m(m) { m.lock_write(); }
        ~ScopeWriteLock() { m.unlock(); }

    private:
        ReadWriteMutex& m;
    };

}

#endif