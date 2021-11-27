//
// Created by light on 19-12-9.
//
#include <iostream>
class Animal {
public:
    Animal() { std::cout << "Animal is called" << std::endl; }
    Animal(int age) : animal1(age) {
        std::cout << "Animal(int age) is called" << std::endl;
        std::cout << "animal1:" << animal1 << std::endl;
    }

    Animal(const Animal &animal) { std::cout << "Animal (const Animal &) is called" << std::endl; }

    Animal &operator=(const Animal &amimal) {
        std::cout << "Animal & operator=(const Animal &) is called" << std::endl;
        return *this;
    }

    ~Animal() { std::cout << "~Animal() is called" << std::endl; }

private:
    int animal1;
    int animal2;
};

class Dog : Animal {
public:
    Dog(int age) : Animal(age) { std::cout << "Dog(int age) is called" << std::endl; }

    ~Dog() { std::cout << "~Dog() is called" << std::endl; }
};

int main() {
    Animal animal(1);
    std::cout << std::endl;
    Dog d(100);
    std::cout << std::endl;
    return 0;
}