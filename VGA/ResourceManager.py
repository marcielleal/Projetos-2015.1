import os

import pygame


from utils import load_image, load_sound, load_font
from constants import *

class ResourceManager(dict):

    ORANGE = (130, 40, 0)

    def __init__(self, game):
        self.game = game
        return super(ResourceManager, self).__init__()

    def __getitem__(self, key):
        if key not in super(ResourceManager, self).keys():
            return self.__load_resource_by_key(key)
        else:
            return super(ResourceManager, self).__getitem__(key)

    def __load_resource_by_key(self, key):
        type, filename = key.split("_", 1)
        if type == "image":
            value = load_image(filename)
            self.__setitem__(key, value)
            return value
        elif type == "block":
            value = load_image(os.path.join("blocks", filename), convert_alpha=False)
            self.__setitem__(key, value)
            return value
        elif type == "shatter":
            value = load_image(os.path.join("blocks", "shattered.png"), convert_alpha=False, colorkey=True)
            value.set_alpha(int(filename))
            self.__setitem__(key, value)
            return value
        elif type == "surface" and filename == "screen":
            value = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
            self.__setitem__(key, value)
            return value
        elif type == "audio":
            value = load_sound(filename)
            self.__setitem__(key, value)
            return value
        elif type == "font":
            fontname, size = filename.split('/')
            value = load_font(fontname, int(size))
            self.__setitem__(key, value)
            return value
        elif type == "livesfont":
            value = self["font_audiowide.ttf/28"].render(filename, True, self.ORANGE)
            self.__setitem__(key, value)
            return value
        elif type == "scorefont":
            value = self["font_audiowide.ttf/17"].render(filename, True, self.ORANGE)
            self.__setitem__(key, value)
            return value
        elif type == "comboplussign":
            value = self["font_audiowide.ttf/40"].render(filename, True, self.ORANGE)
            self.__setitem__(key, value)
            return value
        elif type == "clock":
            value = pygame.time.Clock()
            self.__setitem__(key, value)
            return value
        elif type == "fn":

            if filename == "is_time_distortion_field_active":
                value = self.game.is_time_distortion_field_active
                self.__setitem__(key, value)
                return value
            elif filename == "create_powerup":
                value = self.game.create_powerup
                self.__setitem__(key, value)
                return value
            elif filename == "add_ball":
                value = self.game.add_ball
                self.__setitem__(key, value)
                return value
            elif filename == "activate_time_distortion_field":
                value = self.game.activate_time_distortion_field
                self.__setitem__(key, value)
                return value
            elif filename == "double_damage":
                value = self.game.double_damage
                self.__setitem__(key, value)
                return value
        raise KeyError("Invalid resource key: " + key)