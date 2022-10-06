//********************************************************************
//
// simplesim.cpp
// CSCI 241 Assignment 4
//
// Created by Juviny Noriega (z1917876) COLLOBARED WITH MENTOR (Z193699)
//
//********************************************************************

#include <iostream>
#include <iomanip>
#include "simplesim.h"
#include "sml.h"

using std::cin;
using std::cout;
using std::endl;
using std::internal;
using std::left;
using std::noshowpos;
using std::right;
using std::setfill;
using std::setw;
using std::showpos;

/**
 * Initializes the Simplesim's memory to default values.
 */
simplesim::simplesim()
{
	accumulator=0;
	instruction_counter=0;
	instruction_register=0;
	operation_code=0;
	operand=0;

	for (int i=0;i<=99;i++)
	{
		memory[i]=7777;
	}


}

/**
 * Loads an SML program into the Simplesim's memory.
 *
 * @return Returns true if a valid program is successfully loaded into 
 *         memory; otherwise, false.
 */
bool simplesim::load_program()
{
    int count = 0;
    int instruction = 0;

    while (cin >> instruction && instruction != -99999)
    {
        // Check for invalid word.
	if (instruction <=-9999 or  instruction >=9999)  
	{
		cout<<"***ABEND:pgm load:invalid word***"<<endl;
		return false;
	}
	if(count>=100)
	{
		cout<<"***ABEND:pgm load:pgm too large***"<<endl;
		return false;
	}
	memory[count]=instruction;	


        // Add instruction to memory.

       
        count++;
	}

    return true;
}

/**
 * Executes an SML program loaded into the Simplesim's memory.
 */
void simplesim::execute_program()
{
    bool done = false;
    int read_1;
    while (!done)
    {
        // Check for addressability error.
	if (instruction_counter>99 or instruction_counter<0)
	{
		cout<<"***ABEND:adressability error***"<<endl;
		return;
	}

        // Fetch instruction.
	
        instruction_register = memory[instruction_counter];
		operation_code = instruction_register / 100;
		operand = instruction_register % 100;
	
	//cout<<"operation_code:"<<operation_code<<"\toperand:"<<operand<<endl;

	
        // Execute instruction.
		switch (operation_code)
		{
        case READ:
		//read case withc prints the read value
		cin>>read_1;
		if (read_1>=-9999 and read_1<=9999)
		{	
			cout<<setw(7)<<left<<"READ: "<<setw(5)<<internal<<showpos<<setfill('0')<<internal<<read_1<<setfill(' ')<<endl;
			 memory[operand]=read_1;
			

		}
		else 
		{
			cout<<"***ABEND:illegal input***";
			return;
		}
		

	    
            break;

        case WRITE:
	   cout<<setw(5)<<internal<<showpos<<setfill('0')<<memory[operand]<<setfill(' ')<<endl;
            break;
	case LOAD:
	   accumulator=memory[operand];
	   break;
	case STORE:
	   memory[operand]=accumulator;
	   break;
        // etc.
	case ADD://first operation case
	   int sum1;
	   sum1=accumulator+memory[operand];
	   if (sum1 < -9999)
	   {
		cout<<"***ABEND:underflow***"<<endl;
		return;//error code for underflow
	   }
	   else if (sum1>9999)
	   {
		cout<<"***ABEND:overflow***"<<endl;
		return;
		//error code for overflow
	   }
	   else
	   {
		accumulator=sum1;
		
	   }
	   break;
	 case SUBTRACT:
           int sub;//second operation  case
           sub=accumulator-memory[operand];
           if (sub < -9999)
           {
                cout<<"***ABEND:underflow***"<<endl;
                return;//underflow error
           }
           else if (sub>9999)
           {
                cout<<"***ABEND:overflow***"<<endl;
                return;
           }//overflow error 
           else
           {
                accumulator=sub;
		
           }
           break;

//third operation case
	 case MULTIPLY:
           int mult;
           mult=accumulator*memory[operand];
           if (mult < -9999)
           {
                cout<<"***ABEND:underflow***"<<endl;
                return;//underflow error
           }
           else if (mult>9999)
           {
                cout<<"***ABEND:overflow***"<<endl;
                return;//overflow error 
           }
           else accumulator=mult;
		


	   break;//fourth operation case
	 case DIVIDE:
           
	   
	   if (memory[operand]==0)
	   {
		cout<<"***ABEND:attempted division by 0***"<<endl;
		return;//error for attempted division
	   }
	   int div;
           div=accumulator/memory[operand];
           if (div < -9999)//underflow error 
           {
                cout<<"***ABEND:underflow***"<<endl;
                return;
           }
           else if (div>9999)
           {//overflow error
                cout<<"***ABEND:overflow***"<<endl;
                return;
           }
           else
           {
                accumulator=div;

           }
           break;


	case BRANCH:
	instruction_counter=operand;
	
	case BRANCHNEG:
	if (accumulator<0)
	{
		instruction_counter=operand;
	}
	else instruction_counter++;
	break;
	case BRANCHZERO:
		if (accumulator ==0)
		{
			instruction_counter=operand;
		}
		else instruction_counter++;
	break;
        case HALT:
            done = true;
            break;

        default:
            cout << "*** ABEND: invalid opcode ***\n";
            return;
        }
	
		// Increment instruction counter if needed.
	//omcrements counter incase of not branch and done 
	if (operation_code!=BRANCH and !done)
	{
		instruction_counter++;
	
	}
	}
    // Print successful termination message.
	cout<< "*** Simplesim execution terminated ***\n";

}
/**
 * Prints the contents of the Simplesim's registers and memory.
 */
void simplesim::dump() const
{
    // Print registers.
	cout<< "\n"<<"REGISTERS:"<<endl;
	cout.width(24);
	cout<<showpos<<setfill('0')<<internal<<"accumulator:            "<<setw(5)<<accumulator<<noshowpos<<setfill(' ')<<endl;

	cout<<setfill('0')<<right<<"intruction_counter:     "<<setw(2)<<instruction_counter<<setfill(' ')<<endl;
	
	cout<<showpos << setfill('0')<<internal<<"intruction_register:    "<<setw(5)<<instruction_register<<noshowpos<<setfill(' ')<<endl;
	
	cout<<setfill('0')<<right<<"operation_code:         "<<setw(2)<<operation_code<<setfill(' ')<<endl;
	
	cout<<setfill('0')<<right<<"operand:                "<<setw(2)<<operand<<setfill(' ')<<endl;
	

	cout << "\n\nMEMORY:" << endl;

        cout << setw(8) << "0" << setw(6) << "1" << setw(6) << "2" << setw(6) << "3" << setw(6) << "4" << setw(6) << "5" << setw(6) << "6" << setw(6) << "7" << setw(6) << "8" << setw(6) <<"9" << endl;
//prints array
     for (int i = 0; i < 100; i++)
    {
        if (i % 10 == 0)
        cout << setfill(' ') << right << setw(2) << noshowpos << i;


          cout << ' ' << setw(5) << showpos << internal << setfill('0')
         << memory[i];

        if ((i+1) % 10 == 0)
        cout << endl;
    }

}

    // Print memory.

