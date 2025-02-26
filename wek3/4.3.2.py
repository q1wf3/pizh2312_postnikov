class Pizza:
    def __init__(self, name, price, ingredients):
        self.name = name
        self.price = price
        self.ingredients = ingredients

    def prepare(self):
        print(f"Подготавливаем пиццу: {self.name}")
        print(f"Добавляем ингредиенты: {', '.join(self.ingredients)}")
        print("Выпекаем...")
        print("Нарезаем и упаковываем...")
        print("Пицца готова!")

    def __str__(self):
        return f"{self.name} - {self.price} руб."


class Order:
    def __init__(self):
        self.items = []

    def add_pizza(self, pizza):
        self.items.append(pizza)

    def calculate_total(self):
        total = 0
        for pizza in self.items:
            total += pizza.price
        return total

    def __str__(self):
        if not self.items:
            return "В заказе нет пицц."
        order_str = "Заказ:\n"
        for pizza in self.items:
            order_str += f"  - {pizza}\n"
        order_str += f"Итого: {self.calculate_total()} руб."
        return order_str


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


# Основной цикл программы
terminal = Terminal()
order = terminal.take_order()
if order.items:
    terminal.fulfill_order(order)
else:
    print("Вы не заказали ни одной пиццы.")