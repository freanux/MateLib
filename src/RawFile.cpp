#include "MateLib/RawFile.hpp"

namespace Mate {

    RawFile::RawFile(const char *filename, Mode mode) throw (RawFileException) {
        f = fopen(filename, get_mode(mode));
        if (!f) {
            throw RawFileException(std::string("Cannot open file: ") + filename);
        }
    }

    RawFile::~RawFile() {
        fclose(f);
    }

    RawFile *RawFile::create(const char *filename, Mode mode) throw (MemoryException, RawFileException) {
        try {
            return new RawFile(filename, mode);
        } catch (const std::bad_alloc&) {
            throw MemoryException();
        } catch (const std::exception& e) {
            throw RawFileException(e.what());
        }
    }

    void RawFile::destroy(RawFile *rw) {
        delete rw;
    }

    bool RawFile::is_file_present(const char *filename) {
        FILE *f = fopen(filename, "rb");
        if (f) {
            fclose(f);
            return true;
        }

        return false;
    }

    size_t RawFile::read(void *buffer, size_t sz) const throw () {
        return fread(buffer, 1, sz, f);
    }

    size_t RawFile::write(const void *buffer, size_t sz) const throw () {
        return fwrite(buffer, 1, sz, f);
    }

    void RawFile::seek(long int offset, Seek seek) const throw () {
        fseek(f, static_cast<long>(offset), seek);
    }

    size_t RawFile::get_position() const throw () {
        return static_cast<size_t>(ftell(f));
    }

    const char *RawFile::get_mode(Mode mode) {
        switch (mode) {
            case ModeRead:
                return "r";

            case ModeWrite:
                return "w";

            case ModeReadByte:
                return "rb";

            case ModeWriteByte:
                return "wb";

            case ModeAppend:
                return "a";

            case ModeAppendByte:
                return "ab";
        }

        return 0;
    }

}
