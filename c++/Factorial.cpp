#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::string multiply(std::string a, std::string b)
{
    size_t size_a = a.size();
    size_t size_b = b.size();
    size_t size_p = size_a + size_b;

    std::vector<int> va(size_a), vb(size_b), vp(size_p, 0);
    std::transform(a.rbegin(), a.rend(), va.begin(), [](char c) { return c - '0'; });
    std::transform(b.rbegin(), b.rend(), vb.begin(), [](char c) { return c - '0'; });

    // Multiply
    for (size_t j = 0; j < size_b; j++)
    {
        for (size_t i = 0; i < size_a; i++)
        {
            vp[i + j] += va[i] * vb[j];
        }
    }

    // Process carry
    size_p--;
    for (size_t i = 0; i < size_p; i++)
    {
        vp[i + 1] += vp[i] / 10;
        vp[i] %= 10;
    }

    // Remove unwanted prefix zeros
    while (vp.size() > 1 && *vp.crbegin() == 0)
    {
        vp.pop_back();
    }

    // Convert to string
    std::string p(vp.size(), '0');
    std::transform(vp.rbegin(), vp.rend(), p.begin(), [](int i) { return i + '0'; });

    return p;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage:\n\tfactorial number" << std::endl;
        return 0;
    }

    long long ll;
    try
    {
        ll = std::stoll(argv[1]);
    }
    catch (std::invalid_argument const &e)
    {
        std::cout << "Warning: \"" << argv[1] << "\" is not a number." << std::endl;
        return 1;
    }
    catch (std::out_of_range const &e)
    {
        std::cout << "Warning: \"" << argv[1] << "\" exceeds the long long integer limit." << std::endl;
        return 1;
    }

    if (ll < 1)
    {
        std::cout << "0" << std::endl;
        return 0;
    }

    std::string p("1");
    for (long long i = 2; i <= ll; i++)
        p = multiply(p, std::to_string(i));

    std::cout << p << std::endl;

    return 0;
}
