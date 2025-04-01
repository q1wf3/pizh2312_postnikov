class QueueEmptyError(Exception):
    """Ошибка при попытке взять элемент из пустой очереди"""
    pass

class Queue:
    """Простая реализация очереди (FIFO) для новичков"""
    
    def __init__(self):
        """Создает пустую очередь"""
        self._items = []
    
    def __str__(self):
        """Показывает очередь в виде строки"""
        return "Очередь: " + " -> ".join(str(item) for item in self._items)
    
    def is_empty(self):
        """Проверяет, пуста ли очередь"""
        return len(self._items) == 0
    
    def enqueue(self, item):
        """Добавляет элемент в конец очереди"""
        self._items.append(item)
    
    def dequeue(self):
        """Удаляет и возвращает первый элемент очереди"""
        if self.is_empty():
            raise QueueEmptyError("Очередь пуста!")
        return self._items.pop(0)
    
    def size(self):
        """Возвращает размер очереди"""
        return len(self._items)