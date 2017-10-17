# -*- coding: utf-8 -*-
"""
Created on Mon Oct 16 18:10:33 2017

@author: Alex
"""
import matplotlib.pyplot as plt
import glob

list1 = []
p1 = []
for filename in glob.glob('*.dat'):
    DATA = open(filename,"r")
    list1.append(DATA.read())
    DATA.close()
for objects in list1:
    p1.append(plt.plot(objects))

plt.title("Error vs Learning Time") 
plt.legend([p1[0], p1[1],p1[2],p1[3],p1[4],p1[5]], ["Training",
            "Training Classification","Validation","Validation Classification",
            "Test","Test Classification"])
plt.show()