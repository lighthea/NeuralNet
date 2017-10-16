# -*- coding: utf-8 -*-
"""
Created on Mon Oct 16 18:10:33 2017

@author: Alex
"""
import matplotlib.pyplot as plt
import numpy as np
x=np.linspace(-5,5,100)
p1=plt.plot(x,np.sin(x),marker='o')
p2=plt.plot(x,np.cos(x),marker='v')
plt.title("Fonctions trigonometriques")  # Problemes avec accents (plot_directive) !
plt.legend([p1, p2], ["Sinus", "Cosinus"])
plt.show()