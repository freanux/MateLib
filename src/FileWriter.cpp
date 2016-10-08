#include "MateLib/FileWriter.hpp"

namespace Mate {

    FileWriter::FileWriter(const char *filename) throw (RawFileException)
        : DataWriter(filename), file(filename, RawFile::ModeWriteByte) { }

    FileWriter::~FileWriter() { }

    FileWriter *FileWriter::create(const char *filename) throw (MemoryException, RawFileException) {
        try {
            return new FileWriter(filename);
        } catch (const std::bad_alloc&) {
            throw MemoryException();
        } catch (const std::exception& e) {
            throw RawFileException(e.what());
        }
    }

    void FileWriter::destroy(FileWriter *fw) {
        delete fw;
    }

    size_t FileWriter::write(const void *from, size_t sz) {
        return file.write(from, sz);
    }

}