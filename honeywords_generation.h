#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <map>
std::vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::vector<char> characters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                                'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                                's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
std::vector<char> special_char = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '{', '}', '[', ']', '|', ':', ';', '"', '\'', '<', '>', ',', '.', '?', '/'};
const int k = 19;
char replace(char c)
{
    if (c >= '0' && c <= '9')
    {
        int size = numbers.size();
        int pos = rand() % size;
        return numbers[pos];
    }
    else if (c >= 'a' && c <= 'z')
    {
        int size = characters.size();
        int pos = rand() % size;
        return characters[pos];
    }
    else if (c >= 'A' && c <= 'Z')
    {
        int size = characters.size();
        int pos = rand() % size;
        return characters[pos] - 'a' + 'A';
    }
    else
    {
        int size = special_char.size();
        int pos = rand() % size;
        return special_char[pos];
    }
}

std::vector<std::string> chaffing_tweaking(std::string s)
{
    srand(time(0));
    const int t = 3;
    std::vector<std::string> ans;
    int len = s.length();
    for (int i = 0; i < k; i++)
    {
        std::string res = s;
        for (int i = len - 1; i >= std::max(0, len - t); i--)
        {
            res[i] = replace(res[i]);
        }
        ans.push_back(res);
    }
    return ans;
}

std::vector<std::string> random_password(std::vector<std::string> &list)
{
    srand(time(0));
    std::vector<std::string> ans;
    int len = list.size();
    std::map<int, bool> mp;
    for (int i = 0; i < k; i++)
    {
        int pos = rand() % len;
        while (mp[pos])
        {
            pos = rand() % len;
        }
        mp[pos] = 1;
        ans.push_back(list[pos]);
    }
    return ans;
}
