#ifndef _MATELIB_RAWFILE_HPP_
#define _MATELIB_RAWFILE_HPP_

#include <MateLib/Exception.hpp>
#include <MateLib/Memory.hpp>

#include <cstdio>

namespace Mate {

    class RawFileException : public TextualException {
    public:
        RawFileException(const char *msg) : TextualException(msg) { }
        RawFileException(const std::string& msg) : TextualException(msg) { }
    };

    class RawFile {
    private:
        // copy constructor is needed for temporary in c++98 -> RawFile(const RawFile&);
        RawFile& operator=(const RawFile&);

    public:
        enum Mode {
            ModeRead = 0,
            ModeWrite,
            ModeReadBinary,
            ModeWriteBinary,
            ModeAppend,
            ModeAppendBinary
        };

        enum Seek {
            SeekBeginning = SEEK_SET,
            SeekCurrent = SEEK_CUR,
            SeekEnd = SEEK_END
        };

        RawFile(const char *filename, Mode mode) throw (RawFileException);
        virtual ~RawFile();

        static RawFile *create(const char *filename, Mode mode) throw (MemoryException, RawFileException);
        static void destroy(RawFile *rw);

        static bool is_file_present(const char *filename);

        size_t read(void *buffer, size_t sz) const throw ();
        size_t write(const void *buffer, size_t sz) const throw ();
        void seek(long int offset, Seek seek) const throw ();
        size_t get_position() const throw ();

    private:
        FILE *f;

        const char *get_mode(Mode mode);
    };
}

#endif