#include "big_integer.h"


static const std::string err_symvol = "Число содержит недопустимый символ: ";
static const std::string err_null = "Число не определено.";

class MyException : public std::exception
{
    private:
    const std::string msg;

    public:
        MyException(const std::string msg_) : msg(msg_){}
        virtual ~MyException(){}

        const char* what() const noexcept override
        {
            return msg.c_str();
        }
};

bool big_integer::valid_digit(char symvol)
{
    if(symvol < '0' || symvol > '9')
    {
        const std::string err = err_symvol + std::to_string(symvol);
        throw MyException(err);
    }

    return true;
}

void big_integer::dig_init(const char* str)
{
    size = 0;
    unsigned int null_count = 0;

    while(str[size] != 0)
    {
        if (str[size] == '0') ++null_count; 
        size += static_cast<int>(valid_digit(str[size]));
    }

    size -= null_count; 

    if (size > 0)
    {
        //++size;
        // Need realese void clear_null()
        dig = new char[size];
        for (unsigned int i = 0, j = null_count - 1;  i < size; ++i, ++j)
        {
            dig[i] = str[j];
        }
    }
    else
    {
        throw MyException(err_null);
    }
}

big_integer::big_integer(const char* str)
{
    dig_init(str);
}

big_integer::big_integer(const std::string& str)
{
    size = str.length();
    const char* chars = str.c_str();

    dig_init(chars);
}

big_integer::big_integer(const big_integer& other)
{
    if (size == other.size)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            dig[i] = other.dig[i];
        }
    }
    else
    {
        size = other.size;
        dig = new char[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            dig[i] = other.dig[i];
        }
    }
}

big_integer::big_integer(big_integer&& other) : 
    size(other.size),
    dig(other.dig)
{}

big_integer& big_integer::operator=(const big_integer& other)
{
    return *this = big_integer(other);
}

big_integer& big_integer::operator=(big_integer&& other)
{
    return *this = big_integer(other);
}

const char* big_integer::sum()
{}

big_integer big_integer::operator+(const big_integer& other)
{
    unsigned int new_size = 0; 
    char* new_arr = nullptr;

    unsigned int low_size = 0;
    char* low_arr = nullptr;

    unsigned int null_count = 0;

    if (size >= other.size)
    {
        new_size = size + 3;
        new_arr = new char[new_size]{};

        low_size = other.size;
        low_arr = other.dig;
    }
    else
    {
        new_size = other.size + 3;
        new_arr = other.dig;

        low_size = size;
        low_arr = dig;
    }

    chars = new char[new_size]{};

    for (int i = new_size - 2, j = low_size - 1;
        j >= 0;
        --i, --j)
    {
        int result = static_cast<int>((new_arr[i] - '0') + (low_arr[j] - '0'));
        if (result >= 10)
        {
            result -= 10;
            int up_level = i - 1;
            if (chars[up_level] == 0)
            {
                chars[up_level] = '0' + 1;
            }
            else
            {
                ++chars[up_level];
            }
        }

        chars[i] = '0' + result;
    }
}

big_integer::~big_integer()
{
    delete[] dig;
    dig = nullptr;
}