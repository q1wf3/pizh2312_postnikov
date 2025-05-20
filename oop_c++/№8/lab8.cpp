#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

// Пользовательские классы исключений
class EmployeeException : public std::runtime_error {
public:
    explicit EmployeeException(const std::string& msg) : std::runtime_error(msg) {}
};

class SalaryException : public std::invalid_argument {
public:
    explicit SalaryException(const std::string& msg) : std::invalid_argument(msg) {}
};

class Employee {
protected:
    std::string name;
    double salary;
    
public:
    Employee(std::string n, double s = 0) : name(std::move(n)), salary(s) {
        if (s < 0) throw SalaryException("Отрицательная зарплата: " + std::to_string(s));
    }
    
    virtual void printInfo() const = 0;
    
    bool operator<(const Employee& other) const {
        return name < other.name;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
};

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    emp.printInfo();
    return os;
}

class CurrentEmployee : public Employee {
public:
    CurrentEmployee(std::string n = "Неизвестно", double s = 0) : Employee(std::move(n), s) {}
    
    void printInfo() const override {
        std::cout << name << " (Текущий сотрудник, зарплата: " << salary << ")" << std::endl;
    }
};

class FormerEmployee : public Employee {
public:
    FormerEmployee(std::string n = "Неизвестно", double s = 0) : Employee(std::move(n), s) {}
    
    void printInfo() const override {
        std::cout << name << " (Бывший сотрудник, зарплата: " << salary << ")" << std::endl;
    }
};

template <typename T>
class Array {
private:
    std::vector<T> elements;

public:
    explicit Array(size_t n) {
        if (n > 100) throw std::length_error("Слишком большой размер массива");
        elements.reserve(n);
    }

    void add(const T& element) {
        if (elements.size() >= elements.capacity()) {
            throw std::out_of_range("Массив переполнен");
        }
        elements.push_back(element);
    }

    T& get(size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return elements[index];
    }

    T min() const {
        if (elements.empty()) {
            throw EmployeeException("Попытка найти минимум в пустом массиве");
        }
        return *std::min_element(elements.begin(), elements.end());
    }

    T max() const {
        if (elements.empty()) {
            throw std::runtime_error("Попытка найти максимум в пустом массиве");
        }
        return *std::max_element(elements.begin(), elements.end());
    }
};

void processEmployees() {
    try {
        Array<Employee*> empArray(3);
        CurrentEmployee ce1("Иван", 50000);
        FormerEmployee fe1("Петр", 30000); // Исправлено: положительная зарплата
        CurrentEmployee ce2("Алексей", 60000);
        
        empArray.add(&ce1);
        empArray.add(&fe1);
        empArray.add(&ce2);
        
        // Тест выхода за границы
        empArray.get(3); // Вызовет out_of_range
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Ошибка в processEmployees: " << e.what() << std::endl;
        throw; // Перебрасываем исключение на верхний уровень
    }
}

int main() {
    try {
        // 1. Работа с int
        Array<int> intArray(3);
        intArray.add(5);
        intArray.add(2);
        intArray.add(8);
        std::cout << "Минимальное int: " << intArray.min() << std::endl;
        std::cout << "Максимальное int: " << intArray.max() << std::endl;

        // 2. Обработка исключения string
        try {
            throw std::string("Тестовое исключение string");
        }
        catch (const std::string& e) {
            std::cerr << "Поймано исключение string: " << e << std::endl;
        }

        // 3. Обработка int исключения
        try {
            throw 42;
        }
        catch (int e) {
            std::cerr << "Поймано int исключение: " << e << std::endl;
        }

        // 4. Обработка любого исключения
        try {
            throw 'a';
        }
        catch (...) {
            std::cerr << "Поймано неизвестное исключение" << std::endl;
        }

        // 5. Обработка собственных исключений
        try {
            CurrentEmployee emp("Иван", -1000); // Вызовет SalaryException
        }
        catch (const SalaryException& e) {
            std::cerr << "Ошибка зарплаты: " << e.what() << std::endl;
        }

        // 6. Вложенные исключения
        processEmployees();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Глобальная обработка out_of_range: " << e.what() << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Глобальная обработка runtime_error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Глобальная обработка стандартного исключения: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Глобальная обработка неизвестного исключения" << std::endl;
    }

    // 7. Локальная обработка без передачи наверх
    try {
        Array<char> arr(2);
        arr.add('a');
        arr.add('b');
        arr.add('c'); // Вызовет out_of_range
    }
    catch (const std::exception& e) {
        std::cerr << "Локальная обработка (без передачи): " << e.what() << std::endl;
    }

    return 0;
}