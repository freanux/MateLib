#ifndef _MATELIB_UDPSOCKET_HPP_
#define _MATELIB_UDPSOCKET_HPP_

#include <MateLib/Exception.hpp>

#ifdef __unix__
#include <arpa/inet.h>
#define closesocket(s) ::close(s)
#elif _WIN32
#include "Win.hpp"
#endif

namespace Mate {

    class UDPSocketException : public TextualException {
    public:
        UDPSocketException(const char *msg) : TextualException(msg) { }
        UDPSocketException(const std::string& msg) : TextualException(msg) { }
    };

    class UDPSocket {
    private:
        UDPSocket(const UDPSocket&);
        UDPSocket& operator=(const UDPSocket&);

    public:
        UDPSocket() throw (UDPSocketException);
        UDPSocket(unsigned short port) throw (UDPSocketException);
        virtual ~UDPSocket();

        ssize_t send(uint32_t host, uint16_t port, void *buffer, size_t length) throw (UDPSocketException);
        ssize_t recv(char *buffer, size_t length, uint32_t *host, uint16_t *port) throw (UDPSocketException);
        void set_port(unsigned short port) throw (UDPSocketException);
        unsigned short get_port() const;

    protected:
#ifdef __unix__
        int socket;
#elif _WIN32
        SOCKET socket;
#endif
        unsigned short port;
        struct sockaddr_in addr;

        void create_socket(unsigned short port) throw (UDPSocketException);
    };

}

#endif
