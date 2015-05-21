#/usr/bin/env python
#encoding:utf-8

from datetime import datetime
def mudar(string,car):
	a=string.index("(")+1
	b=string.index(")")
	p=int(string[a:b])+1
	st=""
	for i in range(0,len(string)):
		if i==a: 
			st+=str(p)
			st+=")"
			break
		else: st+=string[i]
	return st

def escrever(lista,a):
	a.write("\n")
	a.write(str(datetime.now()))
	a.write("\n")
	for j in lista:
		a.write(j[22])
		for i in j[0:22]:
			a.write(str(i)+", ")	#23 eh o indice onde existe o nome da lista
		a.write("\n")
