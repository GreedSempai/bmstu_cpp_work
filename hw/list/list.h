#pragma once
#include <iostream>

namespace bmstu {
    template <typename T>
    class list {
        struct node {
    T value_;
    node* next_node_;
    node* prev_node_;

    node() = default;
    node(T value_, node* next_node_ = nullptr, node* prev_node_ = nullptr) : value_(value_), next_node_(next_node_), prev_node_(prev_node_) {}
};
    public:
        list() : size_(0), tail_(new node()), head_(new node()) {
    head_->next_node_ = tail_;
    tail_->prev_node_ = head_;
}

        list(std::initializer_list<T> value) {
            for (const auto& val : value) {
                push_back(val);
            }
        }

        template <typename Type>
            void push_front(const Type& value) {
            node* first = head_->next_node_;
            node* new_first = new node(value, first, head_);
            head_->next_node_ = new_first;
            first->prev_node_ = new_first;
            ++size_;
        }

        template <typename Type>
        void push_back(const Type& value) {
            node* last = tail_->prev_node_;
            node* new_last = new node(value, tail_, last);
            tail_->prev_node_ = new_last;
            last->next_node_ = new_last;
            ++size_;
        }

        size_t size() const {
            return size_;
        }

        template <typename value_t>
        struct list_iterator {
                friend class list;
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type_ = value_t;
                using difference_type = std::ptrdiff_t;
                using pointer = value_t *;
                using reference = value_t &;

                list_iterator()= default;

                list_iterator(node *node) : node_(node) {}

                list_iterator(const list_iterator &other) = default;

                reference operator*() const{
                    assert(node_ != nullptr);
                    return node_->value_;
                }

                pointer operator->() const {
                    assert(node_ !=nullptr);
                    return &(node_->value_);
                }

                list_iterator &operator++() {
                    assert(node_ != nullptr);
                    node_ = node_->next_node_;
                    return *this;
                }

                list_iterator &operator--() {
                    assert(node_ !=nullptr);
                    node_ = node_->prev_node_;
                    return *this;
                }

                list_iterator operator++(int) {
                    list_iterator tmp = *this;
                    ++(*this);
                    return tmp;
                }

                list_iterator operator--(int) {
                    list_iterator tmp = *this;
                    --(*this);
                    return tmp;
                }

                list_iterator operator+(difference_type n) {
                    list_iterator tmp = *this;
                    for (difference_type i = 0; i < n; ++i) {
                        ++tmp;
                    }
                    return tmp;
                }

                list_iterator& operator+=(difference_type n) {
                    for (difference_type i = 0; i < n; ++i) {
                        ++(*this);
                    }
                    return *this;
                }

                bool operator==(const list_iterator& other) const {
                    return node_ == other.node_;
                }

                bool operator!=(const list_iterator& other) const {
                    return node_ != other.node_;
                }

            private:
                node* node_ = nullptr;
            };

            using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = list_iterator<T>;
        using const_iterator = list_iterator<const T>;
        friend bool operator==(const list& l, const list& r) {
            if (l.size() != r.size()) return false;
            for (auto l_it = l.begin(), r_it = r.begin(); l_it != l.end(); ++l_it, ++r_it) {
                if (*l_it != *r_it) {
                    return false;
                }
            }
            return true;
        }

        friend bool operator!=(const list& l, const list& r) {
            return !(l == r);
        }

        friend bool operator<(const list& l, const list& r) {
            return lexicographical_compare_(l, r);
        }

        friend bool operator>(const list& l, const list& r) {
            return !(l <= r);
        }

        friend bool operator<=(const list& l, const list& r) {
            return (l < r || l == r);
        }

        friend bool operator>=(const list& l, const list& r) {
            return !(l < r);
        }

        iterator begin() noexcept {
            return iterator{ head_->next_node_ };
        }

        iterator end() noexcept {
            return iterator{ tail_ };
        }

        const_iterator begin() const noexcept {
            return const_iterator{ head_->next_node_ };
        }

        const_iterator end() const noexcept {
            return const_iterator{ tail_ };
        }

        const_iterator cbegin() const noexcept {
            return const_iterator{ head_->next_node_ };
        }

        const_iterator cend() const noexcept {
            return const_iterator{ tail_ };
        }

        T operator[](size_t pos) const {
            return *(begin() + pos);
        }

        T& operator[](size_t pos) {
            return *(begin() + pos);
        }

    private:
        static bool lexicographical_compare_(const list<T>& l, const list<T>& r) {
            auto lb = l.begin();
            auto rb = r.begin();
            auto le = l.end();
            auto re = r.end();
            for (; (lb != le) && (rb != re); ++lb, ++rb) {
                if (*lb < *rb) {
                    return true;
                }
                if (*rb < *lb) {
                    return false;
                }
            }
            return (lb == le) && (rb != re);
        }
        size_t size_ = 0;
        node* tail_ = nullptr;
        node* head_ = nullptr;
    };
}