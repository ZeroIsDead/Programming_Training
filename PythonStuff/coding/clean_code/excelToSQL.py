import openpyxl as xl


file = "IDB.xlsx"
workbook = xl.load_workbook(file)
worksheets = workbook.sheetnames
worksheetData = {}

for worksheetTitle in worksheets:
    worksheet = workbook[worksheetTitle]
    data = workbook.copy_worksheet(worksheet)
    worksheetData[file + " " + worksheetTitle] = data

workbook.close()

print(worksheetData)



