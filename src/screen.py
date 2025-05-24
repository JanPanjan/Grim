from os import system

class Graphics():
    """drawing, displaying, rendering functions"""

    def draw(self, l: list[list[str]]) -> None:
        """draws the 2D array of strings"""
        for i in range(len(l)):
            for j in range(len(l[0])):
                print(l[i][j], end="")
            print()


class Screen():
    """canvas, window, box, container even for displaying stuff"""
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

    def draw(self) -> None:
        _ = system("clear")
        self.g.draw(self.s)
        self.s = self.init_scr()

