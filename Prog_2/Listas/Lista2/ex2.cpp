#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

bool areAnagrams(const string &str1, const string &str2)
{
  if (str1.length() != str2.length())
  {
    return false;
  }

  unordered_map<char, int> charCount;

  for (char c : str1)
  {
    charCount[c]++;
  }

  for (char c : str2)
  {
    if (charCount.find(c) == charCount.end() || charCount[c] == 0)
    {
      return false;
    }
    else
    {
      charCount[c]--;
    }
  }

  for (const auto &pair : charCount)
  {
    if (pair.second != 0)
    {
      return false;
    }
  }

  return true;
}

int main()
{
  string str1, str2;

  cout << "Digite a primeira string: ";
  cin >> str1;

  cout << "Digite a segunda string: ";
  cin >> str2;

  if (areAnagrams(str1, str2))
  {
    cout << "As strings são anagramas uma da outra." << endl;
  }
  else
  {
    cout << "As strings não são anagramas uma da outra." << endl;
  }

  return 0;
}
