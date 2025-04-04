import numpy as np
from PIL import Image
from math import ceil

image_path = "chars_32.png"
width = 20
height = 32

num_chars = 98
img_cols = 16
border = 2

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

    print('character<uint32_t, 20>{{' + ', '.join([f'0x{d:08x}' for d in data]) + '}},')
