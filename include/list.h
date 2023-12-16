//
// Created by wolala on 23-12-8.
//

#ifndef DATASTRUCTUREFINALWORK_LIST_H
#define DATASTRUCTUREFINALWORK_LIST_H

#include <stdexcept>
#include <memory>

/**
 * @brief 单向链表
 * @tparam T 链表中存储的元素类型
 */

template <typename T>
class List {
public:
    List() = default;
    ~List() {
        while (head) {
            auto next = std::move(head->next);
            head = std::move(next);
        }
    }

    explicit List(const size_t size) : size_(size) {
        resize(size);
    }

    // 移动构造函数
    List(List&& other) noexcept : head(std::move(other.head)), size_(other.size_) {
        other.size_ = 0;
    }

    // 移动赋值运算符
    List& operator=(List&& other) noexcept {
        if (this != &other) {
            head = std::move(other.head);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    // 禁用复制构造函数和复制赋值运算符
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    /**
     * @brief 在链表尾部插入元素
     * @param data
     */
    void push_back(T&& data) {
        if (!head) {
            head = std::make_unique<ListNode>(std::move(data));
        } else {
            ListNode* node = head.get();
            while (node->next) {
                node = node->next.get();
            }
            node->next = std::make_unique<ListNode>(std::move(data));
        }
        size_++;
    }

    /**
     * @brief 删除链表尾部元素
     * @throw std::out_of_range 如果链表为空
     */
    void pop_back() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        if (!head->next) {
            head.reset();
        } else {
            ListNode* node = head.get();
            while (node->next->next) {
                node = node->next.get();
            }
            node->next.reset();
        }
        size_--;
    }

    /**
     * @brief 在链表指定位置插入元素
     * @param index
     * @param data
     * @throw std::out_of_range 如果index超出范围
     */
    void insert(const size_t index, T data) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (index == size_) {
            push_back(data);
            return;
        }
        ListNode *node = head.get();
        for (int i = 0; i < index - 1; i++) {
            node = node->next.get();
        }
        node->next = std::make_unique<ListNode>(ListNode{data, std::move(node->next)});
        size_++;
    }

    /**
     * @brief 删除指定位置的元素
     * @param index
     * @throw std::out_of_range 如果index超出范围
     */
    void erase(const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        if (index == size_ - 1) {
            pop_back();
            return;
        }
        ListNode *node = head.get();
        for (int i = 0; i < index - 1; i++) {
            node = node->next.get();
        }
        node->next = std::move(node->next->next);
        size_--;
    }

    /**
     * @brief 重新设置链表大小
     * @param new_size
     */
    void resize(const size_t new_size) {
        if (new_size < size_) {
            while (size_ > new_size) {
                pop_back();
            }
        } else if (new_size > size_) {
            while (size_ < new_size) {
                push_back(T{});
            }

        }
    }

    /**
     * @brief 重载[]运算符
     * @param index
     * @return T&
     * @throw std::out_of_range 如果index超出范围
     */
    T& operator[](const size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        ListNode *node = head.get();
        for (int i = 0; i < index; i++) {
            node = node->next.get();
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
     * @brief 获取链表大小
     * @return int
     */
    size_t size() {
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
        T data = T{};
        std::unique_ptr<ListNode> next = nullptr;

        explicit ListNode(T&& data, std::unique_ptr<ListNode> next = nullptr) : data(std::move(data)), next(std::move(next)) {}
    } ListNode;

    size_t size_ = 0;

    std::unique_ptr<ListNode> head = nullptr;

};

#endif//DATASTRUCTUREFINALWORK_LIST_H
