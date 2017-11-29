#include "instruction.h"
#include "global.h"
#include <cmath>
void Instruction::execute()
{
	cout<<"Parent execute\n";
}
void Instruction::writeBack()
{}
void Instruction::memory()
{}

Add::Add(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Add::execute()
{
	res = op1 + op2;
	cout<<"EXECUTE: "<<"ADD "<<op1<<" and "<<op2<<"\n";			
}
void Add::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void Add::writeBack()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


And::And(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void And::execute()
{
	res=op1 & op2;
	cout<<"EXECUTE: "<<"AND "<<op1<<" and "<<op2<<"\n";
}
void And::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void And::writeBack()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Eor::Eor(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Eor::execute()
{
	res=op1 ^ op2;
	cout<<"EXECUTE: "<<"EOR "<<op1<<" and "<<op2<<"\n";
}
void Eor::memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}
void Eor::writeBack()
{
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Ldr::Ldr(long des,long address,long offset)
{
    this->des = des;
    this->address = address;
    this->offset = offset;
}
void Ldr::execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Ldr::memory()
{
    ifstream data;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    number = 0;
    for(int i=31;i>=0;i--)
        number += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<number<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
}
void Ldr::writeBack()
{
    R[des] = number;
    cout<<"EXECUTE: write "<<number<<" to R"<<des<<endl;
}


Mov::Mov(long des, long op)
{
	this->op=op;
	this->des=des;
}
void Mov::execute()
{
	res = op;
    cout<<"EXECUTE: "<<"Mov "<<op<<"\n";
}
void Mov::memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}	
void Mov::writeBack()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Mul::Mul(long des,long op1,long op2)
{
    this->op1 = op1;
    this->op2 = op2;
    this->des = des;
}
void Mul::execute()
{
    res = op1 * op2;
    cout<<"EXECUTE: MUL "<<op1<<" and "<<op2<<endl;
} 
void Mul::writeBack()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Mul::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}


Mvn::Mvn(long des, long op)
{
	this->op=op;
	this->des=des;
}
void Mvn::execute()
{
	res = ~op;
    cout<<"EXECUTE: "<<"MVN "<<op<<"\n";
}
void Mvn::memory()
{
	cout<<"MEMORY: No memory operation"<<endl;
}	
void Mvn::writeBack()
{
	R[des]=res;
    cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Orr::Orr(long des, long op1, long op2)
{
	this->op1=op1;
	this->op2=op2;
	this->des=des;
}
void Orr::execute()	
{
	res=op1 | op2;
	cout<<"EXECUTE: "<<"ORR "<<op1<<" and "<<op2<<"\n";
}
void Orr::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}
void Orr::writeBack()
{		
	R[des]=res;
	cout<<"WRITEBACK: "<<"write "<<res<<" to R"<<des<<"\n";
}


Str::Str(long number,long address,long offset)
{
    this->number = number;
    this->address = address;
    this->offset = offset;
}
void Str::execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Str::memory()
{
    fstream data;
    cout<<"MEMORY: "<<number<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (number%2==0?'0':'1');
        number = number/2;
    }
    data.write(numberString,32);
}
void Str::writeBack()
{
    cout<<"EXECUTE: No write-back operation"<<endl;
}


Sub::Sub(long des,long op1,long op2)
{
    this->des = des;
    this->op1 = op1;
    this->op2 = op2;
}
void Sub::execute()
{
    res = op1 - op2;
    cout<<"EXECUTE: SUB "<<op2<<" from "<<op1<<endl;
} 
void Sub::writeBack()
{
    R[des] = res;
    cout<<"WRITEBACK: Write "<<res<<" to R"<<des<<endl;
}
void Sub::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
}


Swi::Swi(long instruction)
{
    this->instruction = instruction;
}
void Swi::execute()
{
    if(instruction == (int)(0x11))
    {
        condition = "Exit";
    }
    else if(instruction == (int)(0x6c))
    {
        cout<<"EXECUTE: Read value from console"<<endl;
        condition = "Read";
        cin>>number;
    }
    else
    {
        cout<<"EXECUTE: Print value in R1"<<endl;
        condition = "Print";
    }
}
void Swi::writeBack()
{
    if(condition == "Read")
    {
        R[0] = number;
        cout<<"WRITEBACK: Write "<<number<<" to R0"<<endl;
    }
    else if(condition == "Print")
    {
        cout<<R[1]<<endl;
    }
}
void Swi::memory()
{
    cout<<"MEMORY: No memory operation"<<endl;
    if(condition == "Exit")
    {
        cout<<"EXIT:"<<endl;
        exit(0);
    }
}


/*Swp::Swp(long des,long number,long address)
{
    this->number = number;
    this->address = address;
    this->des = des;
}
void Swp::execute()
{
    cout<<"EXECUTE: No execute operation"<<endl;
} 
void Swp::memory()
{
    fstream data;
    data.open("DATA.MEM");
    data.seekg(address*32+offset*32,ios::beg);
    data.get(numberString,32);
    long numberTemp = 0;
    for(int i=31;i>=0;i--)
        numberTemp += pow(2,31-i)*(int(numberString[i])-int('0'));
    cout<<"MEMORY: "<<numberTemp<<" loaded from "<<address*32+offset*32<<" address in memory"<<endl;
    swap(number,numberTemp);
    cout<<numberTemp<<" stored at "<<address*32+offset*32<<" address in memory"<<endl;
	data.seekg(address*32+offset*32,ios::beg);
    for(int i=31;i>=0;i--)
    {
        numberString[i] = (numberTemp%2==0?'0':'1');
        numberTemp = numberTemp/2;
    }
    data.write(numberSwping,32);
}
void Swp::writeBack()
{
    R[des] = number;
    cout<<"WRITEBACK: write "<<number<<" to "<<des<<endl;
}*/