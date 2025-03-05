from terminal import Terminal

# Основной цикл программы
terminal = Terminal()
order = terminal.take_order()
if order.items:
    terminal.fulfill_order(order)
else:
    print("Вы не заказали ни одной пиццы.")