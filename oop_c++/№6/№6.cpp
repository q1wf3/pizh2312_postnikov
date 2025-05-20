#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Employee {
private:
    static int count; // Статический счетчик объектов
    
protected:
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

    friend std::ostream& operator<<(std::ostream& os, const Employee& emp);
};

int Employee::count = 0;

std::ostream& operator<<(std::ostream& os, const Employee& emp) {
    emp.printInfo();
    return os;
}

class CurrentEmployee : public Employee {
public:
    double salary;

    CurrentEmployee(std::string n = "Неизвестно", std::string p = "Неизвестно", 
                   std::string h = "Неизвестно", double s = 0.0)
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

    FormerEmployee(std::string n = "Неизвестно", std::string p = "Неизвестно", 
                  std::string h = "Неизвестно", std::string f = "Неизвестно", 
                  std::string r = "Неизвестно")
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

    // Правило пяти (так как есть unique_ptr)
    Department(const Department&) = delete;
    Department& operator=(const Department&) = delete;
    Department(Department&&) = default;
    Department& operator=(Department&&) = default;

    static int getStoredCount() {
        return stored_count;
    }

    // Оператор + для добавления сотрудника
    Department& operator+(std::unique_ptr<Employee> emp) {
        employees.push_back(std::move(emp));
        stored_count++;
        return *this;
    }

    // Префиксный ++
    Department& operator++() {
        employees.push_back(std::make_unique<CurrentEmployee>());
        stored_count++;
        return *this;
    }

    // Постфиксный ++ (используем перемещение вместо копирования)
    Department operator++(int) {
        Department temp(std::move(name));
        temp.employees = std::move(employees);
        temp.stored_count = stored_count;
        
        employees.clear();
        stored_count = 0;
        
        employees.push_back(std::make_unique<FormerEmployee>());
        stored_count++;
        
        return temp;
    }

    // Оператор [] для доступа к сотруднику
    Employee& operator[](size_t index) {
        if (index >= employees.size()) {
            throw std::out_of_range("Индекс выходит за границы массива");
        }
        return *employees[index];
    }

    // Оператор << для вывода отдела
    friend std::ostream& operator<<(std::ostream& os, const Department& dept);

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

std::ostream& operator<<(std::ostream& os, const Department& dept) {
    dept.printAll();
    return os;
}

int main() {
    std::cout << "Объектов Employee до создания: " << Employee::getCount() << std::endl;
    std::cout << "Объектов в отделах: " << Department::getStoredCount() << std::endl;

    Department it("IT");
    
    // Использование оператора +
    it + std::make_unique<CurrentEmployee>("Иван Иванов", "Программист", "2020-01-15", 100000);
    it + std::make_unique<FormerEmployee>("Петр Петров", "Менеджер", "2018-03-10", "2023-01-20", "Уход");

    // Использование префиксного ++
    ++it;
    
    // Использование постфиксного ++
    Department it_copy = it++;

    std::cout << "\nПосле создания объектов:\n";
    std::cout << "Всего объектов Employee: " << Employee::getCount() << std::endl;
    std::cout << "Объектов в отделах: " << Department::getStoredCount() << std::endl;

    std::cout << "\nИнформация об отделе (через оператор <<):\n";
    std::cout << it;

    std::cout << "\nКопия отдела до инкремента:\n";
    std::cout << it_copy;

    // Использование оператора []
    try {
        std::cout << "\nДоступ к сотруднику по индексу 1:\n";
        std::cout << it[1]; // Используем оператор << для Employee
    } catch (const std::out_of_range& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}