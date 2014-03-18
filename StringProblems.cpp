#include <string>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //
    // LeetCode OJ - Reverse words of string
    //
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

    void reverseWordsTestHelper(string str)
    {
        cout << "Input : \"" << str << '"' << endl;
        reverseWords(str);
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

    //
    // LeetCode OJ - Valid Palindrome
    //
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

    //
    // LeetCode OJ - String multiplication
    //
    vector<int> stringToVector(string s)
    {
        vector<int> v;
        size_t size = s.size();
        v.reserve(size);
        for (size_t i = 0; i < size; ++i)
            v.push_back(s[size - i - 1] - '0');

        return v;
    }

    string multiply(string num1, string num2) {
        vector<int> a = stringToVector(num1);
        vector<int> b = stringToVector(num2);
        size_t size_a = a.size();
        size_t size_b = b.size();
        size_t size_m = size_a + size_b;
        vector<int> m(size_m, 0);
        int v;

        // Multiply
        for (size_t j = 0; j < size_b; ++j)
        {
            for (size_t i = 0; i < size_a; ++i)
            {
                m[i + j] += a[i] * b[j];
            }
        }

        // Process carry
        for (size_t i = 0; i < size_m; ++i)
        {
            v = m[i] / 10;
            m[i] %= 10;
            if (v > 0) m[i + 1] += v;
        }

        // Check prefix zeros
        while (size_m > 1 && m[size_m - 1] == 0)
            --size_m;

        // Output string
        string s;
        for (size_t i = 0; i < size_m; ++i)
            s.push_back(m[size_m - i - 1] + '0');

        return s;
    }

    void multiplyTestHelper(string a, string b)
    {
        cout << '"' << a << "\" x \"" << b << "\" = \"" << multiply(a, b) << '"' << endl;
    }

    void multiplyTest()
    {
        cout << "==Test multiply()==" << endl;
        multiplyTestHelper("0", "0");
        multiplyTestHelper("999", "0");
        multiplyTestHelper("999", "999");
        multiplyTestHelper("1", "999");
        multiplyTestHelper("100", "100");
        multiplyTestHelper("999", "100");
        multiplyTestHelper("9999999999999999999", "999999999999999999999999999999");
        multiplyTestHelper("12345678901234567890123456789012345678901234567890", "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
        multiplyTestHelper("1234567890", "1234567890");
        multiplyTestHelper("000", "0000000");
        multiplyTestHelper("00099", "000001");
        cout << endl;
    }
};

int main()
{
    Solution s;

    s.reverseWordsTest();
    s.palindromeTest();
    s.multiplyTest();

    return 0;
}
