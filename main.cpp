#include "set.h"

#include <iostream>
#include <sstream>


bool testSize()
{
  Set<char> s;
  if (s.empty() == false)
    return false;

  if (s.size() != 0)
    return false;

  s.push_back('a');
  s.push_front('b');
  return s.size() == 2;
}

bool testStreamOps()
{
  std::stringstream ss("{a, b, c, d} {a, x, y, z}");
  Set<char> s;
  ss >> s;
  if (s.size() != 4)
    return false;
  ss >> s;
  return s.size() == 7;
}

int main()
{
  if (testSize() == false)
  {
    std::cout << "testSize() failed" << std::endl;
    return 1;
  }
  if (testStreamOps() == false)
  {
    std::cout << "testStreamOps() failed" << std::endl;
    return 1;
  }
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

  Set<char> s3 = s1;
  s3 -= s2;
  std::cout << s3 << std::endl;

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
  std::cout << (e += d) << std::endl;

  if ((e + d) == e.unionize(d))
    std::cout << " e and d unionize" << std::endl;

  std::cout << (e -= d).size() << std::endl;

  Set<std::string> names;
  std::istringstream sNames("{James, Bob, Alice, Samantha}");
  sNames >> names;
  for (int i = 0; i < names.size(); ++i)
    std::cout << names[i] << std::endl;

  std::list<Set<char> > power = e.power();

  for (std::list<Set<char> >::iterator it = power.begin(); it != power.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;

  return 0;
}
