import random
import itertools
from datetime import datetime, timedelta

# Список названий футбольных команд
teams = [
    "Team 1", "Team 2", "Team 3", "Team 4",
    "Team 5", "Team 6", "Team 7", "Team 8",
    "Team 9", "Team 10", "Team 11", "Team 12",
    "Team 13", "Team 14", "Team 15", "Team 16"
]

# Случайное распределение команд по 4 группы
random.shuffle(teams)
groups = [ teams[i*4:(i+1)*4] for i in range(4) ]
# Начальная дата
start_date = datetime(2025, 9, 14)

def print_groups():
    for i, group in enumerate(groups, start=1):
        print(f"Group {i}: {', '.join(group)}")

# Функция для создания календаря игр
def generate_schedule():
    # Все возможные пары в группе
    matches = list(itertools.combinations(range(4), 2))

    # Календарь игр
    schedule = []

    # Генерация игр для каждой группы
    for group in groups:
        for match_day in matches:
            team1 = group[match_day[0]]
            team2 = group[match_day[1]]
            schedule.append((team1, team2))

    # Сортировка календаря по датам
    current_date = start_date
    for match in schedule:
        print(f"{current_date.strftime('%d/%m/%Y, 22:45')}: {match[0]} vs {match[1]}")
        current_date += timedelta(weeks=2)

if __name__ == "__main__":
    # Вывод групп
    print_groups()
    # Генерация и вывод календаря игр
    generate_schedule()