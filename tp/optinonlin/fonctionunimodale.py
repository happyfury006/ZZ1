# import numpy as np
import math as mp

def dichotomique(f,a,b):
    xg=a+(1/4)*(b-a)
    xc=a+(2/4)*(b-a)
    xd=a+(3/4)*(b-a)
    if (b-a)<pow(10,-7):
        return a
    elif f(xc)>f(xd):
        a=xc
        dichotomique(f,a,b)
    elif f(xc)>f(xg):
        b=xc
        dichotomique(f,a,b)
    else:
        a=xg
        b=xd
        dichotomique(f,a,b)

def f1(x):
    return abs(x-100)
def f2(x):
    if x>=50:
        resultat=mp.sqrt(x-50)
    else:
        resultat=mp.sqrt(-(x-50))
    return resultat
def f3(x):
    return min(4*x,x+5)
def f4(x):
    return -pow(x,3)

print(dichotomique(f1,-1000,1000))
print(dichotomique(f2,-1000,1000))
print(dichotomique(f3,-1000,1000))
print(dichotomique(f4,-1000,1000))
