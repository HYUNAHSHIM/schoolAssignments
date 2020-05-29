import glfw
import numpy as np
from OpenGL.GL import *

T = np.array([[1,0.,.0], [0.,1.,.0], [0.,.0,1.]])

def render(T):
     glClear(GL_COLOR_BUFFER_BIT)
     glLoadIdentity()
     # draw cooridnate
     glBegin(GL_LINES)
     glColor3ub(255, 0, 0)
     glVertex2fv(np.array([0.,0.]))
     glVertex2fv(np.array([1.,0.]))
     glColor3ub(0, 255, 0)
     glVertex2fv(np.array([0.,0.]))
     glVertex2fv(np.array([0.,1.]))
     glEnd()
     # draw triangle
     glBegin(GL_TRIANGLES)
     glColor3ub(255, 255, 255)
     glVertex2fv( (T @ np.array([.0,.5,1.]))[:-1] )
     glVertex2fv( (T @ np.array([.0,.0,1.]))[:-1] )
     glVertex2fv( (T @ np.array([.5,.0,1.]))[:-1] )
     glEnd() 

def key_callback(window, key, scancode, action, mods):
     global T
     if action == glfw.PRESS:
          if key == glfw.KEY_Q:
               M = np.array([[1,0.,-.1], [0.,1.,.0], [0.,.0,1.]])
               T = M@T
          elif key == glfw.KEY_E:
               M = np.array([[1,0.,+.1], [0.,1.,.0], [0.,.0,1.]])
               T = M@T
          elif key == glfw.KEY_A:
               M = np.array([[np.cos(np.radians(10)),-np.sin(np.radians(10)),0.],
                            [np.sin(np.radians(10)),np.cos(np.radians(10)),.0],
                            [0.,.0,1.]])
               T = T@M
          elif key == glfw.KEY_D:
               M = np.array([[np.cos(np.radians(-10)),-np.sin(np.radians(-10)),0.],
                            [np.sin(np.radians(-10)),np.cos(np.radians(-10)),.0],
                            [0.,.0,1.]])
               T = T@M
          elif key == glfw.KEY_1:
               T = np.array([[1,0.,.0], [0.,1.,.0], [0.,.0,1.]])
               
          elif key == glfw.KEY_W:
               M = np.array([[0.9,0.,.0], [0.,1.,.0], [0.,.0,1.]])
               T= M@T
          elif key == glfw.KEY_S:
               M = np.array([[np.cos(np.radians(10)),-np.sin(np.radians(10)),0.],
                            [np.sin(np.radians(10)),np.cos(np.radians(10)),.0],
                            [0.,.0,1.]])
               T = M@T

def main():
     global T
     if not glfw.init():
          return
     window = glfw.create_window(480,480,"2017029898-3-1", None, None)
     if not window:
          glfw.terminate()
          return

     glfw.set_key_callback(window, key_callback)
     glfw.make_context_current(window)

     while not glfw.window_should_close(window):
          glfw.poll_events()
          render(T)
          glfw.swap_buffers(window)

     glfw.terminate()

if __name__ == "__main__":
    main()
