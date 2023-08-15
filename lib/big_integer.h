#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <memory>
#include <vector>
#include <iostream>


class big_integer
{
    private:
        char*  dig;
        int size;
    
    public:
        big_integer();
        big_integer(const char* str);
        big_integer(const std::string& str);

        big_integer(const big_integer& other);
        big_integer(big_integer&& other) noexcept;

        big_integer& operator=(const big_integer& other);
        big_integer& operator=(big_integer&& other) noexcept;
        big_integer& operator=(const char* str);
        big_integer& operator=(const std::string& str);

        virtual ~big_integer();

        big_integer operator+(big_integer& other);
        big_integer operator*(big_integer& other);
        friend std::ostream& operator<<(std::ostream& out, big_integer& obj);

        bool valid_digit(char symvol);
        std::string to_str();
        void dig_init(const char* str);
        void dig_init(std::string str);
};

#endif