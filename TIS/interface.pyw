#!/usr/bin/env python
#encoding:utf-8
from Tkinter import *
from Ajuda_em_eventos import *
from apoio import *

exatas=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Exatas: "]
humanas=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Humanas: "]
tecnologicas=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Tecnológicas: "]
biomedicas=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Biomédicas: "]
artes=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Artes: "]
todos=[exatas,humanas,tecnologicas,biomedicas,artes]

class Principal:
	def __init__(self,raiz):
		self.lastlist=0
		self.raiz=raiz
		raiz.title("CONTAGEM")
		self.frame1=Frame(raiz,height="680",width="1024")
		self.frame1.focus_force()
		self.frame1.pack()
		#---------------AREAS----------#
		Label(self.frame1, text="AREA", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=1)
		
		self.bot0=Button(self.frame1, text="EXATAS(0)")
		self.bot0.bind("<1>", event_lambda(self.add,exatas,0,self.bot0,1))
		self.bot0.grid(row=2, column=1)
		
		self.bot1=Button(self.frame1, text="HUMANAS(0)")
		self.bot1.bind("<1>", event_lambda(self.add,humanas,0,self.bot1,2))
		self.bot1.grid(row=3, column=1)
		
		self.bot2=Button(self.frame1, text="TECNOLÓGICAS(0)")
		self.bot2.bind("<1>", event_lambda(self.add,tecnologicas,0,self.bot2,3))
		self.bot2.grid(row=4, column=1)
		
		self.bot3=Button(self.frame1, text="BIOMÉDICAS(0)")
		self.bot3.bind("<1>", event_lambda(self.add,biomedicas,0,self.bot3,4))
		self.bot3.grid(row=5, column=1)
		
		self.bot4=Button(self.frame1, text="ARTES(0)")
		self.bot4.bind("<1>", event_lambda(self.add,artes,0,self.bot4,5))
		self.bot4.grid(row=6, column=1)
		
		#-------------METODOS-------------#
		Label(self.frame1, text="MÉTODOS", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=2)
		
		self.bot5=Button(self.frame1, text="CURSINHO PREPARATORIO(0)")
		self.bot5.bind("<1>", event_lambda(self.add,self.lastlist,1,self.bot5))
		self.bot5.grid(row=2, column=2)
		
		self.bot6=Button(self.frame1, text="LIVROS DIDATICOS(0)")
		self.bot6.bind("<1>", event_lambda(self.add,self.lastlist,2,self.bot6))
		self.bot6.grid(row=3, column=2)
		
		self.bot7=Button(self.frame1, text="SITES DA INTERNET(0)")
		self.bot7.bind("<1>", event_lambda(self.add,self.lastlist,3,self.bot7))
		self.bot7.grid(row=4, column=2)
		
		self.bot8=Button(self.frame1, text="GRUPOS DE ESTUDO(0)")
		self.bot8.bind("<1>", event_lambda(self.add,self.lastlist,4,self.bot8))
		self.bot8.grid(row=5, column=2)
		
		self.bot9=Button(self.frame1, text="OUTROS(0)")
		self.bot9.bind("<1>", event_lambda(self.add,self.lastlist,5,self.bot9))
		self.bot9.grid(row=6, column=2)
		
		#-------------DISPOSITIVOS-------------#
		Label(self.frame1, text="DISPOSITIVOS", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=3)
		
		self.bot10=Button(self.frame1, text="MNHA PROPRIEDADE(0)")
		self.bot10.bind("<1>", event_lambda(self.add,self.lastlist,6,self.bot10))
		self.bot10.grid(row=2, column=3)
		
		self.bot11=Button(self.frame1, text="DE OUTREM(0)")
		self.bot11.bind("<1>", event_lambda(self.add,self.lastlist,7,self.bot11))
		self.bot11.grid(row=3, column=3)
		
		self.bot12=Button(self.frame1, text="LOCAIS PAGOS(0)")
		self.bot12.bind("<1>", event_lambda(self.add,self.lastlist,8,self.bot12))
		self.bot12.grid(row=4, column=3)
		
		self.bot13=Button(self.frame1, text="LOCAIS PÚBLICOS(0)")
		self.bot13.bind("<1>", event_lambda(self.add,self.lastlist,9,self.bot13))
		self.bot13.grid(row=5, column=3)
		
		#-------------METODOS SE ESTUDOU PELA INTERNET-------------#
		Label(self.frame1, text="METODOS PELA INTERNET", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=4)
		
		self.bot14=Button(self.frame1, text="SITES(0)")
		self.bot14.bind("<1>", event_lambda(self.add,self.lastlist,10,self.bot14))
		self.bot14.grid(row=2, column=4)
		
		self.bot15=Button(self.frame1, text="CANAIS DO YOUTUBE(0)")
		self.bot15.bind("<1>", event_lambda(self.add,self.lastlist,11,self.bot15))
		self.bot15.grid(row=3, column=4)
		
		self.bot16=Button(self.frame1, text="PROVAS ANTERIORES(0)")
		self.bot16.bind("<1>", event_lambda(self.add,self.lastlist,12,self.bot16))
		self.bot16.grid(row=4, column=4)
		
		#-------------ERROS-------------#
		Label(self.frame1, text="ERROS", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=5)
		
		self.bot17=Button(self.frame1, text="NUNCA(0)")
		self.bot17.bind("<1>", event_lambda(self.add,self.lastlist,13,self.bot17))
		self.bot17.grid(row=2, column=5)
		
		self.bot18=Button(self.frame1, text="POUCAS VEZES(0)")
		self.bot18.bind("<1>", event_lambda(self.add,self.lastlist,14,self.bot18))
		self.bot18.grid(row=3, column=5)
		
		self.bot19=Button(self.frame1, text="OCASIONALMENTE(0)")
		self.bot19.bind("<1>", event_lambda(self.add,self.lastlist,15,self.bot19))
		self.bot19.grid(row=4, column=5)
		
		self.bot20=Button(self.frame1, text="FREQUENTEMENTE(0)")
		self.bot20.bind("<1>", event_lambda(self.add,self.lastlist,16,self.bot20))
		self.bot20.grid(row=5, column=5)

		#-------------IMPORTANCIA-------------#
		Label(self.frame1, text="IMPORTANCIA", fg="blue", font=("Times New Roman","15", "bold")).grid(row=1, column=6)
		
		self.bot21=Button(self.frame1, text="NENHUMA(0)")
		self.bot21.bind("<1>", event_lambda(self.add,self.lastlist,17,self.bot21))
		self.bot21.grid(row=2, column=6)
		
		self.bot22=Button(self.frame1, text="POUCA(0)")
		self.bot22.bind("<1>", event_lambda(self.add,self.lastlist,18,self.bot22))
		self.bot22.grid(row=3, column=6)
		
		self.bot23=Button(self.frame1, text="IMPORTANTE(0)")
		self.bot23.bind("<1>", event_lambda(self.add,self.lastlist,19,self.bot23))
		self.bot23.grid(row=4, column=6)
		
		self.bot24=Button(self.frame1, text="MUITA(0)")
		self.bot24.bind("<1>", event_lambda(self.add,self.lastlist,20,self.bot24))
		self.bot24.grid(row=5, column=6)

		self.bot25=Button(self.frame1, text="ESSENCIAL(0)")
		self.bot25.bind("<1>", event_lambda(self.add,self.lastlist,21,self.bot25))
		self.bot25.grid(row=6, column=6)
		
	def add(self,lista,num,bot,lb=0):
		if lb: 
			lista[num]+=1
			if lb==1: self.lastlist=0
			elif lb==2: self.lastlist=1
			elif lb==3: self.lastlist=2
			elif lb==4: self.lastlist=3
			elif lb==5: self.lastlist=4
			bot['text']=mudar(bot['text'],lista[num])
		else:
			if self.lastlist==0: 
				exatas[num]+=1
				bot['text']=mudar(bot['text'],exatas[num])
			elif self.lastlist==1: 
				humanas[num]+=1
				bot['text']=mudar(bot['text'],humanas[num])
			elif self.lastlist==2: 
				tecnologicas[num]+=1
				bot['text']=mudar(bot['text'],tecnologicas[num])
			elif self.lastlist==3: 
				biomedicas[num]+=1
				bot['text']=mudar(bot['text'],biomedicas[num])
			elif self.lastlist==4: 
				artes[num]+=1
				bot['text']=mudar(bot['text'],artes[num])
			else: print "WTF?"
		print exatas
		print humanas
		print tecnologicas
		print biomedicas
		print artes
instancia=Tk()
Principal(instancia)
instancia.mainloop()

a=open("arquivo.txt","a")
escrever(todos,a)
a.close()

