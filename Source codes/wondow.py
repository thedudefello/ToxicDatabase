import tkinter as tk
import math
import colorsys
import random
import threading
from screeninfo import get_monitors

# Get the screen width and height to cover the entire screen
screen_width = get_monitors()[0].width
screen_height = get_monitors()[0].height

# Define window settings
num_windows = 5
window_size = 300

class UltraIntricateHyperCubeEffect:
    def __init__(self, root):
        self.root = root
        # Make the entire window background transparent
        self.root.wm_attributes("-transparentcolor", "black")
        # Set the window to always stay on top
        self.root.wm_attributes("-topmost", True)
        # Set canvas background to black and ensure it's also transparent
        self.canvas = tk.Canvas(self.root, width=window_size, height=window_size, bg="black", highlightthickness=0)
        self.canvas.pack()
        self.running = True
        self.hue = random.random()
        self.rotation_angle_x = 0  # Rotation around x-axis
        self.rotation_angle_y = 0  # Rotation around y-axis

        # Randomized movement parameters for bouncing effect
        self.x_velocity = random.choice([-1, 1]) * random.uniform(6, 12)
        self.y_velocity = random.choice([-1, 1]) * random.uniform(6, 12)

    def update_window_position(self):
        """Updates the position and rotation of the window."""
        x, y = self.root.winfo_x(), self.root.winfo_y()

        # Update position with increased velocity
        new_x = x + int(self.x_velocity)
        new_y = y + int(self.y_velocity)

        # Bounce off edges of the full screen
        if new_x <= 0 or new_x + window_size >= screen_width:
            self.x_velocity = -self.x_velocity * random.uniform(0.9, 1.1)  # Add slight randomness to the bounce
        if new_y <= 0 or new_y + window_size >= screen_height:
            self.y_velocity = -self.y_velocity * random.uniform(0.9, 1.1)

        # Update rotation for both x and y axes
        self.rotation_angle_x = (self.rotation_angle_x + 7) % 360
        self.rotation_angle_y = (self.rotation_angle_y + 5) % 360

        # Apply the new geometry to the window
        self.root.geometry(f"{window_size}x{window_size}+{new_x}+{new_y}")
        self.root.after(10, self.update_window_position)  # Faster updates for intense movement

    def draw_ultra_intricate_hypercube(self):
        """Draws an ultra-intricate, multi-layered hyper-cube effect with additional rotation and color detail."""
        self.canvas.delete("all")
        width, height = window_size, window_size

        # Define parameters for ultra-intricate detail
        num_layers = 16  # Number of nested squares
        max_offset = 120  # Maximum displacement from center

        for layer in range(num_layers):
            # Dynamic scale variation for "breathing" effect
            scale_variation = 1 + 0.02 * math.sin(math.radians(self.rotation_angle_x + layer * 5))
            layer_scale = (1 + layer * 0.1) * scale_variation
            layer_rotation_x = self.rotation_angle_x + layer * 15  # Different rotation on x-axis for each layer
            layer_rotation_y = self.rotation_angle_y + layer * 10  # Different rotation on y-axis for each layer
            layer_hue = (self.hue + layer * 0.04) % 1.0  # Layer-specific color transition
            rgb = colorsys.hsv_to_rgb(layer_hue, 1, 1)
            base_color = "#%02x%02x%02x" % (int(rgb[0] * 255), int(rgb[1] * 255), int(rgb[2] * 255))

            # Calculate coordinates for the square vertices with additional offset
            offset_factor = max_offset * layer_scale
            vertices = [
                (width / 2 + offset_factor * math.cos(math.radians(layer_rotation_x + 45)) * math.cos(math.radians(layer_rotation_y)),
                 height / 2 + offset_factor * math.sin(math.radians(layer_rotation_x + 45))),
                (width / 2 + offset_factor * math.cos(math.radians(layer_rotation_x + 135)) * math.cos(math.radians(layer_rotation_y)),
                 height / 2 + offset_factor * math.sin(math.radians(layer_rotation_x + 135))),
                (width / 2 + offset_factor * math.cos(math.radians(layer_rotation_x + 225)) * math.cos(math.radians(layer_rotation_y)),
                 height / 2 + offset_factor * math.sin(math.radians(layer_rotation_x + 225))),
                (width / 2 + offset_factor * math.cos(math.radians(layer_rotation_x + 315)) * math.cos(math.radians(layer_rotation_y)),
                 height / 2 + offset_factor * math.sin(math.radians(layer_rotation_x + 315))),
            ]

            # Draw each side of the nested square with gradient color and additional complex connections
            for i in range(len(vertices)):
                next_i = (i + 1) % len(vertices)
                self.canvas.create_line(vertices[i][0], vertices[i][1], vertices[next_i][0], vertices[next_i][1], fill=base_color, width=2)
                # Draw diagonals and cross-axes connections for additional complexity
                for j in range(i + 2, len(vertices)):
                    self.canvas.create_line(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1], fill=base_color, width=1)

        # Cycle the color spectrum slowly
        self.hue = (self.hue + 0.003) % 1.0
        if self.running:
            self.root.after(20, self.draw_ultra_intricate_hypercube)

    def stop(self):
        """Stops the animation."""
        self.running = False

def create_ultra_intricate_hypercube_window():
    """Creates a new tkinter window with the ultra-intricate hyper-cube effect."""
    root = tk.Tk()
    # Set the window transparency and remove borders
    root.wm_attributes("-transparentcolor", "black", "-topmost", True)  # Black will be treated as transparent and set always on top
    root.overrideredirect(1)  # Remove window decorations for a cleaner look
    # Random initial position on the screen
    root.geometry(f"{window_size}x{window_size}+{random.randint(0, screen_width - window_size)}+{random.randint(0, screen_height - window_size)}")
    hypercube = UltraIntricateHyperCubeEffect(root)
    hypercube.draw_ultra_intricate_hypercube()
    hypercube.update_window_position()
    root.protocol("WM_DELETE_WINDOW", hypercube.stop)  # Stop the animation on close
    root.mainloop()

# Open multiple tkinter windows in separate threads
threads = []
for _ in range(num_windows):
    thread = threading.Thread(target=create_ultra_intricate_hypercube_window)
    threads.append(thread)
    thread.start()

# Keep the threads running
for thread in threads:
    thread.join()
