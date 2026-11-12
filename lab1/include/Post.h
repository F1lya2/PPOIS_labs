/**
 * @file Post.h
 * @brief Заголовочный файл с реализацией Машины Поста.
 * Содержит классы для работы с лентой, программой и самой машиной.
 */

#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstddef>

/**
 * @class PostTape
 * @brief Класс, представляющий бесконечную ленту Машины Поста.
 * Использует std::map для хранения ячеек, что позволяет работать
 * с отрицательными индексами и не выделять память для пустых ячеек.
 */
class PostTape {
private:
    std::map<int, char> cells; ///< Ячейки ленты (индекс -> символ)
    char blank;                ///< Символ пустой ячейки (по умолчанию '0')

public:
    /**
     * @brief Конструктор ленты.
     * @param blankSymbol Символ, обозначающий пустую ячейку (по умолчанию '0').
     */
    explicit PostTape(char blankSymbol = '0');

    PostTape(const PostTape& other) = default;
    PostTape& operator=(const PostTape& other) = default;

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

    /**
     * @brief Оператор сравнения лент.
     * @param other Другая лента.
     * @return true, если ленты идентичны.
     */
    bool operator==(const PostTape& other) const;

    /**
     * @brief Оператор неравенства лент.
     * @param other Другая лента.
     * @return true, если ленты различаются.
     */
    bool operator!=(const PostTape& other) const;

    friend std::ostream& operator<<(std::ostream& os, const PostTape& tape);
    friend std::istream& operator>>(std::istream& is, PostTape& tape);
};

/**
 * @class PostProgram
 * @brief Класс, хранящий набор правил для Машины Поста.
 */
class PostProgram {
public:
    /**
     * @struct Rule
     * @brief Структура одного правила Машины Поста.
     */
    struct Rule {
        int currentState;   ///< Текущее состояние
        char currentSymbol; ///< Текущий символ на ленте
        int newState;       ///< Новое состояние
        char newSymbol;     ///< Новый символ для записи
        char move;          ///< Движение: 'L' (влево), 'R' (вправо), 'N' (на месте)

        bool operator==(const Rule& other) const;
    };

private:
    std::vector<Rule> rules; ///< Вектор правил

public:
    PostProgram() = default;

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

    friend std::ostream& operator<<(std::ostream& os, const PostProgram& program);
    friend std::istream& operator>>(std::istream& is, PostProgram& program);
};

/**
 * @class PostMachine
 * @brief Класс, реализующий саму Машину Поста.
 */
class PostMachine {
private:
    PostTape tape;     ///< Лента машины
    PostProgram program; ///< Программа (набор правил)
    int carriage;      ///< Позиция каретки
    int state;         ///< Текущее состояние
    bool halted;       ///< Флаг остановки
    static const int VIEW_RADIUS = 3; ///< Радиус обзора ленты при выводе

public:
    PostMachine() : carriage(0), state(1), halted(false) {}

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
    void addRule(const PostProgram::Rule& rule) { program.addRule(rule); }

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
    int getState() const { return state; }

    /**
     * @brief Возвращает текущую позицию каретки.
     * @return Позиция каретки.
     */
    int getCarriage() const { return carriage; }
};
