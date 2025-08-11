import os
import shutil
import argparse
import time
from pathlib import Path

def reorganize_files(source, days, size):
    # Получаем текущую дату в секундах
    current_time = time.time()

    # Списки для файлов, которые нужно переместить
    archive_files = []
    small_files = []

    # Проходим по всем файлам в директории source
    for filename in os.listdir(source):
        file_path = os.path.join(source, filename)

        # Пропускаем директории
        if os.path.isdir(file_path):
            continue

        # Получаем время последней модификации файла
        file_mtime = os.path.getmtime(file_path)
        # Получаем размер файла
        file_size = os.path.getsize(file_path)

        # Проверяем, нужно ли переместить файл в Archive
        if (current_time - file_mtime) / (24 * 3600) > days:
            archive_files.append(filename)
        # Проверяем, нужно ли переместить файл в Small
        if file_size < size:
            small_files.append(filename)

    # Создаем директорию Archive и перемещаем файлы, если есть такие
    if archive_files:
        archive_dir = os.path.join(source, 'Archive')
        os.makedirs(archive_dir, exist_ok=True)
        for filename in archive_files:
            shutil.move(os.path.join(source, filename), os.path.join(archive_dir, filename))
        print(f"Moved {len(archive_files)} files to Archive directory.")

    # Создаем директорию Small и перемещаем файлы, если есть такие
    if small_files:
        small_dir = os.path.join(source, 'Small')
        os.makedirs(small_dir, exist_ok=True)
        for filename in small_files:
            shutil.move(os.path.join(source, filename), os.path.join(small_dir, filename))
        print(f"Moved {len(small_files)} files to Small directory.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Reorganize files in a directory.')
    parser.add_argument('--source', '-s', required=True, help='Source directory with files')
    parser.add_argument('--days', '-d', type=int, required=True, help='Number of days to consider a file old')
    parser.add_argument('--size', '-z', type=int, required=True, help='Size in bytes to consider a file small')

    args = parser.parse_args()

    reorganize_files(args.source, args.days, args.size)
