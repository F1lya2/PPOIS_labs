#include <catch2/catch_test_macros.hpp>
#include "Post.h"
#include <sstream>

TEST_CASE("PostTape: запись и чтение") {
    PostTape tape('0');
    REQUIRE(tape.getCell(0) == '0');

    tape.setCell(0, '1');
    REQUIRE(tape.getCell(0) == '1');

    std::ostringstream oss;
    oss << tape;
    REQUIRE(oss.str() == "1");
}

TEST_CASE("PostProgram: парсинг из потока") {
    PostProgram prog;
    std::istringstream input("1 1 -> 2 0 R\n2 0 -> 2 0 N\n");

    input >> prog;

    REQUIRE(prog.getRules().size() == 2);
    REQUIRE(prog.getRules()[0].currentState == 1);
    REQUIRE(prog.getRules()[0].currentSymbol == '1');
    REQUIRE(prog.getRules()[0].move == 'R');
}

TEST_CASE("PostMachine: выполнение одного шага") {
    PostMachine machine;
    std::istringstream tapeData("1 1");
    machine.loadTape(tapeData);


    PostProgram::Rule r{1, '1', 2, '0', 'R'};
    machine.addRule(r);

    machine.step();

    REQUIRE(machine.getState() == 2);
    REQUIRE(machine.getCarriage() == 1);
}
