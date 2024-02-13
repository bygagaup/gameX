#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include <math.h>
#include <stdbool.h>
#include "headers/main.h"


struct Windows win;

struct Player player;

struct Cursor cursor;

SDL_Renderer *renderer;

const Uint8 *keyboard_state;


void DeInit(int error) {
    if (player.texture_hat != NULL) SDL_DestroyTexture(player.texture_hat);
    if (player.png_hat != NULL) SDL_FreeSurface(player.png_hat);
    if (renderer != NULL) SDL_DestroyRenderer(renderer);
    if (win.window != NULL) SDL_DestroyWindow(win.window);
    IMG_Quit();
    SDL_Quit();
    exit(error);
}

void Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Couldn't init SDL: %s", SDL_GetError());
        DeInit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_Log("Couldn't init IMG png: %s", SDL_GetError());
        DeInit(1);
    }

    win.height = DEFAULT_WINDOWS_HEIGHT;
    win.width = DEFAULT_WINDOWS_WIDTH;
    win.window = SDL_CreateWindow("gameX",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  win.width, win.height,
                                  SDL_WINDOW_RESIZABLE);
    if (win.window == NULL) {
        SDL_Log("Failed to create windows: %s", SDL_GetError());
        DeInit(1);
    }

    renderer = SDL_CreateRenderer(win.window, -1, 0);
    if (renderer == NULL) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        DeInit(1);
    }

    // init Player
    player.position.x = DEFAULT_PLAYER_POSITION_X;
    player.position.y = DEFAULT_PLAYER_POSITION_Y;
    player.png_hat = IMG_Load("images/hat.png");
    if (!player.png_hat) {
        SDL_Log("Failed to load png_hat: %s", SDL_GetError());
        DeInit(1);
    }

    player.texture_hat = SDL_CreateTextureFromSurface(renderer, player.png_hat);
    if (!player.texture_hat) {
        SDL_Log("Failed to create texture_hat: %s", SDL_GetError());
        DeInit(1);
    }

    // init Cursor
    cursor.position.x = DEFAULT_CURSOR_POSITION_X;
    cursor.position.y = DEFAULT_CURSOR_POSITION_Y;

    keyboard_state = SDL_GetKeyboardState(NULL);

}

int main(int argc, char *argv[]) {

    Init();
    SDL_Event ev;
    bool isRunning = true;

    while (isRunning) {


        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_WINDOWEVENT:
                    if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        win.width = ev.window.data1;
                        win.height = ev.window.data2;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    cursor.position.x = ev.motion.x;
                    cursor.position.y = ev.motion.y;
                    break;

                case SDL_QUIT:
                    isRunning = false;
                    break;
            }
        }

        if (keyboard_state[SDL_SCANCODE_UP] || keyboard_state[SDL_SCANCODE_W]) {
            player.position.y -= DELTA_PLAYER_MOVE;
        }
        if (keyboard_state[SDL_SCANCODE_DOWN] || keyboard_state[SDL_SCANCODE_S]) {
            player.position.y += DELTA_PLAYER_MOVE;
        }
        if (keyboard_state[SDL_SCANCODE_LEFT] || keyboard_state[SDL_SCANCODE_A]) {
            player.position.x -= DELTA_PLAYER_MOVE;
        }
        if (keyboard_state[SDL_SCANCODE_RIGHT] || keyboard_state[SDL_SCANCODE_D]) {
            player.position.x += DELTA_PLAYER_MOVE;
        }


        player.position.w = DEFAULT_PLAYER_WIDTH;
        player.position.h = DEFAULT_PLAYER_HEIGHT;

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, player.texture_hat, NULL, &player.position);
        SDL_RenderPresent(renderer);

        SDL_Delay(60);
    }

    DeInit(0);
}