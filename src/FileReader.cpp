#include "MateLib/FileReader.hpp"

namespace Mate {

    FileReader::FileReader(const char *filename) throw (RawFileException)
        : DataReader(filename), file(filename, RawFile::ModeReadBinary), size(0)
    {
        // get filelen
        file.seek(0, RawFile::SeekEnd);
        size = file.get_position();
        file.seek(0, RawFile::SeekBeginning);
    }

    FileReader::~FileReader() { }

    FileReader *FileReader::create(const char *filename) throw (MemoryException, RawFileException) {
        try {
            return new FileReader(filename);
        } catch (const std::bad_alloc&) {
            throw MemoryException();
        } catch (const std::exception& e) {
            throw RawFileException(e.what());
        }
    }

    void FileReader::destroy(FileReader *fr) {
        delete fr;
    }

    size_t FileReader::get_size() const {
        return size;
    }

    void FileReader::reset() const {
        file.seek(0, RawFile::SeekBeginning);
    }

    void FileReader::set(size_t pos) const {
        file.seek(pos, RawFile::SeekBeginning);
    }

    size_t FileReader::read(void *into, size_t sz) const {
        return file.read(into, sz);
    }

}