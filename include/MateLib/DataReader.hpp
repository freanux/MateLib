#ifndef _MATELIB_DATAREADER_HPP_
#define _MATELIB_DATAREADER_HPP_

#include <string>

namespace Mate {

    class DataReader {
    private:
        DataReader(const DataReader&);
        const DataReader& operator=(const DataReader&);

    public:
        DataReader();
        DataReader(const char *filename);
        virtual ~DataReader();

        void set_filename(const char *filename);
        const char *get_filename() const;

        virtual size_t get_size() const = 0;
        virtual void reset() const = 0;
        virtual void set(size_t pos) const = 0;
        virtual size_t read(void *into, size_t sz) const = 0;

    private:
        std::string filename;
    };

}

#endif