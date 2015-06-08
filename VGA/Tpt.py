#!/usr/bin/env python2.3
# -*- coding: utf-8 -*-

###############################################################################
#
# Mudanças em relação à versão anterior:
#    - otimizações: usar colorkey ao invés de transparência por pixel (alpha)
#
###############################################################################

import os, sys, copy
import getopt

# E importaremos o pygame tambem para esse exemplo
import pygame
from pygame.locals import *

images_dir = os.path.join( "..", "imagens" )

# O random será muito útil para esse jogo, ele ajuda o jogo a perder
# a monotonia
import random as Random


class GameObject( pygame.sprite.Sprite ):
    """
    Esta é a classe básica de todos os objetos do jogo.
    
    Na verdade as caixas de texto e o seu contador de vida não são desta
    classe, mas seria overkill utilizar uma classe pra fazer aquilo e neste
    caso, elas poderiam ser desta classe.

    Para não precisar se preocupar com a renderização, vamos fazer a
    classe de forma que ela seja compatível com o RenderPlain, que já possui
    uma função otimizada para renderização direta sobre a tela. Para isso,
    temos que ter três coisas nesta classe:
    
    1) Ser derivada de Sprite, isto é uma boa coisa, pois a classe Sprite
       cria várias facilidades para o nosso trabalho, como poder ser removida
       dos grupos em que foi colocada, inclusive o de Render, através de
       uma chamada a self.kill()
       
    2) Ter self.image. Uma vez que precisamos carregar uma imagem, isto só
       nos define o nome que daremos a imagem a ser renderizada.
       
    3) Ter self.rect. Esse retângulo conterá o tamanho da imagem e sua posição.
       Nas formas:
           rect = ( ( x, y ), ( width, height ) )
       ou
           rect = ( x, y, width, height )
       e ainda nos fornece algumas facilidades em troca, como o rect.move que
       já desloca a imagem a ser renderizada com apenas um comando.
    """
    def __init__( self, image, position, speed=None ):
        pygame.sprite.Sprite.__init__( self )
        self.image = image
        if isinstance( self.image, str ):
            self.image = os.path.join( images_dir, self.image )
            self.image = pygame.image.load( self.image )

        self.rect  = self.image.get_rect()
        screen     = pygame.display.get_surface()
        self.area  = screen.get_rect()
        
        self.set_pos( position )
        self.set_speed( speed or ( 0, 2 ) )
    # __init__()


    
    def update( self, dt ):
        move_speed = ( self.speed[ 0 ] * dt / 16,
                       self.speed[ 1 ] * dt / 16 )
        self.rect  = self.rect.move( move_speed )
        if ( self.rect.left > self.area.right ) or \
               ( self.rect.top > self.area.bottom ) or \
               ( self.rect.right < 0 ):
            self.kill()
        if ( self.rect.bottom < - 40 ):
            self.kill()
    # update()


    
    def get_speed( self ):
        return self.speed
    # get_speed()



    def set_speed( self, speed ):
        self.speed = speed
    # set_speed()

    

    def get_pos( self ):
        return ( self.rect.center[ 0 ],
                 self.rect.bottom )
    # get_pos()
    


    def set_pos( self, pos ):
        self.rect.center = ( pos[ 0 ], pos[ 1 ] )
    # get_pos()



    def get_size( self ):
        return self.image.get_size()
    # get_size()
# GameObject




class Fire( GameObject ):
    def __init__( self, position, speed=None, image=None, list=None ):
        if not image:
            image = "tiro.png"
        GameObject.__init__( self, image, position, speed )
        if list != None:
            self.add( list )
    # __init__()
# Fire



