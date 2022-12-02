//
// Created by andre on 2022/12/2.
//

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "load_buffer.h"

ObLoadDataBuffer::ObLoadDataBuffer()
        : data_(nullptr), begin_pos_(0), end_pos_(0), capacity_(0)
{
}

ObLoadDataBuffer::~ObLoadDataBuffer()
{
    reset();
}

void ObLoadDataBuffer::reuse()
{
    begin_pos_ = 0;
    end_pos_ = 0;
}

void ObLoadDataBuffer::reset()
{
//    allocator_.reset();
    data_ = nullptr;
    begin_pos_ = 0;
    end_pos_ = 0;
    capacity_ = 0;
}

int ObLoadDataBuffer::create(int64_t capacity)
{
    data_ = static_cast<char *>(malloc(capacity));
    capacity_ = capacity;
    return 0;
}

int ObLoadDataBuffer::squash()
{
    const int64_t data_size = get_data_size();
    if (data_size > 0) {
        memcpy(data_, data_ + begin_pos_, data_size);
    }
    begin_pos_ = 0;
    end_pos_ = data_size;
    return 0;
}

ObLoadSequentialFileReader::ObLoadSequentialFileReader()
        : offset_(0), is_read_end_(false)
{
}

ObLoadSequentialFileReader::~ObLoadSequentialFileReader()
= default;

int ObLoadSequentialFileReader::open(const std::string &filepath)
{
    file_reader_ = fopen(filepath.c_str(), "r");
    return 0;
}

int ObLoadSequentialFileReader::read_next_buffer(ObLoadDataBuffer &buffer)
{
    if (is_read_end_) {
        return 1;
    } else if (buffer.get_remain_size() > 0) {
        const int64_t buffer_remain_size = buffer.get_remain_size();
        int64_t read_size = 0;
        pread();
        if (OB_FAIL(file_reader_.pread(buffer.end(), buffer_remain_size, offset_, read_size))) {
            LOG_WARN("fail to do pread", KR(ret));
        } else if (read_size == 0) {
            is_read_end_ = true;
            ret = OB_ITER_END;
        } else {
            offset_ += read_size;
            buffer.produce(read_size);
        }
    }
    return ret;
}
