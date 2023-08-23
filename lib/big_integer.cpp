//#include <string.h>
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


    //int size = _size;
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
    //_size = strlen(str) + 1;
    dig_init(str);
}

big_integer::big_integer(const std::string& str)
{
    const char* chars = str.c_str();
    //_size = strlen(chars) + 1;

    dig_init(chars);
}

big_integer::big_integer(const big_integer& other)
{
    if (_size == other._size)
    {
        for (int i = 0; i < _size; ++i)
        {
            _str[i] = other._str[i];
        }
    }
    else
    {
        delete[] _str;
        _size = other._size;
        _str = new char[_size];
        for (int i = 0; i < _size; ++i)
        {
            _str[i] = other._str[i];
        }
    }
}

big_integer::big_integer(big_integer&& other) noexcept :
    _size(other._size)
{
    delete[] _str;
    _str = other._str;
}

big_integer& big_integer::operator=(const big_integer& other)
{
    return *this = big_integer(other);
}

big_integer& big_integer::operator=(big_integer&& other) noexcept
{
    return *this = other;
}

big_integer& big_integer::operator=(const char* str)
{
    delete[] _str; 

    //_size = strlen(str) + 1;
    dig_init(str);

    return *this;
}

big_integer& big_integer::operator=(const std::string& str)
{
    delete[] _str;
    const char* chars = str.c_str();
   // _size = str.length() + 1;

    dig_init(chars);

    return *this;
}

const char* big_integer::to_str() 
{
    return _str;
}

big_integer big_integer::operator+(big_integer& other)
{
    std::string a = this->to_str();
    std::string b = other.to_str();
    std::string c = "";

    while (a.length() != b.length())
    {
        if (a.length() < b.length())
            a = "0" + a;
        else
            b = "0" + b;
    }

    a = "0" + a;
    b = "0" + b;

    int sum = 0;
    int r = 0;
    unsigned int size = a.length();

    for (int i = size - 1; i >= 0; --i)
    {
        sum = (a[i] - '0') + (b[i] - '0') + r;
        r = sum / 10;
        c = static_cast<char>(sum % 10 + '0') + c;
    }

    if (c[0] == '0')
        c.erase(0, 1);

    return big_integer(c);
}

big_integer big_integer::operator+(big_integer&& other) noexcept
{
    return *this + other;
}

big_integer big_integer::operator*(big_integer& other)
{
    const char* col;
    const char* row;
    int col_size = 0;
    int row_size = 0;
    big_integer result;

    if (_size > other._size)
    {
        col = _str;
        row = other._str;
        col_size = _size;
        row_size = other._size;

    }
    else
    {
        col = other._str;
        row = _str;
        col_size = other._size;
        row_size = _size;
    }

    std::cout << "col = " << col << '\n';
    std::cout << "row = " << row << '\n';

    const unsigned int c_size = col_size + row_size;

    int mult = 0;
    int r = 0;
    for (int i = row_size - 2, level = 0; i >= 0; --i, ++level)
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
        for (int j = col_size - 2; j >= 0; --j)
        {
            mult = (row[i] - '0') * (col[j] - '0') + r;
            r = mult / 10;
            c[k] = static_cast<char>(mult % 10 + '0');
            --k;
        }
        for (;k >= 0; --k)
        {
            c[k] = '0';
        }
        big_integer temp(c);
        delete[] c;
        //result = result + std::move(temp);
        result = result + temp;
    }
    
    return result;
}

big_integer big_integer::operator*(big_integer&& other) noexcept
{
    return *this * other;
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