#ifndef SET_H_INCLUDE
#define SET_H_INCLUDE

#include <list>
#include <iostream>

template <typename T>
class Set
{
public:
  Set() {};
  ~Set() { set.empty(); };

  bool contains(const T t) const;
  bool empty() const { return (set.begin() == set.end()); };
  int size() const { return set.size(); };
  Set& push_front(const T t);
  Set& push_back(const T t);

  Set<T> unionize(const Set<T>& other) const;
  Set<T> intersect(const Set<T>& other) const;
  Set<T> difference(const Set<T>& other) const;

  std::list<Set<T> > power() const;

  Set& sort() { set.sort(); return *this; };

  template <typename U>
  friend bool operator==(const Set<U>& a, const Set<U>& b);
  template <typename U>
  friend Set<U> operator+(const Set<U>& a, const Set<U>& b);
  template <typename U>
  friend Set<U> operator-(const Set<U>& a, const Set<U>& b);
  Set<T>& operator+=(const Set<T>& o);
  Set<T>& operator-=(const Set<T>& o);

  T operator[](const int i) const;

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Set<U>& s);
  template <typename U>
  friend std::istream& operator>>(std::istream& is, Set<U>& s);

private:
/*
  typename std::list<T>::iterator find(const T t)
  {
    typename std::list<T>::iterator it = set.begin();
    while (it != set.end() && *it != t)
      ++it;
    return it;
  }
*/
  std::list<T> set;
};

template <typename T>
bool Set<T>::contains(const T t) const
{
//  typename std::list<T>::iterator it = find(t);
//  return it != set.end();
  typename std::list<T>::const_iterator it = set.begin();
  while (it != set.end())
  {
    if (*it == t)
      return true;
    ++it;
  }
  return false;
}

template <typename T>
Set<T>& Set<T>::push_front(const T t)
{
  if (!contains(t))
    set.push_front(t);
  return *this;
}

template <typename T>
Set<T>& Set<T>::push_back(const T t)
{
//  typename std::list<T>::iterator it = find(t);
//  if (it == set.end())
//    set.insert(it, t);
  if (!contains(t))
    set.push_back(t);
  return *this;
}

template <typename T>
Set<T> Set<T>::unionize(const Set<T>& other) const
{
  Set<T> r;

  for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); ++it)
  {
    if (r.contains(*it) == false)
      r.push_front(*it);
  }
  for (typename std::list<T>::const_iterator it = other.set.begin(); it != other.set.end(); ++it)
  {
    if (r.contains(*it) == false)
      r.push_front(*it);
  }
  return r;
}

template <typename T>
Set<T> Set<T>::intersect(const Set<T>& other) const
{
  Set<T> r;

  for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); ++it)
  {
    if (other.contains(*it))
      r.push_front(*it);
  }
  return r;
}

template <typename T>
Set<T> Set<T>::difference(const Set<T>& other) const
{
  Set<T> r;

  for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); ++it)
  {
    if (!other.contains(*it))
      r.push_front(*it);
  }
  for (typename std::list<T>::const_iterator it = other.set.begin(); it != other.set.end(); ++it)
  {
    if (!contains(*it))
      r.push_front(*it);
  }
  return r;
}

template<typename T>
std::list<Set<T> > Set<T>::power() const
{
  std::list<Set<T> > r;

  const unsigned long long p = 1 << set.size();

  for (unsigned long long i = 0; i < p; ++i)
  {
    Set<T> s;
    for (unsigned long long j = 0; j < set.size(); ++j)
    {
      if ((1 << j) & i)
        s.push_front((*this)[j]);
    }
    r.push_front(s);
  }
  return r;
}

template <typename U>
bool operator==(const Set<U>& a, const Set<U>& b)
{
  return (a-b).empty() == (b-a).empty();
}

template <typename U>
Set<U> operator+(const Set<U>& a, const Set<U>& b)
{
  return a.unionize(b);
}
template <typename U>
Set<U> operator-(const Set<U>& a, const Set<U>& b)
{
  Set<U> r;
  typename std::list<U>::const_iterator it = a.set.begin();
  for (; it != a.set.end(); ++it)
  {
    if (!b.contains(*it))
      r.push_front(*it);
  }
  return r;
}
template <typename T>
Set<T>& Set<T>::operator+=(const Set<T>& o)
{
  typename std::list<T>::const_iterator it = o.set.begin();
  for (; it != o.set.end(); ++it)
    push_back(*it);
  return *this;
}
template <typename T>
Set<T>& Set<T>::operator-=(const Set<T>& o)
{
  typename std::list<T>::iterator it = set.begin();
  while (it != set.end())
  {
    if (o.contains(*it))
    {
      set.erase(it);
      it = set.begin();
      break;
    }
    ++it;
  }
  return *this;
}

template <typename T>
T Set<T>::operator[](const int i) const
{
  typename std::list<T>::const_iterator it = set.begin();
  std::advance(it, i);
  return *it;
}

template <typename U>
std::ostream& operator<<(std::ostream& os, const Set<U>& s)
{
  typename std::list<U>::const_iterator it = s.set.begin();
  os << "{";
  const typename std::list<U>::const_iterator end = s.set.end();
  if (it != end)
  {
    os << *it++;
    for (; it != end; ++it)
      os << ", " << *it;
  }
  os << "}";
  return os;
}



template <typename U>
std::istream& operator>>(std::istream& is, Set<U>& s)
{
//  s.set.clear();
  std::string set;
  std::string tmp;
  is >> set;

  while (is >> tmp && tmp.find('}') == std::string::npos)
    set += " " + tmp;
  set += " " + tmp;

  set = set.substr(1, set.size() - 2);

  std::string::size_type start = 0;
  std::string::size_type stop = set.find(',');

  do
  {
    std::stringstream ss(set.substr(start, stop-start));
    U u;
    ss >> u;
    s.push_back(u);
    start = stop + 1;
    stop = set.find(',', start);
  }
  while (start != 0);

  return is;
}

#endif
