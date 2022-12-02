
/**
 * @file heap.hpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include <math.h> 

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (hasAChild(currentIdx)) {
        if (rightChild(currentIdx) < _elems.size()) {
            if (higherPriority(_elems[rightChild(currentIdx)], _elems[leftChild(currentIdx)])) {
                return rightChild(currentIdx);
            }  
        }
        return leftChild(currentIdx); 
    }
    return 1;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!(hasAChild(currentIdx))) {
        return;
    }

    size_t minChildIndex = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[minChildIndex], _elems[currentIdx])) {
        std::swap( _elems[currentIdx], _elems[minChildIndex] );
        heapifyDown(minChildIndex);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root()) //you can't heapify up if you are at the root
        return;
    if (currentIdx == root()) {
        return;
    }
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
    // you need to get the parent, then you need to check if you want to switch with the parent, which would mean the current index would have
    // a higher priority than the parent, if this is the case then you need to swap and then heapify up again from the parentIdx, keep going
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    std::vector<T> vect(1, T());
    _elems = vect;
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(elems[0]);
    for (unsigned i = 0; i < elems.size(); i++) {
        _elems.push_back(elems[i]);
    }

    //you first just need to construct a elem list of the elements then go through the elements backwards and heapify down

    for (unsigned i = _elems.size() - 1; i > 0; i--) {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (!empty()) {
        auto minValue = _elems[1];
        _elems[1] = _elems[_elems.size() - 1];
        _elems.pop_back();
        heapifyDown(1);
        return minValue;
    }
    //to remove an element, you need to swap the highest prioirty item with the last item, then you need to pop from the bottom, which is now the higheset prioirty item, and then you need to heapify down again
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
    //whenever you add in heap you are just adding each element to the end of the elems, then you need to heapify up
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    if (idx < _elems.size()) { //need to first make sure that the idx is correct and not too big
        _elems[idx] = elem;
        heapifyUp(idx);// you should first try to heapify up on the element, then if that doesn't do aythign heapify down should sort itself out
        heapifyDown(idx);
    } 
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.size() == 0;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
