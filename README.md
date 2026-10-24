# Лабораторная работа №1: Машины Поста и Тьюринга

## О проекте
Данный проект реализует абстрактные машины Поста и Тьюринга на языке C++ (стандарт C++17).
Программа поддерживает загрузку начального состояния ленты и правил из файла, пошаговое выполнение, режим логирования, а также интерактивное меню для управления.
В проекте настроены юнит-тесты (Catch2), генерация документации (Doxygen), подсчет покрытия кода (lcov) и CI/CD (GitHub Actions).

## Структура проекта
- `lab1/app/` — исходный код интерактивного меню (`main.cpp`).
- `lab1/include/` — заголовочные файлы классов (`Post.h`, `Turing.h`).
- `lab1/src/` — реализация логики машин (`Post.cpp`, `Turing.cpp`).
- `lab1/tests/` — юнит-тесты и тестовые файлы для запуска.


## Сборка проекта
Выполните следующие команды из папки `lab1`:
- `cmake -S . -B build`
- `cmake --build build`

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON`
- `cmake --build build --target coverage`

## Запуск проекта
- `./build/lab1_app tests/test_post.txt -log`
- `./build/lab1_app tests/test_turing.txt -log`

## Запуск проекта из любой точки
- `./lab1_app /home/f1lya2/PPOIS/PPOIS_labs/lab1/tests/test_post.txt -log`

## Запуск тестов
- `./build/lab1_tests`

## Проверка покрытия кода (локально)

- `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON`
- `cmake --build build`

- `./build/lab1_tests`

- `cd build`


## Генерация документации
- `doxygen Doxyfile`
- `xdg-open docs/html/index.html`

## Принятие файла исполняемым
- `chmod +x lab1_app`