class Ship( GameObject ):
    def __init__( self, position, lives=0, speed=[ 0, 0 ], image=None ):
        self.acceleration = [ 3, 3 ]
        if not image:
            image = "nave.png"
        GameObject.__init__( self, image, position, speed )
        self.set_lives( lives )
    # __init__()

    

    def get_lives( self ):
        return self.lives
    # get_lives()



    def set_lives( self, lives ):
        self.lives = lives
    # set_lives()



    def fire( self, fire_list, image=None ):
        s = list( self.get_speed() )
        s[ 1 ] *= 2
        Fire( self.get_pos(), s, image, fire_list )
    # fire()

    

    def do_hit( self ):
        if self.get_lives() == 0:
            self.kill()
        else:
            self.set_lives( self.get_lives() - 1 )
    # do_hit()



    def do_collision( self ):
        if self.get_lives() == 0:
            self.kill()
        else:
            self.set_lives( self.get_lives() - 1 )
    # do_collision()

    

    def is_dead( self ):
        return self.get_lives() == 0
    # is_dead()



    def accel_top( self ):
        speed = self.get_speed()
        self.set_speed( ( speed[ 0 ], speed[ 1 ] - self.acceleration[ 1 ] ) )
    # accel_top



    def accel_bottom( self ):
        speed = self.get_speed()
        self.set_speed( ( speed[ 0 ], speed[ 1 ] + self.acceleration[ 1 ] ) )
    # accel_bottom



    def accel_left( self ):        
        speed = self.get_speed()
        self.set_speed( ( speed[ 0 ] - self.acceleration[ 0 ], speed[ 1 ] ) )
    # accel_left



    def accel_right( self ):
        speed = self.get_speed()
        self.set_speed( ( speed[ 0 ] + self.acceleration[ 0 ], speed[ 1 ] ) )
    # accel_right
# Ship



class Enemy( Ship ):
    def __init__( self, position, lives=0, behaviour=0, image=None ):
        if not image:
            image = "inimigo.png"

        if   behaviour == 0: # Inimigo normal, desce reto
            speed = (  0, 3 )
        elif behaviour == 1: # Inimigo que desce da esquerda pra direita
            speed = (  2, 3 )
        elif behaviour == 2: # Inimigo que desce da direita pra esquerda
            speed = ( -2, 3 )
            
        Ship.__init__( self, position, lives, speed, image )
    # __init__()
# Enemy




class Player( Ship ):
    """
    A classe Player é uma classe derivada da classe GameObject.
       No entanto, o personagem não morre quando passa da borda, este só
    interrompe o seu movimento (vide update()).
       E possui experiência, que o fará mudar de nivel e melhorar seu tiro.
       A função get_pos() só foi redefinida para que os tiros não saissem da
    parte da frente da nave do personagem, por esta estar virada ao contrário
    das outras.
       A função fire() foi redefinida para levar em conta a experiência do
    jogador (quanto mais experiência, mais tiros).
    """
    def __init__( self, position, lives=10, image=None ):
        if not image:
            image = "nave.png"
        Ship.__init__( self, position, lives, [ 0, 0 ], image )
        self.set_XP( 0 )
    # __init__()


    
    def update( self, dt ):
        move_speed = ( self.speed[ 0 ] * dt / 16,
                       self.speed[ 1 ] * dt / 16)
        self.rect  = self.rect.move( move_speed )
        
        if ( self.rect.right > self.area.right ):
            self.rect.right = self.area.right
            
        elif ( self.rect.left < 0 ):
            self.rect.left = 0
            
        if ( self.rect.bottom > self.area.bottom ):
            self.rect.bottom = self.area.bottom
            
        elif ( self.rect.top < 0 ):
            self.rect.top = 0
    # update()


    
    def get_pos( self ):
        return ( self.rect.center[ 0 ], self.rect.top )
    # get_pos()


    
    def get_XP( self ):
        return self.XP
    # get_XP()

    

    def set_XP( self, XP ):
        self.XP = XP
    # get_XP()


    def fire( self, fire_list, image=None ):
        l = 1
        if self.XP > 10: l = 3
        if self.XP > 50: l = 5
        
        p      = self.get_pos()
        speeds = self.get_fire_speed( l )
        for s in speeds:
            Fire( p, s, image, fire_list )
    # fire()



    def get_fire_speed( self, shots ):
        speeds = []

        if shots <= 0:
            return speeds
        
        if shots == 1:
            speeds += [ (  0, -5 ) ]
            
        if shots > 1 and shots <= 3:
            speeds += [ (  0, -5 ) ]
            speeds += [ ( -2, -3 ) ]
            speeds += [ (  2, -3 ) ]
            
        if shots > 3 and shots <= 5:
            speeds += [ (  0, -5 ) ]
            speeds += [ ( -2, -3 ) ]
            speeds += [ (  2, -3 ) ]
            speeds += [ ( -4, -2 ) ]
            speeds += [ (  4, -2 ) ]

        return speeds
    # get_fire_speed()
