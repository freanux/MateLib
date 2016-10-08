#include "MateLib/DataWriter.hpp"

namespace Mate {

    DataWriter::DataWriter() : filename() { }

    DataWriter::DataWriter(const char *filename) : filename(filename) { }

    DataWriter::~DataWriter() { }

    const char *DataWriter::get_filename() const {
        return filename.c_str();
    }

    void DataWriter::set_filename(const char *filename) {
        this->filename.assign(filename);
    }

}
