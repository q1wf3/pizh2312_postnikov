#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// Базовый класс Employee
class Employee {
protected:
    string name;
    double salary;
    
public:
    Employee(const string& n = "Неизвестно", double s = 0) : name(n), salary(s) {
        if (s < 0) throw invalid_argument("Отрицательная зарплата: " + to_string(s));
    }
    
    virtual ~Employee() = default;
    
    virtual void printInfo() const = 0;
    virtual string getType() const = 0;
    
    friend ostream& operator<<(ostream& os, const Employee& emp);
    friend istream& operator>>(istream& is, Employee& emp);
};

ostream& operator<<(ostream& os, const Employee& emp) {
    os << emp.getType() << " " << emp.name << " " << emp.salary;
    return os;
}

istream& operator>>(istream& is, Employee& emp) {
    is >> emp.name >> emp.salary;
    return is;
}

class CurrentEmployee : public Employee {
public:
    CurrentEmployee(const string& n = "Неизвестно", double s = 0) : Employee(n, s) {}
    
    void printInfo() const override {
        cout << name << " (Текущий сотрудник, зарплата: " << salary << ")" << endl;
    }
    
    string getType() const override { return "Current"; }
};

class FormerEmployee : public Employee {
public:
    FormerEmployee(const string& n = "Неизвестно", double s = 0) : Employee(n, s) {}
    
    void printInfo() const override {
        cout << name << " (Бывший сотрудник, зарплата: " << salary << ")" << endl;
    }
    
    string getType() const override { return "Former"; }
};

// Функция для сохранения данных в файл
void saveToFile(const vector<unique_ptr<Employee>>& employees, const string& filename) {
    ofstream file(filename);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для записи");
    }
    
    for (const auto& emp : employees) {
        file << *emp << endl;
    }
    cout << "Данные сохранены в файл: " << filename << endl;
}

// Функция для загрузки данных из файла
void loadFromFile(vector<unique_ptr<Employee>>& employees, const string& filename) {
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Не удалось открыть файл для чтения");
    }
    
    employees.clear();
    string type, name;
    double salary;
    
    while (file >> type >> name >> salary) {
        if (type == "Current") {
            employees.push_back(make_unique<CurrentEmployee>(name, salary));
        } else if (type == "Former") {
            employees.push_back(make_unique<FormerEmployee>(name, salary));
        }
    }
    cout << "Данные загружены из файла: " << filename << endl;
}

int main() {
    vector<unique_ptr<Employee>> employees;
    
    // Добавление тестовых данных
    employees.push_back(make_unique<CurrentEmployee>("Иван", 50000));
    employees.push_back(make_unique<FormerEmployee>("Петр", 30000));
    
    try {
        // 1. Демонстрация оператора <<
        cout << "Список сотрудников:" << endl;
        for (const auto& emp : employees) {
            cout << *emp << endl;
        }
        
        // 2. Демонстрация оператора >>
        unique_ptr<Employee> newEmp;
        cout << "\nДобавление нового сотрудника:" << endl;
        cout << "Введите тип (Current/Former): ";
        string type;
        cin >> type;
        
        if (type == "Current") {
            newEmp = make_unique<CurrentEmployee>();
        } else if (type == "Former") {
            newEmp = make_unique<FormerEmployee>();
        } else {
            cout << "Неверный тип сотрудника!" << endl;
            return 1;
        }
        
        cout << "Введите имя и зарплату (через пробел): ";
        cin >> *newEmp;
        employees.push_back(move(newEmp));
        
        // 3. Сохранение в файл
        saveToFile(employees, "employees.txt");
        
        // 4. Чтение из файла
        vector<unique_ptr<Employee>> loadedEmployees;
        loadFromFile(loadedEmployees, "employees.txt");
        
        // 5. Вывод загруженных данных
        cout << "\nЗагруженные сотрудники:" << endl;
        for (const auto& emp : loadedEmployees) {
            emp->printInfo();
        }
        
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}