from queue import Queue, QueueEmptyError  # Добавляем импорт исключения

def main():
    # Создаем очередь
    q = Queue()
    
    # Добавляем элементы
    q.enqueue("Первый")
    q.enqueue("Второй")
    q.enqueue("Третий")
    
    print(q)  # Показываем очередь
    
    # Обрабатываем очередь
    while not q.is_empty():
        print(f"Обрабатываем: {q.dequeue()}")
        print(f"Осталось в очереди: {q.size()}")
    
    # Проверяем обработку ошибок
    try:
        q.dequeue()
    except QueueEmptyError as e:
        print(f"Ошибка: {e}")

if __name__ == "__main__":
    main()