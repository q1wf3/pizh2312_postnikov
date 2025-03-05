# main.py

from roman import Roman

# Примеры использования:
num1 = Roman("XIV")
num2 = Roman(6)

print(f"{num1} + {num2} = {num1 + num2}")
print(f"{num1} - {num2} = {num1 - num2}")
print(f"{num1} * {num2} = {num1 * num2}")
print(f"{num1} / {num2} = {num1 / num2}")

print(f"Римское представление числа 1998: {Roman.to_roman(1998)}")
print(f"Десятичное представление числа MCMXCVIII: {Roman.from_roman('MCMXCVIII')}")