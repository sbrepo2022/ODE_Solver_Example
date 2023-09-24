# Реализация методов Адамса-Башфорда 2-го порядка и Рунге-Кутты 4-го порядка для интегрирования системы ОДУ

В данном примере реализуются методы Адамса-Башфорда 2-го порядка и Рунге-Кутты 4-го порядка. Методы загружаются из динамических библиотек (dll), располагающихся в рабочей директории программы (совпадает с расположением программы).

# Инструкция для запуска

## Зависимости для сборки

1) Windows
2) Компилятор MSVC с поддержкой C++ 17
3) CMake

## Клонирование репозитория

```sh
git clone https://github.com/sbrepo2022/ODE_Solver_Example.git
```

## Сборка

В корневой директории проекта:

```sh
sh ./build.sh
```

## Запуск

В корневой директогрии проекта:

```sh
./install/bin/mmps_lab1.exe
```

## Результат

Результатом будет выведен в csv файлы, которые будут находиться в `install/bin`.

Построить графики можно в google colab: https://colab.research.google.com/drive/1opzAwT0v-qaq6LOABiVlKclVS7sGX0-Z?usp=sharing

Необходимо скопировать блокнот и загрузить полученные csv файлы в папку `content` (она открыта по умолчанию в панели проводника)