import pygame

def main():
    pygame.init()

    screen = pygame.display.set_mode((1000, 800))
    clock = pygame.time.Clock()

    data = [[0 for _ in range(16)] for _ in range(10)]
    draw = False
    erase = False

    # Main loop
    run = True
    while run:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                run = False

            if e.type == pygame.MOUSEBUTTONDOWN:

                if e.button == pygame.BUTTON_LEFT:
                    draw = True

                    position = pygame.mouse.get_pos()
                    position = (position[0]//50, position[1]//50)
                    if position[0] > 10:
                        print('{', end='')
                        for b in range(10):
                            byte = 0
                            for bit in range(8):
                                byte |= data[b][bit] << bit
                            print("{0:#0{1}x}".format(byte, 4), end='')
                            print(', ', end='')
                        for b in range(10):
                            byte = 0
                            for bit in range(8):
                                byte |= data[b][bit+8] << bit
                            print("{0:#0{1}x}".format(byte, 4), end='')
                            if b < 9:
                                print(', ', end='')
                        print('}')
                        data = [[0 for _ in range(16)] for _ in range(10)]

                if e.button == pygame.BUTTON_RIGHT:
                    erase = True

            if e.type == pygame.MOUSEBUTTONUP:
                if e.button == pygame.BUTTON_LEFT:
                    draw = False
                if e.button == pygame.BUTTON_RIGHT:
                    erase = False

        if draw:
            position = pygame.mouse.get_pos()
            position = (position[0]//50, position[1]//50)
            if position[0] < 10 and position[1] < 16:
                data[position[0]][position[1]] = True

        if erase:
            position = pygame.mouse.get_pos()
            position = (position[0]//50, position[1]//50)
            if position[0] < 10 and position[1] < 16:
                data[position[0]][position[1]] = False

        clock.tick(30)

        # Draw screen (first step, no shadows)
        screen.fill(pygame.color.Color('black'))

        for c in range(1, 11):
            if c % 2:
                pygame.draw.line(screen, 'blue', (c*50,0), (c*50,800))
            else:
                pygame.draw.line(screen, 'white', (c*50,0), (c*50,800))

        for r in range(1, 17):
            if r == 14 or r == 4:
                pygame.draw.line(screen, 'red', (0,r*50), (500,r*50))
            elif r % 2:
                pygame.draw.line(screen, 'blue', (0,r*50), (500,r*50))
            else:
                pygame.draw.line(screen, 'white', (0,r*50), (500,r*50))

        for row in range(16):
            for col in range(10):
                if data[col][row]:
                    pygame.draw.rect(screen, 'green', (1+col*50,1+row*50,49,49))

        pygame.display.update()


if __name__ == '__main__':
    main()
