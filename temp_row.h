//
// Created by andre on 2022/12/2.
//

#ifndef EXTERN_SORT_TEMP_ROW_H
#define EXTERN_SORT_TEMP_ROW_H

#include <cstdint>
#include <cstdlib>

class RowDatum {
    RowDatum(int64_t k1, int64_t k2, char *line): k1_(k1), k2_(k2), line_(line) {}
    ~RowDatum() {
        free(line_);
    }

    bool operator <(const RowDatum &other) const
    {
        return k1_ < other.k1_ || (k1_ == other.k1_ && k2_ < other.k2_);
    }
    bool operator >(const RowDatum &other) const
    {
        return k1_ > other.k1_ || (k1_ == other.k1_ && k2_ > other.k2_);
    }

private:
    int64_t k1_;
    int64_t  k2_;
    char *line_;
};

#endif //EXTERN_SORT_TEMP_ROW_H
