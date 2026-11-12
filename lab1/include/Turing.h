/**
 * @file Turing.h
 * @brief Заголовочный файл с реализацией Машины Тьюринга.
 * Содержит классы для работы с лентой, программой и самой машиной.
 */

#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstddef>

/**
 * @class TuringTape
 * @brief Класс, представляющий бесконечную ленту Машины Тьюринга.
 */
class TuringTape {
private:
    std::map<int, char> cells; ///< Ячейки ленты (индекс -> символ)
    char blank;                ///< Символ пустой ячейки (по умолчанию '_')

public:
    /**
     * @brief Конструктор ленты.
     * @param blankSymbol Символ, обозначающий пустую ячейку (по умолчанию '_').
     */
    explicit TuringTape(char blankSymbol = '_');

    TuringTape(const TuringTape& other) = default;
    TuringTape& operator=(const TuringTape& other) = default;

    /**
     * @brief Записывает символ в ячейку с заданным индексом.
     * @param index Индекс ячейки.
     * @param value Символ для записи.
     */
    void setCell(int index, char value);

    /**
     * @brief Читает символ из ячейки с заданным индексом.
     * @param index Индекс ячейки.
     * @return Символ из ячейки. Если ячейка пуста, возвращает blank.
     */
    char getCell(int index) const;

    bool operator==(const TuringTape& other) const;
    bool operator!=(const TuringTape& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TuringTape& tape);
    friend std::istream& operator>>(std::istream& is, TuringTape& tape);
};

/**
 * @class TuringProgram
 * @brief Класс, хранящий набор правил для Машины Тьюринга.
 */
class TuringProgram {
public:
    /**
     * @struct Rule
     * @brief Структура одного правила Машины Тьюринга.
     */
    struct Rule {
        std::string currentState; ///< Текущее состояние
        char currentSymbol;       ///< Текущий символ на ленте
        std::string newState;     ///< Новое состояние
        char newSymbol;           ///< Новый символ для записи
        char move;                ///< Движение: 'L', 'R', 'S' (Stay)

        bool operator==(const Rule& other) const;
    };

private:
    std::vector<Rule> rules; ///< Вектор правил

public:
    TuringProgram() = default;

    /**
     * @brief Добавляет новое правило в программу.
     * @param rule Правило для добавления.
     */
    void addRule(const Rule& rule);

    /**
     * @brief Удаляет правило по индексу.
     * @param index Индекс правила для удаления.
     */
    void removeRule(std::size_t index);

    /**
     * @brief Очищает список правил.
     */
    void clear();

    /**
     * @brief Возвращает константную ссылку на вектор правил.
     * @return Вектор правил.
     */
    const std::vector<Rule>& getRules() const;

    friend std::ostream& operator<<(std::ostream& os, const TuringProgram& program);
    friend std::istream& operator>>(std::istream& is, TuringProgram& program);
};

/**
 * @class TuringMachine
 * @brief Класс, реализующий саму Машину Тьюринга.
 */
class TuringMachine {
private:
    TuringTape tape;      ///< Лента машины
    TuringProgram program; ///< Программа (набор правил)
    int carriage;         ///< Позиция каретки
    std::string state;    ///< Текущее состояние
    bool halted;          ///< Флаг остановки

public:
    TuringMachine() : carriage(0), state("q0"), halted(false) {}

    /**
     * @brief Сдвигает каретку вправо.
     */
    void operator++();

    /**
     * @brief Сдвигает каретку влево.
     */
    void operator--();

    /**
     * @brief Загружает состояние ленты из потока.
     * @param is Входной поток.
     */
    void loadTape(std::istream& is);

    /**
     * @brief Загружает программу из потока.
     * @param is Входной поток.
     */
    void loadProgram(std::istream& is);

    /**
     * @brief Выполняет один шаг машины.
     */
    void step();

    /**
     * @brief Запускает машину до остановки или достижения лимита шагов.
     * @param log Если true, выводит состояние после каждого шага.
     */
    void run(bool log = false);

    /**
     * @brief Выводит текущее состояние машины в консоль.
     */
    void printState() const;

    /**
     * @brief Добавляет правило в программу (обертка для меню).
     * @param rule Правило для добавления.
     */
    void addRule(const TuringProgram::Rule& rule) { program.addRule(rule); }

    /**
     * @brief Удаляет правило по индексу (обертка для меню).
     * @param index Индекс правила.
     */
    void removeRule(std::size_t index) { program.removeRule(index); }

    /**
     * @brief Выводит все правила программы в консоль.
     */
    void printRules() const { std::cout << program; }

    /**
     * @brief Возвращает текущее состояние машины.
     * @return Текущее состояние.
     */
    std::string getState() const { return state; }

    /**
     * @brief Возвращает текущую позицию каретки.
     * @return Позиция каретки.
     */
    int getCarriage() const { return carriage; }
};
