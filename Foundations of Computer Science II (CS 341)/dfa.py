# Define sets of characters that fall under the language L. These are considered accepted characters in a given string.
gamma = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'} # All lower-case Roman letters
Lambda = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'} # All Arabic numerals
delta = {'.'}
phi = {'@'}


'''
Initial function begins the DFA processes to parse through each character of a user inputted string.
'''
def dfa(string):
    print("Your inputted string: " + string)
    q1(0, string)


# Below are functions corresponding to each individual state in the DFA.
# Each character read is mapped to the next state. Function call to the next state will be made based on current character being processed.
# Each function/state checks if the end of the string has been reached. If it is not the end, function will continue parsing.
# If character causes string to be rejected, it will go to the trap state and stay there till rest of the string is processed.
# Position of string is kept track of using "index" variable.


# string in language L must start with lower-case Roman letter. If it doesn't, go to trap state.
def q1(index, string):
    char = string[index]  # current character being processed
    print("In starting state: q1.")
    if char in gamma:
        q2((index+1), string)
    else:
        q10((index+1), string)

# if character processed is anything other than letter, numeral, or @, go to trap state
def q2(index, string):
    print("current state: q2    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in delta:
            q9((index+1), string)
        elif char in Lambda or char in gamma:
            q2((index+1), string)
        elif char in phi:
            q3((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter go to trap state
def q3(index, string):
    print("current state: q3    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in gamma:
            q4((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter, numeral, or '.', go to trap state
def q4(index, string):
    print("current state: q4    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in gamma or char in Lambda:
            q4((index+1), string)
        elif char in delta:
            q5((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter go to trap state
def q5(index, string):
    print("current state: q5    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in gamma and char != 'c':
            q4((index+1), string)
        elif char == 'c':
            q6((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter, numeral, or '.', go to trap state
def q6(index, string):
    print("current state: q6    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in delta:
            q5((index+1), string)
        elif char == 'o':
            q7((index+1), string)
        elif (char in gamma and char != 'o') or char in Lambda:
            q4((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter, numeral, or @, go to trap state
def q7(index, string):
    print("current state: q7    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in delta:
            q5((index+1), string)
        elif char == 'm':
            q8((index+1), string)
        elif (char in gamma and char != 'm') or char in Lambda:
            q4((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter, numeral, or '.', go to trap state
def q8(index, string):
    # DFA's accepting state
    print("current state: q8    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is ACCEPTED")
    else:
        char = string[index]
        if char in delta:
            q5((index+1), string)
        elif char in gamma or char in Lambda:
            q4((index+1), string)
        else:
            q10((index+1), string)

# if character processed is anything other than letter, go to trap state
def q9(index, string):
    print("current state: q9    character processed: " + string[index-1])
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        if char in gamma:
            q2((index+1), string)
        else:
            q10((index+1), string)

# string is rejected - will loop in trap state till end of string is reached
def q10(index, string):
    print("current state: q10   character processed: " + string[index-1] + " (IN TRAP STATE)")
    if index == len(string):
        print("String has been parsed & is REJECTED")
    else:
        char = string[index]
        q10((index+1), string)


# Test Cases 1-20
dfa('f8o9o@ab32cdef.com')
dfa('z@c.com')
dfa('ba@ba.co')
dfa('edfg@.com')
dfa('web2web.a.c97c.com@j.k68c42.computer.com')
dfa('fo8o@goo2.com..com')
dfa('ab67qe.@boom.com')
dfa('edu2c@computer56.comp')
dfa('redblue@green..com')
dfa('random6@com')
dfa('p654aa7e@a896.com.com')
dfa('www@com.coma')
dfa('wwwb@com.co')
dfa('34big.com@bbdef29.com')
dfa('food@for.com@')
dfa('net.a.b.4c@comma3.com.com')
dfa('net84work.abb@common.6com.com')
dfa('@abcde.com')
dfa('people5.d7og.c8at@c.com3.com')
dfa('cable..cord@fort.com')


#2. Ask user if they want to enter a string. Enter y or n. Process string if y, quit if n. Ask user again for another string after process is complete.
while True:
    user = input("Would you like to enter a string? (Enter y/n) ")
    if user == 'n':
        quit()
    elif user == 'y':
        string = input("Please enter a string over \u03A3: ")
        dfa(string)
    else:
        input("Invalid option. Hit enter to try again.")
