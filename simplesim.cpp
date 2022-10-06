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
        case ADD:
           break;


        case HALT:
            done = true;
            break;

        default:
            cout << "*** ABEND: invalid opcode ***\n";
            return;
        }

                // Increment instruction counter if needed.

        if (operation_code!=BRANCH and !done)
        {
                instruction_counter++;

        }
    
    // Print successful termination message.
        cout<< "*** Simplesim execution terminated ***\n";

}



 //Prints the contents of the Simplesim's registers and memory.*/
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


        cout<<"\n\nMEMORY:"<< endl;
        int n=0;
        int linecount=0;
        cout<<setw(10)<<"0"<<setw(8)<<"1"<<setw(8)<<"2"<<setw(8)<<"3"<<setw(8)<<"4"<<setw(8)<<"5"<<setw(8)<<"6"<<setw(8)<<"7"<<setw(8)<<"8"<<setw(8)<<"9";
        cout<<endl<<setw(2)<<n;
        for(int i=0;i<=99;i++)
        {
                cout.width(8);


                cout<<setw(8)<<showpos<<memory[i];
                linecount++;

                if (linecount==10)
                {
                        linecount=0;
                        n=n+10;
                        cout<<endl;

                        cout<<noshowpos<<n<<showpos;
                }
                else if (n==100)
                {
                {
                        break;
                }
        }
    // Print memory.
}
