from transport import *

# Создаем транспортные средства
boat = VodnoeTS("Катер")
car = Avtomobil("Toyota")

# Тестируем водный транспорт
boat.start_engine()
boat.move(20)  # не поедет - якорь опущен
boat.raise_anchor()
boat.move(30)
boat.stop_engine()

# Тестируем автомобиль
car.start_engine()
car.move(80)
car.refuel(50)
car.move(100)
car.stop_engine()