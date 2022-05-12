//
// Created by jamabaiz on 4/28/2022.
//

#pragma once

#include <iostream>
#include <fstream>
#include <utility>

class CSVFile;

inline static CSVFile &nextl(CSVFile &file);

inline static CSVFile &flush(CSVFile &file);

class CSVFile {
    std::ofstream file_stream;
    const std::string separator;
public:
    explicit CSVFile(const std::string &file_name, std::string separator = ",")
            : file_stream(), separator(std::move(separator)) {
        file_stream.exceptions(std::ios::failbit | std::ios::badbit);
        file_stream.open(file_name);
    }

    ~CSVFile() {
        flush();
        file_stream.close();
    }

    void flush() {
        file_stream.flush();
    }

    void end_row() {
        file_stream << std::endl;
    }

    CSVFile &operator<<(CSVFile &(*val)(CSVFile &)) {
        return val(*this);
    }

    CSVFile &operator<<(const char *val) {
        file_stream << '"' << val << '"' << separator;
        return *this;
    }

    CSVFile &operator<<(const std::string &val) {
        file_stream << '"' << val << '"' << separator;
        return *this;
    }

    template<typename T>
    CSVFile &operator<<(const T &val) {
        file_stream << val << separator;
        return *this;
    }
};


inline static CSVFile &nextl(CSVFile &file) {
    file.end_row();
    return file;
}

inline static CSVFile &flush(CSVFile &file) {
    file.flush();
    return file;
}