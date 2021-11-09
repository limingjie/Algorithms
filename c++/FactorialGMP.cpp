#include <gmpxx.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage:\n\tfactorial number" << std::endl;
        return 0;
    }

    long l;
    try
    {
        l = std::stol(argv[1]);
    }
    catch (std::invalid_argument const &e)
    {
        std::cout << "Warning: \"" << argv[1] << "\" is not a number." << std::endl;
        return 1;
    }
    catch (std::out_of_range const &e)
    {
        std::cout << "Warning: \"" << argv[1] << "\" exceeds the long integer limit." << std::endl;
        return 1;
    }

    if (l < 1)
    {
        std::cout << "0" << std::endl;
        return 0;
    }

    std::cout << mpz_class::factorial(l) << std::endl;

    return 0;
}
