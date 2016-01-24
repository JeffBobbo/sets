#include "set.h"

#include <iostream>
#include <sstream>

struct S
{
  char a;
};

std::ostream& operator<<(std::ostream& os, const S* const s)
{
  os << s->a;
  return os;
}
std::ostream& operator<<(std::ostream& os, const S& s)
{
  os << s.a;
  return os;
}

int main()
{
  Set<char> s1;
  s1.push_front('c');
  s1.push_front('b');
  s1.push_front('a');
  Set<char> s2;
  s2.push_front('c');
  s2.push_front('b');
  std::cout << s1.intersect(s2) << std::endl;
  std::cout << s1.unionize(s2) << std::endl;
  std::cout << (s1 == s2) << std::endl;
  std::cout << (s2 == s1) << std::endl;
  S sx = {'x'};
  S sy = {'y'};
  S sz = {'z'};
  Set<S*> sp1;
  sp1.push_front(&sx);
  sp1.push_front(&sz);
  Set<S*> sp2;
  sp2.push_front(&sy);
  sp2.push_front(&sz);
  std::cout << sp1.unionize(sp2) << std::endl;
  std::cout << sp1.difference(sp2) << std::endl;

  Set<char> e;
  std::cout << e << std::endl;

  Set<char> d;
  std::string str = "{a, b, c, d} {c, d, f, a}";
  std::istringstream is(str);
  is >> e;
  is >> d;
  std::cout << e << std::endl;
  std::cout << d << std::endl;
  std::cout << e.difference(d).sort() << std::endl;
  std::cout << (e + d) << std::endl;

  if ((e + d) == e.unionize(d))
    std::cout << " e and d unionize" << std::endl;

  Set<std::string> names;
  std::istringstream sNames("{James, Bob, Alice, Samantha}");
  sNames >> names;
  std::cout << names << std::endl;

  std::list<Set<char> > power = e.power();

  for (std::list<Set<char> >::iterator it = power.begin(); it != power.end(); ++it)
  {
    std::cout << *it << std::endl;
  }

  return 0;
}
