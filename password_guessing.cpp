#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cctype>
#include <algorithm>

std::vector<std::pair<std::string, int>> character_sequence_replacement(std::string password);
std::vector<std::pair<std::string, int>> deletions(std::string password);
std::vector<std::pair<std::string, int>> insertions(std::string password);
std::vector<std::pair<std::string, int>> capitalizations(std::string password);
std::pair<std::string, int> leet_speak(std::string password);
std::vector<std::string> substring_movement(std::string password); //
std::vector<std::string> subword_movement(std::string password);   //
std::pair<std::string, int> reverse(std::string password);
std::string replace_first(std::string s, std::string const &toReplace, std::string const &replaceWith);
char transform(char c);
void print(std::vector<std::pair<std::string, int>> &s);
void add(std::vector<std::pair<std::string, int>> &guess, std::vector<std::pair<std::string, int>> &guess_password);

int transform_number = 1;

int main()
{
    std::string password;
    std::cout << "Enter Password to guess:\n";
    std::cin >> password;

    std::vector<std::pair<std::string, int>> guess_password;

    std::vector<std::pair<std::string, int>> guess = character_sequence_replacement(password);
    add(guess, guess_password);

    guess = deletions(password);
    add(guess, guess_password);

    guess = insertions(password);
    add(guess, guess_password);

    guess = capitalizations(password);
    add(guess, guess_password);

    guess_password.push_back(reverse(password));
    guess_password.push_back(leet_speak(password));
    print(guess_password);

    return 0;
}

std::string replace_first(std::string s, std::string const &toReplace, std::string const &replaceWith)
{
    size_t pos = s.find(toReplace);
    if (pos == std::string::npos)
        return "";
    s.replace(pos, toReplace.length(), replaceWith);
    return s;
}

std::vector<std::pair<std::string, int>> character_sequence_replacement(std::string password)
{
    std::map<std::string, std::vector<std::string>> replacements;
    replacements["qwer"] = {"1234", "1qaz"};
    replacements["qwe"] = {"qwer", "qaz"};
    replacements["asd"] = {"asdf", "wsx"};
    replacements["wsx"] = {"2wsx", "wer"};
    replacements["asdf"] = {"1234", "zxcv"};
    replacements["5678"] = {"qwer", "1234"};
    replacements["qa"] = {"qwe", "qaz"};

    std::vector<std::pair<std::string, int>> guess;
    for (std::pair<std::string, std::vector<std::string>> p : replacements)
    {
        for (std::string s : p.second)
        {
            std::string guess_password = replace_first(password, p.first, s);
            if (guess_password != "")
                guess.push_back({guess_password, transform_number++});
        }
    }
    return guess;
}

std::vector<std::pair<std::string, int>> deletions(std::string password)
{
    std::string delete_numbers;
    std::string delete_uppercase;
    std::string delete_symbols;
    std::string backward_deletions;
    std::vector<std::pair<std::string, int>> results;
    for (char c : password)
    {
        if (!(c >= '0' && c <= '9'))
        {
            delete_numbers.push_back(c);
        }
        if (!(c >= 'A' && c <= 'Z'))
        {
            delete_uppercase.push_back(c);
        }

        if (isalnum(static_cast<unsigned char>(c)))
        {
            delete_symbols.push_back(c);
        }
        backward_deletions.push_back(c);
        results.push_back({backward_deletions, transform_number++});
    }
    return results;
}

std::vector<std::pair<std::string, int>> insertions(std::string password)
{
    std::vector<std::string> insertions_string = {
        "08", "01", "07", "23", "123", "087", "007", "1", "0"};

    std::vector<std::pair<std::string, int>> guess;

    for (std::string s : insertions_string)
    {
        guess.push_back({password + s, transform_number++});
    }
    return guess;
}

std::vector<std::pair<std::string, int>> capitalizations(std::string password)
{
    int len = password.length();
    std::vector<std::pair<std::string, int>> guess;
    for (int i = 0; i < len; i++)
    {
        if (password[i] >= 'a' && password[i] <= 'z')
        {
            password[i] -= 32;
            guess.push_back({password, transform_number++});
        }
    }

    return guess;
}

std::pair<std::string, int> reverse(std::string password)
{
    reverse(password.begin(), password.end());
    return {password, transform_number++};
}

std::pair<std::string, int> leet_speak(std::string password)
{
    int len = password.length();
    for (int i = 0; i < len; i++)
    {
        password[i] = transform(password[i]);
    }
    return {password, transform_number++};
}

void add(std::vector<std::pair<std::string, int>> &guess, std::vector<std::pair<std::string, int>> &guess_password)
{
    for (std::pair<std::string, int> s : guess)
    {
        guess_password.push_back(s);
    }
}
char transform(char c)
{
    switch (c)
    {
    case 'o':
        return '0';
    case 'a':
        return '@';
    case 's':
        return '$';
    case 'i':
        return '1';
    case 'e':
        return '3';
    case 't':
        return '7';
    default:
        return c;
    }
    return c;
}

void print(std::vector<std::pair<std::string, int>> &s)
{
    std::cout << "Possible Passwords are:\n";
    for (std::pair<std::string, int> password : s)
    {
        std::cout << password.first << " " << password.second << "\n";
    }
}