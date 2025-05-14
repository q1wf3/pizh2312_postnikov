#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Базовый класс (дополнительный из лаб. работы №1)
class Employee {
protected:
    std::string name;
    std::string position;
    std::string hire_date;

public:
    Employee(std::string n, std::string p, std::string h) 
        : name(n), position(p), hire_date(h) {}

    virtual ~Employee() {
        std::cout << "Деструктор Employee для " << name << std::endl;
    }

    // Чисто виртуальная функция
    virtual void printFullInfo() const = 0;

    void printBasicInfo() const {
        std::cout << "Имя: " << name << ", Должность: " << position 
                  << ", Дата приема: " << hire_date;
    }
};

// Классы-наследники (из лаб. работы №3)
class CurrentEmployee : public Employee {
private:
    double salary;

public:
    CurrentEmployee(std::string n, std::string p, std::string h, double s) 
        : Employee(n, p, h), salary(s) {}

    ~CurrentEmployee() {
        std::cout << "Деструктор CurrentEmployee для " << name << std::endl;
    }

    void printFullInfo() const override {
        printBasicInfo();
        std::cout << ", Зарплата: " << salary << std::endl;
    }
};

class FormerEmployee : public Employee {
private:
    std::string fire_date;
    std::string reason;

public:
    FormerEmployee(std::string n, std::string p, std::string h, 
                  std::string f, std::string r) 
        : Employee(n, p, h), fire_date(f), reason(r) {}

    ~FormerEmployee() {
        std::cout << "Деструктор FormerEmployee для " << name << std::endl;
    }

    void printFullInfo() const override {
        printBasicInfo();
        std::cout << ", Дата увольнения: " << fire_date 
                  << ", Причина: " << reason << std::endl;
    }
};

// Основной класс (из лаб. работы №1)
class Department {
private:
    std::string name;
    std::string phone;
    std::vector<std::unique_ptr<Employee>> employees;

public:
    Department(std::string n, std::string p) : name(n), phone(p) {}

    void addEmployee(std::unique_ptr<Employee> emp) {
        employees.push_back(std::move(emp));
    }

    void printDepartmentInfo() const {
        std::cout << "Отдел: " << name << ", Телефон: " << phone << std::endl;
        std::cout << "Сотрудники:" << std::endl;
        for (const auto& emp : employees) {
            emp->printFullInfo();
        }
    }
};

int main() {
    //Массив объектов базового класса
    std::vector<std::unique_ptr<Employee>> employees;
    employees.push_back(std::make_unique<CurrentEmployee>("Иван Иванов", "Программист", "2020-01-15", 100000));
    employees.push_back(std::make_unique<FormerEmployee>("Петр Петров", "Менеджер", "2018-03-10", "2023-01-20", "Увольнение"));
    employees.push_back(std::make_unique<CurrentEmployee>("Мария Сидорова", "Дизайнер", "2021-11-15", 90000));

    //Вывод данных (полиморфизм)
    std::cout << "=== Вывод массива сотрудников ===" << std::endl;
    for (const auto& emp : employees) {
        emp->printFullInfo();
    }

    //Демонстрация работы с Department
    Department dev("Разработка", "123-45-67");
    dev.addEmployee(std::make_unique<CurrentEmployee>("Алексей Алексеев", "Тестировщик", "2022-06-01", 80000));
    dev.addEmployee(std::make_unique<FormerEmployee>("Ольга Петрова", "Аналитик", "2019-05-20", "2023-02-15", "Собственное желание"));

    std::cout << "\n=== Информация об отделе ===" << std::endl;
    dev.printDepartmentInfo();

    return 0;
}
