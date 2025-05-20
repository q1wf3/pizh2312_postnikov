#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory> // Добавлен для unique_ptr и make_unique

using namespace std;

class Employee {
protected:
    string name;
    string position;
    string hire_date;

public:
    Employee(string n = "Неизвестно", string p = "Неизвестно", string h = "Неизвестно") 
        : name(n), position(p), hire_date(h) {}

    virtual ~Employee() = default;

    virtual void printInfo() const {
        cout << "Имя: " << name << ", Должность: " << position 
             << ", Дата приема: " << hire_date;
    }

    string getName() const { return name; }
    void setName(string n) { name = n; }
};

class CurrentEmployee : public Employee {
    double salary;

public:
    CurrentEmployee(string n = "Неизвестно", string p = "Неизвестно", 
                   string h = "Неизвестно", double s = 0) 
        : Employee(n, p, h), salary(s) {}

    void printInfo() const override {
        Employee::printInfo();
        cout << ", Зарплата: " << salary;
    }

    void setSalary(double s) { salary = s; }
};

class FormerEmployee : public Employee {
    string fire_date;
    string reason;

public:
    FormerEmployee(string n = "Неизвестно", string p = "Неизвестно", 
                  string h = "Неизвестно", string f = "Неизвестно", 
                  string r = "Неизвестно") 
        : Employee(n, p, h), fire_date(f), reason(r) {}

    void printInfo() const override {
        Employee::printInfo();
        cout << ", Дата увольнения: " << fire_date 
             << ", Причина: " << reason;
    }
};

int main() {
    // 1. Создание и заполнение контейнера стандартного типа
    vector<int> numbers = {10, 5, 8, 3, 7};
    
    // 2. Просмотр контейнера
    cout << "Исходный числовой массив:\n";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << "\n\n";

    // 3. Изменение контейнера
    numbers.erase(remove(numbers.begin(), numbers.end(), 5), numbers.end()); // Удаление элемента
    numbers[1] = 12; // Изменение элемента

    // 4. Просмотр с итераторами
    cout << "Измененный числовой массив (с итераторами):\n";
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";

    // 5. Работа с пользовательским типом
    vector<unique_ptr<Employee>> employees;
    employees.push_back(make_unique<CurrentEmployee>("Иван Иванов", "Программист", "2020-01-15", 50000));
    employees.push_back(make_unique<FormerEmployee>("Петр Петров", "Менеджер", "2018-03-10", "2023-01-20", "Уход"));
    employees.push_back(make_unique<CurrentEmployee>("Алексей Алексеев", "Тестировщик", "2021-06-01", 45000));

    // 6. Просмотр контейнера пользовательского типа
    cout << "Список сотрудников:\n";
    for (const auto& emp : employees) {
        emp->printInfo();
        cout << "\n";
    }

    // 7. Изменение контейнера пользовательского типа
    employees.erase(employees.begin() + 1); // Удаление второго сотрудника
    
    // Изменение первого сотрудника
    if (auto ce = dynamic_cast<CurrentEmployee*>(employees[0].get())) {
        ce->setName("Иван Николаев");
        ce->setSalary(55000);
    }

    // 8. Просмотр с итераторами
    cout << "\nИзмененный список сотрудников (с итераторами):\n";
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        (*it)->printInfo();
        cout << "\n";
    }

    return 0;
}