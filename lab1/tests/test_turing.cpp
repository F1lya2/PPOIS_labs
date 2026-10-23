#include <catch2/catch_test_macros.hpp>
#include "Turing.h"
#include <sstream>

TEST_CASE("TuringTape: базовые операции") {
    TuringTape tape('_');
    REQUIRE(tape.getCell(0) == '_');

    tape.setCell(0, 'A');
    REQUIRE(tape.getCell(0) == 'A');
}

TEST_CASE("TuringProgram: парсинг") {
    TuringProgram prog;
    std::istringstream input("q0 A -> q1 B R\n");

    input >> prog;
    REQUIRE(prog.getRules().size() == 1);
    REQUIRE(prog.getRules()[0].currentState == "q0");
    REQUIRE(prog.getRules()[0].move == 'R');
}

TEST_CASE("TuringMachine: команда Stay (S)") {
    TuringMachine machine;
    std::istringstream tapeData("A");
    machine.loadTape(tapeData);

    TuringProgram::Rule r{"q0", 'A', "q1", 'B', 'S'};
    machine.addRule(r);

    machine.step();


    REQUIRE(machine.getState() == "q1");
    REQUIRE(machine.getCarriage() == 0);
}
