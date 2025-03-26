# Программирование на языке высокого уровня (Python).
# Задание week_04_1. Вариант 8
#
# Выполнил: Постников И.В.
# Группа: ПИЖ-б-о-23-1(2)
from deposits import TermDeposit, BonusDeposit, CompoundInterestDeposit

def get_input_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Ошибка: введите число")

def get_input_int(prompt):
    while True:
        try:
            return int(input(prompt))
        except ValueError:
            print("Ошибка: введите целое число")

def main():
    print("Консультант по банковским вкладам\n")
    
    principal = get_input_float("Сумма вклада: ")
    rate = get_input_float("Годовая ставка (например 0.05 для 5%): ")
    term = get_input_int("Срок (лет): ")
    
    print("\nТипы вкладов:")
    print("1. Срочный вклад (простые проценты)")
    print("2. Бонусный вклад")
    print("3. Вклад с капитализацией")
    
    choice = get_input_int("Ваш выбор (1-3): ")
    
    if choice == 1:
        deposit = TermDeposit(principal, rate)
    elif choice == 2:
        threshold = get_input_float("Порог для бонуса: ")
        bonus = get_input_float("Бонусный процент: ")
        deposit = BonusDeposit(principal, rate, threshold, bonus)
    elif choice == 3:
        freq = get_input_int("Частота капитализации в год: ")
        deposit = CompoundInterestDeposit(principal, rate, freq)
    else:
        print("Неверный выбор")
        return
    
    profit = deposit.calculate_profit(term)
    print(f"\nРезультаты:")
    print(f"- Прибыль за {term} лет: {profit:.2f}")
    print(f"- Итоговая сумма: {principal + profit:.2f}")

if __name__ == "__main__":
     main()
