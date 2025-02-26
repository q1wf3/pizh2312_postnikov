from random import randint

class Soldier:
    def makeHealth(self, value):
        self.health = value
    def makeKick(self, enemy):
        enemy.health -= 20

class Battle:
    def battle(self, u1, u2):
        while u1.health > 0 and u2.health > 0:
            n = randint(1,2)
            if n == 1:
                u1.makeKick(u2)
                print("Первый бьет второго")
                print("У второго осталось", u2.health)
                print()
            else:
                u2.makeKick(u1)
                print("Второй бьет первого")
                print("У первого осталось", u1.health)
                print()

        if u1.health > u2.health:
            self.result = "ПЕРВЫЙ ПОБЕДИЛ"
        elif u2.health > u1.health:
            self.result = "ВТОРОЙ ПОБЕДИЛ"

    def whowin(self):
        print(self.result)

first = Soldier()
second = Soldier()
first.makeHealth(100)
second.makeHealth(100)

b = Battle()
b.battle(first, second)
b.whowin()