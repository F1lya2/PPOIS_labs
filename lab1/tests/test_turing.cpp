#include <catch2/catch_test_macros.hpp>
#include "Turing.h"
#include <sstream>

TEST_CASE("TuringTape: пустые ячейки, сравнение, ввод/вывод") {
    TuringTape tape('_');
    REQUIRE(tape.getCell(10) == '_');

    tape.setCell(10, 'A');
    REQUIRE(tape.getCell(10) == 'A');

    TuringTape t1('_');
    TuringTape t2('_');
    REQUIRE(t1 == t2);
    REQUIRE_FALSE(t1 != t2);

    std::istringstream in("A B _");
    in >> t1;
    REQUIRE(t1.getCell(0) == 'A');
    REQUIRE(t1.getCell(1) == 'B');
    REQUIRE(t1.getCell(2) == '_');

    std::ostringstream out;
    out << t1;
    REQUIRE(out.str() == "AB_");

    TuringTape emptyTape('_');
    std::ostringstream emptyOut;
    emptyOut << emptyTape;
    REQUIRE(emptyOut.str() == "_");
}

TEST_CASE("TuringProgram: Rule, управление правилами, ввод/вывод") {
    TuringProgram::Rule r1{"q0", 'A', "q1", 'B', 'R'};
    TuringProgram::Rule r2{"q0", 'A', "q1", 'B', 'R'};
    TuringProgram::Rule r3{"q0", 'A', "q1", 'B', 'S'};

    REQUIRE(r1 == r2);
    REQUIRE_FALSE(r1 == r3);

    TuringProgram prog;
    prog.addRule(r1);
    prog.addRule(r2);
    REQUIRE(prog.getRules().size() == 2);

    prog.removeRule(5);
    prog.removeRule(0);
    REQUIRE(prog.getRules().size() == 1);

    std::ostringstream out;
    out << prog;
    REQUIRE(out.str() == "q0 A -> q1 B R\n");

    prog.clear();
    REQUIRE(prog.getRules().empty());

    std::istringstream in("q0 A -> q1 B R\n");
    in >> prog;
    REQUIRE(prog.getRules().size() == 1);
}

TEST_CASE("TuringMachine: каретка и геттеры") {
    TuringMachine m;
    REQUIRE(m.getState() == "q0");
    REQUIRE(m.getCarriage() == 0);

    m.operator++();
    REQUIRE(m.getCarriage() == 1);

    m.operator--();
    REQUIRE(m.getCarriage() == 0);
}

TEST_CASE("TuringMachine: загрузка, печать и шаг") {
    TuringMachine m;
    std::istringstream tapeInput("A");
    m.loadTape(tapeInput);

    std::istringstream progInput("q0 A -> q1 B S\n");
    m.loadProgram(progInput);

    m.printRules();
    m.printState();

    m.step();
    REQUIRE(m.getState() == "q1");
    REQUIRE(m.getCarriage() == 0);

    m.step();
}

TEST_CASE("TuringMachine: run с логом и без") {
    TuringMachine m;
    std::istringstream tapeInput("A A");
    m.loadTape(tapeInput);
    m.addRule({"q0", 'A', "q0", 'B', 'R'});

    m.run(false);
    REQUIRE(m.getCarriage() == 2);

    TuringMachine m2;
    std::istringstream tapeInput2("A");
    m2.loadTape(tapeInput2);
    m2.addRule({"q0", 'A', "q0", 'B', 'R'});
    m2.run(true);
    REQUIRE(m2.getCarriage() == 1);
}
