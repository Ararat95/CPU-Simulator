#include "simulator.h"

int main ()
{
    CPU* obj = CPU::getInstance();
    try {
        obj->start();
        obj->print();
    }
    catch (...) {
        std::cout << "Exeption catched!!!" << std::endl;
    }
}