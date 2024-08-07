from PIL import Image

# Function to create an image from the grid
def create_image_from_grid(input_file, output_file):
    # Read the grid from the text file
    with open(input_file, 'r') as file:
        grid = [line.strip() for line in file.readlines()]

    # Check that the grid is 1500x1500
    if len(grid) != 1500 or any(len(row) != 1500 for row in grid):
        raise ValueError("The input grid must be 1500x1500")

    # Create a new image with mode 'RGB' for colored pixels
    image = Image.new('RGB', (1500, 1500))

    # Fill the image with pixels based on the grid
    pixels = image.load()
    for y in range(1500):
        for x in range(1500):
            if grid[y][x] == '#':
                pixels[x, y] = (0, 0, 0)  # Black pixel
            elif grid[y][x] == 'A':
                pixels[x, y] = (255, 0, 0)  # Red pixel
            elif grid[y][x] == 'B':
                pixels[x, y] = (0, 0, 255)  # Blue pixel
            else:
                pixels[x, y] = (255, 255, 255)  # White pixel

    # Save the image
    image.save(output_file)

# Example usage
create_image_from_grid('grid.txt', 'output.png')
