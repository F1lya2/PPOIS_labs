#include "../include/Turing.h"
#include <sstream>
#include <algorithm>

constexpr int VIEW_RADIUS = 4;

TuringTape::TuringTape(char blankSymbol) : blank(blankSymbol){}

void TuringTape::setCell(int index, char value){
    cells[index] = value;
}

char TuringTape::getCell(int index) const{
    auto it = cells.find(index);
    if(it != cells.end()){
        return it->second;
    }
    return blank;
}

bool TuringTape::operator==(const TuringTape &other) const{
    return cells == other.cells && blank == other.blank;
}

bool TuringTape::operator!=(const TuringTape &other) const{
    return !(*this==other);
}

std::ostream& operator<<(std::ostream& os, const TuringTape& tape){
    if(tape.cells.empty()){
        os << tape.blank;
        return os;
    }
    int minIdx = tape.cells.begin()->first;
    int maxIdx = tape.cells.rbegin()->first;

    for(int i = minIdx; i<=maxIdx; i++){
        os << tape.getCell(i);
    }
    return os;
}

std::istream& operator>>(std::istream& is, TuringTape& tape){
    char c;
    int index = 0;
    while(is.get(c) && c != '\n') {
        if(c !=' ' && c != '\r'){
            tape.setCell(index++, c);
        }
    }
    return is;
}


bool TuringProgram::Rule::operator==(const Rule &other) const{
    return currentState == other.currentState && currentSymbol == other.currentSymbol && newState == other.newState && newSymbol == other.newSymbol && move == other.move;
}

void TuringProgram::addRule(const Rule& rule) {
    rules.push_back(rule);
}

void TuringProgram::removeRule(std::size_t index){
    if(index < rules.size()){
        rules.erase(rules.begin() + index);
    }
}

void TuringProgram::clear(){
    rules.clear();
}

const std::vector<TuringProgram::Rule>& TuringProgram::getRules() const{
    return rules;
}

std::ostream& operator<<(std::ostream& os, const TuringProgram& program){
    for(const auto& rule : program.getRules()){
        os << rule.currentState << " " << rule.currentSymbol << " -> " << rule.newState << " " << rule.newSymbol << " " << rule.move << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, TuringProgram& program){
    program.clear();
    std::string line;
    while(std::getline(is, line)){
        if(line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        TuringProgram::Rule rule{};
        std::string arrow;

        if(iss >> rule.currentState >> rule.currentSymbol >> arrow >> rule.newState >> rule.newSymbol >> rule.move){
            if(arrow == "->"){
                program.addRule(rule);
            }
        }
    }
    return is;
}

void TuringMachine::operator++(){
    ++carriage;
}

void TuringMachine::operator--(){
    --carriage;
}

void TuringMachine::loadTape(std::istream& is){
    is >> tape;
}

void TuringMachine::loadProgram(std::istream& is){
    is >> program;
}

void TuringMachine::step() {
    if (halted) return;

    char currentChar = tape.getCell(carriage);

    auto it = std::find_if(program.getRules().begin(), program.getRules().end(),
        [&](const TuringProgram::Rule& rule) {
            return rule.currentState == state && rule.currentSymbol == currentChar;
        });

    if (it != program.getRules().end()) {
        tape.setCell(carriage, it->newSymbol);
        state = it->newState;
        if (it->move == 'R') { ++(*this); }
        else if (it->move == 'L') { --(*this); }
        else if (it->move == 'S' || it->move == 'N') { /* stay */ }
    } else {
        halted = true;
    }
}

void TuringMachine::run(bool log){
    int stepCount = 0;
    const int MAX_STEPS = 10000;

    while(!halted && stepCount < MAX_STEPS){
        if(log){
            std::cout << "Шаг" << stepCount << ":";
            printState();
            std::cout << "\n";
        }
        step();
        stepCount++;
    }

    if(log){
        std::cout << "Финальное состояние: ";
        printState();
        std::cout << "\n";
    }
}

void TuringMachine::printState() const{
    std::cout << "Состояние: " << state << " | Каретка: " << carriage << " | Лента: ";

    for(int i = carriage - VIEW_RADIUS; i <= carriage + VIEW_RADIUS; i++){
        if(i == carriage){
            std::cout << "[" << tape.getCell(i) << "]";
        }
        else{
            std::cout << tape.getCell(i);
        }
    }
}
