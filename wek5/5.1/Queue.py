class QueueEmptyError(Exception): pass

class Queue:
    def __init__(self):
        self._items = []
    
    def __str__(self):
        return "Queue: " + " -> ".join(map(str, self._items))
    
    def is_empty(self):
        return not self._items
    
    def enqueue(self, item):
        self._items.append(item)
    
    def dequeue(self):
        if self.is_empty():
            raise QueueEmptyError("Queue is empty")
        return self._items.pop(0)
    
    def size(self):
        return len(self._items)


# Пример использования
if __name__ == "__main__":
    q = Queue()
    q.enqueue(1)
    q.enqueue(2)
    
    print(q)
    
    while not q.is_empty():
        print(f"Processing: {q.dequeue()}")
    
    try:
        q.dequeue()
    except QueueEmptyError as e:
        print(f"Error: {e}")