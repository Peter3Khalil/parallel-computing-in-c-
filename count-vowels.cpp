#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

string vowels = "aeiou";
string vowelsUpperCase = "AEIOU";

int getVowelIndex(char letter)
{
    for (int i = 0; i < vowels.length(); i++)
    {
        if (vowels[i] == letter || vowelsUpperCase[i] == letter)
            return i;
    }

    return -1;
}

void main()
{

    string sentence = "I am peter";
    string s = "";
    vector<string> words;
    for (int i = 0; i < sentence.size(); i++)
    {
        bool isLastChar = i == sentence.size() - 1;
        if (isalpha(sentence[i]) && !isLastChar)
            s += sentence[i];
        else if (isalpha(sentence[i]) && isLastChar)
        {
            s += sentence[i];
            words.push_back(s);
        }
        else if (!s.empty())
        {
            words.push_back(s);
            s = "";
        }
    }
    int vowelOccurrences[5] = {0};

    char **matrix = new char *[words.size()];
#pragma omp parallel
    {
#pragma omp for collapse(2)
        for (int i = 0; i < words.size(); i++)
        {
            string currWord = words.at(i);
            matrix[i] = new char[currWord.size()];
            for (int j = 0; j < currWord.size(); j++)
                matrix[i][j] = currWord.at(j);
        }
    }

#pragma omp parallel
    {
#pragma omp for collapse(2)
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words.at(i).size(); j++)
                if (getVowelIndex(matrix[i][j]) != -1)
                    vowelOccurrences[getVowelIndex(matrix[i][j])]++;
        }
    }

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = 0; j < words.at(i).size(); j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }

    cout << "\n\n\n";
    for (int i = 0; i < 5; i++)
        cout << vowelOccurrences[i] << " ";
    cout << "\n";

    system("pause");
}