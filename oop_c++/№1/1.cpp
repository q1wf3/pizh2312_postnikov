#include <iostream>
#include <string>
#include <vector>

class Employee {
private:
    std::string __name;
    std::string __position;
    std::string __hire_date;

public:
    Employee(std::string name, std::string position, std::string hire_date) :
        __name(name), __position(position), __hire_date(hire_date) {}

    std::string getName() const {
        return __name;
    }

    std::string getPosition() const {
        return __position;
    }

    std::string getHireDate() const {
        return __hire_date;
    }

    void setName(std::string newName) {
        __name = newName;
    }

    void setPosition(std::string newPosition) {
        __position = newPosition;
    }

    void setHireDate(std::string newHireDate) {
        __hire_date = newHireDate;
    }

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee) {
        os << "Имя: " << employee.__name << ", Должность: " << employee.__position
           << ", Дата приема: " << employee.__hire_date;
        return os;
    }
};

class Department {
private:
    std::string __name;
    std::string __phone;
    std::vector<Employee> __employees;

public:
    Department(std::string name, std::string phone) :
        __name(name), __phone(phone) {}

    std::string getName() const {
        return __name;
    }

    std::string getPhone() const {
        return __phone;
    }

    void setName(std::string newName) {
        __name = newName;
    }

    void setPhone(std::string newPhone) {
        __phone = newPhone;
    }

    void addEmployee(const Employee& employee) {
        __employees.push_back(employee);
    }

    // Overloaded setInfo methods
    void setInfo(std::string name, std::string phone) {
        __name = name;
        __phone = phone;
    }

    void setInfo(std::string name, int phone_indicator ) { //Изменили тип
        __name = name;
    }

    void setInfo(int phone_indicator , std::string phone) { //Изменили тип
        __phone = phone;
    }

    void displayDepartmentInfo() const {
        std::cout << "Отдел: " << __name << ", Телефон: " << __phone << std::endl;
        std::cout << "Список сотрудников:" << std::endl;
        for (const auto& employee : __employees) {
            std::cout << employee << std::endl;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Department& department) {
        os << "Отдел: " << department.__name << ", Телефон: " << department.__phone << std::endl;
        os << "Список сотрудников:" << std::endl;
        for (const auto& employee : department.__employees) {
            os << employee << std::endl;
        }
        return os;
    }
};

int main() {
    Department department("Отдел разработки", "123-45-67");
    department.setInfo("Новый отдел разработки", 1); //Использовали новую сигнатуру

    Employee employee1("Иван Иванов", "Программист", "2022-01-15");
    Employee employee2("Петр Петров", "Тестировщик", "2023-03-10");

    department.addEmployee(employee1);
    department.addEmployee(employee2);

    department.displayDepartmentInfo();

    return 0;
}