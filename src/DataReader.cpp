#include "MateLib/DataReader.hpp"

namespace Mate {

    DataReader::DataReader() : filename() { }

    DataReader::DataReader(const char *filename) : filename(filename) { }

    DataReader::~DataReader() { }

    void DataReader::set_filename(const char *filename) {
        this->filename.assign(filename);
    }

    const char *DataReader::get_filename() const {
        return filename.c_str();
    }

}