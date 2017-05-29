#ifndef _MATELIB_PROCESS_HPP_
#define _MATELIB_PROCESS_HPP_

#include <MateLib/Exception.hpp>

#include <vector>
#include <string>
#include <sys/types.h>

namespace Mate {

    class ProcessException : public TextualException {
    public:
        ProcessException(const char *msg) : TextualException(msg) { }
        ProcessException(const std::string& msg) : TextualException(msg) { }
    };

    class Process {
    private:
        Process(const Process&);
        Process& operator=(const Process&);

    public:
        typedef std::vector<std::string> Arguments;

        Process(const Arguments& args);
        ~Process();

        void wait();

    private:
        pid_t pid;
        bool exited;
    };

}

#endif
