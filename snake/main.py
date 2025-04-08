import pygame
import time
from snake_game import Snake, Apple, WINDOW_WIDTH, WINDOW_HEIGHT, BLACK, WHITE, load_high_score, save_high_score #Импортируем всё необходимое

def main():
    """
    Основной игровой цикл.
    """
    pygame.init()
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("Змейка")
    clock = pygame.time.Clock()
    font = pygame.font.Font(None, 36) #Шрифт для отображения счета
    game_over_font = pygame.font.Font(None, 48) #Шрифт для отображения "Game Over"

    snake = Snake(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2)
    apple = Apple()
    game_over = False

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT and snake.direction != 'RIGHT':
                    snake.direction = 'LEFT'
            elif event.key == pygame.K_RIGHT and snake.direction != 'LEFT':
                snake.direction = 'RIGHT'
            elif event.key == pygame.K_r and game_over:  # Перезапуск по кнопке 'R'
                snake.reset()
                apple.respawn()
                game_over = False

        if not game_over:
            snake.move()

            # Поедание яблока
            if snake.body[0][0] == apple.x and snake.body[0][1] == apple.y:
                snake.grow()
                apple.respawn()

            # Проверка столкновений
            if snake.check_collision():
                game_over = True
                snake.update_high_score()

            screen.fill(BLACK)
            snake.draw(screen)
            apple.draw(screen)

            #Отображение счета
            score_text = font.render(f"Счет: {snake.score}  Рекорд: {snake.high_score}", True, WHITE)
            screen.blit(score_text, (5, 5))

            pygame.display.flip()
            clock.tick(15)  # Контроль FPS

        else: #Game Over
            screen.fill(BLACK)
            game_over_text = game_over_font.render("Game Over! Нажмите R для перезапуска", True, RED)
            score_text = font.render(f"Счет: {snake.score}  Рекорд: {snake.high_score}", True, WHITE)

            game_over_rect = game_over_text.get_rect(center=(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2 - 20))
            score_rect = score_text.get_rect(center=(WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2 + 20))

            screen.blit(game_over_text, game_over_rect)
            screen.blit(score_text, score_rect)

            pygame.display.flip()
            time.sleep(2)  # Пауза перед перезапуском (или ожиданием нажатия R)

if __name__ == "__main__":
    main()