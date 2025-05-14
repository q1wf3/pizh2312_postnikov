#include <iostream>
#include <string>
#include <vector>

class Employee {
private:
    std::string __name;
    std::string __position;
    std::string __hire_date;

public:
    // Конструктор без параметров
    Employee() : __name("Неизвестно"), __position("Неизвестно"), __hire_date("Неизвестно") {
        std::cout << "Вызван конструктор Employee без параметров" << std::endl;
    }

    // Конструктор с параметрами
    Employee(std::string name, std::string position, std::string hire_date) :
        __name(name), __position(position), __hire_date(hire_date) {
        std::cout << "Вызван конструктор Employee с параметрами для " << name << std::endl;
    }

    // Конструктор копирования
    Employee(const Employee& other) :
        __name(other.__name), __position(other.__position), __hire_date(other.__hire_date) {
        std::cout << "Вызван конструктор копирования Employee для " << other.__name << std::endl;
    }

    // Деструктор
    ~Employee() {
        std::cout << "Вызван деструктор Employee для " << __name << std::endl;
    }

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
    // Конструктор без параметров
    Department() : __name("Неизвестно"), __phone("Неизвестно") {
        std::cout << "Вызван конструктор Department без параметров" << std::endl;
    }

    // Конструктор с параметрами
    Department(std::string name, std::string phone) :
        __name(name), __phone(phone) {
        std::cout << "Вызван конструктор Department с параметрами для " << name << std::endl;
    }

    // Конструктор копирования
    Department(const Department& other) :
        __name(other.__name), __phone(other.__phone), __employees(other.__employees) {
        std::cout << "Вызван конструктор копирования Department для " << other.__name << std::endl;
    }

    // Деструктор
    ~Department() {
        std::cout << "Вызван деструктор Department для " << __name << std::endl;
    }

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

    // Новый метод - создает и добавляет сотрудника
    void createAndAddEmployee(std::string name, std::string position, std::string hire_date) {
        Employee newEmployee(name, position, hire_date);
        __employees.push_back(newEmployee);
    }

    // Новый метод - создает копии сотрудника
    void addCopiesOfEmployee(const Employee& employee, int count) {
        for (int i = 0; i < count; i++) {
            __employees.push_back(Employee(employee));
        }
    }

    void setInfo(std::string name, std::string phone) {
        __name = name;
        __phone = phone;
    }

    void setInfo(std::string name, int phone_indicator) {
        __name = name;
    }

    void setInfo(int phone_indicator, std::string phone) {
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
    // Демонстрация всех конструкторов
    
    std::cout << "\n=== Создание сотрудников ===" << std::endl;
    Employee emp1;
    Employee emp2("Алексей Алексеев", "Аналитик", "2021-05-20");
    Employee emp3(emp2); 
    
    //Конструкторы Department
    std::cout << "\n=== Создание отделов ===" << std::endl;
    Department dep1; // без параметров
    Department dep2("Отдел кадров", "987-65-43"); // с параметрами
    
    std::cout << "\n=== Использование новых методов ===" << std::endl;
    Department dep3("Тестовый отдел", "111-11-11");
    
    // Создание и добавление нового сотрудника
    dep3.createAndAddEmployee("Мария Иванова", "Дизайнер", "2023-01-10");
    
    Employee empToCopy("Сергей Сергеев", "Менеджер", "2020-11-15");
    dep3.addCopiesOfEmployee(empToCopy, 2);
    
    // Вывод информации
    std::cout << "\n=== Информация об отделах ===" << std::endl;
    dep3.displayDepartmentInfo();
    
    std::cout << "\n=== Копирование отдела ===" << std::endl;
    Department dep4(dep3);
    dep4.displayDepartmentInfo();
    
    std::cout << "\n=== Конец программы ===" << std::endl;
    return 0;
}
