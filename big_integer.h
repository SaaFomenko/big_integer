#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <memory>
#include <vector>
#include <string>


class big_integer
{
    private:
        char*  dig;
        unsigned int size;
    
    public:
        big_integer(const char* str);
        big_integer(const std::string& str);

        big_integer(const big_integer& other);
        big_integer(big_integer&& other) noexcept;

        big_integer& operator=(const big_integer& other);
        big_integer& operator=(big_integer&& other) noexcept;

        virtual ~big_integer();

        big_integer operator+(const big_integer& other);
        big_integer operator*(const big_integer& other);

        bool valid_digit(char symvol);
        std::string to_str();
        void clear_null(const char* str);
        void clear_null(std::string str);
};

#endif