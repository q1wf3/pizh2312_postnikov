class Pizza:
    def __init__(self, name, price, ingredients):
        self.name = name
        self.price = price
        self.ingredients = ingredients

    def prepare(self):
        print(f"Готовим пиццу {self.name}...")

    def __str__(self):
        return f"{self.name} ({self.price} руб.) - {', '.join(self.ingredients)}"
