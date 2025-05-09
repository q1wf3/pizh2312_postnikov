from pizza import Pizza
from order import Order

class Terminal:
    def __init__(self):
        self.menu = {
            1: Pizza("Пепперони", 899, ["Пепперони", "Сыр", "Томатный соус"]),
            2: Pizza("BBQ Чикен", 990, ["Курица", "BBQ Соус", "Сыр", "Лук"]),
            3: Pizza("Дары Моря", 1000, ["Креветки", "Кальмары", "Мидии", "Чеснок", "Оливковое масло"])
        }

    def display_menu(self):
        print("Меню:")
        for key, pizza in self.menu.items():
            print(f"{key}. {pizza}")

    def take_order(self):
        order = Order()
        while True:
            self.display_menu()
            choice = input("Введите номер пиццы, которую хотите заказать (или 'готово' для завершения): ")

            if choice.lower() == 'готово':
                break

            try:
                choice = int(choice)
                if choice in self.menu:
                    pizza = self.menu[choice]
                    order.add_pizza(pizza)
                    print(f"Добавлена пицца {pizza.name} в ваш заказ.")
                else:
                    print("Неверный номер пиццы.")
            except ValueError:
                print("Неверный ввод. Пожалуйста, введите номер или 'готово'.")

        return order

    def process_payment(self, order):
        total = order.calculate_total()
        print(f"Сумма вашего заказа: {total} руб.")
        while True:
            payment = input("Введите сумму оплаты: ")
            try:
                payment = float(payment)
                if payment >= total:
                    change = payment - total
                    print("Оплата принята.")
                    if change > 0:
                        print(f"Ваша сдача: {change:.2f} руб.")
                    return True
                else:
                    print("Недостаточно средств.")
            except ValueError:
                print("Неверная сумма оплаты.")
        return False

    def fulfill_order(self, order):
        if self.process_payment(order):
            print("\nДетали заказа:")
            print(order)

            for pizza in order.items:
                pizza.prepare()
            print("\nВаш заказ готовится. Спасибо за ваш заказ!\n")