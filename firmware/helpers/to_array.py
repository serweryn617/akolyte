import numpy as np
from PIL import Image
from math import ceil

image_path = "chars_8.png"
num_chars = 96
img_cols = 16
border = 1

width = 5
height = 8

img_rows = ceil(num_chars / img_cols)
img_chr_w, img_chr_h = width + border * 2, height + border * 2

image = Image.open(image_path).convert('L')  # convert to grayscale
pixel_data = np.array(image)
binary_data = (pixel_data < 128).astype(np.uint8)

for n in range(num_chars):
    img_x = (n % img_cols) * img_chr_w + border
    img_y = (n // img_cols) * img_chr_h + border

    data = []

    for x in range(width):
        column = 0
        for y in range(height):
            if binary_data[img_y + y, img_x + x]:
                column |= (1 << y)
        data.append(column)

    print('{' + ', '.join([hex(d) for d in data]) + '},')
