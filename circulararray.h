#include <iostream>
#include <string>
using namespace std;

template <class T> class CircularArray {
private:
  T *array;
  int capacity;
  int back, front;

public:
  CircularArray(int _capacity = 10);
  virtual ~CircularArray() { delete[] array; }
  void resize() {
    T *temp = array;
    array = new T[capacity + 8];
    for (auto i = 0; i < capacity; i++) {
      array[i] = temp[(front + i) % capacity];
    }
    front = 0;
    back = capacity - 1;
    capacity = capacity + 8;

    delete[] temp;
  }
  void push_front(T data) {
    if (this->is_full()) {
      this->resize();
    }
    if (this->is_empty()) {
      front++;
      back++;
    } else {
      front--;
      front = ((front % capacity) + capacity) % capacity;
    }
    array[front] = data;
  }
  void push_back(T data) {
    if (this->is_full()) {
      this->resize();
    }
    if (this->is_empty()) {
      front++;
    }
    back++;
    back %= capacity;
    array[back] = data;
  }
  void insert(T data, int pos) {
    if (this->is_full()) {
      this->resize();
    }
    for (int i = (front + pos) % capacity; i != back; i = (i + 1) % capacity) {
      array[(i + 1) % capacity] = array[i];
    }
    array[(front + pos) % capacity] = data;

    back++;
  }
  T pop_front() {
    if (this->is_empty()) {
      throw runtime_error("Circular array is empty");
    }
    T data = array[front];
    if (front == back) {
      front = back = -1;
    } else {
      front = next(front);
    }
    return data;
  }
  T pop_back() {
    if (this->is_empty()) {
      throw runtime_error("Circular array is empty");
    }
    T data = array[back];
    if (front == back) {
      front = back = -1;
    } else {
      back = prev(back);
    }
    return data;
  }
  bool is_full() { return (back + 1) % capacity == front; }
  bool is_empty() { return front == -1; }
  int size() {
    if (front == -1) {
      return 0;
    }
    if (front <= back) {
      return back - front + 1;
    } else {
      return capacity - (front - back - 1);
    }
  }
  void clear() { front = back - 1; }
  T &operator[](int index) { return array[(front + index) % capacity]; }
  void sort() {
    if (is_empty()) {
      return;
    }
    int current = front;
    int minIndex;
    while (current != back) {
      minIndex = current;
      int nextIndex = next(current);
      while (nextIndex != (back + 1) % capacity) {
        if (array[nextIndex] < array[minIndex]) {
          minIndex = nextIndex;
        }
        nextIndex = next(nextIndex);
      }
      if (current != minIndex) {
        T temp = array[current];
        array[current] = array[minIndex];
        array[minIndex] = temp;
      }
      current = next(current);
    }
  }
  bool is_sorted() {
    if (is_empty()) {
      return true;
    }
    int current = front;
    int nextIndex = next(current);
    while (current != back) {
      if (array[current] > array[nextIndex]) {
        return false;
      }
      current = next(current);
      nextIndex = next(nextIndex);
    }
    return true;
  }
  void reverse() {
    int first = front, last = back;
    while (first != last && (next(first) != last && prev(last) != first)) {
      int temp = array[first];
      array[first] = array[last];
      array[last] = temp;

      first++;
      first %= capacity;
      last--;
      last = ((last % capacity) + capacity) % capacity;
    }
  }
  string to_string(string sep = " ") {
    string result = "";
    for (auto i = 0; i < this->size(); i++) {
      string temp = std::to_string(array[(front + i) % capacity]);
      result += temp + sep;
    }
    return result;
  }
  void killSelfPointer() {
    for (int i = 0; i < this->size(); i++) {
      (*this)[i]->killSelf();
    }
    delete[] array;
  }

private:
  int next(int index) { return (index + 1) % capacity; }
  int prev(int index) {
    return (((index - 1) % capacity) + capacity) % capacity;
  }
};

template <class T> CircularArray<T>::CircularArray(int _capacity) {
  this->capacity = _capacity;
  this->array = new T[_capacity];
  this->front = this->back = -1; // empty
}