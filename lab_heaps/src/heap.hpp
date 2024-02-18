
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <math.h>       /* floor */
#include <algorithm>
#include <iostream>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
void heap<T, Compare>::print() const{
    for (unsigned i = 1; i < _elems.size(); ++i) {
        std::cout << _elems[i] << ", ";
    }
    std::cout << std::endl;

}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return (2 * currentIdx < _elems.size());
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    T left = _elems[2*currentIdx];
    T right = _elems[2*currentIdx + 1];
    if (higherPriority(left, right)) {
        return 2 * currentIdx;
    } else {
        return 2 * currentIdx + 1;
    }
    return 0;
}


template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{   
    if (!hasAChild(currentIdx)) {
        return;
    }

    bool ifRight = false;
    
    T current = _elems[currentIdx];
    T left = _elems[leftChild(currentIdx)];
    T higher = left;


    if (2*currentIdx + 1 < _elems.size()) {
        T right = _elems[rightChild(currentIdx)];

        if (higherPriority(right, left)) {
            higher = right;
            ifRight = true;
        }
    }
    if (higherPriority(current, higher)) {
        higher = current;
        ifRight = false;
    }
    if (higher != current) {
        if (!ifRight) {
            std::swap(_elems[currentIdx], _elems[leftChild(currentIdx)]);
        } else {
            std::swap(_elems[currentIdx], _elems[rightChild(currentIdx)]);
        }
        if (!ifRight) {
            heapifyDown(leftChild(currentIdx));
        } else {
            heapifyDown(rightChild(currentIdx));
        }
    } 
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
    std::cout << "pushed, size : " << _elems.size() << std::endl;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T());
    for(unsigned i = 0; i < elems.size(); i++)
	{
		_elems.push_back(elems[i]);
	}
	for(unsigned i = parent(_elems.size() - 1); i > 0 ; i--)
	{
		heapifyDown(i);	
	}


}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (_elems.size() > 1) {
        T high = _elems[1];
        _elems[1] = _elems[_elems.size() - 1];
        _elems.pop_back();
        heapifyDown(1);
        return high;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (_elems.size() > 1) {
        return _elems[1];
    }
    
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    T prev = _elems[idx];
    _elems[idx] = elem;
    if (higherPriority(prev, elem)) {
        heapifyDown(idx);
    } else {
        heapifyUp(idx);
    }
    
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() < 2 ) return true;
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
