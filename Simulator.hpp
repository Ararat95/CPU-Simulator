#include "simulator.h"
CPU::CPU () : r1{}, r2{}, r3{}, r4{}, r5{}, r6{}, r7{}, r8{}, r9{}, r10{}
{
    set_inst();
    reset_jmps();
}
void CPU::start ()
{
    std::string line;
    get_labels();
    file.open("assembly.txt");
    if (file.is_open())
    {
        while(std::getline(file,line))
        {
            if (line == "")
            {
                continue;
            }
            do_it(line);
        }
    }
    else
    {
        std::cout << "file is not open\n";
    }
    file.close();
}
void CPU::get_labels ()
{
    std::string line;
    file.open("assembly.txt");
    if (file.is_open())
    {
        while (std::getline(file,line))
        {
            if (line.find(':') != -1)
            {
                line.erase(line.begin() + line.find(':'));
                label[line] = file.tellg();
            }
        }
    }
    file.close();
}

void CPU::do_it(std::string line)
{
    std::string operation = "";
    std::string dest = "";
    std::string src = "";
    if (line.find(':') != -1)
    {
        return;
    }
    if (line.find(',') != -1)
    {
        line.erase(line.begin() + line.find(','));
    }
    int space = 0;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ' ')
        {
            ++space;
            continue;
        }
        if (space == 0)
        {
            operation += line[i];
        }
        else if (space == 1)
        {
            dest += line[i];
        }
        else if (space == 2)
        {
            src += line[i];
        }
    }
    (this->*inst[operation])(dest,src);
}
bool CPU::check_num (std::string tmp)
{
    for (int i = 0; i < tmp.size(); ++i)
    {
        if (!(tmp[i] >= '0' && tmp[i] <= '9'))
        {
            return false;
        }
    }
    return true;
}
bool CPU::check_reg (std::string tmp)
{
    if (registers.find(tmp) != registers.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CPU::mov (std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src))
        {
            *registers[dest] = stoi(src);
            return;
        }
        else if (check_reg(src))
        {
            *registers[dest] = *registers[src];
            return;
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::add(std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src))
        {
            *registers[dest] += stoi(src);
            return;
        }
        else if (check_reg(src))
        {
            *registers[dest] += *registers[src];
            return;
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::div (std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src))
        {
            *registers[dest] /= stoi(src);
            return;
        }
        else if (check_reg(src))
        {
            *registers[dest] /= *registers[src];
            return;
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::mul (std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src))
        {
            *registers[dest] *= stoi(src);
            return;
        }
        else if (check_reg(src))
        {
            *registers[dest] *= *registers[src];
            return;
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::sub (std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src))
        {
            *registers[dest] -= stoi(src);
            return;
        }
        else if (check_reg(src))
        {
            *registers[dest] -= *registers[src];
            return;
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::jmp (std::string& dest, std::string& src)
{
    file.seekg(label[dest]);
}
void CPU::cmp (std::string& dest, std::string& src)
{
    if (check_reg(dest))
    {
        if (check_num(src) && src != "0")
        {
            if(*registers[dest] == stoi(src))
            {
                jmps["je"] = true;
                jmps["jle"] = true;
                jmps["jge"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] < stoi(src))
            {
                jmps["jl"] = true;
                jmps["jle"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] > stoi(src))
            {
                jmps["jg"] = true;
                jmps["jge"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
        }
        else if (check_num(src) && src == "0")
        {
             if(*registers[dest] == stoi(src))
            {
                jmps["je"] = true;
                jmps["jle"] = true;
                jmps["jge"] = true;
                jmps["jz"] = true;
                return;
            }
            else if (*registers[dest] < stoi(src))
            {
                jmps["jl"] = true;
                jmps["jle"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] > stoi(src))
            {
                jmps["jg"] = true;
                jmps["jge"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
        }
        if (check_reg(src) && *registers[src] != 0)
        {
            if(*registers[dest] == *registers[src])
            {
                jmps["je"] = true;
                jmps["jle"] = true;
                jmps["jge"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] < *registers[src])
            {
                jmps["jl"] = true;
                jmps["jle"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] > *registers[src])
            {
                jmps["jg"] = true;
                jmps["jge"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
        }
        else if (check_reg(src) && *registers[src] == 0)
        {
            if(*registers[dest] == *registers[src])
            {
                jmps["je"] = true;
                jmps["jle"] = true;
                jmps["jge"] = true;
                jmps["jz"] = true;
                return;
            }
            else if (*registers[dest] < *registers[src])
            {
                jmps["jl"] = true;
                jmps["jle"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
            else if (*registers[dest] > *registers[src])
            {
                jmps["jg"] = true;
                jmps["jge"] = true;
                jmps["jne"] = true;
                jmps["jnz"] = true;
                return;
            }
        }
    }
    throw std::runtime_error ("Register not found\n");
}
void CPU::jl (std::string& dest, std::string& src)
{
    if (jmps["jl"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jle (std::string& dest, std::string& src)
{
     if (jmps["jle"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jg (std::string& dest, std::string& src)
{
     if (jmps["jg"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jge (std::string& dest, std::string& src)
{
     if (jmps["jge"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jz (std::string& dest, std::string& src)
{
     if (jmps["jz"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jnz (std::string& dest, std::string& src)
{
     if (jmps["jnz"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::je (std::string& dest, std::string& src)
{
     if (jmps["je"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}
void CPU::jne (std::string& dest, std::string& src)
{
    if (jmps["jne"])
    {
        file.seekg(label[dest]);
    }
    reset_jmps();
}

void CPU::set_inst()
{
    //register 
    registers["r1"] = &r1;
    registers["r2"] = &r2;
    registers["r3"] = &r3;
    registers["r4"] = &r4;
    registers["r5"] = &r5;
    registers["r6"] = &r6;
    registers["r7"] = &r7;
    registers["r8"] = &r8;
    registers["r9"] = &r9;
    registers["r10"] = &r10;
    //operations
    inst["mov"] = &CPU::mov;
    inst["cmp"] = &CPU::cmp;
    inst["mul"] = &CPU::mul;
    inst["add"] = &CPU::add;
    inst["sub"] = &CPU::sub;
    inst["div"] = &CPU::div;
    inst["jmp"] = &CPU::jmp;
    inst["jl"] = &CPU::jl;
    inst["jle"] = &CPU::jle;
    inst["jne"] = &CPU::jne;
    inst["jnz"] = &CPU::jnz;
    inst["jg"] = &CPU::jg;
    inst["jge"] = &CPU::jge;
    inst["jz"] = &CPU::jz;
    inst["je"] = &CPU::je;
}

void CPU::reset_jmps ()
{
     //jumps
    jmps["jl"] = false;
    jmps["jle"] = false;
    jmps["jne"] = false;
    jmps["je"] = false;
    jmps["jg"] = false;
    jmps["jge"] = false;
    jmps["jz"] = false;
    jmps["jnz"] = false;
}
void CPU::print ()
{
    for (std::map <std::string,int*> :: iterator it = registers.begin(); it != registers.end(); ++it)
    {
        std::cout << it->first << ' ' << *(it->second) << std::endl;
    }
}