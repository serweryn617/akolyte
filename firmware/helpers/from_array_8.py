import numpy as np
from PIL import Image
from math import ceil

from data import font_8


width = 5
height = 8
border = 1
img_cols = 16


img_rows = ceil(96 / img_cols)
img_chr_w, img_chr_h = width + border * 2, height + border * 2
image_data = np.ones((img_chr_h * img_rows, img_chr_w * img_cols), dtype=np.uint8) * 220

for n, char_data in enumerate(font_8):
    img_x = (n % img_cols) * img_chr_w + border
    img_y = (n // img_cols) * img_chr_h + border

    for x in range(width):
        column = char_data[x]
        for y in range(height):
            image_data[img_y + y, img_x + x] = 0 if column & (1 << y) else 255

image = Image.fromarray(image_data)
image.save("chars_8.png")
