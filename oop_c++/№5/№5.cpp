#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Employee {
private:
    static int count; // Статический счетчик объектов
    
protected:  // Изменили private на protected для доступа в наследниках
    std::string name;
    std::string position;
    std::string hire_date;

public:
    Employee(std::string n, std::string p, std::string h)
        : name(n), position(p), hire_date(h) {
        count++;
    }

    virtual ~Employee() {
        count--;
    }

    static int getCount() {
        return count;
    }

    virtual void printInfo() const = 0;
};

int Employee::count = 0;

class CurrentEmployee : public Employee {
public:
    double salary;

    CurrentEmployee(std::string n, std::string p, std::string h, double s)
        : Employee(n, p, h), salary(s) {}

    void printInfo() const override {
        std::cout << name << " (" << position << "), работает с " << hire_date 
                  << ", зарплата: " << salary << std::endl;
    }
};

class FormerEmployee : public Employee {
public:
    std::string fire_date;
    std::string reason;

    FormerEmployee(std::string n, std::string p, std::string h, 
                  std::string f, std::string r)
        : Employee(n, p, h), fire_date(f), reason(r) {}

    void printInfo() const override {
        std::cout << name << " (" << position << "), работал с " << hire_date
                  << " по " << fire_date << ", причина: " << reason << std::endl;
    }
};

class Department {
private:
    static int stored_count;
    
    std::string name;
    std::vector<std::unique_ptr<Employee>> employees;

public:
    Department(std::string n) : name(n) {}

    static int getStoredCount() {
        return stored_count;
    }

    void addEmployee(std::unique_ptr<Employee> emp) {
        employees.push_back(std::move(emp));
        stored_count++;
    }

    void printAll() const {
        std::cout << "Отдел: " << name << "\nСотрудники:\n";
        for (const auto& emp : employees) {
            emp->printInfo();
        }
    }

    ~Department() {
        stored_count -= employees.size();
    }
};

int Department::stored_count = 0;

int main() {
    std::cout << "Объектов Employee до создания: " << Employee::getCount() << std::endl;
    std::cout << "Объектов в отделах: " << Department::getStoredCount() << std::endl;

    Department it("IT");
    it.addEmployee(std::make_unique<CurrentEmployee>(
        "Иван Иванов", "Программист", "2020-01-15", 100000));
    it.addEmployee(std::make_unique<FormerEmployee>(
        "Петр Петров", "Менеджер", "2018-03-10", "2023-01-20", "Уход"));

    std::cout << "\nПосле создания объектов:\n";
    std::cout << "Всего объектов Employee: " << Employee::getCount() << std::endl;
    std::cout << "Объектов в отделах: " << Department::getStoredCount() << std::endl;

    std::cout << "\nИнформация об отделе:\n";
    it.printAll();

    return 0;
}