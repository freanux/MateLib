#ifndef _MATELIB_TCPSOCKET_HPP_
#define _MATELIB_TCPSOCKET_HPP_

#include <MateLib/Exception.hpp>

#include <stdint.h>

#ifdef _MSC_VER
    #pragma warning( disable : 4290 )
#endif

namespace Mate {

    class TCPSocketException : public TextualException {
    public:
        TCPSocketException(const char *msg) : TextualException(msg) { }
        TCPSocketException(const std::string& msg) : TextualException(msg) { }
    };

    class TCPSocket {
    private:
        TCPSocket(const TCPSocket&);
        TCPSocket& operator=(const TCPSocket&);

    public:
        TCPSocket();
        virtual ~TCPSocket();

        void connect(const char *ip_address, uint16_t port) throw (TCPSocketException);
        bool activity(time_t sec, long usec) throw (TCPSocketException);
        void listen(const char *address, uint16_t port, int backlog) throw (TCPSocketException);
        void listen(const char *address, uint16_t port) throw (TCPSocketException);
        void listen(uint16_t port, int backlog) throw (TCPSocketException);
        void listen(uint16_t port) throw (TCPSocketException);
        void accept(const TCPSocket& socket) throw (TCPSocketException);
        void close();

        size_t send(const char *buffer, size_t size) throw (TCPSocketException);
        size_t send(const std::string& buffer) throw (TCPSocketException);
        size_t receive(void *buffer, size_t size) throw (TCPSocketException);
        bool get_error() const;
        bool is_connected() const;
        uint16_t get_port() throw (TCPSocketException);
        unsigned long get_address() throw (TCPSocketException);

    private:
        static const int DefaultBacklog;

        int socket;
        bool connected;
        bool listening;
        bool error;
        bool tls;
        bool disconnecting;

        void check_states() throw (TCPSocketException);
    };

}

#endif
