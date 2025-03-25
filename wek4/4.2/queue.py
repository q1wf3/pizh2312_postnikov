import json

class Queue:
    """Класс, реализующий структуру данных 'Очередь' (FIFO - First In First Out)"""
    
    def __init__(self, *items):
        """Инициализация очереди с начальными элементами (если они есть)"""
        self._items = list(items)  # Основное хранилище элементов
    
    def __str__(self):
        """Строковое представление очереди"""
        return f"Queue({', '.join(map(str, self._items))})"
    
    def __len__(self):
        """Возвращает количество элементов в очереди"""
        return len(self._items)
    
    def __add__(self, other):
        """Сложение двух очередей (конкатенация)"""
        if isinstance(other, Queue):
            return Queue(*(self._items + other._items))
        raise TypeError("Можно складывать только с другой очередью")
    
    def __sub__(self, other):
        """Вычитание элементов очереди (удаление совпадающих элементов)"""
        if isinstance(other, Queue):
            return Queue(*[item for item in self._items if item not in other._items])
        raise TypeError("Можно вычитать только другую очередь")
    
    def enqueue(self, item):
        """Добавление элемента в конец очереди"""
        self._items.append(item)
    
    def dequeue(self):
        """Удаление и возврат элемента из начала очереди"""
        if not self.is_empty():
            return self._items.pop(0)
        raise IndexError("Очередь пуста")
    
    def is_empty(self):
        """Проверка очереди на пустоту"""
        return len(self._items) == 0
    
    def peek(self):
        """Просмотр первого элемента без удаления"""
        if not self.is_empty():
            return self._items[0]
        raise IndexError("Очередь пуста")
    
    def clear(self):
        """Очистка очереди"""
        self._items.clear()
    
    def save(self, filename):
        """Сохранение очереди в JSON-файл"""
        with open(filename, 'w') as f:
            json.dump(self._items, f)
    
    @classmethod
    def from_string(cls, str_value):
        """Создание очереди из строки (элементы разделены запятыми)"""
        items = [item.strip() for item in str_value.split(',') if item.strip()]
        return cls(*items)
    
    def load(self, filename):
        """Загрузка очереди из JSON-файла"""
        with open(filename, 'r') as f:
            self._items = json.load(f)
    
    @property
    def size(self):
        """Свойство: размер очереди (только для чтения)"""
        return len(self._items)