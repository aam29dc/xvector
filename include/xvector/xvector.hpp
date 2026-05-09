#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>

template <typename T> class Xvector {
public:
  using size_t = std::size_t;

  Xvector();
  Xvector(const Xvector<T> &other);
  Xvector &operator=(const Xvector<T> &other);
  Xvector(Xvector<T> &&other) noexcept;
  Xvector &operator=(Xvector<T> &&other) noexcept;

  Xvector(std::initializer_list<T> list);

  virtual ~Xvector();

  void push_back(const T &);
  void pop_back();

  void reserve(const size_t capacity);

  T &operator[](const size_t index);

  size_t size() const;
  size_t capacity() const;

  void clear();

  T *begin();
  T *end();

  const T *begin() const;
  const T *end() const;

  template <typename... Args> T &emplace_back(Args &&...args);

private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void reallocate(const size_t capacity);
};

template <typename T>
Xvector<T>::Xvector() : data_(nullptr), size_(0), capacity_(0) {
  std::cout << "C.\n";
}

template <typename T>
Xvector<T>::Xvector(std::initializer_list<T> list)
    : data_(nullptr), size_(0), capacity_(0) {
  reallocate(list.size());
  for (const auto &val : list) {
    data_[size_++] = val;
  }
  std::cout << "il.\n";
}

template <typename T> Xvector<T>::Xvector(const Xvector<T> &other) {
  size_ = other.size_;
  capacity_ = other.capacity_;

  data_ = new T[capacity_];
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

template <typename T>
Xvector<T> &Xvector<T>::operator=(const Xvector<T> &other) {
  if (this == &other) {
    return *this;
  }

  T *newData = new T[other.capacity_];

  for (size_t i = 0; i < other.size_; ++i) {
    newData[i] = other.data_[i];
  }

  delete[] data_;
  data_ = newData;

  size_ = other.size_;
  capacity_ = other.capacity_;

  return *this;
}

template <typename T> Xvector<T>::Xvector(Xvector<T> &&other) noexcept {
  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
Xvector<T> &Xvector<T>::operator=(Xvector<T> &&other) noexcept {
  if (this == &other) {
    return *this;
  }

  delete[] data_;

  data_ = other.data_;
  size_ = other.size_;
  capacity_ = other.capacity_;

  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;

  return *this;
}

template <typename T> Xvector<T>::~Xvector() { delete[] data_; }

template <typename T> void Xvector<T>::push_back(const T &value) {
  if (size_ == capacity_) {
    size_t capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    reallocate(capacity);
  }

  data_[size_++] = value;
}

template <typename T> void Xvector<T>::pop_back() {
  if (size_ > 0)
    --size_;
}

template <typename T> void Xvector<T>::reallocate(const size_t capacity) {
  T *newData = new T[capacity];

  for (size_t i = 0; i < size_; ++i) {
    newData[i] = data_[i];
  }

  delete[] data_;
  data_ = newData;
  capacity_ = capacity;
}

template <typename T> void Xvector<T>::reserve(const size_t capacity) {
  if (capacity <= capacity_)
    return;

  T *newData = new T[capacity];

  for (size_t i = 0; i < capacity; ++i) {
    newData[i] = data_[i];
  }

  delete[] data_;

  data_ = newData;
  capacity_ = capacity;
}

template <typename T> T &Xvector<T>::operator[](const size_t index) {
  return data_[index];
}

template <typename T> size_t Xvector<T>::size() const { return size_; }

template <typename T> size_t Xvector<T>::capacity() const { return capacity_; }

template <typename T> void Xvector<T>::clear() { size_ = 0; }

template <typename T> T *Xvector<T>::begin() { return data_; }

template <typename T> const T *Xvector<T>::begin() const { return data_; }

template <typename T> T *Xvector<T>::end() { return data_ + size_; }

template <typename T> const T *Xvector<T>::end() const { return data_ + size_; }

template <typename T>
template <typename... Args>
T &Xvector<T>::emplace_back(Args &&...args) {
  //
}
