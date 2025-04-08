import pygame
import random
import json

# Цвета
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)

# Размеры окна и клетки
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 480
CELL_SIZE = 20

def load_high_score():
    """Загружает рекорд из файла."""
    try:
        with open("highscore.txt", "r") as f:
            return int(f.read())
    except FileNotFoundError:
        return 0

def save_high_score(score):
    """Сохраняет рекорд в файл."""
    try:
        with open("highscore.txt", "w") as f:
            f.write(str(score))
    except Exception as e:
        print(f"Ошибка при сохранении рекорда: {e}")


class GameObject:
    """
    Базовый класс для игровых объектов.
    """
    def __init__(self, x, y, size, color):
        self.x = x
        self.y = y
        self.size = size
        self.color = color

    def draw(self, screen):
        """
        Отрисовывает объект на экране.
        """
        pygame.draw.rect(screen, self.color, (self.x, self.y, self.size, self.size))


class Snake:
    """
    Реализует змею и ее поведение.
    """
    def __init__(self, x, y):
        self.size = CELL_SIZE
        self.color = GREEN
        self.x = x
        self.y = y
        self.body = [(x, y)]  # Список координат сегментов змеи
        self.direction = random.choice(['UP', 'DOWN', 'LEFT', 'RIGHT']) #Начальное направление
        self.speed = CELL_SIZE  # Шаг движения за кадр
        self.score = 0
        self.high_score = load_high_score()

    def move(self):
        """
        Двигает змею в текущем направлении.
        """
        head_x = self.body[0][0]
        head_y = self.body[0][1]

        if self.direction == 'UP':
            new_head = (head_x, head_y - self.speed)
        elif self.direction == 'DOWN':
            new_head = (head_x, head_y + self.speed)
        elif self.direction == 'LEFT':
            new_head = (head_x - self.speed, head_y)
        elif self.direction == 'RIGHT':
            new_head = (head_x + self.speed, head_y)

        self.body.insert(0, new_head)  # Добавляем новую голову
        self.body.pop()  # Удаляем последний сегмент (если не съели яблоко)

    def grow(self):
        """
        Увеличивает длину змеи.
        """
        tail_x, tail_y = self.body[-1]
        self.body.append((tail_x, tail_y))  # Добавляем сегмент в хвост
        self.score += 1

    def check_collision(self):
        """
        Проверяет столкновения змеи с собой и стенами.
        """
        head_x, head_y = self.body[0]

        # Столкновение со стенами
        if head_x < 0 or head_x >= WINDOW_WIDTH or head_y < 0 or head_y >= WINDOW_HEIGHT:
            return True

        # Столкновение с собой
        if (head_x, head_y) in self.body[1:]:
            return True

        return False

    def draw(self, screen):
        """
        Отрисовывает змею на экране.
        """
        for x, y in self.body:
            pygame.draw.rect(screen, self.color, (x, y, self.size, self.size))

    def reset(self):
        """Ресет змеи"""
        self.x = WINDOW_WIDTH // 2
        self.y = WINDOW_HEIGHT // 2
        self.body = [(self.x, self.y)]
        self.direction = random.choice(['UP', 'DOWN', 'LEFT', 'RIGHT'])
        self.score = 0

    def update_high_score(self):
        """Обновляет рекорд, если текущий счет больше рекорда."""
        if self.score > self.high_score:
            self.high_score = self.score
            save_high_score(self.high_score) #Сохраняем в файл


class Apple(GameObject):
    """
    Реализует яблоко.
    """
    def __init__(self):
        self.size = CELL_SIZE
        self.color = RED
        self.x = random.randrange(0, WINDOW_WIDTH // CELL_SIZE) * CELL_SIZE
        self.y = random.randrange(0, WINDOW_HEIGHT // CELL_SIZE) * CELL_SIZE

    def respawn(self):
        """
        Перемещает яблоко в случайную позицию.
        """
        self.x = random.randrange(0, WINDOW_WIDTH // CELL_SIZE) * CELL_SIZE
        self.y = random.randrange(0, WINDOW_HEIGHT // CELL_SIZE) * CELL_SIZE