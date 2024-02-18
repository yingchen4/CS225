/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
#include <string>
template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1

  return List<T>::ListIterator(NULL, tail_);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  while (head_ != NULL) {
    ListNode * temp = head_;
    head_ = head_->next;
    delete temp;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  if (head_ == NULL) {
    head_ = newNode;
  } else {
    tail_->next = newNode;
    newNode->next = NULL;
    newNode->prev = tail_;
  }
  tail_ = newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
  if (start == NULL) {
    return NULL;
  }
  if (splitPoint == 0){
    return start;
  }
  if (length_<=splitPoint) {
    return NULL;
  }
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  curr -> prev -> next = NULL;
  tail_ = curr -> prev;
  curr -> prev = NULL;
  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if (head_ == NULL || head_->next == NULL) {
    return;
  }
  ListNode * curr = head_;
  ListNode * move;
  while (curr->next != tail_) {
    move = curr->next;
    curr -> next = move -> next;
    move -> next -> prev = curr;
    tail_ -> next = move;
    move -> prev = tail_;
    move -> next = NULL;
    tail_ = move;
    curr = curr -> next;
  }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  if (startPoint == endPoint) {
    return;
  }
  ListNode * start = startPoint;
  ListNode * end = endPoint;
  while (start != end && start -> prev != end) {
    ListNode * tempS = start;
    ListNode * sPrev = start -> prev;
    ListNode * eNext = end -> next;
    ListNode * sNext = start -> next;
    ListNode * ePrev = end -> prev;

    if (start -> next == end) {
      sNext = start;
      ePrev = end;
    }

    start = end;
    start -> prev = sPrev;
    start -> next = sNext;
    end = tempS;
    end -> prev = ePrev;
    end -> next = eNext;
    if (sPrev != NULL) {
      sPrev -> next = start;
    }
    sNext -> prev = start;
    ePrev -> next = end;
    if (eNext != NULL) {
      eNext -> prev = end;
    }

    start = start->next;
    end = end->prev;
  }

  ListNode * temp = startPoint;
  if (startPoint == head_) {
    head_ = endPoint;
  }
  if (endPoint == tail_) {
    tail_ = startPoint;
  }
  startPoint = endPoint;
  endPoint = temp;
  
  // std::cout << "_______inReverse_______ :" << std::endl;
  // std::cout << "startPoint :" << startPoint->data << std::endl;
  // std::cout << "startPointnext :" << startPoint->next->data << std::endl;
  // std::cout << "endpoint2 :" << endPoint->data << std::endl;
  // std::cout << startPoint->next->data << std::endl;
  // std::cout << endPoint->next->data << std::endl;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) { //6
  /// @todo Graded in mp_lists part 2
  int size = length_; //8
  ListNode * start = head_;
  ListNode * end = head_;
  ListNode * newStart = head_;
  if (n>size) {
    reverse(head_,tail_);
    return;
  } else {
    while (n < size) {
      for (int count = 0; count < n - 1; count++ ) {
        end = end->next;
      }
      // std::cout << "start-end2: "<<start->data << " - " <<end->data <<std::endl;
      newStart = end->next;
      reverse(start,end);
      // print(std::cout);
      // std::cout << std::endl;
      // std::cout << "start-end: "<<start->data << " - " <<end->data <<std::endl;
      // std::cout << "newStart: "<<newStart->data << std::endl;
      size -= n;
      start = newStart;
      end = newStart;
    }
    if (size > 0) {
      for (int count = 0; count < size - 1; count++ ) {
        end = end->next;
        // std::cout << "loop-end: "<< end->data << std::endl;
      }
        // std::cout << "newStart: "<<newStart->data << std::endl;
        // std::cout << "end: "<< end->data << std::endl;
        reverse(newStart,end);
      }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  ListNode * start = first;
  ListNode * two = second;
  ListNode * one = start;
  while (two != NULL) {
    if (two->data < one->data) {
      if (start == one) {
        start = two;
      }
      ListNode * prev1 = one -> prev;
      ListNode * next2 = two -> next;
      if (prev1 != NULL) {
        prev1 -> next = two;
      }
      two -> prev = prev1;
      two -> next = one;
      one -> prev = two;
      one = two;
      two = next2;
    }
    
    if (one->next == NULL) {
      one -> next=two;
      two -> prev = one;
      return start;
    }
    one = one -> next;
    
  }

  return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2

  if (chainLength <= 1) {
    return start;
  }

  int half = chainLength / 2;
  int rest = chainLength - half;
  ListNode * secondBegin = split(start, half);//1

  ListNode * one = mergesort(start, half);//1
  ListNode * two = mergesort(secondBegin, rest);

  return merge(one,two);

}
