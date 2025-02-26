Класс «Темы» (Themes)

Экземпляру класса при инициализации передается аргумент — список тем для разговора.

Класс реализует методы:

add_theme(value) — добавить тему в конец;
shift_one() — сдвинуть темы на одну вправо (последняя становится первой, остальные сдвигаются);
reverse_order() — поменять порядок тем на обратный;
get_themes() — возвращает список тем;
get_first() — возвращает первую тему.

Пример 1
Ввод:
t1 = Themes(['weather', 'rain'])
t1.add_theme('warm')
print(t1.get_themes())
t1.shift_one()
print(t1.get_first())
Вывод:
('weather', 'rain', 'warm')
warm

Пример 2
Ввод:
t1 = Themes(['sun', 'feeding'])
t1.add_theme('cool')
t1.shift_one()
print(t1.get_first())
t1.reverse_order()
print(t1.get_themes())
Вывод:
cool
('feeding', 'sun', 'cool')