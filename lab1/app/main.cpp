#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Post.h"
#include "Turing.h"

void printMenu() {
    std::cout << "\n=== МЕНЮ ===\n";
    std::cout << "1. Загрузить программу из файла\n";
    std::cout << "2. Добавить правило\n";
    std::cout << "3. Удалить правило\n";
    std::cout << "4. Просмотреть правила\n";
    std::cout << "5. Сделать один шаг\n";
    std::cout << "6. Выполнить всю программу\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

// Очистка буфера ввода (защита от ввода букв вместо цифр)
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <файл_программы> [-log]\n";
        return 1;
    }
    std::string filename = argv[1];
    bool log = (argc >= 3 && std::string(argv[2]) == "-log");

    std::cout << "Выберите машину:\n1. Машина Поста\n2. Машина Тьюринга\n> ";
    int machineChoice;
    if (!(std::cin >> machineChoice)) {
        clearInput();
        std::cerr << "Ошибка ввода.\n";
        return 1;
    }

    PostMachine post;
    TuringMachine turing;

    // Загружаем данные из файла
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return 1;
    }

    // В зависимости от выбора загружаем и показываем меню
    if (machineChoice == 1) {
        post.loadTape(file);
        post.loadProgram(file);
        std::cout << "\n[Машина Поста успешно загружена]\n";
    } else if (machineChoice == 2) {
        turing.loadTape(file);
        turing.loadProgram(file);
        std::cout << "\n[Машина Тьюринга успешно загружена]\n";
    } else {
        std::cerr << "Неверный выбор.\n";
        return 1;
    }
    file.close();

    int choice;
    do {
        printMenu();
        if (!(std::cin >> choice)) {
            clearInput();
            std::cout << "Введите число!\n";
            continue;
        }

        if (machineChoice == 1) { // Меню для Поста
            switch (choice) {
                case 1: {
                    std::cout << "Введите путь к файлу: ";
                    std::string f; std::cin >> f;
                    std::ifstream newFile(f);
                    if (newFile.is_open()) {

                        post.loadTape(newFile);
                        post.loadProgram(newFile);
                    }
                    else std::cout << "Файл не найден.\n";
                    break;
                }
                case 2: {
                    PostProgram::Rule r;
                    std::cout << "Введите: состояние символ -> новое_состояние новый_символ R/L/N\n";
                    std::string arrow;
                    if (std::cin >> r.currentState >> r.currentSymbol >> arrow >> r.newState >> r.newSymbol >> r.move) {
                        post.addRule(r);
                        std::cout << "Правило добавлено.\n";
                    } else { clearInput(); std::cout << "Неверный формат.\n"; }
                    break;
                }
                case 3: {
                    std::size_t idx;
                    std::cout << "Введите индекс правила для удаления (с 0): "; std::cin >> idx;
                    post.removeRule(idx);
                    break;
                }
                case 4: post.printRules(); break;
                case 5: post.step(); post.printState(); std::cout << "\n"; break;
                case 6: post.run(log); break;
            }
        } else if (machineChoice == 2) { // Меню для Тьюринга
            switch (choice) {
                case 1: {
                    std::cout << "Введите путь к файлу: ";
                    std::string f; std::cin >> f;
                    std::ifstream newFile(f);
                    if (newFile.is_open()) {
                        turing.loadTape(newFile);
                        turing.loadProgram(newFile);
                    }
                    else std::cout << "Файл не найден.\n";
                    break;
                }
                case 2: {
                    TuringProgram::Rule r;
                    std::cout << "Введите: состояние символ -> новое_состояние новый_символ R/L/S\n";
                    std::string arrow;
                    if (std::cin >> r.currentState >> r.currentSymbol >> arrow >> r.newState >> r.newSymbol >> r.move) {
                        turing.addRule(r);
                        std::cout << "Правило добавлено.\n";
                    } else { clearInput(); std::cout << "Неверный формат.\n"; }
                    break;
                }
                case 3: {
                    std::size_t idx;
                    std::cout << "Введите индекс правила для удаления (с 0): "; std::cin >> idx;
                    turing.removeRule(idx);
                    break;
                }
                case 4: turing.printRules(); break;
                case 5: turing.step(); turing.printState(); std::cout << "\n"; break;
                case 6: turing.run(log); break;
            }
        }
    } while (choice != 0);

    std::cout << "Выход...\n";
    return 0;
}
