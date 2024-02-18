
#include <iostream>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;
    ListNode* tail_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }
    ListIterator (ListNode * x, ListNode * t) {
        position_ = x;
        tail_ = t;
    }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int num) {
        // @TODO: graded in mp_lists part 1
        ListIterator temp = *this;
        position_ = position_->next;
        return temp;
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        if (position_ == NULL) {
            position_ = tail_;
        } else {
            position_ = position_->prev;
        }
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int num) {
        // @TODO: graded in mp_lists part 1
        ListIterator temp = *this;
        if (position_ == NULL) {
            position_ = tail_;
        } else {
            position_ = position_->prev;
        }
        return temp;
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        if (rhs.position_ != position_) {
            return true;
        }
        return false;
    }

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
