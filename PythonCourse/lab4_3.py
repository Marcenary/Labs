from sqlalchemy import create_engine, Column, Integer, String, ForeignKey, func
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship

# Создаем базу данных и подключаемся к ней
engine = create_engine('sqlite:///library.db', echo=True)
Base = declarative_base()

# Определяем таблицы
class Авторы(Base):
    __tablename__ = 'Авторы'
    id = Column(Integer, primary_key=True)
    имя = Column(String)
    фамилия = Column(String)
    страна = Column(String)
    год_рождения = Column(Integer)

class Книги(Base):
    __tablename__ = 'Книги'
    id = Column(Integer, primary_key=True)
    id_автора = Column(Integer, ForeignKey('Авторы.id'))
    название = Column(String)
    количество_страниц = Column(Integer)
    год_издания = Column(Integer)

# Создаем таблицы в базе данных
Base.metadata.create_all(engine)

# Создаем сессию для работы с базой данных
Session = sessionmaker(bind=engine)
session = Session()

# Функция для вывода фамилий авторов, родившихся между X и Y годами
def get_authors_by_birth_range(X, Y):
    authors = session.query(Авторы.фамилия).filter(Авторы.год_рождения.between(X, Y)).all()
    return [author.фамилия for author in authors]

# Функция для вывода всех книг, написанных авторами из России
def get_books_by_russian_authors():
    books = session.query(Книги.название).join(Авторы).filter(Авторы.страна == 'Россия').all()
    return [book.название for book in books]

# Функция для вывода всех книг с количеством страниц более N
def get_books_by_pages_more_than(N):
    books = session.query(Книги.название).filter(Книги.количество_страниц > N).all()
    return [book.название for book in books]

# Функция для вывода всех авторов с числом книг более N
def get_authors_with_more_than_N_books(N):
    authors = session.query(Авторы.фамилия).join(Книги).group_by(Авторы.id).having(func.count(Книги.id) > N).all()
    return [author.фамилия for author in authors]

# Пример использования функций
X, Y = 1900, 2000
N = 100

print("Авторы, родившиеся между", X, "и", Y, "годами:", get_authors_by_birth_range(X, Y))
print("Книги, написанные авторами из России:", get_books_by_russian_authors())
print("Книги с количеством страниц более", N, ":", get_books_by_pages_more_than(N))
print("Авторы с числом книг более", N, ":", get_authors_with_more_than_N_books(N))

# Закрываем сессию
session.close()
