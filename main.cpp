#include <iostream>
#include "lib/big_integer.h"


int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    auto sum = number1 + number2;
    std::cout << number1 << " + " << number2 << " = " << sum << '\n'; // 193099

    auto mult = number1 * number2;
    std::cout << number1 << " * " << number2 << " = " << mult << '\n'; // 8996887300

    return 0;
}

