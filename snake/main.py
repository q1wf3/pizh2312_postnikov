from snake_game import *
import pygame

# Инициализация
pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption('Змейка: Сквозь границы')
clock = pygame.time.Clock()

# Цвета
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
YELLOW = (255, 255, 0)

# Шрифты
font = pygame.font.SysFont('arial', 25)
big_font = pygame.font.SysFont('arial', 50)

def main():
    snake = Snake()
    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
            random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
    high_score = load_high_score()
    running = True
    
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN:
                if not snake.alive and event.key == pygame.K_SPACE:
                    snake.reset()
                    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                            random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
                elif snake.alive:
                    if event.key == pygame.K_UP and snake.direction != 'DOWN':
                        snake.direction = 'UP'
                    elif event.key == pygame.K_DOWN and snake.direction != 'UP':
                        snake.direction = 'DOWN'
                    elif event.key == pygame.K_LEFT and snake.direction != 'RIGHT':
                        snake.direction = 'LEFT'
                    elif event.key == pygame.K_RIGHT and snake.direction != 'LEFT':
                        snake.direction = 'RIGHT'
        
        if snake.alive:
            snake.move()
            
            if snake.positions[0] == food:
                snake.grow()
                food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                        random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
                while food in snake.positions:
                    food = (random.randrange(0, SCREEN_WIDTH, GRID_SIZE), 
                            random.randrange(0, SCREEN_HEIGHT, GRID_SIZE))
            
            if snake.check_collision():
                if snake.score > high_score:
                    high_score = snake.score
                    save_high_score(high_score)
        
        # Отрисовка
        screen.fill(BLACK)
        
        for pos in snake.positions:
            pygame.draw.rect(screen, GREEN, (pos[0], pos[1], snake.thickness, snake.thickness))
        
        pygame.draw.rect(screen, RED, (food[0], food[1], snake.thickness, snake.thickness))
        
        # Простой счётчик вверху слева
        score_text = font.render(f'Счет: {snake.score}', True, WHITE)
        high_score_text = font.render(f'Рекорд: {high_score}', True, YELLOW)
        screen.blit(score_text, (10, 10))
        screen.blit(high_score_text, (10, 40))
        
        if not snake.alive:
            game_over_text = big_font.render('Игра окончена!', True, RED)
            restart_text = font.render('Нажми ПРОБЕЛ', True, WHITE)
            screen.blit(game_over_text, (SCREEN_WIDTH//2 - game_over_text.get_width()//2, SCREEN_HEIGHT//2 - 50))
            screen.blit(restart_text, (SCREEN_WIDTH//2 - restart_text.get_width()//2, SCREEN_HEIGHT//2 + 20))
        
        pygame.display.flip()
        clock.tick(snake.speed if snake.alive else 60)
    
    pygame.quit()

if __name__ == "__main__":
    main()