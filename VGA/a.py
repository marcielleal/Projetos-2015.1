#!/usr/bin/env python2.3
# -*- coding: utf-8 -*-
import pygame
from pygame import sprite
from pygame import Rect
from constants import *
import sys

def is_instance_method(obj):
    """Checks if an object is a bound method on an instance."""
    if not isinstance(obj, types.MethodType):
        return False # Not a method
    if obj.im_self is None:
        return False # Method is not bound
    if issubclass(obj.im_class, type) or obj.im_class is types.ClassType:
        return False # Method is a classmethod
    return True

class Paddle(sprite.Sprite):
    def __init__(self, image_getter, position):
        sprite.Sprite.__init__(self)
        self.image_getter = image_getter
        self.rect = Rect((position[0], position[1]), (self.image_getter().get_width(), self.image_getter().get_height()))
        
    def update(self, posX, moveToPos=False):
        image_width_halved = self.image_getter().get_width() / 2
        x = self.rect.centerx
        if moveToPos:#Não deixa sair do conteiner maior
            if posX != 0:
                x = max(LEFT_BOUND+image_width_halved, posX)
        else:
            x = max(LEFT_BOUND+image_width_halved, x + posX)
        x = min(RIGHT_BOUND-image_width_halved, x)
        self.rect.centerx = x

    def __getstate__(self):
        return dict((k, v) for k, v in self.__dict__.iteritems()
                           if not is_instance_method(getattr(self, k))) 

pygame.init()
size = width, height = 868, 768
screen = pygame.display.set_mode(size)
black = 0, 0, 0
speed=[1,1]

paddle = pygame.image.load("/home/badboy/github/VGA/imagens/paddle.png")
paddlerect = paddle.get_rect()
paddlerect.centery=480

ball=pygame.image.load("/home/badboy/github/VGA/imagens/ball.png")
ballrect = ball.get_rect()
ballrect.centery=paddlerect.top-(ballrect.height/2)

while 1:
	paddlerect.centerx= pygame.mouse.get_pos()[0]
	
	for event in pygame.event.get():
		if event.type == pygame.QUIT: sys.exit()

	if ballrect.left < 0 or ballrect.right > width:
		speed[0]=-speed[0]
	if ballrect.top < 0 or ballrect.bottom > paddlerect.top:
		print paddlerect.center
		print paddlerect.width
		speed[1]=-speed[1]
	ballrect=ballrect.move(speed)
	
	screen.fill(black)
	screen.blit(paddle,paddlerect)
	screen.blit(ball,ballrect)
	pygame.display.flip()
		
