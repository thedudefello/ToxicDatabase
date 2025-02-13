import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GL.shaders import compileProgram, compileShader
import numpy as np
import time

# Vertex Shader
VERTEX_SHADER = """
#version 330
in vec2 position;
out vec2 fragCoord;
void main() {
    fragCoord = position;
    gl_Position = vec4(position, 0.0, 1.0);
}
"""

# Fragment Shader for XOR Fractal with Pulsating Rainbow
FRAGMENT_SHADER = """
#version 330
in vec2 fragCoord;
out vec4 color;

uniform float time;
uniform vec2 resolution;

float xor_fractal(float x, float y) {
    return mod(float(int(x) ^ int(y)), 255.0) / 255.0;
}

vec3 hsv2rgb(float h, float s, float v) {
    vec3 rgb = clamp(abs(mod(h * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) - 3.0) - 1.0, 0.0, 1.0);
    return v * mix(vec3(1.0), rgb, s);
}

void main() {
    vec2 uv = fragCoord * resolution.xy / resolution.y;
    float fractal_value = xor_fractal(uv.x * 100.0, uv.y * 100.0);

    // Pulsating color based on time and fractal_value
    float hue = mod(time * 0.1 + fractal_value, 1.0);
    float alpha = 0.5 + 0.5 * sin(time * 3.0);
    vec3 rainbow = hsv2rgb(hue, 1.0, 1.0);

    color = vec4(rainbow * fractal_value, alpha);
}
"""

# Initialize Pygame and OpenGL
pygame.init()
screen = pygame.display.set_mode((800, 800), DOUBLEBUF | OPENGL)
pygame.display.set_caption("XOR Fractal Effect")

# Compile shaders and create shader program
shader = compileProgram(
    compileShader(VERTEX_SHADER, GL_VERTEX_SHADER),
    compileShader(FRAGMENT_SHADER, GL_FRAGMENT_SHADER)
)

# Define a fullscreen quad
quad = np.array([
    -1.0, -1.0,
     1.0, -1.0,
     1.0,  1.0,
    -1.0,  1.0,
], dtype=np.float32)

# Bind the quad to a vertex array
VAO = glGenVertexArrays(1)
VBO = glGenBuffers(1)

glBindVertexArray(VAO)
glBindBuffer(GL_ARRAY_BUFFER, VBO)
glBufferData(GL_ARRAY_BUFFER, quad.nbytes, quad, GL_STATIC_DRAW)

# Position attribute
position = glGetAttribLocation(shader, "position")
glEnableVertexAttribArray(position)
glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 0, ctypes.c_void_p(0))

# Main rendering loop
running = True
start_time = time.time()

while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
            break

    # Clear screen
    glClear(GL_COLOR_BUFFER_BIT)

    # Activate shader and pass in uniforms
    glUseProgram(shader)
    current_time = time.time() - start_time
    glUniform1f(glGetUniformLocation(shader, "time"), current_time)
    glUniform2f(glGetUniformLocation(shader, "resolution"), 800, 800)

    # Draw the quad
    glBindVertexArray(VAO)
    glDrawArrays(GL_QUADS, 0, 4)

    # Swap buffers
    pygame.display.flip()
    pygame.time.wait(10)

# Clean up
glDeleteBuffers(1, [VBO])
glDeleteVertexArrays(1, [VAO])
glUseProgram(0)
pygame.quit()