# Player



class PlayerXPStatus:
    """
    Esta classe representa a experiência do usuário
    """
    font    = None
    last_xp = -1
    fgcolor = None
    bgcolor = None
    image   = None
    
    def __init__( self, player, pos=None, font=None, ptsize=30,
                  fgcolor="0xffff00", bgcolor=None ):
        self.player  = player
        self.fgcolor = pygame.color.Color( fgcolor )
        if bgcolor:
            self.bgcolor = pygame.color.Color( bgcolor )
        self.pos     = pos or [ 0, 0 ]
        self.font    = pygame.font.Font( font, ptsize )
    # __init__()

    def update( self, dt ):
        pass
    # update()

    def draw( self, screen ):
        xp = self.player.get_XP()
        if self.last_xp != xp:
            self.last_xp = xp
            text = "XP: % 4d" % xp
            if self.bgcolor:
                self.image = self.font.render( text, False, self.fgcolor,
                                               self.bgcolor )
            else:
                self.image = self.font.render( text, False, self.fgcolor,
                                               ( 255, 0, 255 ) )
                self.image.set_colorkey( ( 255, 0, 255 ), RLEACCEL )
                
        screen.blit( self.image, self.pos )
            
    # draw()
# PlayerXPStatus




class PlayerLifeStatus:
    """
    Esta classe representa o contador de vidas do jogador
    """
    player     = None
    pos        = None
    image      = None
    size_image = None
    spacing    = 5
    def __init__( self, player, pos=None, image=None ):
        self.image = image or "nave_status.png"
        if isinstance( self.image, str ):
            self.image = os.path.join( images_dir, self.image )
            self.image = pygame.image.load( self.image )
            
        self.player     = player
        self.pos        = pos or [ 5, 5 ]
        self.size_image = self.image.get_size()
    # __init__()



    def update( self, dt ):
        pass
    # update()



    def draw( self, screen ):
        pos = copy.copy( self.pos )
        for i in range( self.player.get_lives() ):
            pos[ 0 ] += self.size_image[ 0 ] + self.spacing
            screen.blit( self.image, pos )
    # draw()
# PlayerLifeStatus




