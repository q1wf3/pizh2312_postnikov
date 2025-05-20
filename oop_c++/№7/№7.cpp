#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Employee {
protected:
    std::string name;
    
public:
    Employee(std::string n) : name(n) {}
    
    virtual void printInfo() const = 0;
    
    // Операторы сравнения для min() и max()
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
    CurrentEmployee(std::string n = "Неизвестно") : Employee(n) {}
    
    void printInfo() const override {
        std::cout << name << " (Текущий сотрудник)" << std::endl;
    }
};

class FormerEmployee : public Employee {
public:
    FormerEmployee(std::string n = "Неизвестно") : Employee(n) {}
    
    void printInfo() const override {
        std::cout << name << " (Бывший сотрудник)" << std::endl;
    }
};

// Шаблонный класс Array
template <typename T>
class Array {
private:
    std::vector<T> elements;

public:
    // Конструктор с заданным размером
    Array(size_t n) {
        elements.reserve(n);
    }

    // Добавление элемента
    void add(const T& element) {
        elements.push_back(element);
    }

    // Получение элемента по индексу
    T& get(size_t index) {
        if (index >= elements.size()) {
            throw std::out_of_range("Индекс вне диапазона");
        }
        return elements[index];
    }

    // Поиск минимального элемента
    T min() const {
        if (elements.empty()) {
            throw std::runtime_error("Массив пуст");
        }
        return *std::min_element(elements.begin(), elements.end());
    }

    // Поиск максимального элемента
    T max() const {
        if (elements.empty()) {
            throw std::runtime_error("Массив пуст");
        }
        return *std::max_element(elements.begin(), elements.end());
    }
};

int main() {
    // Демонстрация работы шаблонного класса

    // 1. Для типа int
    Array<int> intArray(3);
    intArray.add(5);
    intArray.add(2);
    intArray.add(8);
    std::cout << "Минимальное int: " << intArray.min() << std::endl;
    std::cout << "Максимальное int: " << intArray.max() << std::endl;

    // 2. Для типа char
    Array<char> charArray(3);
    charArray.add('c');
    charArray.add('a');
    charArray.add('b');
    std::cout << "Минимальное char: " << charArray.min() << std::endl;
    std::cout << "Максимальное char: " << charArray.max() << std::endl;

    // 3. Для указателей на Employee
    Array<Employee*> empArray(3);
    CurrentEmployee ce1("Иван");
    FormerEmployee fe1("Петр");
    CurrentEmployee ce2("Алексей");
    
    empArray.add(&ce1);
    empArray.add(&fe1);
    empArray.add(&ce2);
    std::cout << "Сотрудник с минимальным именем: ";
    empArray.min()->printInfo();
    std::cout << "Сотрудник с максимальным именем: ";
    empArray.max()->printInfo();

    // 4. Для CurrentEmployee
    Array<CurrentEmployee> currentEmpArray(2);
    currentEmpArray.add(CurrentEmployee("Дмитрий"));
    currentEmpArray.add(CurrentEmployee("Борис"));
    std::cout << "Текущий сотрудник с минимальным именем: ";
    currentEmpArray.min().printInfo();
    std::cout << "Текущий сотрудник с максимальным именем: ";
    currentEmpArray.max().printInfo();

    return 0;
}