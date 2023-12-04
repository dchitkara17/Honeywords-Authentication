#include "guess.h"
#include <fstream>

int total_guesses = 0;
const int val = 4;
std::map<int, int> mp;
std::vector<int> weights;
const int max_guesses = 5;
int total_maximum_guesses = 1e5;

void set_weights()
{
    const int N = 50;
    weights.resize(N);

    std::ifstream inputFile("weights.txt");
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }
    int num1, num2;
    while (inputFile >> num1 >> num2)
    {
        weights[num1] = num2;
    }
}

std::vector<std::string> get_passwords(std::string line)
{
    std::vector<std::string> result;
    std::string password;
    for (char c : line)
    {
        if (c == ':' && password != "")
        {
            result.push_back(password);
            password = "";
        }
        else if (c != ':')
            password.push_back(c);
    }
    if (password != "")
        result.push_back(password);
    return result;
}

bool match(std::vector<std::pair<std::string, int>> &guesses, std::vector<std::string> &passwords)
{

    // for (std::string password : passwords)
    // {
    //     // if (guesses.find(password) != guesses.end())
    //     //     return true;

    // }
    int size = guesses.size();
    int psize = passwords.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 1; j < psize; j++)
        {
            if (guesses[i].first == passwords[j])
            {
                mp[guesses[i].second]++;
                total_guesses += i + 1;
                return true;
            }
        }
        if (i == max_guesses - 1)
            break;
    }
    total_guesses += std::min(size, max_guesses);
    return false;
}

bool sort_help(std::pair<std::string, int> &p1, std::pair<std::string, int> &p2)
{
    return weights[p1.second] > weights[p2.second];
}

bool check_transformations(std::vector<std::string> &passwords)
{
    // for (std::string password : passwords)
    // {
    std::vector<std::pair<std::string, int>> guesses = guess(passwords[0]);
    sort(guesses.begin(), guesses.end(), sort_help);
    // }
    // return false;
    return match(guesses, passwords);
}

void accuracy(std::string &input_path)
{
    set_weights();
    std::ifstream inputFile(input_path);
    // Check if the file was successfully opened.
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the file." << std::endl;
        return;
    }

    std::string line;
    int correct = 0;
    int total = 0;
    while (std::getline(inputFile, line))
    {
        std::vector<std::string> passwords = get_passwords(line);
        if (passwords.size() < 2)
            continue;

        if (check_transformations(passwords))
        {
            correct++;
        }
        total++;
        if (total_guesses > total_maximum_guesses)
            break;
    }

    std::cout << "Passwords Cracked = " << correct << "\n";
    std::cout << "Total Guesses = " << total_guesses << "\n";
    std::cout << "\n";
    // std::cout << "Accuracy = " << (double)(correct * 100) / total << "%\n";
    // std::cout << "Avg guesses = " << (double)total_guesses / (val * total) << "\n";
    // for (std::pair<int, int> p : mp)
    // {
    //     std::cout << p.first << " " << p.second << "\n";
    // }
}

int main()
{
    std::cout << "Enter file name: ";
    std::string file_name;
    std::cin >> file_name;
    accuracy(file_name);
}