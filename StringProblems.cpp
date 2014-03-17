#include <string>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        string dest;

        size_t word_end = 0;
        size_t word_start = s.size();
        bool first = true;

        while (true)
        {
            word_end = s.find_last_not_of(' ', word_start);
            if (word_end != string::npos)
            {

                if (!first)
                    dest.push_back(' ');
                else
                    first = false;

                word_start = s.find_last_of(' ', word_end);
                if (word_start == string::npos)
                {
                    for (size_t i = 0; i <= word_end ; i++)
                    {
                        dest.push_back(s[i]);
                    }

                    break;
                }
                else
                {
                    for (size_t i = word_start + 1; i <= word_end ; i++)
                    {
                        dest.push_back(s[i]);
                    }
                }
            }
            else
            {
                break;
            }
        }

        s = dest;
    }
    
    bool isPalindrome(string s) {
        string temp;
        size_t size = s.size();
        
        // remove chars other than alpha number
        for(size_t i = 0; i < size; ++i)
        {
            if (isalnum(s[i])) temp.push_back(toupper(s[i]));
        }
        
        cout << " ==> " << temp << ' ';
        
        // check palindrome
        size = temp.size();
        
        for(size_t i = 0; i < size / 2; ++i)
        {
            if (temp[i] != temp[size - 1 - i]) return false;
        }
        
        return true;
    }
};

void reverseWordsTestHelper(string str)
{
    Solution s;
    cout << "Input : \"" << str << '"' << endl;
    s.reverseWords(str);
    cout << "Output: \"" << str << '"' << endl;
}

void reverseWordsTest()
{
    cout << "==Test reverseWords()==" << endl;
    reverseWordsTestHelper("Hello World");
    reverseWordsTestHelper("  Hello World");
    reverseWordsTestHelper("Hello World  ");
    reverseWordsTestHelper("Hello   World");
    reverseWordsTestHelper("   Hello    World   Hello    World   Hello    World   Hello    World   Hello    World   Hello    World   ");
    cout << endl;
}

void palindromeTestHelper(string str)
{
    Solution s;
    cout << '"' << str << '"';
    if (s.isPalindrome(str))
        cout << "is Palindrome";
    else
        cout << "is no Palindrome";
    cout << endl;
}

void palindromeTest()
{
    cout << "==Test palindrome()==" << endl;
    palindromeTestHelper("");
    palindromeTestHelper("aA");
    palindromeTestHelper("A man, a plan, a canal: Panama");
    palindromeTestHelper("Hello World!");
    cout << endl;

}

int main()
{
    reverseWordsTest();
    palindromeTest();
    return 0;
}