class Background:
    """
    Esta classe representa o ator "Fundo" do jogo.

    Ela poreria ser herdeira de GameObject, porém como ela não precisa de todos
    aqueles recursos, implemento somente alguns métodos (update() e draw())
    """
    image = None
    pos   = None
    
    def __init__( self, image="tile.png" ):
        """
        Com essa função criamos uma superfície, formada de uma repetição da
        imagem passada, de forma a cobrir a tela e um pouco mais.

        Aqui é o único lugar onde podemos carregar a imagem, utilizando
            load( image ).convert(),
        este comando não tem nenhuma relação com o formato de arquivo da
        imagem. Ele converte a imagem para o formato do pixel[1] da tela,
        representando um ganho de até 6X na performance final[2].

        [1] Formato de Pixel: Toda imagem é formada por um conjunto de pixels,
            estes são descritos por uma quantidade de bits que representam as
            cores. Em geral utiliza-se RGB (Red, Green, Blue) ou RGBA (RGB +
            Aplha/Transparência).    Em geral a tela tem um formato de 16 BPP
            (bits per pixel) e as imagens com transparência são 32 BPP (RGBA,
            variação de 256 níveis para cada cor e transparência). Ao converter
            para o formato da tela, você perde a resolução de cores e a
            transparência, como estas não são informações importantes para o
            fundo, é conveniente converter para este formato.
        [2] O ganho de performance se dá à necessidade de mesclar as imagens
            (usando o canal alpha) e então transformar para o formato da tela.
            Ao converter, elimina-se o alpha (e a necessidade de mesclar) e a
            necessidade de converter a cada "blit".
        """

        if isinstance( image, str ):
            image = os.path.join( images_dir, image )
            image = pygame.image.load( image )
            image.set_alpha( None, RLEACCEL ) # disable alpha
            image = image.convert()

        self.isize = image.get_size()
        self.pos = [ 0, -1 * self.isize[ 1 ] ]
        screen      = pygame.display.get_surface()
        screen_size = screen.get_size()

        from math import ceil
        w = ( ceil( float( screen_size[ 0 ] ) / self.isize[ 0 ] ) + 1 ) * \
            self.isize[ 0 ]
        h = ( ceil( float( screen_size[ 1 ] ) / self.isize[ 1 ] ) + 1 ) * \
            self.isize[ 1 ]

        back = pygame.Surface( ( w, h ) )
        
        for i in range( ( back.get_size()[ 0 ] / self.isize[ 0 ] ) ):
            for j in range( ( back.get_size()[ 1 ] / self.isize[ 1 ] ) ):
                back.blit( image, ( i * self.isize[ 0 ], j * self.isize[ 1 ] ) )

        back.set_alpha( None, RLEACCEL )
        self.image = back.convert()
    # __init__()



    def update( self, dt ):
        self.pos[ 1 ] += 1
        if ( self.pos[ 1 ] > 0 ):
            self.pos[ 1 ] -= self.isize[ 1 ]
    # update()



    def draw( self, screen ):
        screen.blit( self.image, self.pos )
    # draw()
# Background




