#!/usr/bin/env python
# -*- coding: utf-8 -*-

# USO:
# Para desenhar um arquivo de entrada do Trabalho 1, faça:
# $ python drawtrab1.py < arquivo


# tutorial completo em
# http://matplotlib.sourceforge.net/users/pyplot_tutorial.html
import sys
from matplotlib.pyplot import figure, show

def le_poligono(p = 0):
    global abscissas
    global ordenadas
    global maxx
    global maxy
    global minx
    global miny

    ax = []
    ay = []
    n=int(sys.stdin.readline()) #
    for i in range(n):
        a=(sys.stdin.readline().split())
        x = int(a[0])
        y = int(a[1])
	ax.append(x)
	ay.append(y)
        if x > maxx:
            maxx = x
        if x < minx:
            minx = x
        if y > maxy:
            maxy = y
        if y < miny:
            miny = y
    ax.append(ax[0])
    ay.append(ay[0])
    abscissas.append(ax)
    ordenadas.append(ay)

def le_entrada():
    global n_poly
    global n_point
    global px
    global py
    global maxx
    global maxy
    global minx
    global miny
    
    a=(sys.stdin.readline().split())
    n_poly = int(a[0])
    n_point = int(a[1])

    for p in range(n_poly):
        le_poligono(p)

    for p in range(n_point):
        a=(sys.stdin.readline().split())
        x = int(a[0])
        y = int(a[1])
        if x > maxx:
            maxx = x
        if x < minx:
            minx = x
        if y > maxy:
            maxy = y
        if y < miny:
            miny = y
	px.append(x)
	py.append(y)


abscissas = []
ordenadas = []
px = []
py = []

maxx = -99999
maxy = -99999
minx = 99999
miny = 99999
le_entrada()
dx = maxx - minx
dy = maxy - miny
ex = dx * 0.1
ey = dy * 0.1
e = int(max(ex,ey)) + 1

print dx, dy, ex, ey, e
print abscissas
print ordenadas
print px
print py

#dimensoes da figura num retangulo
dx = dx + 2*e
dy = dy + 2*e
maxx = maxx + e
maxy = maxy + e
minx = minx - e
miny = miny - e
print dx, dy
print minx, maxx
print miny, maxy

fig = figure(1,figsize=(dx,dy))
#em xlim e ylim coloca-se os limites da coisa nos respect eixos
ax = fig.add_subplot(111, autoscale_on=False, xlim=(minx,maxx), ylim=(miny,maxy))

#gravar na imagem os poligonos
for p in range(n_poly):
    line, = ax.plot(abscissas[p], ordenadas[p], lw=3, color='black')

#gravar na imagem os pontos
for p in range(n_point):
    line, = ax.plot(px[p], py[p], 'ro')

show()
