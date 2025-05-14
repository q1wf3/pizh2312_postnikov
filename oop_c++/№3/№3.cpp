#include <iostream>
#include <string>
#include <vector>

class Employee {
protected:
    std::string name;
    std::string position;
    std::string hire_date;

public:
    Employee() : name("Неизвестно"), position("Неизвестно"), hire_date("Неизвестно") {
        std::cout << "Конструктор Employee" << std::endl;
    }

    Employee(std::string n, std::string p, std::string h) : name(n), position(p), hire_date(h) {
        std::cout << "Конструктор Employee для " << n << std::endl;
    }

    virtual ~Employee() {
        std::cout << "Деструктор Employee для " << name << std::endl;
    }

    virtual void printInfo() const {
        std::cout << "Имя: " << name << ", Должность: " << position 
                  << ", Дата приема: " << hire_date;
    }
};

class CurrentEmployee : public Employee {
private:
    double salary;

public:
    CurrentEmployee(std::string n, std::string p, std::string h, double s) 
        : Employee(n, p, h), salary(s) {
        std::cout << "Конструктор CurrentEmployee для " << n << std::endl;
    }

    ~CurrentEmployee() {
        std::cout << "Деструктор CurrentEmployee для " << name << std::endl;
    }

    void printInfo() const override {
        Employee::printInfo();
        std::cout << ", Зарплата: " << salary;
    }
};

class FormerEmployee : public Employee {
private:
    std::string fire_date;
    std::string reason;

public:
    FormerEmployee(std::string n, std::string p, std::string h, 
                  std::string f, std::string r) 
        : Employee(n, p, h), fire_date(f), reason(r) {
        std::cout << "Конструктор FormerEmployee для " << n << std::endl;
    }

    ~FormerEmployee() {
        std::cout << "Деструктор FormerEmployee для " << name << std::endl;
    }

    void printInfo() const override {
        Employee::printInfo();
        std::cout << ", Дата увольнения: " << fire_date 
                  << ", Причина: " << reason;
    }
};

int main() {
    // Создание объектов разных типов
    std::cout << "\n=== Создание объектов ===" << std::endl;
    Employee emp1("Иван Иванов", "Программист", "2020-01-15");
    CurrentEmployee emp2("Петр Петров", "Менеджер", "2021-03-10", 50000);
    FormerEmployee emp3("Сергей Сергеев", "Аналитик", "2019-05-20", "2023-02-15", "Собственное желание");

    // Вывод информации
    std::cout << "\n=== Информация о сотрудниках ===" << std::endl;
    emp1.printInfo(); std::cout << std::endl;
    emp2.printInfo(); std::cout << std::endl;
    emp3.printInfo(); std::cout << std::endl;

    // Массив базового класса
    std::cout << "\n=== Массив Employee ===" << std::endl;
    Employee* employees[3];
    employees[0] = new Employee("Алексей Алексеев", "Тестировщик", "2022-06-01");
    employees[1] = new CurrentEmployee("Мария Иванова", "Дизайнер", "2021-09-15", 45000);
    employees[2] = new FormerEmployee("Ольга Петрова", "Бухгалтер", "2018-03-10", "2023-01-20", "Увольнение");

    for (int i = 0; i < 3; i++) {
        employees[i]->printInfo(); 
        std::cout << std::endl;
        delete employees[i];
    }

    // Массив наследника
    std::cout << "\n=== Массив CurrentEmployee ===" << std::endl;
    CurrentEmployee currentEmps[2] = {
        CurrentEmployee("Дмитрий Дмитриев", "Инженер", "2020-07-01", 55000),
        CurrentEmployee("Елена Еленова", "Маркетолог", "2021-11-20", 48000)
    };

    for (const auto& emp : currentEmps) {
        emp.printInfo(); 
        std::cout << std::endl;
    }

    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}