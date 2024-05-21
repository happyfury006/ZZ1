#puissance itérée et méthode de deflation
#question 1
import numpy as np
from math import sqrt
A=np.matrix([[3,4,0],[1,3,0],[0,0,2]])
# eps=1*pow(10,-15)
eps=1E-15
x0=np.matrix([2,1,1]).T


# def norme(Vect):
#    S=0
#    for i in range(len(Vect)):
#       S+=pow(Vect[i],2)
#    return sqrt(S)



def puissance_iteree(A,x0,eps):
   x=x0
   lbda=1
   lbd=0
   while(abs(lbd-lbda)>eps) :
      lbda=lbd
      Ax=np.dot(A,x)
      x=Ax/np.linalg.norm(Ax)
      lbd=(x.T*Ax)/(x.T*x)
   return lbd,x


print(puissance_iteree(A,x0,eps))



