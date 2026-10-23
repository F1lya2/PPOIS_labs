#pragma once

#include <iostream>
#include <vector>
#include <map>

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
public:
    struct Rule{
        std::string currentState;
        char currentSymbol;
        std::string newState;
        char newSymbol;
        char move;

        bool operator==(const Rule& other) const;
    };

private:
    std::vector<Rule> rules;

public:
    TuringProgram() = default;

    void addRule(const Rule& rule);
    void removeRule(std::size_t index);
    void clear();
    const std::vector<Rule>& getRules() const;

    friend std::ostream& operator<<(std::ostream& os, const TuringProgram& program);
    friend std::istream& operator>>(std::istream& is, TuringProgram& program);
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

   void addRule(const TuringProgram::Rule& rule) { program.addRule(rule); }
   void removeRule(std::size_t index) { program.removeRule(index); }
   void printRules() const { std::cout << program; }

   std::string getState() const { return state; }
   int getCarriage() const { return carriage; }
};
