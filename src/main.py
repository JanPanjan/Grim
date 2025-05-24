import os
import time
from screen import Screen

def main():
    win = Screen(45, 189) # font size 12
    x = win.r // 2
    y = win.c // 2 - 3
    down = True
    right = True
    fps = 60

    while True:
        win.putchar(" DVD ", [x, y])
        win.putchar("VIDEO", [x + 1, y])
        win.draw()

        time.sleep(1 / fps)

        if down:
            x += 1
        if not down:
            x -= 1
        if x == win.r - 3:
            down = False
        if x == 1:
            down = True
        if right:
            y += 1
        if not right:
            y -= 1
        if y == win.c - 6:
            right = False
        if y == 1:
            right = True


if __name__ == "__main__":
    main()
