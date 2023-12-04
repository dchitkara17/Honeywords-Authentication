#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "password_guess.h"
#include "honeywords_generation.h"
std::ofstream outputFile;
std::ofstream chaffing_file;
std::ofstream random_file;
std::vector<std::string> list;
bool expected_char(char c)
{
    if (c > 32 && c < 127)
        return true;
    return false;
}

bool check_string(std::string &s)
{
    if (s == "")
        return false;
    for (char c : s)
    {
        if (!expected_char(c))
            return false;
    }
    return true;
}

bool sort_help(std::string &s1, std::string &s2)
{
    if (s1.length() != s2.length())
        return s1.length() > s2.length();
    return s1 > s2;
}

std::string remove(std::string &s)
{
    std::string ans = "";
    for (char c : s)
    {
        if (c != '.')
            ans.push_back(c);
    }
    return ans;
}

std::pair<std::string, std::string> split_string(std::string &s)
{
    int pos = -1;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        if (s[i] == ':')
        {
            if (pos == -1)
                pos = i;
            else
                return {"", ""};
        }
    }
    if (pos != -1)
        return {s.substr(0, pos), s.substr(pos + 1, len - 1 - pos)};
    else
    {
        return {"", ""};
    }
}

std::vector<std::string> clean_data(std::vector<std::string> &data)
{
    std::vector<std::string> res;
    int len = data.size();
    for (int i = 0; i < len; i++)
    {
        if (i && data[i] == data[i - 1])
            continue;
        res.push_back(data[i]);
    }
    return res;
}

std::pair<std::string, std::string> get_data(std::vector<std::string> &data)
{
    std::set<std::string> guesses = guess(data[0]);
    int len = data.size();
    for (int i = 1; i < len; i++)
    {
        if (guesses.find(data[i]) != guesses.end())
        {
            return {data[0], data[i]};
        }
    }
    return {data[0], data[1]};
}

void add_data(std::pair<std::string, std::string> &data)
{
    outputFile << data.first << ":" << data.second << "\n";
}

void add_chaffing_tweaking(std::pair<std::string, std::string> &data)
{
    std::vector<std::string> ans = chaffing_tweaking(data.second);
    chaffing_file << data.first << ":" << data.second;
    for (auto &s : ans)
    {
        chaffing_file << ":" << s;
    }
    chaffing_file << "\n";
}

void add_random_password(std::pair<std::string, std::string> &data)
{
    std::vector<std::string> ans = random_password(list);
    random_file << data.first << ":" << data.second;
    for (auto &s : ans)
    {
        random_file << ":" << s;
    }
    random_file << "\n";
}

void read_data(std::filesystem::path path)
{
    // Create an input file stream.
    std::ifstream inputFile(path);

    // Check if the file was successfully opened.
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::vector<std::string> password;
    // Read and print the contents of the file.
    std::string prev_email = "";
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (!line.empty() && line[line.length() - 1] == 13)
            line.pop_back();

        std::pair<std::string, std::string> p = split_string(line);

        if (p.first == "")
            continue;
        p.first = remove(p.first);
        if (!check_string(p.second))
        {
            continue;
        }
        if (p.first == prev_email)
        {
            int len = password.size();
            if (len > 0 && password[len - 1] == p.second)
                continue;
            password.push_back(p.second);
        }
        else
        {
            sort(password.begin(), password.end(), sort_help);
            password = clean_data(password);
            if (password.size() > 1)
            {
                std::pair<std::string, std::string> p = get_data(password);
                add_data(p);
                add_chaffing_tweaking(p);
                add_random_password(p);
            }
            password.clear();
            prev_email = p.first;
            password.push_back(p.second);
        }
    }

    // Close the file stream.
    inputFile.close();
}

void dfs(std::filesystem::path currentDirectory)
{
    static int count = 0;
    if (count > 60)
        return;
    for (const auto &entry : std::filesystem::directory_iterator(currentDirectory))
    {
        if (std::filesystem::is_regular_file(entry))
        {
            read_data(entry.path());
            std::cout << "File: " << entry.path() << " Done: " << count << std::endl;
            count++;
        }
        else
            dfs(entry.path());
    }
}

void init_list()
{
    std::ifstream inputFile("list_1000.txt");
    // Check if the file was successfully opened.
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string line;
    int max_val = 1000;
    while (std::getline(inputFile, line) && max_val--)
    {
        list.push_back(line);
    }
    inputFile.close();
}

int main()
{
    init_list();
    std::cout << "Output file Name: ";
    std::string output_file;
    std::cin >> output_file;

    outputFile.open(output_file + ".txt");
    std::string honeyword_file = output_file + "_chaffing_tweaking";
    chaffing_file.open(honeyword_file + ".txt");
    random_file.open(output_file + "_random_honeyword.txt");
    std::cout << "Path to input file: ";
    std::string input_file;
    std::cin >> input_file;
    std::filesystem::path currentDirectory = input_file;
    dfs(currentDirectory);
    outputFile.close();
    return 0;
}
