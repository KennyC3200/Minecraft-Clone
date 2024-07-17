#include "mesh_buffer.hpp"

template<typename T>
void MeshBuffer<T>::init(size_t capacity) {
    this->capacity = capacity;
    data = new T[capacity];
}

template<typename T>
void MeshBuffer<T>::destroy() {
    delete[] data;
}

template<typename T>
void MeshBuffer<T>::prepare() {
    elements = 0;
}
