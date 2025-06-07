// This project was done by Caleb Fernandes and Jadon Orr

#include "GritVMBase.hpp"
#include "GritVM.hpp"
#include <fstream>
#include <iostream>

using namespace std;

// Check Machine Status:
STATUS GritVM::load(const string filename, const vector<long> &initialMemory)
{
    if (machineStatus != WAITING)
        return machineStatus;
    // reads in the file and throws error if cannot open
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("Cannot open file: " + filename);
    };
    // copy the initial memory into dataMem
    dataMem = initialMemory;

    string line;
    while (getline(file, line))
    {
        // Ignore empty lines and comments
        if (line.empty() || line[0] == '#')
        {
            continue;
        }
        // Parse the instruction
        Instruction instr = GVMHelper::parseInstruction(line);
        // if instruction is unknow, make status errored
        if (instr.operation == UNKNOWN_INSTRUCTION)
        {
            machineStatus = ERRORED;
            return machineStatus;
        }
        // Add instruction to the instruction memory
        instructMem.push_back(instr);
    }
    file.close();
    if (instructMem.empty())
    {
        machineStatus = WAITING;
    }
    else
    {
        machineStatus = READY;
    }
    return machineStatus;
};

// This method loads the GVM program into the GritVM object and copies initialMemory into the
// data memory. Returns the current machine status. Throws if file cannot be read.

// This method starts the evaluation of the instructions. Returns the current machine status.
STATUS GritVM::run()
{
    if (machineStatus == READY)
        machineStatus = RUNNING;
    else
    {
        return machineStatus;
    }
    for (currentInstruct = instructMem.begin(); currentInstruct != instructMem.end();)
    {
        int jumpDistance = evaluate(*currentInstruct);
        if (jumpDistance == 0)
        {
            machineStatus = ERRORED;
            return machineStatus;
        }

        // Stop execution if HALT is encountered
        if (machineStatus == HALTED)
            return machineStatus;

        moveForward(jumpDistance);
    }
    return machineStatus;
};

// Returns a copy of the current dataMem
vector<long> GritVM::getDataMem() { return dataMem; };
// Sets the accumulator to 0, clears the dataMem and instructMem, sets the machineStatus to
// WAITING.
STATUS GritVM::reset()
{
    accumulator = 0;
    dataMem.clear();
    instructMem.clear();
    machineStatus = WAITING;
    return machineStatus;
};

// function definitions instructions
void GritVM::clear()
{
    accumulator = 0;
}

// DM Management Function
void GritVM::at(const int &index)
{
    if (index < 0 || index >= dataMem.size())
    {
        machineStatus = ERRORED;
        return;
    }
    accumulator = dataMem[index];
};
void GritVM::set(const int &index)
{
    if (index < 0 || index >= (int)dataMem.size())
    {
        machineStatus = ERRORED;
        return;
    }
    dataMem[index] = accumulator;
};
void GritVM::insertG(const int &index)
{
    dataMem.insert(dataMem.begin() + index, accumulator);
};
void GritVM::eraseG(const int &index)
{
    dataMem.erase(dataMem.begin() + index);
};

// Accumulator Maths with a Constant
void GritVM::addConst(const int &val) { accumulator = accumulator + val; };
void GritVM::subConst(const int &val) { accumulator = accumulator - val; };
void GritVM::mulConst(const int &val) { accumulator = accumulator * val; };
void GritVM::divConst(const int &val) { accumulator = accumulator / val; };

// Accumulator Maths with Mem Location
void GritVM::addMem(const int &val) { accumulator = accumulator + dataMem[val]; };
void GritVM::subMem(const int &val) { accumulator = accumulator - dataMem[val]; };
void GritVM::mulMem(const int &val) { accumulator = accumulator * dataMem[val]; };
void GritVM::divMem(const int &val) { accumulator = accumulator / dataMem[val]; };

// Instruction Jump Functions
int GritVM::jumpRel(const int &val) { return val; };
int GritVM::jumpZero(const int &val)
{
    if (accumulator == 0)
    {
        return val;
    }
    else
    {
        return 1;
    }
};

// Jumps Val spaces (back/forward) if accumlator is not zero, else it returns 1
int GritVM::jumpNZero(const int &val)
{
    if (accumulator != 0)
    {
        return val;
    }
    else
    {
        return 1;
    }
};

// Misc Functions

// Noop function that does nothing
void GritVM::noop() {};

// Halt function that changes MachineStatus to HALTED
void GritVM::halt() { machineStatus = HALTED; };

// Prints output
void GritVM::output() { cout << accumulator << endl; };

// Checks Memory to see if there is enough space else changes Status to Errored
int GritVM::checkMem(const int &val)
{
    if (dataMem.size() < val)
    {

        machineStatus = ERRORED;
        return 0;
    }
    return 1;
};

// evaluate and moveForward
int GritVM::evaluate(Instruction i)
{
    switch (i.operation)
    {
    case CLEAR:
        clear();
        return 1;
    case AT:
        at(i.argument);
        return 1;
    case SET:
        set(i.argument);
        return 1;
    case INSERT:
        insertG(i.argument);
        return 1;
    case ERASE:
        eraseG(i.argument);
        return 1;
    case ADDCONST:
        addConst(i.argument);
        return 1;
    case SUBCONST:
        subConst(i.argument);
        return 1;
    case MULCONST:
        mulConst(i.argument);
        return 1;
    case DIVCONST:
        divConst(i.argument);
        return 1;
    case ADDMEM:
        addMem(i.argument);
        return 1;
    case SUBMEM:
        subMem(i.argument);
        return 1;
    case MULMEM:
        mulMem(i.argument);
        return 1;
    case DIVMEM:
        divMem(i.argument);
        return 1;
    case JUMPREL:
        return jumpRel(i.argument);
    case JUMPZERO:
        return jumpZero(i.argument);
    case JUMPNZERO:
        return jumpNZero(i.argument);
    case NOOP:
        noop();
        return 1;
    case HALT:
        halt();
        return 1;
    case OUTPUT:
        output();
        return 1;
    case CHECKMEM:
        return checkMem(i.argument);
    default:
        return 0;
    }
};

// advances forward by spaces
void GritVM::moveForward(const int &spaces)
{
    advance(currentInstruct, spaces);
};

// Prints the state of the GritVM virtual machine
void GritVM::printVM(bool printData, bool printInstruction)
{
    // Prints a header for the output dump
    cout << "****** Output Dump ******" << endl;

    // Prints the machine's current status using a helper function
    cout << "Status: " << GVMHelper::statusToString(machineStatus) << endl;

    // Prints the value of the accumulator
    cout << "Accumulator: " << accumulator << endl;

    // If printData is true, print the contents of the data memory
    if (printData)
    {
        cout << "*** Data Memory ***" << endl;
        int index = 0;
        vector<long>::iterator it = dataMem.begin();

        // Iterates through the data memory vector and prints each value with its location index
        while (it != dataMem.end())
        {
            long item = (*it);
            cout << "Location " << index++ << ": " << item << endl;
            it++;
        }
    }

    // If printInstruction is true, print the contents of the instruction memory
    if (printInstruction)
    {
        cout << "*** Instruction Memory ***" << endl;
        int index = 0;
        list<Instruction>::iterator it = instructMem.begin();

        // Iterates through the instruction list and prints each instruction with its index
        while (it != instructMem.end())
        {
            Instruction item = (*it);
            cout << "Instruction " << index++ << ": "
                 << GVMHelper::instructionToString(item.operation)
                 << " " << item.argument << endl;
            it++;
        }
    }
}
