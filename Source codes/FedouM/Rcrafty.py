import pygame
import sys
import random

# Инициализация Pygame
pygame.init()

# Размеры окна (соотношение 16:9)
WIDTH, HEIGHT = 854, 480 
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Rcrafty 1.0")

# Цвета
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (128, 128, 128)
BROWN = (139, 69, 19)  # Земля
BLUE = (0, 0, 255)  # Вода
STONE_COLOR = (100, 100, 100)  # Камень
MENU_BACKGROUND = (150, 75, 0)  # Коричневый фон для меню

# Размер блока
BLOCK_SIZE = 50

# Игрок
PLAYER_SIZE = 50
player_pos = [WIDTH // 2, HEIGHT // 2]  # Позиция игрока (в центре экрана)
player_speed = 200  # Скорость игрока (пикселей в секунду)

# Камера
camera_offset = [0, 0]  # Смещение камеры (координаты мира)

# Мир
world_blocks = {}  # Храним координаты блоков (ключ: (x, y), значение: цвет блока)
GROUND_HEIGHT = 10  # Высота земли (номер строки от нижней границы)
GROUND_DEPTH = 5  # Толщина слоя земли
WATER_LEVEL = GROUND_HEIGHT + 2  # Уровень воды

# Шрифт для текста
font = pygame.font.Font(None, 36)

# Главные переменные
running = True
menu = True  # Находимся в главном меню
loading = False  # Флаг загрузки мира

# Ограничение FPS
clock = pygame.time.Clock()

# Инвентарь
inventory_slots = 5  # Количество слотов
slot_width = 80  # Ширина одного слота
slot_margin = 10  # Отступ между слотами
inventory = {"dirt": 0, "stone": 0}  # Счетчик ресурсов (земля, камень)
selected_block = "dirt"  # По умолчанию выбран блок "земля"

# Функция для генерации мира
def generate_world():
    global world_blocks
    for x in range(-50, 50):  # Генерация в пределах от -50 до 50 блоков по оси X
        for y in range(GROUND_HEIGHT + GROUND_DEPTH * 10):  # Увеличиваем глубину слоя земли
            if y > GROUND_HEIGHT:  # Генерация слоя земли
                world_blocks[(x, y)] = BROWN
            elif y == GROUND_HEIGHT:  # Поверхность земли
                if random.random() < 0.2:  # 20% шанс появления камня
                    world_blocks[(x, y)] = STONE_COLOR
                else:
                    world_blocks[(x, y)] = BROWN
            elif y == WATER_LEVEL:  # Генерация воды ниже уровня земли
                world_blocks[(x, y)] = BLUE

# Функция для рисования мира
def draw_world():
    # Рисуем блоки мира
    for (block_x, block_y), color in world_blocks.items():
        # Координаты блока с учетом камеры
        draw_x = block_x * BLOCK_SIZE + camera_offset[0]
        draw_y = block_y * BLOCK_SIZE + camera_offset[1]
        pygame.draw.rect(screen, color, (draw_x, draw_y, BLOCK_SIZE, BLOCK_SIZE))
        pygame.draw.rect(screen, BLACK, (draw_x, draw_y, BLOCK_SIZE, BLOCK_SIZE), 1)  # Контур

# Функция для рисования игрока
def draw_player():
    # Тело игрока
    body_rect = pygame.Rect(player_pos[0] - PLAYER_SIZE // 2, player_pos[1] - PLAYER_SIZE // 4, PLAYER_SIZE, PLAYER_SIZE)
    pygame.draw.rect(screen, GRAY, body_rect)
    # Голова игрока
    head_center = (player_pos[0], player_pos[1] - PLAYER_SIZE // 2)
    pygame.draw.circle(screen, GRAY, head_center, PLAYER_SIZE // 4)

# Функция для рисования инвентаря
def draw_inventory():
    inventory_width = inventory_slots * slot_width + (inventory_slots - 1) * slot_margin
    start_x = (WIDTH - inventory_width) // 2  # Вычисляем центр по горизонтали
    y = HEIGHT - 100  # Расположение инвентаря внизу экрана
    for i, (block_type, count) in enumerate(inventory.items()):
        slot_x = start_x + i * (slot_width + slot_margin)
        pygame.draw.rect(screen, WHITE, (slot_x, y, slot_width, slot_width), 2)  # Контур слота
        block_color = BROWN if block_type == "dirt" else STONE_COLOR
        pygame.draw.rect(screen, block_color, (slot_x + 5, y + 5, slot_width - 10, slot_width - 10))  # Цвет блока
        if count > 0:
            text = font.render(str(count), True, BLACK)
            screen.blit(text, (slot_x + 5, y + 5))

# Функция для добавления блока в инвентарь
def add_to_inventory(block_type):
    if block_type == BROWN:
        inventory["dirt"] += 1
    elif block_type == STONE_COLOR:
        inventory["stone"] += 1

# Функция для установки блока
def place_block(block_type, pos):
    if block_type == "dirt" and inventory["dirt"] > 0:
        world_blocks[pos] = BROWN
        inventory["dirt"] -= 1
    elif block_type == "stone" and inventory["stone"] > 0:
        world_blocks[pos] = STONE_COLOR
        inventory["stone"] -= 1

# Функция для проверки столкновения с блоками
# Функция для проверки столкновения с блоками
def check_collision(player_rect):
    # Проверяем, не столкнется ли игрок с блоками
    for (block_x, block_y), color in world_blocks.items():
        block_rect = pygame.Rect(block_x * BLOCK_SIZE + camera_offset[0], block_y * BLOCK_SIZE + camera_offset[1], BLOCK_SIZE, BLOCK_SIZE)
        if player_rect.colliderect(block_rect):
            return True  # Есть столкновение
    return False  # Нет столкновения

# Основной цикл программы
while running:
    dt = clock.tick(1440) / 1000.0  # Время между кадрами в секундах

    # Обработка событий
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            if menu:
                menu = False
                loading = True
            else:
                # Добавление/удаление блоков
                mouse_pos = pygame.mouse.get_pos()
                world_x = (mouse_pos[0] - camera_offset[0]) // BLOCK_SIZE
                world_y = (mouse_pos[1] - camera_offset[1]) // BLOCK_SIZE
                block_coords = (world_x, world_y)
                if event.button == 1:  # Левая кнопка мыши (ломать блок)
                    if block_coords in world_blocks:
                        block_type = world_blocks.pop(block_coords)  # Удаляем блок из мира
                        add_to_inventory(block_type)  # Добавляем его в инвентарь
                elif event.button == 3:  # Правая кнопка мыши (ставить блок)
                    place_block(selected_block, block_coords)

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:  # Клавиша 1 для выбора земли
                selected_block = "dirt"
            elif event.key == pygame.K_2:  # Клавиша 2 для выбора камня
                selected_block = "stone"

    # Движение игрока
    keys = pygame.key.get_pressed()
    if not menu and not loading:
        new_x = player_pos[0]
        new_y = player_pos[1]
        
        if keys[pygame.K_w]:
            new_y -= player_speed * dt
        if keys[pygame.K_s]:
            new_y += player_speed * dt
        if keys[pygame.K_a]:
            new_x -= player_speed * dt
        if keys[pygame.K_d]:
            new_x += player_speed * dt
        
        # Создаем прямоугольник игрока для проверки столкновений
        player_rect = pygame.Rect(new_x - PLAYER_SIZE // 2, new_y - PLAYER_SIZE // 2, PLAYER_SIZE, PLAYER_SIZE)

        # Проверяем столкновение перед тем, как перемещать игрока
        if not check_collision(player_rect):
            player_pos[0] = new_x
            player_pos[1] = new_y

    # Движение камеры
    if not menu and not loading:
        if keys[pygame.K_w]:
            camera_offset[1] += player_speed * dt
        if keys[pygame.K_s]:
            camera_offset[1] -= player_speed * dt
        if keys[pygame.K_a]:
            camera_offset[0] += player_speed * dt
        if keys[pygame.K_d]:
            camera_offset[0] -= player_speed * dt

    # Рисуем экран
    if menu:
        screen.fill(MENU_BACKGROUND)
        text = font.render("Single Play", True, WHITE)
        rect = text.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        pygame.draw.rect(screen, BLACK, rect.inflate(20, 20))  # Кнопка с черной рамкой
        screen.blit(text, rect)
    elif loading:
        screen.fill(BLACK)
        text = font.render("Loading world...", True, WHITE)
        rect = text.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(text, rect)
        pygame.display.flip()
        pygame.time.wait(4000)  # Симуляция загрузки
        generate_world()
        loading = False
    else:
        screen.fill(WHITE)
        draw_world()
        draw_player()
        draw_inventory()
        text = font.render("Rcrafty 1.0", True, BLACK)
        fps_text = font.render(f"FPS: {int(clock.get_fps())}", True, BLACK)
        screen.blit(text, (10, 10))
        screen.blit(fps_text, (10, 40))

    pygame.display.flip()
