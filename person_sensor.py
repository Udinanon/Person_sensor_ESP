#Python Code
import serial
import json
import time
import pygame

serialcomm = serial.Serial('/dev/ttyUSB0', 9600)
serialcomm.timeout = 1

def main():
    # Setup Pygame
    pygame.init()
    screen = pygame.display.set_mode((255, 255))
    clock = pygame.time.Clock()
    running = True

    while True:
        recv_string = serialcomm.readline().decode('ascii')
        #print(recv_string)
        try:
            recv_data = json.loads(recv_string)
            # print("OK")
            print(recv_data["n_faces"])
             # fill the screen with a color to wipe away anything from last frame
            screen.fill("black")
            for face_index in range(recv_data["n_faces"]):
                face = recv_data["faces"][face_index]
                pos = pygame.Rect(tuple(face["box"]))
                
                pygame.draw.rect(screen, "white", pos)


        except:
            
            pass
        # RENDER YOUR GAME HERE     

        # flip() the display to put your work on screen
        pygame.display.flip()

        clock.tick(60)  # limits FPS to 60
    serialcomm.close()
    
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()