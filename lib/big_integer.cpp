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
    unsigned int null_count = 0;

    while(str[i] != 0)
    {
        i += static_cast<int>(valid_digit(str[i]));
    }

    size = i;

    i = 0;
    while(str[i] == '0' && i < size)
    { 
        ++null_count;
        ++i;
    }

    size -= null_count; 


    if (size <= 0)
    {
        size = 2;
        _str = new char[size]{'0', 0};
    }
    else if (size > 0)
    {
        //++size;
        // Need realese void clear_null()
        _str = new char[size + 1];
        unsigned int j_str = 0;
        if (null_count > 0) j_str = null_count - 1;

        for (unsigned int i = 0, j = j_str ;  i < size; ++i, ++j)
        {
            _str[i] = str[j];
        }

        _str[size] = static_cast<char>(0);
    }
    else
    {
        throw MyException(err_null);
    }
}

big_integer::big_integer() : 
    _str{new char[2]{'0', 0}},
    size{1}
{}

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
            _str[i] = other._str[i];
        }
    }
    else
    {
        delete[] _str;
        size = other.size;
        _str = new char[size];
        for (unsigned int i = 0; i < size; ++i)
        {
            _str[i] = other._str[i];
        }
    }
}

big_integer::big_integer(big_integer&& other) noexcept : 
    size(other.size)
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
    return *this = big_integer(other);
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
    // str = new char[size + 1];

    // for (unsigned int i = 0; i < size; ++i)
    // {
    //     str[i] = dig[i];
    // }

    // str[size] = static_cast<char>(0);
    const char* str = _str;

    return str;
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
//    char* c;
    big_integer result;

    if (size < other.size)
    {
        col = to_str();
        row = other.to_str();
        col_size = size;
        row_size = other.size;
    }
    else
    {
        col = other.to_str();
        row = to_str();
        col_size = other.size;
        row_size = size;
    }

    int c_size = col_size + row_size;

    int mult = 0;
    int r = 0;
    for (int i = row_size - 2, level = 0; i >= 0; --i, ++level)
    {
        char c[c_size]{};
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
        if (k >= 0)
        {
            c[k] = '0';
        }
        big_integer temp(c);
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

int big_integer::str_size()
{
    return size;
}