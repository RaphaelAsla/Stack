#include <cstring>
#include <iostream>
#include <optional>

const int default_stack_size = 8;
const int default_bump_size = 8;

template <typename T>
class Stack {
  private:
    T* start = nullptr;
    T* end = nullptr;
    T* occupied = nullptr;

  public:
    std::size_t size() { return this->end - this->start; }

    std::size_t occupied_size() { return this->occupied - this->start; }

    void realloc(std::size_t new_size) {
        T* new_ptr = new T[this->occupied_size() + new_size];
        for (std::size_t i = 0; i < this->occupied_size(); i++) {
            new_ptr[i] = std::move(this->start[i]);
        }
        const std::size_t occupied_offset = this->occupied - this->start;
        const std::size_t end_offset = this->end - this->start + new_size;
        delete[] this->start;
        this->start = new_ptr;
        this->occupied = this->start + occupied_offset;
        this->end = this->start + end_offset;
    }

    void push(T value) {
        if (this->occupied == this->end) {
            realloc(this->occupied_size() + default_bump_size);
        }
        *this->occupied++ = value;
    }

    std::optional<T> pop() {
        if (this->occupied == this->start) {
            return {};
        }
        return *--this->occupied;
    }

    bool is_empty() { return this->occupied == this->start; }

    Stack() {
        this->start = new T[default_stack_size];
        this->end = this->start + default_stack_size;
        this->occupied = this->start;
    }

    Stack(size_t size) {
        this->start = new T[size];
        this->end = this->start + size;
        this->occupied = this->start;
    }

    ~Stack() { delete[] this->start; }
};
