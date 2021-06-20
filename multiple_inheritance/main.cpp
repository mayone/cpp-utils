#include <iostream>

#include "inherit.hpp"

class Hi
{
public:
    void say_hi() { std::cout << "Hi\n"; }
};

class Hello
{
public:
    void say_hello() { std::cout << "Hello\n"; }
};

class World
{
public:
    void say_world() { std::cout << "World\n"; }
};

using HWInherit = inherit::object<
    Hi,
    Hello,
    World>;

class HelloWorld : public HWInherit
{
};

int main()
{
    HelloWorld hw;
    hw.say_hi();
    hw.say_hello();
    hw.say_world();
}