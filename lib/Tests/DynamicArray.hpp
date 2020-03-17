//
// Created by gogagum on 26.10.18.
//

#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include <glob.h>
#include <cassert>

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray(size_t size = 0)
        : size_(size),
          buffer_size_(1) {
      while (buffer_size_ < size) {
        buffer_size_ *= 2;
      }
      buffer_ = new T[buffer_size_];
    }

    DynamicArray(size_t size, T* array)
        : DynamicArray(size) {
      for (int i = 0; i < size; ++i) {
        buffer_[i] = array[i];
      }
    }

    DynamicArray(size_t size, const T &element)
        : DynamicArray(size) {
      for (int i = 0; i < size; ++i) {
        buffer_[i] = element;
      }
    }

    template <typename Iterator>
    DynamicArray(const Iterator& it1, const Iterator& it2)
        : DynamicArray() {
      for (auto i = it1; i != it2; ++i) {
        PushBack(*i);
      }
    }

    DynamicArray(const DynamicArray<T> &otherArray)
        : size_(otherArray.size_), buffer_size_(otherArray.buffer_size_) {
      buffer_ = new T[buffer_size_];
      for (int i = 0; i < size_; ++i) {
        buffer_[i] = otherArray.buffer_[i];
      }
    }

    auto operator[](int index) -> T& {
      assert(index >= 0 && index < size_);
      return buffer_[index];
    }

    auto operator[](int index) const -> const T& {
      assert(index >= 0 && index < size_);
      return buffer_[index];
    };

    void PushBack(T new_element) {
      if (size_ == buffer_size_) {
        Reserve(2 * buffer_size_);
      }
      buffer_[size_] = new_element;
      ++size_;
    }

    auto PopBack() -> T {
      assert(!Empty());
      T to_return = buffer_[size_ - 1];
      --size_;
      if (size_ > 0 && size_ * 4 < buffer_size_) {
        Reserve(buffer_size_/2);
      }
      return to_return;
    }

    void Reserve(size_t new_buffer_size) {
      assert(new_buffer_size >= size_);
      buffer_size_ = new_buffer_size;
      auto new_buffer = new T[new_buffer_size];
      for (int i = 0; i < size_; ++i) {
        new_buffer[i] = buffer_[i];
      }
      delete [] buffer_;
      buffer_ = new_buffer;
    }

    void Erase(int index) {
      assert(index >= 0 && index < size_);
      --size_;
      if (size_ * 4 < buffer_size_ && buffer_size_ != 1) {
        buffer_size_ /= 2;
        auto  new_buffer = new T[buffer_size_];
        for (int i = 0; i < index; ++i) {
          new_buffer[i] = buffer_[i];
        }
        for (int i = index; i < size_; ++i) {
          new_buffer[i] = buffer_[i + 1];
        }
        delete [] buffer_;
        buffer_ = new_buffer;
      } else {
        for (int i = index; i < size_; ++i) {
          buffer_[i] = buffer_[i + 1];
        }
      }
    }

    void Clear() {
      delete [] buffer_;
      buffer_size_ = 1;
      buffer_ = new T[buffer_size_];
      size_ = 0;
    }

    [[nodiscard]] auto Empty() const -> bool {
      return size_ == 0;
    }

    [[nodiscard]] auto Size() const -> size_t {
      return size_;
    }

    ~DynamicArray() {
      delete [] buffer_;
    }

private:
    T* buffer_;
    size_t size_{};
    size_t buffer_size_{};
};

template <typename T>
auto operator== (const DynamicArray<T> &d_array_1,
                 const DynamicArray<T> &d_array_2) -> bool {
    if (d_array_1.Size() != d_array_2.Size()) {
      return false;
    } else {
      for (int i = 0; i < d_array_1.Size(); ++i) {
        if (d_array_1[i] != d_array_2[i]) {
          return false;
        }
      }
    }
    return true;
}


#endif  //  DYNAMICARRAY_H
