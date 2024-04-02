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
    elif f(xc)>f(xg):
        b=xc
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

#nombre d'or

def nombreor(f,a,b):
    xg=a+(1/4)*(b-a)
    xc=a+(2/4)*(b-a)
    xd=a+(3/4)*(b-a)
    if (b-a)<pow(10,-7):
        return a
    if f(xg)>f(xd):
        a=xg
    if f(xg)<f(xd):
        b=xd
    else:
        a=xg
        b=xd
    nombreor(f,a,b)


#question 3
 
# quetion 4

# alpha=w/v
# xg=ak +alpha
# xd=bk-alpha

# question 5

# les deux premier cas l'intervalle est divisé de 1/3
# le dernier cas l'intervalle est diviser de 2/3

# question 6

# 6 évaluation de la fonction f doivent être faite par itération

# question 7

# xg=ak+(bk-ak)/2-eps
# xg=ak+(bk-ak)/2+eps
    
# question 8 

#alpha = racine(w/u)
# 1+sqrt(5)/2
# 
question 9

