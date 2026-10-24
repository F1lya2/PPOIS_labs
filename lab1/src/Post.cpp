#include "../include/Post.h"
#include <sstream>
#include <algorithm>

PostTape::PostTape(char blankSymbol) : blank(blankSymbol) {}

void PostTape::setCell(int index, char value){
    cells[index] = value;
}

char PostTape::getCell(int index) const{
    auto it = cells.find(index);
    if (it !=cells.end()){
        return it->second;
    }
    return blank;
}

bool PostTape::operator==(const PostTape& other) const{
    return cells == other.cells && blank == other.blank;
}

bool PostTape::operator!=(const PostTape& other) const{
    return !(*this==other);
}

std::ostream& operator<<(std::ostream& os, const PostTape& tape){
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

std::istream& operator>>(std::istream& is, PostTape& tape){
    char c;
    int index = 0;
    while(is.get(c) && c!='\n'){
        if(c != ' ' && c!= '\r'){
            tape.setCell(index++, c);
        }
    }
    return is;
}

bool PostProgram::Rule::operator==(const Rule& other) const{
    return currentState == other.currentState &&
        currentSymbol == other.currentSymbol &&
        newState == other.newState &&
        newSymbol == other.newSymbol &&
        move == other.move;
}

void PostProgram::addRule(const Rule& rule){
    rules.push_back(rule);
}

void PostProgram::removeRule(std::size_t index){
    if(index< rules.size()){
        rules.erase(rules.begin() + index);
    }
}

void PostProgram::clear(){
    rules.clear();
}

const std::vector<PostProgram::Rule>& PostProgram::getRules() const{
    return rules;
}

std::ostream& operator<<(std::ostream& os, const PostProgram& program){
    for(const auto& rule : program.getRules()){
        os << rule.currentState << " " << rule.currentSymbol << " -> " << rule.newState << " " << rule.newSymbol << " " << rule.move << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, PostProgram& program) {
    program.clear();
    std::string line;
    while (std::getline(is, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        PostProgram::Rule rule;
        std::string arrow;

        if (iss >> rule.currentState >> rule.currentSymbol >> arrow
                >> rule.newState >> rule.newSymbol >> rule.move) {
            if (arrow == "->") {
                program.addRule(rule);
            }
        }
    }
    return is;
}

void PostMachine::operator++(){
    ++carriage;
}

void PostMachine::operator--(){
    --carriage;
}

void PostMachine::loadTape(std::istream& is){
    is >> tape;
}

void PostMachine::loadProgram(std::istream& is) {
    is >> program; // Просто вызываем нашу перегрузку оператора!
}

void PostMachine::step() {
    if (halted) return;

    char currentChar = tape.getCell(carriage);

    auto it = std::find_if(program.getRules().begin(), program.getRules().end(),
        [&](const PostProgram::Rule& rule) {
            return rule.currentState == state && rule.currentSymbol == currentChar;
        });

    if (it != program.getRules().end()) {
        tape.setCell(carriage, it->newSymbol);
        state = it->newState;
        if (it->move == 'R') { ++(*this); }
        else if (it->move == 'L') { --(*this); }
    } else {
        halted = true;
    }
}

void PostMachine::run(bool log){
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

void PostMachine::printState() const{
    std::cout << "Состояние: " << state << " | Каретка: " << carriage << " | Лента: ";

    for(int i = carriage - VIEW_RADIUS; i<= carriage + VIEW_RADIUS; i++){
        if(i == carriage){
            std::cout << "[" << tape.getCell(i) << "]";
        }
        else{
            std::cout << tape.getCell(i);
        }
    }
}
