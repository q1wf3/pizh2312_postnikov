class TermDeposit:
    """Срочный вклад с простыми процентами"""
    def __init__(self, principal, interest_rate):
        self.principal = principal
        self.interest_rate = interest_rate

    def calculate_profit(self, term_years):
        return self.principal * self.interest_rate * term_years


class BonusDeposit:
    """Бонусный вклад с дополнительным процентом"""
    def __init__(self, principal, interest_rate, bonus_threshold, bonus_percent):
        self.principal = principal
        self.interest_rate = interest_rate
        self.bonus_threshold = bonus_threshold
        self.bonus_percent = bonus_percent / 100

    def calculate_profit(self, term_years):
        profit = self.principal * self.interest_rate * term_years
        if self.principal > self.bonus_threshold:
            profit += profit * self.bonus_percent
        return profit


class CompoundInterestDeposit:
    """Вклад с капитализацией процентов"""
    def __init__(self, principal, interest_rate, compounding_frequency):
        self.principal = principal
        self.interest_rate = interest_rate
        self.compounding_frequency = compounding_frequency

    def calculate_profit(self, term_years):
        rate_per_period = self.interest_rate / self.compounding_frequency
        periods = term_years * self.compounding_frequency
        amount = self.principal * (1 + rate_per_period) ** periods
        return amount - self.principal