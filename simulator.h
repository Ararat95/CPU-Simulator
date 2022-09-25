#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <fstream>
#include <iostream>
#include <map>

class CPU
{
public:
    CPU ();
public:
    typedef void (CPU::*f_point)(std::string&, std::string&);
    void start (); // for start the program
    void print (); // to print registers

public:
    //instructions
    void mov (std::string&, std::string&);
    void jmp (std::string&, std::string&);
    void cmp (std::string&, std::string&);
    void add (std::string&, std::string&);
    void sub (std::string&, std::string&);
    void mul (std::string&, std::string&);
    void div (std::string&, std::string&);
    void jl (std::string&, std::string&);
    void jle (std::string&, std::string&);
    void je (std::string&, std::string&);
    void jne (std::string&, std::string&);
    void jge (std::string&, std::string&);
    void jz (std::string&, std::string&);
    void jnz (std::string&, std::string&);
    void jg (std::string&, std::string&);
private:
    std::fstream file; // file
    std::map <std::string, std::streampos> label; // to save labels
    std::map <std::string, bool> jmps; // to focus jumps
    std::map <std::string, int*> registers; // map for registers
    std::map <std::string,f_point > inst; // map for instructions
    //registers
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;
    int r7;
    int r8;
    int r9;
    int r10;
private:
     //used functions
    void do_it (std::string);
    void reset_jmps();
    void set_inst();
    bool check_num (std::string);
    bool check_reg (std::string);
    void get_labels ();

};
#endif //SIMULATOR_H