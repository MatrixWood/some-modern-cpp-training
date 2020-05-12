#include <algorithm>
#include <cassert>

class shared_ptr_count {
public:
  shared_ptr_count() : pn(nullptr) {}
  shared_ptr_count(const shared_ptr_count& count) : pn(count.pn) {}

  void swap(shared_ptr_count& lhs) throw() {
    std::swap(pn, lhs.pn);
  }

  long use_count() const throw() {
    long count = 0;
    if (pn != nullptr) {
      count = *pn;
    }
    return count;
  }

  template <class U>
  void acquire(U* p) {
    if (p != nullptr) {
      if (pn == nullptr) {
        try {
          pn = new long(1);
        }
        catch (std::bad_alloc&) {
          delete p;
          throw;
        }
      }
      else {
        ++(*pn);
      }
    }
  }

  template <class U>
  void release(U* p) throw() {
    if (pn != nullptr) {
      --(*pn);
      if (*pn == 0) {
        delete p;
        delete pn;
      }
      pn = nullptr;
    }
  }

public:
  long* pn; // reference counter
};

template <class T>
class shared_ptr {
public:
  using element_type = T;
  
  shared_ptr() : px(nullptr), pn() {}

  explicit shared_ptr(T* p) : pn() {
    acquire(p);
  }

  template <class U>
  shared_ptr(const shared_ptr<U>& ptr, T* p) : pn(ptr.pn) {
    acquire(p);
  }

  template <class U>
  shared_ptr(const shared_ptr<U>& ptr) : pn(ptr.pn) {
    assert((ptr.px == nullptr) || (ptr.pn.use_count() != 0));
    acquire(static_cast<typename shared_ptr<T>::element_type*>(ptr.px));
  }

  shared_ptr(const shared_ptr& ptr) : pn(ptr.pn) {
    assert((ptr.px == nullptr) || (ptr.pn.use_count() != 0));
    acquire(ptr.px);
  }

  shared_ptr& operator = (shared_ptr ptr) {
    swap(ptr);
    return *this;
  }

  ~shared_ptr() {
    release();
  }

  void reset() {
    release();
  }

  void reset(T* p) {
    assert((p == nullptr) || (px != p));
    release();
    acquire(p);
  }

  void swap(shared_ptr& lhs) {
    std::swap(px, lhs.px);
    pn.swap(lhs.pn);
  }

  operator bool () const {
    return (pn.use_count() > 0);
  }

  bool unique() const {
    return (pn.use_count() == 1);
  }

  long use_count() const {
    return pn.use_count();
  }

  T& operator * () const {
    assert(px != nullptr);
    return *px;
  }

  T* operator -> () const {
    assert(px != nullptr);
    return px;
  }

  T* get() const {
    return px;
  }

private:
  void acquire(T* p) {
    pn.acquire(p);
    px = p;
  }

  void release() {
    pn.release(px);
    px = nullptr;
  }

private:
  template <class U>
  friend class shared_ptr;

private:
  T* px;  // native pointer
  shared_ptr_count pn;  // reference counter
};

template<class T, class U> bool operator == (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() == r.get());
}
template<class T, class U> bool operator != (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() != r.get());
}
template<class T, class U> bool operator <= (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() <= r.get());
}
template<class T, class U> bool operator < (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() < r.get());
}
template<class T, class U> bool operator >= (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() >= r.get());
}
template<class T, class U> bool operator > (const shared_ptr<T>& l, const shared_ptr<U>& r) {
  return (l.get() > r.get());
}

template<class T, class U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U>& ptr) {
  return shared_ptr<T>(ptr, static_cast<typename shared_ptr<T>::element_type*>(ptr.get()));
}

template<class T, class U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U>& ptr) {
  T* p = dynamic_cast<typename shared_ptr<T>::element_type*>(ptr.get());
  if (NULL != p) {
    return shared_ptr<T>(ptr, p);
  }
  else {
    return shared_ptr<T>();
  }
}