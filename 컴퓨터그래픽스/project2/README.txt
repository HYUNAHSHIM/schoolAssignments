1. What I added

(1) New Function

=================================================================
def startRollerCoaster():
    global animationMode, cow2wld, ControlPoints, spline, cow2wldroller
    animationMode = True
    cow2wldroller = cow2wld.copy()
    Index = -1
    spline = 0

    track = []
    for i in range(3):
        for j in range(len(ControlPoints)):
            tmp = ControlPoints[j].copy()
            track.append(tmp)
    ControlPoints = track.copy()    

def endRollerCoaster():
    global ControlPoints, cow2wld, cow2wldroller, pickInfo, animationMode
    del ControlPoints[0:len(ControlPoints)+1]
    animationMode = False

def getControlPoint(i):
    global ControlPoints

    if i>= 0 and i < len(ControlPoints):
        return getTranslation(ControlPoints[i])

    return getTranslation(ControlPoints[len(ControlPoints)-1])


def getNowSplinePoint():
    global spline,  Index
    t = (float)(spline/60)
    p0 = getControlPoint(Index+0)
    p1 = getControlPoint(Index+1)
    p2 = getControlPoint(Index+2)
    p3 = getControlPoint(Index+3)
    p = 0.5 * ((2.0*p1) + (-1 * p0+p2)*t + (2.0*p0 - 5.0*p1 + 4.0*p2 - p3)* t*t + (-1 * p0 + 3.0*p1-3.0*p2+p3) * t**3)
    return vector3(p[0],p[1],p[2])

def rollerCoasterTimer():
    global cow2wldroller, spline, Index, ControlPoints
    if animationMode == False:
        return
    nt = getNowSplinePoint()
    setTranslation(cow2wldroller,nt)

    spline= spline +1
    if spline == 60:
        spline = 0
        Index = Index +1
        if Index == len(ControlPoints)-2:
            endRollerCoaster()
            return

def drawControlPointCows():
    global ControlPoints
    for i in range(len(ControlPoints)):
        drawCow(ControlPoints[i], False)

=================================================================
-startRollerCoaster(): for문에서 6마리의 소를 넣어주고 이 순서대로 3번 해줍니다.

-endRollerCoaster(): 이 함수가 호출되면 rollercoaster를 종료 해줍니다. 즉 animationmode를 false로
바꿔줍니다.

-getControlPoint(i): i에 따라서 control point를 가져옵니다.

-getNowSplinePoint(): Catmull-Rom spline curve를 계산해 줍니다.

-rollerCoasterTimer(): control point에 맞게 cow의 위치를 변경해 줍니다.

-drawControlPointCows(): animationmode가 아닌경우 display에서 호출해 줍니다.

(2) Modified Function

=================================================================

def display():
    ...

    # TODO: 
    # update cow2wld here to animate the cow.
    #animTime=glfw.get_time()-animStartTime;
    #you need to modify both the translation and rotation parts of the cow2wld matrix.

    if animationMode:
        drawCow(cow2wldroller, cursorOnCowBoundingBox)
    else:
        drawCow(cow2wld, cursorOnCowBoundingBox)
        drawControlPointCows()

    glFlush();

def onMouseButton(window,button, state, mods):
    global isDrag, V_DRAG, H_DRAG, cow2wld,ControlPoints, animationMode, first
    GLFW_DOWN=1;
    GLFW_UP=0;
    x, y=glfw.get_cursor_pos(window)
    if button == glfw.MOUSE_BUTTON_LEFT:
        if state == GLFW_DOWN:
            isDrag = V_DRAG
            print( "Left mouse down-click at %d %d\n" % (x,y))

            # start vertical dragging
        elif state == GLFW_UP and isDrag!= 0:
            if animationMode == False:
                if first == True:
                    nowControlPoint = cow2wld.copy()
                    ControlPoints.append(nowControlPoint)
                    if(len(ControlPoints) == 6):
                        startRollerCoaster()
                        first = False
                first = True
            isDrag = H_DRAG
            print("Left mouse up\n")
            # start horizontal dragging using mouse-move events.
    elif button == glfw.MOUSE_BUTTON_RIGHT:
        if state == GLFW_DOWN:
            print( "Right mouse click at (%d, %d)\n"%(x,y) );

def onMouseDrag(window, x, y):
    global isDrag,cursorOnCowBoundingBox, pickInfo, cow2wld, V_DRAG
    if isDrag: 
        print( "in drag mode %d\n"% isDrag);
        if  isDrag==V_DRAG:
            # vertical dragging
            # TODO:
            # create a dragging plane perpendicular to the ray direction, 
            # and test intersection with the screen ray.
            if cursorOnCowBoundingBox:
                ray=screenCoordToRay(window, x, y)
                pp=pickInfo
                p=Plane(vector3(1,0,0), getTranslation(cow2wld));
                c=ray.intersectsPlane(p);

                currentPos=ray.getPoint(c[1])

                
                T=np.eye(4)
                setTranslation(T, currentPos-getTranslation(cow2wld))
                cow2wld=T@cow2wld

    ...

       

def main():

    ...

    initialize(window);
    previous = glfw.get_time()  
    time = 2.0                  
    while not glfw.window_should_close(window):
        glfw.poll_events()
        display()
        if animationMode:
            now = glfw.get_time()
            delta = now - previous
            previous = now
            time = time - delta
            if(time <= 0.0):
                rollerCoasterTimer()

        glfw.swap_buffers(window)

    ...

=================================================================

-display(): modified the part to draw cow

-onMouseButton(window,button, state, mods): modified not to display cow when I click the cow first time

-onMouseDrag(window, x, y): added the part of vertical drag

-main(): added timer