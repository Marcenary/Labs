import os
import random
import subprocess
import argparse

def get_duration(file_path):
    cmd = [
        'ffprobe',
        '-i', file_path,
        '-show_entries', 'format=duration',
        '-v', 'quiet',
        '-of', 'csv=p=0'
    ]
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    return float(result.stdout.decode('utf-8').strip())

def create_track_mix(source, destination, count, frame, log, extended):
    # Получаем список всех mp3 файлов в директории source
    files = [f for f in os.listdir(source) if f.endswith('.mp3')]

    if count is not None:
        files = files[:count]

    if log:
        print(f"--- processing {len(files)} files")

    # Создаем временные файлы для каждого фрагмента
    temp_files = []
    for i, file in enumerate(files):
        input_file = os.path.join(source, file)
        output_file = os.path.join(source, f"temp_{i}.wav")

        # Получаем продолжительность файла
        duration = get_duration(input_file)

        if duration <= frame:
            print(f"File {file} is too short to extract a {frame} second fragment. Skipping.")
            continue

        # Генерируем случайное время начала фрагмента
        start_time = random.randint(0, int(duration) - frame)

        # Команда для FFmpeg
        cmd = [
            'ffmpeg',
            '-i', input_file,
            '-ss', str(start_time),
            '-t', str(frame),
        ]

        if extended:
            cmd.extend([
                '-af', f'afade=t=in:st=0:d=1,afade=t=out:st={frame-1}:d=1'
            ])

        cmd.extend([
            '-y', output_file
        ])

        if log:
            print(f"Running command: {' '.join(cmd)}")

        # Запускаем FFmpeg
        result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if log:
            print(f"FFmpeg output: {result.stderr.decode('utf-8')}")

        temp_files.append(output_file)

        if log:
            print(f"--- processing file {i+1}: {file}")

    # Создаем список файлов для конкатенации
    with open(os.path.join(source, 'file_list.txt'), 'w') as f:
        for temp_file in temp_files:
            f.write(f"file '{temp_file}'\n")

    # Конкатенируем все временные файлы в один промежуточный WAV файл
    intermediate_file = os.path.join(source, 'intermediate.wav')
    cmd = [
        'ffmpeg',
        '-f', 'concat',
        '-safe', '0',
        '-i', os.path.join(source, 'file_list.txt'),
        '-c', 'copy',
        '-y',
        intermediate_file
    ]

    if log:
        print(f"Running concat command: {' '.join(cmd)}")

    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if log:
        print(f"FFmpeg concat output: {result.stderr.decode('utf-8')}")

    # Конвертируем промежуточный WAV файл в MP3
    if destination is None:
        destination = os.path.join(source, 'mix.mp3')

    cmd = [
        'ffmpeg',
        '-i', intermediate_file,
        '-y',
        destination
    ]

    if log:
        print(f"Running convert command: {' '.join(cmd)}")

    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if log:
        print(f"FFmpeg convert output: {result.stderr.decode('utf-8')}")

    # Удаляем временные файлы
    for temp_file in temp_files:
        os.remove(temp_file)
    os.remove(os.path.join(source, 'file_list.txt'))
    os.remove(intermediate_file)

    if log:
        print("--- done!")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Create a track mix from mp3 files.')
    parser.add_argument('--source', '-s', required=True, help='Source directory with mp3 files')
    parser.add_argument('--destination', '-d', help='Destination file name')
    parser.add_argument('--count', '-c', type=int, help='Number of files to process')
    parser.add_argument('--frame', '-f', type=int, default=10, help='Duration of each fragment in seconds')
    parser.add_argument('--log', '-l', action='store_true', help='Enable logging')
    parser.add_argument('--extended', '-e', action='store_true', help='Enable fade in/out')

    args = parser.parse_args()

    create_track_mix(args.source, args.destination, args.count, args.frame, args.log, args.extended)
