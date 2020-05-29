import glfw
import numpy as np
from OpenGL.GL import *

tp = [GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_QUADS, GL_QUAD_STRIP, GL_POLYGON]
type_def = 4

def render():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    glBegin(tp[type_def-1])
    for n in range(0,12):
        glVertex(np.cos(np.pi*2*(n/12)),np.sin(np.pi*2*(n/12)))
    glEnd()

def key_callback(window, key, scancode, action, mods):
    global type_def
    if action==glfw.PRESS:
        if key == glfw.KEY_1:
            type_def = 1
        elif key == glfw.KEY_2:
            type_def = 2
        elif key == glfw.KEY_3:
            type_def = 3
        elif key == glfw.KEY_4:
            type_def = 4
        elif key == glfw.KEY_5:
            type_def = 5
        elif key == glfw.KEY_6:
            type_def = 6
        elif key == glfw.KEY_7:
            type_def = 7
        elif key == glfw.KEY_8:
            type_def = 8
        elif key == glfw.KEY_9:
            type_def = 9
        elif key == glfw.KEY_0:
            type_def = 0

        return
                     
        
def main():
    if not glfw.init():
            return
    window = glfw.create_window(480,480, "2017029898-2-1", None, None)
    if not window:
            glfw.terminate()
            return

    glfw.set_key_callback(window, key_callback)

    glfw.make_context_current(window)

    while not glfw.window_should_close(window):
            glfw.poll_events()
            render()
            glfw.swap_buffers(window)

    glfw.terminate()

if __name__ == "__main__":
    main()
