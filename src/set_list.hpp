#ifndef SET_LIST_HPP
#define SET_LIST_HPP

#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <ranges>

template <typename T>
class SetList {
    struct ListNode {
        T data;
        std::shared_ptr<ListNode> next;
    };

public:
    class ListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit ListIterator(std::shared_ptr<ListNode> ptr = nullptr):ptr(ptr) {}

        ListIterator& operator++(){
            if (ptr) ptr = ptr->next;
            return *this;
        }
        ListIterator operator++(int){
            ListIterator tmp = *this;
            if (ptr) ptr = ptr->next;
            return tmp;
        }
        T& operator*() const{return ptr -> data;}
        T* operator->() const{return &ptr -> data;}
        bool operator==(const ListIterator& other) const = default;

    private:
        std::shared_ptr<ListNode> ptr;
    };

    using value_type = T;
    using iterator = ListIterator;
    // Normally there would be a const_iterator too

    SetList() = default;

    template <std::ranges::input_range Rng>
    explicit SetList(Rng&& rng) {
        std::ranges::for_each(std::forward<Rng>(rng),
                              std::bind_front(&SetList::insert, this));
    }

    ListIterator begin(){
        return ListIterator(head);
    }
    ListIterator end(){
        return ListIterator(nullptr);
    }
    
    bool contains(const T& value){
        for (auto iter = begin(); iter != end(); ++iter){
            if(*iter == value){return true;}
        }
        return false;
        }
    
    ListIterator insert(T value){
        if (!contains(value)){
            head = std::make_shared<ListNode>(std::move(value), std::move(head));
            return ListIterator(head);
        }
        return end();
    }

private:
    std::shared_ptr<ListNode> head = nullptr;
};

#endif




