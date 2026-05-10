#pragma once
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <stdexcept>

template <typename T> class Xvector {
public:
  using size_t = std::size_t;

  constexpr Xvector() noexcept;
  Xvector(const Xvector<T> &other);
  Xvector &operator=(const Xvector<T> &other);
  Xvector(Xvector<T> &&other) noexcept;
  Xvector &operator=(Xvector<T> &&other) noexcept;

  Xvector(std::initializer_list<T> list);

  ~Xvector();

  void push_back(const T &);
  void pop_back() noexcept;
  void insert(const size_t index, const T &value);
  void erase(const size_t index);
  T &front() noexcept;
  T &back() noexcept;
  constexpr T &front() const noexcept;
  constexpr T &back() const noexcept;

  [[nodiscard]] constexpr bool empty() const noexcept;
  [[nodiscard]] constexpr size_t size() const noexcept;
  [[nodiscard]] constexpr size_t capacity() const noexcept;
  [[nodiscard]] constexpr size_t max_size() const noexcept;
  void shrink_to_fit();
  void swap(Xvector<T> &other) noexcept;
  void reserve(const size_t capacity);
  void resize(const size_t size, const T &value = T());

  T &operator[](const size_t index) noexcept;
  const T &operator[](const size_t index) const noexcept;

  void clear() noexcept;

  T *begin() noexcept;
  T *end() noexcept;
  const T *begin() const noexcept;
  const T *end() const noexcept;

  const T *cbegin() const noexcept;
  const T *cend() const noexcept;

  T *data() noexcept;
  const T *data() const noexcept;

  T &at(const size_t index);
  const T &at(const size_t index) const;

  //  template <typename... Args> T &emplace_back(Args &&...args);

  bool operator==(const Xvector<T> &other) const noexcept;
  bool operator!=(const Xvector<T> &other) const noexcept;

private:
  T *data_;
  size_t size_;
  size_t capacity_;

  void reallocate(const size_t capacity);
};

template <typename T>
constexpr Xvector<T>::Xvector() noexcept
    : data_(nullptr), size_(0), capacity_(0) {
#ifndef XVECTOR_DEBUG
  std::cout << "C.\n";
#endif
}

template <typename T>
Xvector<T>::Xvector(std::initializer_list<T> list)
    : data_(nullptr), size_(0), capacity_(0) {
  reallocate(list.size());
  for (const auto &val : list) {
    data_[size_++] = val;
  }
}

template <typename T>
Xvector<T>::Xvector(const Xvector<T> &other)
    : size_(other.size_), capacity_(other.capacity_) {
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

template <typename T>
Xvector<T>::Xvector(Xvector<T> &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {

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
  if (size_ >= capacity_) {
    size_t capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    reallocate(capacity);
  }

  data_[size_++] = value;
}

template <typename T> void Xvector<T>::pop_back() noexcept {
  if (size_ > 0)
    --size_;
}

template <typename T>
void Xvector<T>::insert(const size_t index, const T &value) {
  if (index > size_) {
    throw std::out_of_range("insert: index out of range");
  }
  if (size_ == capacity_) {
    size_t newCap = (capacity_ == 0) ? 1 : capacity_ * 2;
    reallocate(newCap);
  }
  for (size_t i = size_; i > index; --i) {
    data_[i] = data_[i - 1];
  }
  data_[index] = value;
  ++size_;
}

template <typename T> void Xvector<T>::erase(const size_t index) {
  if (index >= size_) {
    throw std::out_of_range("erase: index out of range");
  }
  for (size_t i = index; i < size_ + 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }
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

  reallocate(capacity);
}

template <typename T> T &Xvector<T>::operator[](const size_t index) noexcept {
  return data_[index];
}

template <typename T> constexpr size_t Xvector<T>::size() const noexcept {
  return size_;
}

template <typename T> constexpr size_t Xvector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T> constexpr size_t Xvector<T>::max_size() const noexcept {
  return static_cast<size_t>(-1) / sizeof(T);
}

template <typename T> void Xvector<T>::shrink_to_fit() {
  if (size_ == capacity_)
    return;

  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    return;
  }

  reallocate(size_);
}

template <typename T> void Xvector<T>::clear() noexcept { size_ = 0; }

template <typename T> T *Xvector<T>::begin() noexcept { return data_; }

template <typename T> const T *Xvector<T>::begin() const noexcept {
  return data_;
}

template <typename T> T *Xvector<T>::end() noexcept { return data_ + size_; }

template <typename T> const T *Xvector<T>::end() const noexcept {
  return data_ + size_;
}

template <typename T> const T *Xvector<T>::cbegin() const noexcept {
  return data_;
}

template <typename T> const T *Xvector<T>::cend() const noexcept {
  return data_ + size_;
}

template <typename T> T *Xvector<T>::data() noexcept { return data_; }
template <typename T> const T *Xvector<T>::data() const noexcept {
  return data_;
}

template <typename T> T &Xvector<T>::at(const size_t index) {
  if (index >= size_)
    throw std::out_of_range("out of range");
  return data_[index];
}

template <typename T> const T &Xvector<T>::at(const size_t index) const {
  if (index >= size_)
    throw std::out_of_range("out of range");
  return data_[index];
}

template <typename T>
bool Xvector<T>::operator==(const Xvector<T> &other) const noexcept {
  if (size_ != other.size_)
    return false;
  //  if(capacity_ != other.capacity_) return false; // capacity is irrelevant

  for (size_t i = 0; i < size_; ++i) {
    if (data_[i] != other.data_[i])
      return false;
  }
  return true;
}

template <typename T>
bool Xvector<T>::operator!=(const Xvector<T> &other) const noexcept {
  return !(*this == other);
}

template <typename T>
const T &Xvector<T>::operator[](const size_t index) const noexcept {
  return data_[index];
}

template <typename T> T &Xvector<T>::front() noexcept { return *this->begin(); }

template <typename T> T &Xvector<T>::back() noexcept {
  return *(this->end() - 1);
}

template <typename T> constexpr T &Xvector<T>::front() const noexcept {
  return *this->begin();
}

template <typename T> constexpr T &Xvector<T>::back() const noexcept {
  return *(this->end() - 1);
}

template <typename T> constexpr bool Xvector<T>::empty() const noexcept {
  return size_ == 0;
}

template <typename T> void Xvector<T>::swap(Xvector<T> &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void Xvector<T>::resize(const size_t size, const T &value) {
  if (size == size_)
    return;

  if (size < size_) {
    size_ = size;
    return;
  }

  if (size > capacity_) {
    size_t newCap = (capacity_ == 0) ? 1 : capacity_;
    while (newCap < size) {
      newCap *= 2;
    }
    reallocate(newCap);
  }

  for (size_t i = size_; i < size; ++i) {
    data_[i] = value;
  }

  size_ = size;

  return;
}
