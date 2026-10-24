#include <catch2/catch_test_macros.hpp>
#include "Post.h"
#include <sstream>

TEST_CASE("PostTape: конструктор, чтение/запись, пустые ячейки") {
    PostTape tape('0');
    REQUIRE(tape.getCell(5) == '0');

    tape.setCell(5, '1');
    REQUIRE(tape.getCell(5) == '1');

    tape.setCell(-1, '1');
    REQUIRE(tape.getCell(-1) == '1');
}

TEST_CASE("PostTape: операторы сравнения") {
    PostTape t1('0');
    PostTape t2('0');
    REQUIRE(t1 == t2);
    REQUIRE_FALSE(t1 != t2);

    t1.setCell(0, '1');
    REQUIRE(t1 != t2);
    REQUIRE_FALSE(t1 == t2);
}

TEST_CASE("PostTape: перегрузка ввода/вывода") {
    PostTape tape('0');
    std::istringstream input("1 0 1\n");
    input >> tape;

    std::ostringstream output;
    output << tape;
    REQUIRE(output.str() == "101");

    PostTape emptyTape('0');
    std::ostringstream emptyOut;
    emptyOut << emptyTape;
    REQUIRE(emptyOut.str() == "0");
}

TEST_CASE("PostProgram: Rule сравнение") {
    PostProgram::Rule r1{1, '1', 2, '0', 'R'};
    PostProgram::Rule r2{1, '1', 2, '0', 'R'};
    PostProgram::Rule r3{1, '1', 2, '0', 'L'};

    REQUIRE(r1 == r2);
    REQUIRE_FALSE(r1 == r3);
}

TEST_CASE("PostProgram: управление правилами и вывод") {
    PostProgram prog;
    prog.addRule({1, '1', 2, '0', 'R'});
    prog.addRule({2, '0', 3, '1', 'L'});

    REQUIRE(prog.getRules().size() == 2);

    std::ostringstream out;
    out << prog;
    REQUIRE(out.str() == "1 1 -> 2 0 R\n2 0 -> 3 1 L\n");

    prog.removeRule(5);
    prog.removeRule(0);
    REQUIRE(prog.getRules().size() == 1);

    prog.clear();
    REQUIRE(prog.getRules().empty());
}

TEST_CASE("PostProgram: перегрузка ввода") {
    PostProgram prog;
    std::istringstream input("1 1 -> 2 0 R\n2 0 -> 2 0 N\n");
    input >> prog;

    REQUIRE(prog.getRules().size() == 2);
}

TEST_CASE("PostMachine: каретка и геттеры") {
    PostMachine m;
    REQUIRE(m.getState() == 1);
    REQUIRE(m.getCarriage() == 0);

    m.operator++();
    REQUIRE(m.getCarriage() == 1);

    m.operator--();
    REQUIRE(m.getCarriage() == 0);
}

TEST_CASE("PostMachine: загрузка, печать и шаг") {
    PostMachine m;
    std::istringstream tapeInput("1 0");
    m.loadTape(tapeInput);

    std::istringstream progInput("1 1 -> 2 0 R\n");
    m.loadProgram(progInput);

    m.printRules();
    m.printState();

    m.step();
    REQUIRE(m.getState() == 2);
    REQUIRE(m.getCarriage() == 1);

    m.step();
}

TEST_CASE("PostMachine: run с логом и без") {
    PostMachine m;
    std::istringstream tapeInput("1 1");
    m.loadTape(tapeInput);
    m.addRule({1, '1', 1, '0', 'R'});

    m.run(false);
    REQUIRE(m.getCarriage() == 2);

    PostMachine m2;
    std::istringstream tapeInput2("1");
    m2.loadTape(tapeInput2);
    m2.addRule({1, '1', 1, '0', 'R'});
    m2.run(true);
    REQUIRE(m2.getCarriage() == 1);
}
