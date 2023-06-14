#1. Define variables.
digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'} # All Arabic numerals
operators = {'+', '-', '*', '/'} #other accepted terminals include %, ., (, )
stack = [] #use to push/pop (,),% symbols


'''
Initial function begins the PDA processes to parse through each character of a user inputted string.
'''
def pda(string):
    print("\nYour inputted string: " + string)
    q1(0, string)


# 2.
# Below are functions corresponding to each individual state in the PDA.
# Each character read is mapped to the next state. Function call to the next state will be made based on current character being processed.
# Each function/state will "crash" and stop processing string if no specific mapping exists.
# Position of string is kept track of using "index" variable.
# Each state prints out the symbol read, popped, and pushed.
# \u03B5 is unicode for the symbol epsilon which represents the empty string


# Every string in the language must start with % symbol
def q1(index, string):
    char = string[index]  # current character being processed
    print("In starting state: q1.")
    if char == '%':
        stack.append('%')
        q2((index+1), string, '\u03B5', '%')
    else:
        print("PDA has crashed and & string is REJECTED")

# Branches into the 3 ways a string in the language can start with after %: digit, (, .
def q2(index, string, pop, push):
    print("current state: q2\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q4((index+1), string, '\u03B5', '\u03B5')
    elif char == '.':
        q3((index+1), string, '\u03B5', '\u03B5')
    elif char == '(':
        stack.append('(')
        q7((index+1), string, '\u03B5', '(')
    else:
        print("PDA has crashed and & string is REJECTED")

# State q3 called after '.' symbol read; next symbol read is digit
def q3(index, string, pop, push):
    print("current state: q3\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q6((index+1), string, '\u03B5', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

# State q4 called after digit is called; next symbol read is '.'
def q4(index, string, pop, push):
    print("current state: q4\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q4((index+1), string, '\u03B5', '\u03B5') #loop within same state for each digit read
    elif char == '.':
        q5((index+1), string, '\u03B5', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

def q5(index, string, pop, push):
    print("current state: q5\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q5((index+1), string, '\u03B5', '\u03B5') #loop within same state for each digit read
    elif char in operators:
        q8((index+1), string, '\u03B5', '\u03B5')
    elif char == ')' and stack[-1] == '(': #peek top of the stack beforing popping
        stack.pop()
        q9((index+1), string, '(', '\u03B5')
    elif char == '%':
        q10((index+1), string, '%', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

def q6(index, string, pop, push):
    print("current state: q6\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q6((index+1), string, '\u03B5', '\u03B5') #loop within same state for each digit read
    elif char in operators:
        q8((index+1), string, '\u03B5', '\u03B5')
    elif char == ')' and stack[-1] == '(': #peek top of the stack beforing popping
        stack.pop()
        q9((index+1), string, '(', '\u03B5') 
    elif char == '%' and stack[-1] == '%': #peek top of the stack beforing popping
        stack.pop()
        q10((index+1), string, '%', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

# State q7 called after '(' symbol read
def q7(index, string, pop, push):
    print("current state: q7\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in digits:
        q4((index+1), string, '\u03B5', '\u03B5')
    elif char == '.':
        q3((index+1), string, '\u03B5', '\u03B5')
    elif char == '(':
        stack.append('(')
        q7((index+1), string, '\u03B5', '(') #loop within same state for each digit read
    else:
        print("PDA has crashed and & string is REJECTED")

# State q8 called after operator symbol read
def q8(index, string, pop, push):
    print("current state: q8\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char == '(':
        stack.append('(')
        q7((index+1), string, '\u03B5', '(') 
    elif char in digits:
        q4((index+1), string, '\u03B5', '\u03B5')
    elif char == '.':
        q3((index+1), string, '\u03B5', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

# State q9 called after ')' symbol read
def q9(index, string, pop, push):
    print("current state: q9\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    char = string[index]
    if char in operators:
        q8((index+1), string, '\u03B5', '\u03B5')    
    elif char == ')' and stack[-1] == '(': #peek top of the stack beforing popping
        stack.pop()
        q9((index+1), string, '(', '\u03B5') #loop within same state for each digit read
    elif char == '%' and stack[-1] == '%': #peek top of the stack beforing popping
        stack.pop()
        q10((index+1), string, '%', '\u03B5')
    else:
        print("PDA has crashed and & string is REJECTED")

# PDA's accept state --> Every string in the language must end with % symbol
def q10(index, string, pop, push):
    print("current state: q10\tcharacter read: " + string[index-1] + "\tpopped: " + pop + "\tpushed: " + push)
    if index == len(string):
        print("String has been parsed & is ACCEPTED")
    else:
        print("PDA has crashed and & string is REJECTED")


#3. Ask user if they want to enter a string. Enter y or n. Process string if y, quit if n. Ask user again for another string after process is complete.
while True:
    user = input("Would you like to enter a string? (Enter y/n) ")
    if user == 'n':
        quit()
    elif user == 'y':
        string = input("Please enter a string over \u03A3: ")
        pda(string)
    else:
        input("Invalid option. Hit enter to try again.")


# TEST CASES
pda('%381.5886%') #1
pda('%.8+7.-8.00/90.765+%') #2
pda('%7956.+.492*341.2/060.10/52581.263-.9+.53/7.%') #3
pda('%382.89*34%') #4
pda('%4.239-.*7.29%') #5
pda('%6.88.6+32.208%') #6
pda('%(1.2+(3.4-.9)/39).3%') #7
pda('%(.3)64%') #8
pda('%((824.23+(9.22-00.0)*21.2))+((.2/7.))%') #9
pda('%(())%') #10
pda('%((14.252+(692.211*(.39+492.1))/49.235)%') #11
pda('%+6.5\%') #12
pda('%26.0*(.87/((4.+.2)/(23.531)-2.9)+6.)/(((823.*.333-57.*8.0)/.33+.0))%') #13
pda('%.0*(32.922+.7-*9.))%') #14
pda('%(4.+(.8-9.))/2.)*3.4+(5.21/34.2%') #15
