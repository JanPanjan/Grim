import os
import time

class Graphics():
    def draw(self, l: list[list[str]]) -> None:
        for i in range(len(l)):
            for j in range(len(l[0])):
                print(l[i][j], end="")
            print()

class Screen():
    def __init__(self, r: int, c: int) -> None:
        self.r: int = r
        self.c: int = c
        self.s: list[list[str]] = self.init_scr()
        self.g: Graphics = Graphics()

    def init_scr(self) -> list[list[str]]:
        screen: list[list[str]] = list()
        for i in range(self.r):
            screen.append([]) # make space for a new row
            for j in range(self.c):
                if (i == 0 or i == self.r - 1) and (j == 0 or j == self.c - 1):
                    screen[i].append("+")
                elif i == 0 or i == self.r - 1:
                    screen[i].append("-")
                elif j == 0 or j == self.c - 1:
                    screen[i].append("|")
                else:
                    screen[i].append(" ")
        return screen

    def putchar(self, c: str, pos: list[int]) -> None:
        for i in range(len(c)):
            if i == self.c:
                break
            self.s[pos[0]][pos[1] + i] = c[i]

    def restore(self) -> None:
        self.s = self.init_scr()

    def refresh(self) -> None:
        _ = os.system("clear")
        self.g.draw(self.s)
        self.restore()

def main():
    win = Screen(22, 83)
    x = win.r // 2
    y = win.c // 2 - 3
    down = True
    right = True

    while True:
        win.putchar(" DVD ", [x, y])
        win.putchar("VIDEO", [x + 1, y])
        win.refresh()
        time.sleep(0.05)

        if (x == win.r + 1 and y == win.c - 6) or (x == win.r + 1 and y == 1) or (x == 1 and y == win.c - 6) or (x == 1 and y == 1):
            msg = "B O O M"
            x = win.r // 2
            y = (win.c // 2) - (len(msg) // 2)
            n = 50
            blank = True

            while n > 0:
                win.putchar(str(n), [0, 0])
                if blank:
                    win.putchar(" " * len(msg), [x, y])
                else:
                    win.putchar(msg, [x, y])
                win.refresh()
                time.sleep(0.05)
                n -= 1
                blank = not blank if n % 5 == 0 else blank

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
