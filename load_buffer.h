//
// Created by andre on 2022/12/2.
//

#ifndef EXTERN_SORT_LOAD_BUFFER_H
#define EXTERN_SORT_LOAD_BUFFER_H

#include <cstdint>
#include <string>
#include <cstdio>

class ObLoadDataBuffer
{
public:
    ObLoadDataBuffer();
    ~ObLoadDataBuffer();
    void reuse();
    void reset();
    int create(int64_t capacity);
    int squash();
    char *data() const { return data_; }
    char *begin() const { return data_ + begin_pos_; }
    char *end() const { return data_ + end_pos_; }
    bool empty() const { return end_pos_ == begin_pos_; }
    int64_t get_data_size() const { return end_pos_ - begin_pos_; }
    int64_t get_remain_size() const { return capacity_ - end_pos_; }
    void consume(int64_t size) { begin_pos_ += size; }
    void produce(int64_t size) { end_pos_ += size; }
private:
    char *data_;
    int64_t begin_pos_;
    int64_t end_pos_;
    int64_t capacity_;
};

class ObLoadSequentialFileReader
{
public:
    ObLoadSequentialFileReader();
    ~ObLoadSequentialFileReader();
    int open(const std::string &filepath);
    int read_next_buffer(ObLoadDataBuffer &buffer);
private:
    FILE *file_reader_{};
    int64_t offset_;
    bool is_read_end_;
};


#endif //EXTERN_SORT_LOAD_BUFFER_H
