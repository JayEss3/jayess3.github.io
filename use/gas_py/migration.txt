# James Spies, jspies2017@my.fit.edu
# CSE 2050, Fall 2019
# Project: Manatee Migration

from sys import(stdin, stdout)
#Recursive statement to get maximum possible distance
#for amount of cans of gas
def RECURSION(cans, C, R, distance):
    #Base case: no more cans of gas,
    #gone max distance
    if(cans == 0):
        #Multiply distance by 100 bc fuel consumption
        #is based on 100 km
        return (distance * 100)
    #If you have 2 or 1 cans of gas left,
    #Fill up boat and go as far as you can
    elif(cans <= 2):

        cans -= 1

        distance += C / R

        return RECURSION(cans, C, R, distance)
    #If you have more than 2 cans of gas,
    #Move all cans of gas to a new spot away
    #using only one can of gas to move all
    #other cans of gas.
    else:

        cans -= 1

        distance += (C / R) / ((cans * 2) - 1)

        return RECURSION(cans, C, R, distance)

for line in stdin:
    
    cans, C, R = [i for i in line.split()]
    #Convert variables to proper varialbe form
    cans = int(cans)
    C = float(C)
    R = float(R)
    #Proper output method
    stdout.write(f'{(RECURSION(cans, C, R, 0))}\n')
