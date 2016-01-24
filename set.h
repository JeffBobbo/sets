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

  Set& push_front(const T t);
  Set& push_back(const T t);

  Set<T> unionize(const Set<T>& other) const;
  Set<T> intersect(const Set<T>& other) const;
  Set<T> difference(const Set<T>& other) const;

  Set& sort() { set.sort(); return *this; };

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Set<U>& s);
  template <typename U>
  friend std::istream& operator>>(std::istream& is, Set<U>& s);

private:
  std::list<T> set;
};

template <typename T>
bool Set<T>::contains(const T t) const
{
  for (typename std::list<T>::const_iterator it = set.begin(); it != set.end(); ++it)
  {
    if (*it == t)
      return true;
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
  s.set.clear();
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
    s.push_front(u);
    start = stop + 1;
    stop = set.find(',', start);
  }
  while (start != 0);

  return is;
}

#endif
