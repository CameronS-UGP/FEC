# Calculates total fuel cost based on location input

print("Welcome to Fuel Expense Calculator\n")

def mainMenu(username):
    print("""
    Main Menu
    1: Calculate fuel expense for a shift
    2: View fuel expense history""")

def login():
    input("Enter Username: ")

username = input("Please enter your driver name: ")
mainMenu(username)