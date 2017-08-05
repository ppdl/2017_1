#############################
univ_id = "2013147513" ## Univ. Num.
password = "01034415131"   ## Your Phone Number
#############################

from tkinter import Tk, Canvas, Frame, Button, BOTH, TOP, LEFT, RIGHT, BOTTOM
from Problem import Problem
MARGIN = 20  # Pixels around the board
SIDE = 50  # Width of every board cell.
WIDTH = HEIGHT = MARGIN * 2 + SIDE * 9  # Width and height of the whole board
DELAY = 0.05  # the delay time makes the changing number visible

class SudokuUI(Frame):
    def __init__(self, parent):
        Frame.__init__(self, parent)
        self.parent = parent
        self.__initUI()

    def __initUI(self):
        self.parent.title("AI: Sudoku Solver")
        self.pack(fill=BOTH)
        self.canvas = Canvas(self, width=WIDTH, height=HEIGHT + 10)
        self.problem = Problem(self.canvas, 0, DELAY)

        # Initialize each cell in the puzzle
        for i in range(1, 10):
            for j in range(1, 10):
                self.item = self.canvas.create_text(
                    MARGIN + (j - 1) * SIDE + SIDE / 2, MARGIN + (i - 1) * SIDE + SIDE / 2,
                    text='', tags="numbers", fill="black", font=("Helvetica", 12)
                )
        self.item = self.canvas.create_text(40, 490, text='Count :', fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(95, 490, text='', fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(170, 490, text='Average :', fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(225, 490, text='',fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(320, 490, text='Ranking :',fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(370, 490, text='', fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(420, 490, text='Total :', fill="black", font=("Helvetica", 13))
        self.item = self.canvas.create_text(460, 490, text='', fill="black", font=("Helvetica", 13))
        self.canvas.pack(fill=BOTH, side=TOP)
        self.start_button1 = Button(self, text="__Start__", command=self.__start_solver)
        self.start_button2 = Button(self, text="__Submit__", command=self.__submit)
        self.start_button2.pack(side=LEFT)
        self.start_button1.pack(side=RIGHT)
        self.start_button2.config(state="disabled")
        self.__draw_grid()

    # Draws 9x9 grid
    def __draw_grid(self):
        for i in range(10):
            width = 3 if i % 3 == 0 else 1
            x0 = MARGIN + i * SIDE
            y0 = MARGIN
            x1 = MARGIN + i * SIDE
            y1 = HEIGHT - MARGIN
            self.canvas.create_line(x0, y0, x1, y1, fill="black", width=width)
            x0 = MARGIN
            y0 = MARGIN + i * SIDE
            x1 = WIDTH - MARGIN
            y1 = MARGIN + i * SIDE
            self.canvas.create_line(x0, y0, x1, y1, fill="black", width=width)

    def __start_solver(self):
        self.start_button1.config(state="disabled")
        for i in range(100):
            for m in range(1, 10):
                for n in range(1, 10):
                    self.canvas.itemconfig(9 * (m - 1) + n, text='', tags="numbers", fill="black")
            self.SudokuSolver = SudokuSolver(self.problem)
            self.SudokuSolver.solver()
            if self.problem.finished == 0:
                self.problem.fail()
                break
            self.canvas.update()
            self.problem = Problem(self.canvas, self.problem.tk, 0)
        self.problem.update_a()
        self.start_button2.config(state="active")

    def __submit(self):
        request = self.problem.submit(univ_id, password)
        message = request.split(',')
        if int(message[0]) == 100:
            self.problem.fail_10min()
        elif int(message[0]) == 101:
            self.canvas.update()
            self.canvas.itemconfig(87, text=int(message[1]), tags="numbers", fill="blue")
            self.canvas.itemconfig(89, text=int(message[2]), tags="numbers", fill="blue")
            self.problem.already_done()
        elif int(message[0]) == 102:
            self.canvas.update()
            self.canvas.itemconfig(87, text=int(message[1]), tags="numbers", fill="blue")
            self.canvas.itemconfig(89, text=int(message[2]), tags="numbers", fill="blue")
            self.problem.is_done()
        elif int(message[0]) == 501:
            print("501")
            self.problem.wrong_id_pw()

class SudokuSolver():
    def __init__(self, problem):
        self.problem = problem
        
    def getMinCell(self,puzzle,vlst,hlst,qlst):
        for _ in range(81):
            min = 10
            for i in range(9):
                for j in range(9):                   
                    if self.puzzle[i][j] != 0:
                        continue
                    posNum = list(range(1,10))
                    hx = i - i%3
                    hy = j - j%3
                    for k in range(1,10):
                        if k in vlst[j]:
                            posNum.remove(k)
                            continue
                        elif k in hlst[i]:
                            posNum.remove(k)
                            continue
                        elif k in qlst[hx + int(hy/3)]:
                            posNum.remove(k)
                            continue
                    if len(posNum) < min:
                        min = len(posNum)
                        minx = i
                        miny = j
                        t = posNum
            return [minx,miny,t]
            
    def solver(self):
        # TO DO: need to write solver
        # Your code goes here..
        
        self.puzzle = [[0] * 9 for _ in range(9)]
        
        vlst = [[] for _ in range(9)]
        hlst = [[] for _ in range(9)]
        qlst = [[] for _ in range(9)]
            
        for _ in range(81):
            minCoord = self.getMinCell(self.puzzle,vlst,hlst,qlst)
            minx = minCoord[0]
            miny = minCoord[1]
            posNum = minCoord[2]
            
            hX = minx - minx%3
            hY = miny - miny%3
            
            for k in posNum:
                if self.problem.checker(minx+1,miny+1,k) == 1:
                    self.puzzle[minx][miny] = k
                    hlst[minx].append(k)
                    vlst[miny].append(k)
                    qlst[hX + int(hY/3)].append(k)
                    break
                               
        # If the problem has finished, this function will display "Finished!"
        # self.problem.is_done()

if __name__ == "__main__":
    root = Tk()
    SudokuUI(root)
    root.geometry("%dx%d" % (WIDTH, HEIGHT + 40))
    root.mainloop()
