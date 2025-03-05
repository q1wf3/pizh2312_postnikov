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