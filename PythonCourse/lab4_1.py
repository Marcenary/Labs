import os
import struct
import sys

def read_id3v1_tag(file_path):
    try:
        with open(file_path, 'rb') as f:
            f.seek(-128, 2)  # Переход к последним 128 байтам файла
            tag_data = f.read(128)
            if tag_data[:3].decode('utf-8', errors='ignore') != 'TAG':
                return None
            return tag_data
    except IOError:
        return None

def parse_id3v1_tag(tag_data):
    if not tag_data:
        return None

    # Распаковка данных тега
    tag = {
        'header': tag_data[0:3].decode('utf-8', errors='ignore'),
        'title': tag_data[3:33].decode('utf-8', errors='ignore').strip(),
        'artist': tag_data[33:63].decode('utf-8', errors='ignore').strip(),
        'album': tag_data[63:93].decode('utf-8', errors='ignore').strip(),
        'year': tag_data[93:97].decode('utf-8', errors='ignore').strip(),
        'comment': tag_data[97:127].decode('utf-8', errors='ignore').strip(),
        'track': struct.unpack('B', tag_data[126:127])[0],
        'genre': struct.unpack('B', tag_data[127:128])[0]
    }

    return tag

def print_hex_dump(data):
    for i in range(0, len(data), 16):
        line = data[i:i+16]
        hex_line = ' '.join(f'{b:02x}' for b in line)
        print(f'{i:08x}: {hex_line}')

def main(directory, dump_hex):
    for filename in os.listdir(directory):
        if filename.endswith('.mp3'):
            file_path = os.path.join(directory, filename)
            tag_data = read_id3v1_tag(file_path)
            if tag_data:
                tag = parse_id3v1_tag(tag_data)
                if tag:
                    print(f"{tag['artist']} - {tag['title']} - {tag['album']}")
                    if dump_hex:
                        print(f"Hex dump for {filename}:")
                        print_hex_dump(tag_data)

if __name__ == "__main__":
    directory = sys.argv[1]
    dump_hex = '-d' in sys.argv
    main(directory, dump_hex)
