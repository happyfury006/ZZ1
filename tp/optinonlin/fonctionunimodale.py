import numpy as np
import math as mp
import matplotlib.pyplot as plt

# Question 1 :
#     Soit *x le minimum de la fonction unimodale K
# Pour K+1:
# 1er cas :
#     Si f(xc)>f(xd) alors la fonction sur [xc;xd] est décroissante
#     Ainsi sur le nouvel intervalle [xc;xd] f reste unimodale
# 2eme cas:
#     Si f(xc)>f(xg) alors la fonction sur [xc;xg] est croissante
#     ainsi sur le nouvel intervalle [xc;xg] f reste unimodale
# 3emme cas :
#     Si f(xc)=<f(xg) et f(xc)=<f(xd) alors la fonction est décroissante entre xg et *x puis croissante entre  *x et xd
#     Ainsi la fonction f est unimodale sur [xg;xd]

#Question 2 :

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




#question 3
# Soit f une fonction initialement unimodale alors 

# quetion 4

# alpha=w/v
# xg=ak +alpha
# xd=bk-alpha

# question 5

# les deux premier cas l'intervalle est divisé de 1/3
# le dernier cas l'intervalle est diviser de 2/3

# question 6

# 2 évaluations de la fonction f doivent être faite par itération

# question 7

# xg=ak+(bk-ak)/2-eps
# xg=ak+(bk-ak)/2+eps
    
# question 8 

#alpha = racine(w/u)
# 1+sqrt(5)/2

# question 9


# Question 10 :
# Il n'y a qu'un seule evaluation de la fonction f a chaque itération 

# Question 11 :

#nombre d'or

def nombreor(f,a,b):
    xg=a+(1/4)*(b-a)
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


# Question 12 :
L = [2500, 3500, 4380, 4389, 4725, 4800, 3700, 3500, 7000, 7500, 2000, 1200]

def cout(p,L,a,b):
    s=0
    for i in range(1,len(L)):
        s+=pow((max(0,L[i]-p)),2)
    return a*p+b*s


# Question 13 :


def affichage(L,C):
    Y=[]
    X=[x for x in range(0,C)]
    for i in X:
        Y.append(cout(i,L,1,0.5))
    plt.plot(X,Y)
    plt.show()
affichage(L,8000)

#question 14 :

dichotomique(cout,0,8000)

#question 15 :

nombreor(cout,0,8000)

#question 16 :