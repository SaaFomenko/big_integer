#include "big_integer.h"


static const std::string err_symvol = "Число содержит недопустимый символ: ";
static const std::string err_null = "Число не определено.";

bool big_integer::valid_digit(char symvol)
{
    if(symvol < '0' || symvol > '9')
    {
        const std::string err = err_symvol + std::to_string(symvol);
        throw MyException(err);
    }

    return true;
}

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

big_integer::big_integer(const char* str)
{
    size = 0;

    while(str[size] != 0)
    {
        
        size += static_cast<int>(valid_digit(str[size]));
    }

    if (size > 0)
    {
        ++size;
        dig = new char[size];
        for (unsigned int i = 0;  i < size; ++i)
        {
            dig[i] = str[i];
        }
    }
    else
    {
        throw MyException(err_null);
    }
}

big_integer::big_integer(const std::string& str)
{
    size = str.length();
    if (size > 0)
    {
        dig = new char[size];
        const char* chars = str.c_str();
        for (unsigned int i = 0; i < size; ++i)
        {
            if (valid_digit(chars[i]))
            {
                dig[i] = chars[i];
            }
        }
    }
    else
    {
        throw MyException(err_null);
    }
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

big_integer big_integer::operator+(const big_integer& other)
{
    big_integer result = size > other.size ? big_integer(*this) : big_integer(other);

    

}

big_integer::~big_integer()
{
    delete[] dig;
    dig = nullptr;
}