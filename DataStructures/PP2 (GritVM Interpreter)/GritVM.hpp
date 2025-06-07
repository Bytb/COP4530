// This project was done by Caleb Fernandes and Jadon Orr

#pragma once

#include <string>
#include <vector>
#include <list>
#include "GritVMBase.hpp"

class GritVM : public GritVMInterface
{
public:
    GritVM() : machineStatus(WAITING), accumulator(0) {};
    STATUS load(const std::string filename, const std::vector<long> &initialMemory);
    // This method loads the GVM program into the GritVM object and copies initialMemory into the
    // data memory. Returns the current machine status. Throws if file cannot be read.
    STATUS run();
    // This method starts the evaluation of the instructions. Returns the current machine status.
    std::vector<long> getDataMem();
    // Returns a copy of the current dataMem
    STATUS reset();
    // Sets the accumulator to 0, clears the dataMem and instructMem, sets the machineStatus to
    // WAITING.

    // Accumulator Function
    void clear();
    // DM Management Function
    void at(const int &index);
    void set(const int &index);
    void insertG(const int &index);
    void eraseG(const int &index);

    // Accumulator Maths with a Constant
    void addConst(const int &val);
    void subConst(const int &val);
    void mulConst(const int &val);
    void divConst(const int &val);

    // Accumulator Maths with a Memory Location
    void addMem(const int &val);
    void subMem(const int &val);
    void mulMem(const int &val);
    void divMem(const int &val);

    // Instruction Jump Functions
    int jumpRel(const int &val);
    int jumpZero(const int &val);
    int jumpNZero(const int &val);

    // Misc Functions
    void noop();
    void halt();
    void output();
    int checkMem(const int &val);

    // evaluate and moveForward
    int evaluate(Instruction i);
    void moveForward(const int &spaces);

    // print function
    void printVM(bool printData, bool printInstruction);

private:
    std::vector<long> dataMem;
    std::list<Instruction> instructMem;
    std::list<Instruction>::iterator currentInstruct;
    STATUS machineStatus;
    long accumulator;
};