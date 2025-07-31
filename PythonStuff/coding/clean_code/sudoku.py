import random

class cell:
    def __init__(self, value, x, y) -> None:
        self.value = value
        self.x = x
        self.y = y

class entropyCell:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
        self.gridPos = self.calculatePosition()
        self.entropy = list(map(str, range(1,10)))

    def calculatePosition(self):
        return (self.x//3, self.y//3)
    
    def removeEntropy(self, value):
        if value in self.entropy:
            self.entropy.remove(value)

    def checkCollapseableEntropy(self):
        return len(self.entropy) == 1



class board:
    def __init__(self, x, y) -> None:
        self.xDim = x
        self.yDim = y
        self.grid = self.createBoard()

    def __str__(self) -> str:
        return "\n".join([" ".join([rowCell.value 
                                    if isinstance(rowCell, cell) else 
                                    "-" 
                                    for rowCell in row]) for row in self.grid])
        

    def createBoard(self):
        return [[entropyCell(x, y) for x in range(self.xDim)] for y in range(self.yDim)]

class collapser:
    def __init__(self, board) -> None:
        self.board = board

    def collapseAll(self):
        for row in self.board:
            for rowCell in row:
                if isinstance(rowCell, cell):
                    continue
                self.collapse(rowCell)

    def collapse(self, currentCell):
        if not currentCell.entropy:
            return 
        
        completedCell = cell(random.sample(currentCell.entropy, 1)[0], currentCell.x, currentCell.y)
        self.board[currentCell.y][currentCell.x] = completedCell
        self.changeSurroundingEntropy(currentCell, completedCell.value)

    def changeSurroundingEntropy(self, cell, entropyValue):
        surroundingEntropyCells = self.getAffectedEntropy(cell)
        for eCell in surroundingEntropyCells:
            if isinstance(eCell, entropyCell):
                eCell.removeEntropy(entropyValue)
                if eCell.checkCollapseableEntropy():
                    self.collapse(eCell)

    def getAffectedEntropy(self, cell):
        row = self.board[cell.y]
        column = [currentRow[cell.x] for currentRow in self.board]
        gridCol = range(cell.gridPos[1]*3, (cell.gridPos[1]+1)*3)
        gridRow = range(cell.gridPos[0]*3, (cell.gridPos[0]+1)*3)
        grid = [self.board[y][x] for y in gridCol for x in gridRow]
        return row + column + grid


class boardFactory:
    def makeBoard(self):
        currentBoard = board(9, 9)
        collapsingUnit = collapser(currentBoard.grid)
        collapsingUnit.collapseAll()
        return currentBoard
    

class sudokuGame:
    def __init__(self) -> None:
        factory = boardFactory()
        self.newBoard = factory.makeBoard()

    def play(self):
        print(self.newBoard)

if __name__ == "__main__":
    game = sudokuGame()
    game.play()