class Game:
    screen      = None
    screen_size = None
    run         = True
    interval    = 0
    level       = 0
    list        = None
    player      = None
    player_life = None
    player_xp   = None
    background  = None    
    
    def __init__( self, size, fullscreen ):
        """
        Esta é a função que inicializa o pygame, define a resolução da tela,
        caption, e disabilitamos o mouse dentro desta.
        """
        actors = {}
        pygame.init()
        flags = DOUBLEBUF
        if fullscreen:
            flags |= FULLSCREEN
        self.screen       = pygame.display.set_mode( size, flags )
        self.screen_size = self.screen.get_size()

        pygame.mouse.set_visible( 0 )
        pygame.display.set_caption( 'Título da Janela' )

        self.load_images()
    # init()



    def load_images( self ):
        """
        Lê as imagens necessarias pelo jogo.
        """
        def load_image( filename ):
            img = pygame.image.load( os.path.join( images_dir, filename ) )
            img.set_alpha( None, RLEACCEL ) # disable alpha.
            img.convert()
            img.set_colorkey( ( 255, 0, 255 ), RLEACCEL ) # magenta
            return img
        # load_image()

        self.image_player        = load_image( "nave.png" )
        self.image_player_status = load_image( "nave_status.png" )
        self.image_enemy         = load_image( "inimigo.png" )
        self.image_fire          = load_image( "tiro.png" )
        self.image_enemy_fire    = load_image( "tiro_inimigo.png" )
    # load_images()


    
    def handle_events( self ):
        """
        Trata o evento e toma a ação necessária.
        """
        player = self.player

        for event in pygame.event.get():
            t = event.type
            if t in ( KEYDOWN, KEYUP ):
                k = event.key
        
            if t == QUIT:
                self.run = False

            elif t == KEYDOWN:
                if   k == K_ESCAPE:
                    self.run = False
                elif k == K_LCTRL or k == K_RCTRL:
                    self.interval = 0
                    player.fire( self.list[ "fire" ], self.image_fire )
                elif k == K_UP:
                    player.accel_top()
                elif k == K_DOWN:
                    player.accel_bottom()
                elif k == K_RIGHT:
                    player.accel_right()
                elif k == K_LEFT:
                    player.accel_left()
        
            elif t == KEYUP:
                if   k == K_DOWN:
                    player.accel_top()
                elif k == K_UP:
                    player.accel_bottom()
                elif k == K_LEFT:
                    player.accel_right()
                elif k == K_RIGHT:
                    player.accel_left()
        
            keys = pygame.key.get_pressed()
            if self.interval > 10:
                self.interval = 0
                if keys[ K_RCTRL ] or keys[ K_LCTRL ]:
                    player.fire( self.list[ "fire" ], self.image_fire )
    # handle_events()




    def actors_update( self, dt ):        
        self.background.update( dt )
        
        for actor in self.list.values():
            actor.update( dt )
            
        self.player_life.update( dt )
        self.player_xp.update( dt )
    # actors_update()



    def actors_draw( self ):
        self.background.draw( self.screen )
        
        for actor in self.list.values():
            actor.draw( self.screen )
            
        self.player_life.draw( self.screen )
        self.player_xp.draw( self.screen )
    # actors_draw()
    


    def actor_check_hit( self, actor, list, action ):
        if   isinstance( actor, pygame.sprite.RenderPlain ):
            hitted = pygame.sprite.groupcollide( actor, list, 1, 0 )
            for v in hitted.values():
                for o in v:
                    action( o )
            return hitted
        
        elif isinstance( actor, pygame.sprite.Sprite ):
            if pygame.sprite.spritecollide( actor, list, 1 ):
                action()
            return actor.is_dead()
    # actor_check_hit()


    
    def actors_act( self ):
        # Verifica se personagem foi atingido por um tiro
        self.actor_check_hit( self.player, self.list[ "enemies_fire" ],
                              self.player.do_hit )
        if self.player.is_dead():
            self.run = False
            return
            
        # Verifica se o personagem trombou em algum inimigo
        self.actor_check_hit( self.player, self.list[ "enemies" ],
                              self.player.do_collision )
        if self.player.is_dead():
            self.run = False
            return

        # Verifica se o personagem atingiu algum alvo.
        hitted = self.actor_check_hit( self.list[ "fire" ],
                                       self.list[ "enemies" ],
                                       Enemy.do_hit )
        
        # Aumenta a eXPeriência baseado no número de acertos:
        self.player.set_XP( self.player.get_XP() + len( hitted ) )
    # actors_check_hit()



    def change_level( self ):
        xp = self.player.get_XP()
        if   xp > 10  and self.level == 0:
            self.background = Background( "tile2.png" )
            self.level = 1
            self.player.set_lives( self.player.get_lives() + 3 )
        elif xp > 50  and self.level == 1:
            self.background = Background( "tile3.png" )
            self.level = 2        
            self.player.set_lives( self.player.get_lives() + 6 )
    # change_level()



    def manage( self ):
        self.ticks += 1
        # Faz os inimigos atirarem aleatóriamente
        if self.ticks > Random.randint( 20, 30 ):
            for enemy in self.list[ "enemies" ].sprites():
                if Random.randint( 0, 10 ) > 5:
                    enemy.fire( self.list[ "enemies_fire" ],
                                image=self.image_enemy_fire )
                    self.ticks = 0
        
        # criamos mais inimigos randomicamente para o jogo não ficar chato
        r = Random.randint( 0, 100 )
        x = Random.randint( 1, self.screen_size[ 0 ] / 20 )
        if ( r > ( 40 * len( self.list[ "enemies" ] ) ) ):
            behaviour = Random.randint( 0, 2 )
            lives     = self.level
            enemy     = Enemy( [ 0, 0 ], lives, behaviour,
                               image=self.image_enemy )
            size      = enemy.get_size()
            enemy.set_pos( [ x * size[ 0 ], - size[ 1 ] ] )
            self.list[ "enemies" ].add( enemy )


        # Verifica se ascendeu de nível
        self.change_level()
    # manage()


    
    def loop( self ):
        """
        Laço principal
        """
        # Criamos o fundo
        self.background = Background( "tile.png" )

        # Inicializamos o relogio e o dt que vai limitar o valor de
        # frames por segundo do jogo
        clock         = pygame.time.Clock()
        dt            = 16
        self.ticks    = 0
        self.interval = 1

        pos         = [ self.screen_size[ 0 ] / 2, self.screen_size[ 1 ] ]
        self.player = Player( pos, lives=10, image=self.image_player )

        self.player_life = PlayerLifeStatus( self.player, [ 5, 5 ],
                                             image=self.image_player_status )
        self.player_xp   = PlayerXPStatus( self.player,
                                           [ self.screen_size[ 0 ] - 100, 5 ],
                                           fgcolor="0xff0000" )

        self.list = {
            "player"       : pygame.sprite.RenderPlain( self.player ),
            "enemies"      : pygame.sprite.RenderPlain( Enemy( [ 120, 0 ],
                                                               image=self.image_enemy ) ),
            "fire"         : pygame.sprite.RenderPlain(),
            "enemies_fire" : pygame.sprite.RenderPlain()
            }

        # assim iniciamos o loop principal do programa
        while self.run:
            clock.tick( 1000 / dt )
            self.interval += 1

            # Handle Input Events
            self.handle_events()

            # Atualiza Elementos
            self.actors_update( dt )

            # Faça os atores atuarem
            self.actors_act()

            # Faça a manutenção do jogo, como criar inimigos, etc.
            self.manage()
            
            # Desenhe para o back buffer
            self.actors_draw()
            
            # ao fim do desenho temos que trocar o front buffer e o back buffer
            pygame.display.flip()

            print "FPS: %0.2f" % clock.get_fps()
        # while self.run
    # loop()
