#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>

class PostTape{
private:
    std::map<int, char> cells;
    char blank;

public:
    explicit PostTape(char blankSymbol = '0');

    PostTape(const PostTape& other) = default;
    PostTape& operator=(const PostTape& other) = default;

    void setCell(int index, char value);
    char getCell(int index) const;

    bool operator==(const PostTape& other) const;
    bool operator!=(const PostTape& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PostTape& tape);
    friend std::istream& operator>>(std::istream& is, PostTape& tape);
};

class PostProgram{
public:
    struct Rule{
        int currentState;
        char currentSymbol;
        int newState;
        char newSymbol;
        char move;

        bool operator==(const Rule& other) const;
    };

private:
    std::vector<Rule> rules;

public:
    PostProgram() = default;

    void addRule(const Rule& rule);
    void removeRule(std::size_t index);
    void clear();
    const std::vector<Rule>& getRules() const;

    friend std::ostream& operator<<(std::ostream& os, const PostProgram& program);
    friend std::istream& operator>>(std::istream& is, PostProgram& program);
};

class PostMachine{
private:
    PostTape tape;
    PostProgram program;
    int carriage; // Позиция каретки
    int state; //Текущее состояние
    bool halted; //Флаг остановки
    static const int VIEW_RADIUS = 3; //область видимости
public:
    PostMachine(): carriage(0), state(1), halted(false){}

    void operator++();
    void operator--();

    void loadTape(std::istream& is);
    void loadProgram(std::istream& is);

    void step();
    void run(bool log = false);

    void printState() const;

    void addRule(const PostProgram::Rule& rule) { program.addRule(rule); }
    void removeRule(std::size_t index) { program.removeRule(index); }
    void printRules() const { std::cout << program; }
};
