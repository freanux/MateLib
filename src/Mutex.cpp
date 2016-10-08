#include "MateLib/Mutex.hpp"

namespace Mate {

    Mutex::Mutex() throw (MutexException) {
        try {
            mutex = new mutex_t;
        } catch (const std::exception& e) {
            throw MutexException(e.what());
        }
#ifdef __unix__
        pthread_mutex_init(&mutex->h_mutex, NULL);
#elif _WIN32
        mutex->h_mutex = CreateMutex(NULL, FALSE, NULL);
#endif
    }

    Mutex::~Mutex() {
#ifdef __unix__
        pthread_mutex_destroy(&mutex->h_mutex);
#elif _WIN32
        CloseHandle(mutex->h_mutex);
#endif
        delete mutex;
    }

    void Mutex::lock() {
#ifdef __unix__
        pthread_mutex_lock(&mutex->h_mutex);
#elif _WIN32
        WaitForSingleObject(mutex->h_mutex, INFINITE);
#endif
    }

    void Mutex::unlock() {
#ifdef __unix__
        pthread_mutex_unlock(&mutex->h_mutex);
#elif _WIN32
        ReleaseMutex(mutex->h_mutex);
#endif
    }

    void Mutex::scope_enter() {
        lock();
    }

    void Mutex::scope_leave() {
        unlock();
    }

    // -------------------------------------------------------------------------
    ReadWriteMutex::ReadWriteMutex() throw (MutexException) { }

    void ReadWriteMutex::lock_write() {
        pthread_rwlock_wrlock(&lock_rw);
    }

    void ReadWriteMutex::lock_read() {
        pthread_rwlock_rdlock(&lock_rw);
    }

    void ReadWriteMutex::unlock() {
        pthread_rwlock_unlock(&lock_rw);
    }

}