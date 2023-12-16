//
// Created by wolala on 23-12-16.
//

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdexcept>
#include <memory>
/**
 * @brief 动态数组
 * @tparam T 数组中存储的元素类型
 */
template <typename T>
class DynamicArray {
public:
    DynamicArray() = default;
    ~DynamicArray() = default;

    explicit DynamicArray(const size_t size) : data_(std::make_unique<T[]>(size)), size_(size), capacity_(size * 2) {}

    // 禁止复制
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    // 实现移动构造函数和移动赋值运算符
    DynamicArray(DynamicArray&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_), capacity_(other.capacity_) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    void resize(const size_t new_size) {
        if (new_size == 0) {
            data_.reset();
            size_ = capacity_ = 0;
            return;
        }
        auto new_data = std::make_unique<T[]>(new_size);
        for (size_t i = 0; i < std::min(size_, new_size); i++) {
            new_data[i] = std::move(data_[i]);
        }
        data_ = std::move(new_data);
        size_ = std::min(size_, new_size);
        capacity_ = new_size;
    }

    void push_back(const T data) {
        if (size_ == 0) {
            resize(1);
        } else if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_++] = data;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Array is empty");
        }
        size_--;
        if (size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
    }

    void insert(const size_t index, const T data) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        for (size_t i = size_; i > index; i--) {
            data_[i] = data_[i - 1];
        }
        data_[index] = data;
        size_++;
    }

    void erase(const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size_ - 1; i++) {
            data_[i] = data_[i + 1];
        }
        size_--;
        if (size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
    }

    T& operator[](const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    template <typename Compare>
    void heap_sort(const size_t start_index, const size_t end_index, Compare compare) {
        if (start_index >= end_index || start_index >= size_ || end_index > size_ || size_ <= 1) {
            return;
        }

        // 堆化
        for (size_t i = (end_index + start_index) / 2; i > start_index; --i) {
            sift_down(i - 1, end_index, compare);
        }
        sift_down(start_index, end_index, compare);

        // 排序
        for (size_t i = end_index - 1; i > start_index; --i) {
            std::swap(data_[start_index], data_[i]);
            sift_down(start_index, i, compare);
        }
    }

    size_t size() {
        return this->size_;
    }

private:
    std::unique_ptr<T[]> data_;
    size_t size_ = 0;
    size_t capacity_ = 0;

    template <typename Compare>
    void sift_down(const size_t start, const size_t end, Compare compare) {
        size_t root = start;
        while ((root * 2 + 1) < end) {
            size_t child = root * 2 + 1;
            if (child + 1 < end && compare(data_[child], data_[child + 1])) {
                ++child;
            }
            if (compare(data_[root], data_[child])) {
                std::swap(data_[root], data_[child]);
                root = child;
            } else {
                return;
            }
        }
    }

};

#endif //DYNAMIC_ARRAY_H
