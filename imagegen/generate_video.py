#!./env/bin/python

import argparse
import os
import tempfile
from pathlib import Path
from PIL import Image


def get_next_available_filename(directory, base_name="video", extension=".mp4"):
    # Start the counter at 1
    counter = 1
    
    # Loop to find the next available filename
    while True:
        filename = f"{base_name}{counter}{extension}"
        file_path = os.path.join(directory, filename)
        
        # If the file does not exist, return the filename
        if not os.path.exists(file_path):
            return filename
        
        # Increment the counter for the next check
        counter += 1

parser = argparse.ArgumentParser(prog='generate_video')
parser.add_argument('filename')
parser.add_argument('-f', '--fps', default=60)
parser.add_argument('-s', '--size', default=300) # width = height
parser.add_argument('-r', '--rescale', default=3)
parser.add_argument('-k', '--skip', default=1)

args = parser.parse_args()

# You may have to edit these if your DLA is too big
scale = args.rescale
skip = int(args.skip)
width = args.size
height = args.size
image = Image.new('1', (width, height), 1)

with open(args.filename) as file:
    with tempfile.TemporaryDirectory() as tmpdirname:
        Path("videos").mkdir(parents=True, exist_ok=True)
        
        counter = 0
        i = 0
        for line in file:
            x, y = map(lambda s: int(s.strip()), line.split(','))
            x += width // 2
            y += height // 2
            image.putpixel((x, y), 0)

            if counter >= skip:
                if scale > 1:
                    scaled = image.resize((width * scale, height * scale))
                    scaled.save(f"{tmpdirname}/{str(i).zfill(5)}.png")
                else:
                    image.save(f"{tmpdirname}/{str(i).zfill(5)}.png")
                i += 1
                counter = 0
            counter += 1

        video_filename = get_next_available_filename("videos")
        os.system(f"ffmpeg -f image2 -r {args.fps} -i \
                {tmpdirname}/%05d.png -vcodec mpeg4 -y ./videos/{video_filename}")
