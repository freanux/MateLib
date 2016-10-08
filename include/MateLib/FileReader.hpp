#ifndef _MATELIB_FILEREADER_HPP_
#define _MATELIB_FILEREADER_HPP_

#include <MateLib/RawFile.hpp>
#include <MateLib/DataReader.hpp>
#include <MateLib/Memory.hpp>

namespace Mate {

    class FileReader : public DataReader {
    private:
        // copy constructor is needed for temporary in c++98 -> FileReader(const FileReader&);
        FileReader& operator=(const FileReader&);

    public:
        FileReader(const char *filename) throw (RawFileException);
        virtual ~FileReader();

        static FileReader *create(const char *filename) throw (MemoryException, RawFileException);
        static void destroy(FileReader *fr);

        // DataReader
        virtual size_t get_size() const;
        virtual void reset() const;
        virtual void set(size_t pos) const;
        virtual size_t read(void *into, size_t sz) const;

    private:
        RawFile file;
        size_t size;
    };

}

#endif