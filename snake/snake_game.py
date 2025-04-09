import pygame
import random
import os
import json
from pygame import mixer

# Настройки игры
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
GRID_SIZE = 20
INITIAL_SPEED = 10
SPEED_INCREMENT = 0.5
SNAKE_GROWTH = 3

class Snake:
    def __init__(self):
        self.reset()
        
    def reset(self):
        self.positions = [(SCREEN_WIDTH//2, SCREEN_HEIGHT//2)]
        self.direction = 'RIGHT'
        self.length = 5
        self.score = 0
        self.speed = INITIAL_SPEED
        self.thickness = GRID_SIZE
        self.alive = True
    
    def move(self):
        if not self.alive:
            return
            
        head_x, head_y = self.positions[0]
        if self.direction == 'UP':
            new_head = (head_x, (head_y - GRID_SIZE) % SCREEN_HEIGHT)
        elif self.direction == 'DOWN':
            new_head = (head_x, (head_y + GRID_SIZE) % SCREEN_HEIGHT)
        elif self.direction == 'LEFT':
            new_head = ((head_x - GRID_SIZE) % SCREEN_WIDTH, head_y)
        elif self.direction == 'RIGHT':
            new_head = ((head_x + GRID_SIZE) % SCREEN_WIDTH, head_y)
            
        self.positions.insert(0, new_head)
        if len(self.positions) > self.length:
            self.positions.pop()

    def grow(self):
        self.length += SNAKE_GROWTH
        self.score += 10
        self.speed += SPEED_INCREMENT

    def check_collision(self):
        # Проверка только на столкновение с собой
        head = self.positions[0]
        if head in self.positions[1:]:
            self.alive = False
        return not self.alive

def load_high_score():
    if os.path.exists('highscore.json'):
        try:
            with open('highscore.json', 'r') as f:
                return json.load(f).get('highscore', 0)
        except:
            return 0
    return 0

def save_high_score(score):
    with open('highscore.json', 'w') as f:
        json.dump({'highscore': score}, f)