//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_LIST_H
#define DATASTRUCTUREFINALWORK_LIST_H

#include <exception>
#include <stdexcept>

/**
 * @brief 双向链表
 * @tparam T 链表中存储的元素类型
 */

template <typename T>
class List {
public:
    List() {
        size_ = 0;
        head = nullptr;
        tail = nullptr;
    }
    ~List() {
        ListNode *node = head;
        while (node != nullptr) {
            ListNode *next_node = node->next;
            delete node;
            node = next_node;
        }
    }
    explicit List(int size) {
        resize(size);
    }

    /**
     * @brief 在链表尾部插入元素
     * @param data
     */
    void push_back(T data) {
        auto *new_node = new ListNode;
        new_node->data = data;
        if (tail == nullptr) {
            new_node->prev = nullptr;
            new_node->next = nullptr;
            head = new_node;
            tail = new_node;
        } else {
            new_node->prev = tail;
            new_node->next = nullptr;
            tail->next = new_node;
            tail = new_node;
        }
        size_++;
    }

    /**
     * @brief 删除链表尾部元素
     * @throw std::out_of_range 如果链表为空
     */
    void pop_back() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        ListNode *node = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        delete node;
        size_--;
    }

    /**
     * @brief 在链表指定位置插入元素
     * @param index
     * @param data
     * @throw std::out_of_range 如果index超出范围
     */
    void insert(int index, T data) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        auto *node = new ListNode;
        node->data = data;
        if (index == 0) {
            node->prev = nullptr;
            node->next = head;
            if (head != nullptr) {
                head->prev = node;
            }
            head = node;
            if (tail == nullptr) {
                tail = node;
            }
        } else {
            ListNode *prev_node = head;
            for (int i = 0; i < index - 1; i++) {
                prev_node = prev_node->next;
            }
            node->prev = prev_node;
            node->next = prev_node->next;
            if (prev_node->next != nullptr) {
                prev_node->next->prev = node;
            }
            prev_node->next = node;
            if (tail == prev_node) {
                tail = node;
            }
        }
        size_++;
    }

    /**
     * @brief 删除指定位置的元素
     * @param index
     * @throw std::out_of_range 如果index超出范围
     */
    void erase(int index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        ListNode *node = head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        if (node == head) {
            head = node->next;
        }
        if (node == tail) {
            tail = node->prev;
        }
        delete node;
        size_--;
    }

    /**
     * @brief 重新设置链表大小
     * @param new_size
     */
    void resize(int new_size) {
        if (new_size < size_) {
            for (int i = 0; i < size_ - new_size; i++) {
                pop_back();
            }
        } else if (new_size > size_) {
            for (int i = 0; i < new_size - size_; i++) {
                push_back(T());
            }
        } else {
            return;
        }
        size_ = new_size;
    }

    /**
     * @brief 基于堆排序的链表排序
     */
    template<typename Compare>
    void heap_sort(int start_index, int end_index, Compare compare) {
        int size = end_index - start_index + 1;
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(start_index, size, i, compare);
        }
        for (int i = size - 1; i >= 0; i--) {
            std::swap((*this)[start_index], (*this)[start_index + i]);
            heapify(start_index, i, 0, compare);
        }
    }

    /**
     * @brief 重载[]运算符
     * @param index
     * @return T&
     * @throw std::out_of_range 如果index超出范围
     */
    T& operator[](int index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        ListNode *node = head;
        for (int i = 0; i < index; i++) {
            node = node->next;
        }
        return node->data;
    }

    /**
     * @brief 获取链表头部元素
     * @return T&
     */
    T& front() {
        return head->data;
    }

    /**
     * @brief 获取链表尾部元素
     * @return T&
     */
    T& back() {
        return tail->data;
    }

    /**
     * @brief 获取链表大小
     * @return int
     */
    int size() {
        return this->size_;
    }

    /**
     * @brief 判断链表是否为空
     * @return bool
     */
    bool empty() {
        return this->size_ == 0;
    }

private:
    typedef struct ListNode {
        T data;
        ListNode *prev;
        ListNode *next;
    } ListNode;
    int size_ = 0;
    ListNode *head = nullptr;
    ListNode *tail = nullptr;

    /**
     * @brief 堆化
     * @param start_index
     * @param size
     * @param index
     * @param compare
     */
    template<typename Compare>
    void heapify(int start_index, int size, int index, Compare compare) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < size && compare((*this)[start_index + left], (*this)[start_index + largest])) {
            largest = left;
        }
        if (right < size && compare((*this)[start_index + right], (*this)[start_index + largest])) {
            largest = right;
        }
        if (largest != index) {
            std::swap((*this)[start_index + index], (*this)[start_index + largest]);
            heapify(start_index, size, largest, compare);
        }
    }

};

#endif//DATASTRUCTUREFINALWORK_LIST_H
