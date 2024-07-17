#pragma once

#include "../util/util.hpp"

template<typename T>
class MeshBuffer {
public:
    T *data;

    // the capacity of the data (in elements)
    size_t capacity;

    // current number of elements into the data
    size_t elements;

    void init(size_t capacity);
    void destroy();
    void prepare();
};
