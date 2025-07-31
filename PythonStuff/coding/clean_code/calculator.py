class calculator():
    def solveAskedEquation(self) -> None:
        self.solveEquationErrorHandling()

    def solveEquationErrorHandling(self) -> None:
        try:
            equation = self.calculateEquation(self.askEquation())
            self.printEquation(equation)
        except Exception as e:
            print(e)

    def printEquation(self, equation) -> None:
        print(equation)

    def askEquation(self) -> str:
        return self.removeSpaces(input("Equation: "))

    def removeSpaces(self, sequence: str) -> str:
        return sequence.replace(" ", "")

    def checkValidEquation(self, sequence: str) -> bool:
        validBrackets = self.checkValidBrackets(sequence)
        validOperators = self.checkValidOperators(sequence)
        validNumbers = self.checkValidNumbers(sequence)
        return validBrackets and validOperators and validNumbers

    def checkValidBrackets(self, sequence: str) -> bool:
        validCount = self.checkValidBracketCount(sequence)
        validOrder = self.checkValidBracketOrdering(sequence)
        return validCount and validOrder

    def checkValidBracketCount(self, sequence: str) -> bool:
        bracketOpenCount = sequence.count("(")
        bracketCloseCount = sequence.count(")")
        return bracketOpenCount > 0 and bracketCloseCount > 0

    def checkValidBracketOrdering(self, sequence: str) -> bool:
        bracketCount = 0
        for character in sequence:
            if character == "(":
                bracketCount += 1
            if character == ")":
                bracketCount -= 1
            if bracketCount < 0:
                return False
        return bracketCount == 0

    def checkValidOperators(self, sequence: str) -> bool:
        return True

    def checkValidNumbers(self, sequence: str) -> bool:
        return True

    def calculateEquation(self, equation: str) -> str:
        while not equation.isdigit() and not self.isFloat(equation):
            equation = self.checkPriority(equation)

        return self.removeUselessFloat(equation)

    def isFloat(self, number: str) -> bool:
        return number.replace(".", "").isdigit()

    def removeUselessFloat(self, number: str) -> str:
        if self.checkValidFloat(number):
            return number
        decimalIndex = number.index(".")
        return str(number[:decimalIndex])

    def checkValidFloat(self, number: str) -> bool:
        if "." not in number:
            return True
        decimalIndex = number.index(".")+1
        return sum(int(i) for i in number[decimalIndex:]) > 0

    def checkPriority(self, equation: str) -> str:
        equationPriority = ["(", ")", "**", "//", "*", "/", "+", "-"]
        for priorityItem in equationPriority:
            if priorityItem in equation:
                return self.solveEquation(priorityItem, equation)
        return equation

    def solveEquation(self, item: str, equation: str) -> str:
        BRACKETS = "()"
        if item in BRACKETS:
            return self.solveBracketedEquation(equation)
        else:
            return self.solvePartOfEquation(item, equation)

    def replaceEquation(self, partOfEquation: str, answer: str, equation: str) -> str:
        equation = equation.replace(partOfEquation, answer, 1)
        return equation

    def solveBracketedEquation(self, equation: str) -> str:
        separatedEquation, equationWithoutBracket = self.separateBracketedEquation(
            equation)
        calculatedValue = self.calculateEquation(equationWithoutBracket)
        return equation.replace(separatedEquation, calculatedValue, 1)

    # Still Unclear
    def separateBracketedEquation(self, equation: str) -> tuple:
        startingIndex = equation.index("(")+1
        endingIndex = self.findEndingBracket(startingIndex, equation)
        return equation[startingIndex-1:endingIndex], equation[startingIndex:endingIndex-1]

    def findEndingBracket(self, startingIndex: int, equation: str) -> int:
        bracketCount, endingIndex = 1, startingIndex
        while bracketCount:
            bracketCount += self.checkBrackets(equation[endingIndex])
            endingIndex += 1
        return endingIndex

    # Switch Case Function
    def checkBrackets(self, character: str) -> int:
        if character == "(":
            return 1
        elif character == ")":
            return -1
        return 0

    def solvePartOfEquation(self, operator: str, equation: str) -> str:
        seperatedEquation = self.separatePartOfEquation(operator, equation)
        calculatedValue = str(self.operationErrorHandling(
            operator, seperatedEquation))
        return equation.replace(seperatedEquation, calculatedValue, 1)

    # Switch Case Function
    def doOperation(self, operator: str, equation: str) -> float:
        valueOne, valueTwo = map(float, equation.split(operator))
        if operator == "**":
            return valueOne ** valueTwo
        if operator == "//":
            return valueOne ** -valueTwo
        if operator == "*":
            return valueOne * valueTwo
        if operator == "/":
            return valueOne / valueTwo
        if operator == "+":
            return valueOne + valueTwo
        if operator == "-":
            return valueOne - valueTwo
        return 0.0

    def operationErrorHandling(self, operator: str, equation: str) -> float:
        try:
            return self.doOperation(operator, equation)
        except:
            print("Value Error!")
            return 0.0

    def separatePartOfEquation(self, operator: str, equation: str) -> str:
        startingIndex = equation.index(operator)
        startIndex = self.separateNumbersBehind(startingIndex, equation)
        endIndex = self.separateNumbersFront(
            startingIndex+len(operator), equation)

        return equation[startIndex+1:endIndex]

    def separateNumbersFront(self, startingIndex: int, equation: str) -> int:
        iteratingIndex = startingIndex
        while self.checkValidDigitandIndex(iteratingIndex, equation):
            iteratingIndex += 1
        return iteratingIndex

    def separateNumbersBehind(self, startingIndex: int, equation: str) -> int:
        iteratingIndex = startingIndex-1
        while self.checkValidDigitandIndex(iteratingIndex, equation):
            iteratingIndex -= 1
        return iteratingIndex

    def checkValidDigitandIndex(self, index: int, sequence: str) -> bool:
        validIndex = self.checkValidIndex(index, sequence)
        if not validIndex:
            return False
        validCharacter = self.checkValidIntegerAndFraction(sequence[index])
        return validCharacter

    def checkValidIndex(self, index: int, sequence: str) -> bool:
        return 0 <= index < len(sequence)

    def checkValidIntegerAndFraction(self, character: str) -> bool:
        return character.isdigit() or character == "."


def answerEquations():
    NewCalculator = calculator()
    NewCalculator.solveAskedEquation()
    while continueAsking():
        NewCalculator.solveAskedEquation()


def continueAsking():
    response = input("Exit? ")
    return response.lower() not in "yes"


answerEquations()
