# Программирование на языке высокого уровня (Python).
# Задание week_05_1. Вариант 8
#
# Выполнил: Постников И.В.
# Группа: ПИЖ-б-о-23-1(2)

class QueueEmptyError(Exception): 
    pass

class Queue:
    """Реализация очереди FIFO (First In - First Out)"""
    
    def __init__(self):
        self._items = []  # Хранилище элементов очереди
    
    def __str__(self):
        return "Очередь: " + " → ".join(map(str, self._items))
    
    def is_empty(self):
        return not self._items  # True если очередь пуста
    
    def enqueue(self, item):
        self._items.append(item)  # Добавление в конец
    
    def dequeue(self):
        if self.is_empty():
            raise QueueEmptyError("Очередь пуста!")
        return self._items.pop(0)  # Удаление из начала
    
    def size(self):
        return len(self._items)  # Текущий размер очереди


# Тестовый пример использования
if __name__ == "__main__":
    q = Queue()
    q.enqueue("Первый")
    q.enqueue("Второй")
    
    print(q)  # Очередь: Первый → Второй
    
    # Обработка всех элементов
    while not q.is_empty():
        print(f"Извлечено: {q.dequeue()}")
    
    # Проверка обработки ошибок
    try:
        q.dequeue()
    except QueueEmptyError as e:
        print(f"Ошибка: {e}")  # Должно сработать исключение