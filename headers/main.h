//
// Created by balak on 28.11.2023.
//

#ifndef GAMEX_MAIN_H
#define GAMEX_MAIN_H

struct Windows {
    SDL_Window *window;
    int width;
    int height;
};

#define DEFAULT_WINDOWS_WIDTH 800
#define DEFAULT_WINDOWS_HEIGHT 800

struct Player {
    SDL_Surface *png_hat;
    SDL_Texture *texture_hat;
    SDL_Rect position;
};

#define DEFAULT_PLAYER_WIDTH 35
#define DEFAULT_PLAYER_HEIGHT 38
#define DELTA_PLAYER_MOVE 10
#define DEFAULT_PLAYER_POSITION_X (DEFAULT_WINDOWS_WIDTH / 2)
#define DEFAULT_PLAYER_POSITION_Y (DEFAULT_WINDOWS_HEIGHT / 2)

struct Cursor {
    struct SDL_Rect position;
};

#define DEFAULT_CURSOR_POSITION_X (DEFAULT_WINDOWS_WIDTH / 2)
#define DEFAULT_CURSOR_POSITION_Y (DEFAULT_WINDOWS_HEIGHT / 2)


#endif //GAMEX_MAIN_H
