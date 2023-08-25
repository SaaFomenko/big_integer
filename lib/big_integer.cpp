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
    int i = 0;
    int null_count = 0;

    while(str[i] != 0)
    {
        i += static_cast<int>(valid_digit(str[i]));
    }

    int str_size = i + 1;

    i = 0;
    while(str[i] == '0' && i < str_size - 1)
    { 
        ++null_count;
        ++i;
    }

    _size = str_size - null_count; 

    if (_size <= 1)
    {
        _str = new char[2]{'0', 0};
    }
    else if (_size > 1)
    {
        _str = new char[_size];
        _str[_size - 1] = 0;

        for (int i = _size - 2, j = str_size - 2; i >= 0; --i, --j)
        {
            _str[i] = str[j];
        }
    }
    else
    {
        throw MyException(err_null);
    }
}

big_integer::big_integer() : 
    _size{2},
    _str{new char[2]{'0', 0}}
{}

big_integer::big_integer(const char* str)
{
    dig_init(str);
}

big_integer::big_integer(const std::string& str)
{
    const char* chars = str.c_str();

    dig_init(chars);
}

big_integer::big_integer(const big_integer& other) 
: big_integer(other._str)
{}

big_integer::big_integer(big_integer&& other) noexcept 
:   _str(nullptr),
   _size(0)
{
    std::swap(_str, other._str);
    std::swap(_str, other._str);
}

big_integer& big_integer::operator=(const big_integer& other)
{
    return *this = big_integer(other);
}

big_integer& big_integer::operator=(big_integer&& other) noexcept 
{
    _size = other._size;
    std::swap(_str, other._str);

    return *this;
}

big_integer& big_integer::operator=(const char* str)
{
    delete[] _str; 

    dig_init(str);

    return *this;
}

big_integer& big_integer::operator=(const std::string& str)
{
    delete[] _str;
    const char* chars = str.c_str();

    dig_init(chars);

    return *this;
}

const char* big_integer::to_str() 
{
    return _str;
}

big_integer big_integer::operator+(big_integer& other)
{
    big_integer* a;
    big_integer* b;
    char* c;
    int c_size = 0;

    if (_size >= other._size)
    {
        a = this;
        b = &other;
        c_size = _size + 1;
    }
    else
    {
        a = &other;
        b = this;
        c_size = other._size + 1;
    }

    c = new char[c_size];
    c[0] = '0';

    int sum = 0;
    int r = 0;

    for (int i = b->_size - 2, j = a->_size - 2, k = c_size - 2;
        i >= 0;
        --i, --j, --k)
    {
        sum = (a->_str[j] - '0') + (b->_str[i] - '0') + r;
        r = sum / 10;
        c[k] = static_cast<char>(sum % 10 + '0');
        if (j >= 0 && i == 0)
        {
            --j;
            --k;
            if (r == 0)
            {
                for (; j >= 0; --j, --k)
                {
                    c[k] = a->_str[j];
                }
            }
            else
            {
                for(; r != 0 && j >= 0; --j, --k)
                {
                    sum = (a->_str[j] - '0') + r;
                    r = sum / 10;
                    c[k] = static_cast<char>(sum % 10 + '0');
                } 
            }
        }
    }

    big_integer result(c);
    delete[] c;
    return result;
}

big_integer big_integer::operator+=(big_integer&& other) noexcept
{
    big_integer sum = *this + other;
    return sum;
}

big_integer big_integer::operator*(big_integer& other)
{
    big_integer* col;
    big_integer* row;
    big_integer result;

    if (_size > other._size)
    {
        col = this;
        row = &other;
    }
    else
    {
        col = &other;
        row = this;
    }

    const unsigned int c_size = col->_size + row->_size;

    int mult = 0;
    int r = 0;
    for (int i = row->_size - 2, level = 0; i >= 0; --i, ++level)
    {
        char* c = new char[c_size];
        c[c_size - 1] = 0;
        int k = c_size - 2;
        if (level > 0)
        {
            for (int l = k; l >= k - level; --l)
            {
                c[l] = '0';
            }
            k -=level;
        }
        for (int j = col->_size - 2; j >= 0; --j)
        {
            mult = (row->_str[i] - '0') * (col->_str[j] - '0') + r;
            r = mult / 10;
            c[k] = static_cast<char>(mult % 10 + '0');
            --k;
        }
        for (;k >= 0; --k)
        {
            c[k] = '0';
        }
     //   big_integer temp(c);
        result = result + big_integer(c);
        delete[] c;
    }
    
    return result;
}

big_integer big_integer::operator*(big_integer&& other) noexcept
{
    big_integer mult = *this * other;
    return mult;
}


std::ostream& operator<<(std::ostream& out, big_integer& obj)
{
    out << obj.to_str();

    return out;
}

big_integer::~big_integer()
{
    delete[] _str;
    _str = nullptr;
}

int big_integer::len()
{
    return _size - 1;
}