#!/usr/bin/env python
#encoding: utf-8
from datetime import datetime
# ---------- código da classe curry (início) ----------
class curry:
	"""da receita de Scott David Daniel
	"curry – associando parâmetros com funções" no 
	"Python Cookbook"
	"""
	def __init__ (self, fun, *args, **kwargs):
		self.fun = fun
		self.pending = args[:]
		self.kwargs = kwargs.copy()
	def __call__ (self, *args, **kwargs):
		if kwargs and self.kwargs:
			kw = self.kwargs.copy()
			kw.update(kwargs)
		else:	
			kw = kwargs or self.kwargs
		return self.fun(*(self.pending + args), **kw)
# ---------- código da classe curry (final) ----------
# ---------- código da função event_lambda (começo) --------
def event_lambda (f, *args, **kwds ):
	"""Uma função auxiliary que envolve 
	lambda numa interface mais amigável
	Obrigado a Chad Netzer pelo código."""
	return lambda event, f=f, args=args, kwds=kwds : f( *args, **kwds )
# ---------- código da função event_lambda (final) -----------
