from queue import Queue

def main():
    print("Тестирование класса Queue\n")
    
    # Создание очереди
    q1 = Queue(1, 2, 3)
    print(f"Создана очередь: {q1}")
    
    # Добавление элементов
    q1.enqueue(4)
    q1.enqueue(5)
    print(f"После добавления 4 и 5: {q1}")
    
    # Удаление элемента
    print(f"\nИзвлеченный элемент: {q1.dequeue()}")
    print(f"Очередь после извлечения: {q1}")
    
    # Просмотр первого элемента
    print(f"\nПервый элемент (без удаления): {q1.peek()}")
    
    # Размер очереди
    print(f"\nТекущий размер очереди: {q1.size}")
    
    # Создание из строки
    q2 = Queue.from_string("a, b, c, d")
    print(f"\nОчередь из строки: {q2}")
    
    # Операции с очередями
    q3 = q1 + q2
    print(f"\nРезультат сложения q1 + q2: {q3}")
    
    q4 = q3 - Queue(2, 'b')
    print(f"Результат вычитания [2, 'b']: {q4}")
    
    # Сохранение и загрузка
    q4.save("queue_data.json")
    q5 = Queue()
    q5.load("queue_data.json")
    print(f"\nОчередь после загрузки из файла: {q5}")
    
    # Очистка
    q5.clear()
    print(f"\nОчередь после очистки: {q5}")
    print(f"Пуста ли очередь? {q5.is_empty()}")

if __name__ == "__main__":
    main()