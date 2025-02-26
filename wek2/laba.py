from abc import ABC, abstractmethod

# Абстракция: Абстрактный класс для представления темы
class AbstractTheme(ABC):
    @abstractmethod
    def get_name(self):
        pass

# Класс Theme наследуется от AbstractTheme
class Theme(AbstractTheme):
    def __init__(self, name):
        self._name = name  # Инкапсуляция: Защищенный атрибут
    
    def get_name(self):
        return self._name

    def __str__(self):  # Полиморфизм: Перегрузка метода __str__
        return self._name
    
    def __call__(self): # Делаем объект вызываемым
        return self.get_name()

# Наследование: Расширение класса Theme
class AdvancedTheme(Theme):
    def __init__(self, name, description):
        super().__init__(name)
        self._description = description

    def __str__(self): #Полиморфизм
      return f"{super().__str__()} (Описание: {self._description})"
      
    def get_description(self):
        return self._description

# Композиция: Класс Themes содержит список объектов Theme
class Themes:
    def __init__(self, themes):
        self._themes = [Theme(theme) if isinstance(theme, str) else theme for theme in themes] # преобразуем имена тем в объекты Theme
    

    def add_theme(self, value):
        if isinstance(value, str):
            self._themes.append(Theme(value)) # Преобразуем имя темы в объект Theme
        else:
            self._themes.append(value)


    def shift_one(self):
        if self._themes:
            self._themes = [self._themes[-1]] + self._themes[:-1]

    def reverse_order(self):
        self._themes = self._themes[::-1]

    def get_themes(self):
        return tuple(str(theme) for theme in self._themes) # Преобразуем объекты Theme в строки

    def get_first(self):
        return str(self._themes[0]) if self._themes else None # Преобразуем объект Theme в строку

# Пример использования (как в исходном задании):
tl = Themes(['weather', 'rain']) # Создание экземпляров Theme происходит внутри Themes
tl.add_theme('warm') # Создание экземпляра Theme происходит внутри Themes
print(tl.get_themes())
tl.shift_one()
print(tl.get_first())

tl = Themes(['sun', 'feeding'])
tl.add_theme('cool')
tl.shift_one()
print(tl.get_first())
tl.reverse_order()
print(tl.get_themes())

#пример использования __call__
weather = Theme("Weather")
print(weather()) #выводит Weather