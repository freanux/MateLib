#include "MateLib/Process.hpp"

#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <algorithm>
#include <signal.h>
#include <sys/wait.h>

namespace Mate {

    static const char *to_cstr(const std::string& s) {
        return s.c_str();
    }

    Process::Process(const Arguments& args) : pid(0), exited(false) {
        pid = fork();
        if (pid < 0) {
            throw ProcessException(std::string("Fork failed: ") + strerror(errno));
        } else if (pid == 0) {
            std::vector<const char *> argv;
            std::transform(args.begin(), args.end(), std::back_inserter(argv), to_cstr);
            argv.push_back(0);
            execvp(argv[0], const_cast<char **>(&argv[0]));
            _exit(EXIT_FAILURE);
        }
    }

    Process::~Process() {
        if (!exited) {
            kill(pid, SIGTERM); // or SIGKILL
            wait();
        }
    }

    void Process::wait() {
        if (!exited) {
            int status;
            waitpid(pid, &status, 0);
            exited = true;
        }
    }

}
