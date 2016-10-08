#ifndef _MATELIB_DATAWRITER_HPP_
#define _MATELIB_DATAWRITER_HPP_

#include <string>

namespace Mate {

    class DataWriter {
    private:
        DataWriter(const DataWriter&);
        DataWriter& operator=(const DataWriter&);

    public:
        DataWriter();
        DataWriter(const char *filename);
        virtual ~DataWriter();

        const char *get_filename() const;
        void set_filename(const char *filename);

        virtual size_t write(const void *from, size_t sz) = 0;

    private:
        std::string filename;
    };

}

#endif