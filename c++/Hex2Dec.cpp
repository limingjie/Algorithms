#include <algorithm> // transform
#include <iostream>
#include <string>
#include <vector>

// hex2dec - Convert Hexadecimal to Decimal
// The function convert from string to string, it is not limited by integer size.
// e.g. 0x12A = 1 x 16^2 + 2 x 16^1 + 10 x 16^0
//            = [(1 x 16) + 2] x 16 + 10
//            = 298
// Algorithm explained
//     hex   1   2   A
//           V   V   V
//  vector   1   2  10    - Convert to vector of integers in reverse order [10, 2, 1]
// Loop #1       |   |    - 1 x 16
//     x16  16   V   |
//   split   1   6   V
//     add   1   8  10
//   carry   1   8  10    - process carry on the first 2 digits
// Loop #2           |    - [(1 x 16) + 2] x 16
//     x16  16 128   |
//   split   1   6   V
//              12   8
//     add   1  18  18
//   carry   2   9   8    - process carry on the first 3 digits
// End Loop
std::string hex2dec(const std::string hex)
{
    // Validate input in a lazy way, return 0 if invalid.
    if (hex.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
    {
        return "0";
    }

    // Omit leading zeros, return 0 if all digits are zeros.
    size_t first = hex.find_first_not_of("0");
    if (first == std::string::npos)
    {
        return "0";
    }

    // Reverse the hexadecimal for easy extending and convert it to a vector of integers
    std::vector<int> h(hex.size() - first);
    std::transform(hex.rbegin(), hex.rend() - first, h.begin(), [](char c) {
        if (c >= 'a' && c <= 'f')
            return c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            return c - 'A' + 10;
        return c - '0';
    });

    // Convert to decimal
    for (int i = h.size() - 1; i > 0; i--)
    {
        // x16
        for (int j = i; j < h.size(); j++)
        {
            int t = h[j] * 16;
            h[j - 1] += t % 10;
            h[j] = t / 10;
        }

        // Process carry
        for (int j = i - 1; j < h.size(); j++)
        {
            int c = h[j] / 10;
            h[j] %= 10;
            if (j + 1 == h.size() && c != 0)
                h.push_back(c);
            else
                h[j + 1] += c;
        }
    }

    // Convert to string
    std::string d(h.size(), '0');
    std::transform(h.rbegin(), h.rend(), d.begin(), [](int i) { return i + '0'; });

    return d;
}

int main(void)
{
    std::vector<std::string> tc{
        "0",
        "000",
        "001",
        "010",
        "0abc",
        "00abc",
        "000abc",
        "ABCabc",
        "1234567890ABCDEF",
        "FFFFffffFFFFffff",                 // 64 bits
        "FFFFffffFFFFffffFFFFffffFFFFffff", // 128 bits
        "1234567890abcdef1234567890abcdef1234567890abcdef",
        "DeadFeed",
        "Invalid"};

    for (const auto &t : tc)
    {
        std::cout << "0x" << t << " = " << hex2dec(t) << std::endl;
    }

    return 0;
}
