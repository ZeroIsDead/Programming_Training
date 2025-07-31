# Update Details
# DIsplay
# Remove
# Restock


# Name, Stock, Price
items = {
    "cereal" : [10, 10],
    "milk" : [100, 10],
    "water": [1000, 10],
    ["tea", 200, 10]
}

# Update Details
# DIsplay
# Remove
# Restock


def check_if_item_exist():
    while True:
        itemName = input("Enter the Name of the Item You Want to Restock: ")

        if itemName in [i[0] for i in items]:
            return

def display_item():
    while True:
        itemName = input("Enter the Name of the Item You Want to Restock: ")

        for i in range(len(items)):
            if itemName == items[i][0]:
                print(items[i])
                return

def remove_item():
    while True:
        itemName = input("Enter the Name of the Item You Want to Restock: ")

        for i in range(len(items)):
            if itemName == items[i][0]:
                items.pop(i)
                return

    

def restock_item():
    while True:
        itemName = input("Enter the Name of the Item You Want to Restock: ")

        itemIndex = 0
        validName = False

        for i in range(len(items)):
            if itemName == items[i][0]:
                validName = True
                itemIndex = i
                break

        if validName:
            break
    
    while True:        
        amount = input("Enter the Amount You want to restock: ")

        if amount.isnumeric() and int(amount) > 0:
            items[itemIndex][1] = int(amount)
            return
        