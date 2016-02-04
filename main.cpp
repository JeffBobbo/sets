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
  if (s.size() != 7)
    return false;
  std::stringstream os;
  os << s;
  return os.str() == "{a, b, c, d, x, y, z}";
}

bool testCombinations()
{
  Set<char> a, b;
  std::stringstream sa("{a, b, c}");
  sa >> a;
  std::stringstream sb("{b, c, d}");
  sb >> b;

  Set<char> aub = a.unionize(b);
  if (aub.size() != 4)
    return false;
  Set<char> anb = a.intersect(b);
  if (anb.size() != 2)
    return false;
  Set<char> adb = a.difference(b);
  if (adb.size() != 2)
    return false;
  return true;
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
  if (testCombinations() == false)
  {
    std::cout << "testCombinations() failed" << std::endl;
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

  Set<std::string> names;
  std::istringstream sNames("{James, Bob, Alice, Samantha}");
  sNames >> names;
  for (int i = 0; i < names.size(); ++i)
    std::cout << names[i] << std::endl;

  std::list<Set<char> > power = s1.power();

  for (std::list<Set<char> >::iterator it = power.begin(); it != power.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;

  return 0;
}
