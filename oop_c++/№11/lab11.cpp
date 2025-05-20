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

    bool operator>(const Employee& other) const { return name > other.name; }
    bool operator<(const Employee& other) const { return name < other.name; }
    bool isPosition(const std::string& pos) const { return position == pos; }
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

    // 2. Сортировка по убыванию
    std::sort(employees.begin(), employees.end(), [](auto a, auto b) { return *a > *b; });

    // 3. Поиск и перемещение менеджеров
    std::list<Employee*> managers;
    std::string target = "Менеджер";
    for (auto it = employees.begin(); it != employees.end(); ) {
        if ((*it)->isPosition(target)) {
            managers.push_back(*it);
            it = employees.erase(it);
        } else {
            ++it;
        }
    }

    // 4. Сортировка по возрастанию
    std::sort(employees.begin(), employees.end(), [](auto a, auto b) { return *a < *b; });
    managers.sort([](auto a, auto b) { return *a < *b; });

    // 5. Вывод результатов
    std::cout << "=== Основные сотрудники ===\n";
    for (const auto& emp : employees) {
        emp->printInfo(); 
        std::cout << "\n";
    }

    std::cout << "\n=== Менеджеры ===\n";
    for (const auto& emp : managers) {
        emp->printInfo(); 
        std::cout << "\n";
    }

    // Очистка памяти
    for (auto& emp : employees) delete emp;
    for (auto& emp : managers) delete emp;

    return 0;
}