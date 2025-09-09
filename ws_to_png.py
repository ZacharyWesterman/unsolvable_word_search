#! /usr/bin/env python3
# Takes input from stdin in the form of a word search grid and outputs a PNG image of the grid.
# Example usage: ./unsolvable_word_search | ./ws_to_png.py puzzle.png

import sys
from PIL import Image, ImageDraw, ImageFont


def main():
    if len(sys.argv) != 3:
        print("Usage: ws_to_png.py <title> <output.png>")
        sys.exit(1)

    title = sys.argv[1]
    output_file = sys.argv[2]

    # Read the grid from stdin
    grid = [line.replace(' ', '').strip()
            for line in sys.stdin if line.strip()]
    if not grid:
        print("No input grid provided.")
        sys.exit(1)

    rows = len(grid)
    cols = len(grid[0])

    # Create an image with white background
    cell_size = 50
    img_width = cols * cell_size
    img_height = rows * cell_size
    image = Image.new("RGB", (img_width, img_height), 2147483647)
    draw = ImageDraw.Draw(image)

    # Load a font
    try:
        font = ImageFont.truetype("arial.ttf", 36)
    except IOError:
        font = ImageFont.load_default()

    # Draw the grid and letters
    for r in range(rows):
        for c in range(cols):
            x0 = c * cell_size
            y0 = r * cell_size
            x1 = x0 + cell_size
            y1 = y0 + cell_size

            # Draw cell border
            draw.rectangle([x0, y0, x1, y1], outline="black")

            # Draw letter centered in the cell
            letter = grid[r][c]
            w = draw.textlength(letter, font=font)
            h = w
            text_x = x0 + (cell_size - w) / 2
            # Adjust vertical position slightly
            text_y = y0 + (cell_size - h) / 2 - 5
            draw.text((text_x, text_y), letter, fill=0, font=font)

    # Make a new image that's taller and wider to add a border and title
    img_width += 100
    img_height += 150
    new_image = Image.new("RGB", (img_width, img_height), 2147483647)
    new_image.paste(image, (50, 100))
    image = new_image
    draw = ImageDraw.Draw(image)

    # Add a border around the entire grid, and a title
    border_size = 10
    draw.rectangle([40, 90, img_width - 40, img_height - 40],
                   outline="black", width=border_size)
    title_w = draw.textlength(title, font=font)
    title_x = (img_width - title_w) / 2
    draw.text((title_x, 20), title, fill=0, font=font)

    # Save the image
    image.save(output_file)
    print(f"Saved word search image to {output_file}")


if __name__ == "__main__":
    main()
