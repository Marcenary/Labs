import sqlite3
import json
import hashlib
import xml.etree.ElementTree as ET
from xml.dom import minidom

def hash_password(password):
    return hashlib.sha1(password.encode()).hexdigest()

# Подключение к базе данных
def connect_to_db(db_name):
    conn = sqlite3.connect(db_name)
    return conn

# Авторизация пользователя
def authorize_user(conn, username, password):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Users WHERE username = ? AND password = ?", (username, password))
    user = cursor.fetchone()
    if user:
        print("Authorization successful")
        return True
    else:
        print("Authorization failed")
        return False

# Получение информации об авторе
def get_author_info(conn, author_id):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM Авторы WHERE id = ?", (author_id,))
    author = cursor.fetchone()
    if author:
        return {
            "id": author[0],
            "имя": author[1],
            "страна": author[2],
            "годы жизни": author[3]
        }
    else:
        return None

# Сохранение информации об авторе в формате JSON
def save_author_info_json(author_info, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(author_info, f, ensure_ascii=False, indent=4)

# Сохранение информации об авторе в формате XML
def save_author_info_xml(author_info, filename):
    author = ET.Element("author")
    name = ET.SubElement(author, "name")
    name.text = author_info["имя"]
    country = ET.SubElement(author, "country")
    country.text = author_info["страна"]
    years = ET.SubElement(author, "years")
    years.text = author_info["годы жизни"]

    xml_str = ET.tostring(author, encoding='utf-8')
    dom = minidom.parseString(xml_str)
    with open(filename, 'w', encoding='utf-8') as f:
        dom.writexml(f, indent="", encoding='utf-8')

# Пример использования
conn = connect_to_db('library.db')
pas = input("Input password: ")
if authorize_user(conn, 'user1', hash_password(pas)):
    author_info = get_author_info(conn, 1)
    if author_info:
        save_author_info_json(author_info, 'author_info.json')
        save_author_info_xml(author_info, 'author_info.xml')
else: print("Password uncorrect!")

conn.close()
