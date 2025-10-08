#include "gfx/gfx.h"
#include "vec2/vec2.h"
#include "planet/planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int main()
{
    srand(time(NULL));
    struct gfx_context_t *ctxt = 
        gfx_create("Planetary system", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!ctxt)
    {
        fprintf(stderr, "Graphics initialization failed!\n");
        return EXIT_FAILURE;
    }

    double delta_T = 5000.0;

    system_t system = create_system(delta_T);


    double r_ecran = R_ECRAN;
    double step = (R_ECRAN - (R_ECRAN/10)) / 100;
    uint32_t center = 0;
    while (true)
    {
        gfx_present(ctxt);
        gfx_clear(ctxt, COLOR_BLACK);
        update_system(&system, delta_T);
        show_system(ctxt, &system, r_ecran, center);
        SDL_Keycode key = gfx_keypressed();
        if (key == SDLK_ESCAPE)
        {
            break;
        }
        else if (key == SDLK_DOWN && r_ecran <= R_ECRAN - step) 
        { 
            r_ecran = r_ecran + step;
        }
        else if (key == SDLK_UP && r_ecran > R_ECRAN/10)
        {
            r_ecran = r_ecran - step;
        }
        else if( key == SDLK_1){
            if (center == MERCURE){
                center = 0;
            }
            else {
                center = MERCURE;
            }
        }
        else if(key == SDLK_2){
            if (center == VENUS){
                center = 0;
            }
            else {
                center = VENUS;
            }
        }
        else if(key == SDLK_3){
            if (center == TERRE){
                center = 0;
            }
            else {
                center = TERRE;
            }

        }
        else if(key == SDLK_4){
            if (center == MARS){
                center = 0;
            }
            else {
                center = MARS;
            }

        }
        else if(key == SDLK_5){
            if (center == JUPITER){
                center = 0;
            }
            else {
                center = JUPITER;
            }

        }
        else if(key == SDLK_6){
            if (center == SATURNE){
                center = 0;
            }
            else {
                center = SATURNE;
            }
            
        }
        else if(key == SDLK_7){
            if (center == URANUS){
                center = 0;
            }
            else {
                center = URANUS;
            }
        }
        else if(key == SDLK_8){
            if (center == NEPTUNE){
                center = 0;
            }
            else {
                center = NEPTUNE;
            }
        }
    }

    free_system(&system);
    gfx_destroy(ctxt);
    return EXIT_SUCCESS;
}
