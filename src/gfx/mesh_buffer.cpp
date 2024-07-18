#include "mesh_buffer.hpp"

template<typename T>
void MeshBuffer<T>::init(size_t capacity) {
    destroy();

    this->capacity = capacity;
    data = new T[capacity];
}

template<typename T>
void MeshBuffer<T>::destroy() {
    if (data == nullptr) {
        return;
    }
    delete[] data;
}

template<typename T>
void MeshBuffer<T>::prepare() {
    elements = 0;
}

template<typename T>
void MeshBuffer<T>::append(T value) {
    data[elements++] = value;
}
