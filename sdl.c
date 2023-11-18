#include "SDL2/SDL.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO); // Инициализация SDL для видео

    SDL_Window* window = SDL_CreateWindow(
        "Пример окна SDL",          // заголовок окна
        SDL_WINDOWPOS_UNDEFINED,    // начальная x позиция
        SDL_WINDOWPOS_UNDEFINED,    // начальная y позиция
        640,                        // ширина в пикселях
        480,                        // высота в пикселях
        0                           // флаги окна
    );

    if (window == NULL) {
        // В случае ошибки
        SDL_Quit();
        return 1;
    }

    SDL_Delay(5000);  // Показ окна на 5 секунд

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
