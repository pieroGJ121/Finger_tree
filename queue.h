#include "circulararray.h"

template <typename T> class Queue : public CircularArray<T> {
public:
  Queue(int capacity = 10) : CircularArray<T>(capacity) {}
  ~Queue() { this->killSelf(); }

  void enqueue(T data) { this->push_back(data); }

  T top() { return this->array[this->front]; }
  T dequeue() {
    if (this->is_empty()) {
      throw runtime_error("Queue is empty");
    }
    return this->pop_front();
  }
};
