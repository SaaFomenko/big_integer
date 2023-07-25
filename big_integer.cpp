#include "big_integer.h"


static const std::string err_symvol = "Число содержит недопустимый символ: ";
static const std::string err_null = "Число не определено";

bool valid_digit(char symvol)
{
    if(symvol < '0' || symvol > '9')
    {
        const std::string err = err_symvol + std::to_string(symvol) + "\n";
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
    unsigned int size = 0;

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
    unsigned int size = str.length();
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