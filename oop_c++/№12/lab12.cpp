#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

class Employee {
protected:
    std::string name;
    std::string position;
    std::string hire_date;

public:
    Employee(std::string n, std::string p, std::string h) 
        : name(n), position(p), hire_date(h) {}

    virtual void printInfo() const {
        std::cout << name << " (" << position << ") с " << hire_date;
    }

    std::string getName() const { return name; }
    std::string getPosition() const { return position; }
    std::string getHireDate() const { return hire_date; }
};

class CurrentEmployee : public Employee {
    double salary;
public:
    CurrentEmployee(std::string n, std::string p, std::string h, double s) 
        : Employee(n, p, h), salary(s) {}

    void printInfo() const override {
        Employee::printInfo();
        std::cout << ", зарплата: " << salary;
    }
};

class FormerEmployee : public Employee {
    std::string fire_date;
    std::string reason;
public:
    FormerEmployee(std::string n, std::string p, std::string h, 
                 std::string f, std::string r) 
        : Employee(n, p, h), fire_date(f), reason(r) {}

    void printInfo() const override {
        Employee::printInfo();
        std::cout << ", уволен " << fire_date << " (" << reason << ")";
    }
};

int main() {
    // 1. Создание и заполнение контейнера
    std::vector<Employee*> employees = {
        new CurrentEmployee("Петр Петров", "Менеджер", "2021-03-10", 50000),
        new FormerEmployee("Сергей Сергеев", "Аналитик", "2019-05-20", "2023-02-15", "Собственное желание"),
        new CurrentEmployee("Дмитрий Дмитриев", "Инженер", "2020-07-01", 55000),
        new Employee("Иван Иванов", "Программист", "2020-01-15"),
        new FormerEmployee("Ольга Петрова", "Бухгалтер", "2018-03-10", "2023-01-20", "Увольнение")
    };

    // 2. Сортировка по убыванию с использованием лямбда-функции
    std::sort(employees.begin(), employees.end(), 
        [](const Employee* a, const Employee* b) {
            return a->getName() > b->getName();
        });

    // 3. Поиск и перемещение менеджеров с использованием лямбда-функции
    std::list<Employee*> managers;
    std::string target_position = "Менеджер";
    
    auto it = std::remove_if(employees.begin(), employees.end(),
        [&](Employee* emp) {
            if (emp->getPosition() == target_position) {
                managers.push_back(emp);
                return true;
            }
            return false;
        });
    
    employees.erase(it, employees.end());

    // 4. Сортировка по возрастанию с использованием лямбда-функций
    std::sort(employees.begin(), employees.end(),
        [](const Employee* a, const Employee* b) {
            return a->getName() < b->getName();
        });

    managers.sort([](const Employee* a, const Employee* b) {
        return a->getName() < b->getName();
    });

    // 5. Вывод результатов с использованием лямбда-функции
    auto printEmployee = [](const Employee* emp) {
        emp->printInfo();
        std::cout << std::endl;
    };

    std::cout << "=== Основные сотрудники ===\n";
    std::for_each(employees.begin(), employees.end(), printEmployee);

    std::cout << "\n=== Менеджеры ===\n";
    std::for_each(managers.begin(), managers.end(), printEmployee);

    // Очистка памяти
    std::for_each(employees.begin(), employees.end(), [](Employee* emp) { delete emp; });
    std::for_each(managers.begin(), managers.end(), [](Employee* emp) { delete emp; });

    // 6. Выводы
    std::cout << "\n=== Выводы ===\n";
    std::cout << "1. Все алгоритмы (сортировка, поиск, удаление, обход) реализованы с использованием лямбда-функций\n";
    std::cout << "2. Лямбда-функции обеспечивают более компактный и локализованный код\n";
    std::cout << "3. Использование лямбд упрощает передачу контекста (например, target_position)\n";
    std::cout << "4. Код стал более читаемым и модульным благодаря лямбда-выражениям\n";

    return 0;
}