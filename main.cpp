#include <iostream>
#include "big_integer.h"


int main()
{
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result.to_str() << '\n'; // 193099

    return 0;
}