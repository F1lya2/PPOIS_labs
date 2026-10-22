#pragma once

#include <iostream>
#include <vector>

class TuringTape{
private:
    std::map<int, char> cells;
    char blank;

public:
    explicit TuringTape(char blankSymbol = '_');

    TuringTape(const TuringTape& other) = default;
    TuringTape& operator=(const TuringTape& other) = default;

    void setCell(int index, char value);
    char getCell(int index) const;

    bool operator==(const TuringTape& other) const;
    bool operator!=(const TuringTape& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TuringTape& tape);
    friend std::istream& operator>>(std::istream& is, TuringTape& tape);
};

class TuringProgram{

};

class TuringMachine{
private:
    TuringTape tape;
    TuringProgram program;
    int carriage;
    std::string state;
    bool halted;

public:
   TuringMachine() : carriage(0), state("q0"), halted(false){}

   void operator++();
   void operator--();

   void loadTape(std::istream& is);
   void loadProgram(std::istream& is);

   void step();
   void run(bool log = false);

   void printState() const;
};