# Game


def usage():
    """
    Imprime informações de uso deste programa.
    """
    prog = sys.argv[ 0 ]
    print "Usage:"
    print "\t%s [-f|--fullscreen] [-r <XxY>|--resolution=<XxY>]" % prog
    print
# usage()



def parse_opts( argv ):
    """
    Pega as informações da linha de comando e retorna 
    """
    # Analise a linha de commando usando 'getopt'
    try:
        opts, args = getopt.gnu_getopt( argv[ 1 : ],
                                        "hfr:",
                                        [ "help",
                                          "fullscreen",
                                          "resolution=" ] )
    except getopt.GetoptError:
        # imprime informacao e sai
        usage()
        sys.exit( 2 )

    options = {
        "fullscreen":  False,
        "resolution": ( 640, 480 ),
        }

    for o, a in opts:
        if o in ( "-f", "--fullscreen" ):
            options[ "fullscreen" ] = True
        elif o in ( "-h", "--help" ):
            usage()
            sys.exit( 0 )
        elif o in ( "-r", "--resolution" ):
            a = a.lower()
            r = a.split( "x" )
            if len( r ) == 2:
                options[ "resolution" ] = r
                continue

            r = a.split( "," )
            if len( r ) == 2:
                options[ "resolution" ] = r
                continue

            r = a.split( ":" )
            if len( r ) == 2:
                options[ "resolution" ] = r
                continue
    # for o, a in opts
    r = options[ "resolution" ]
    options[ "resolution" ] = [ int( r[ 0 ] ), int( r[ 1 ] ) ]
    return options
# parse_opts()



def main( argv ):
    #primeiro vamos verificar que estamos no diretorio certo para conseguir
    #encontrar as imagens e outros recursos, e inicializar o pygame com as
    #opcoes passadas pela linha de comando
    fullpath = os.path.abspath( argv[ 0 ] )
    dir = os.path.dirname( fullpath )
    os.chdir( dir )

    options = parse_opts( argv )
    game = Game( options[ "resolution" ], options[ "fullscreen" ] )
    game.loop()
# main()
        
# este comando fala para o python chamar o main se estao executando o script
if __name__ == '__main__':
    main( sys.argv )

