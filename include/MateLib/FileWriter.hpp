#ifndef _MATELIB_FILEWRITER_HPP_
#define _MATELIB_FILEWRITER_HPP_

#include <MateLib/RawFile.hpp>
#include <MateLib/DataWriter.hpp>
#include <MateLib/Memory.hpp>

namespace Mate {

    class FileWriter : public DataWriter {
    private:
        // copy constructor is needed for temporary in c++98 -> FileWriter(const FileWriter&);
        FileWriter& operator=(const FileWriter&);

    public:
        FileWriter(const char *filename) throw (RawFileException);
        virtual ~FileWriter();

        static FileWriter *create(const char *filename) throw (MemoryException, RawFileException);
        static void destroy(FileWriter *fw);

        size_t write(const char *s);

        // DataWriter
        virtual size_t write(const void *from, size_t sz);

    private:
        RawFile file;
    };

}

#endif