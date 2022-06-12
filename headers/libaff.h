#ifndef _H_LIBAFF_
#define _H_LIBAFF_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_image.h>

#include "menu.h"

#define xFF "255"
#define x00 "000"
// Color "r,g,b,t"
#define WHITE_SDL xFF xFF xFF xFF
#define RED_SDL xFF x00 x00 xFF
#define YELLOW_SDL xFF xFF x00 xFF

void SDL_PrintVersion(void);

void SDL_Initialization(void);
SDL_Window *SDL_InitializationWindow(SDL_Window *window);
SDL_Renderer *SDL_InitializationRenderer(SDL_Window *window, SDL_Renderer *renderer);

void SDL_ExitWithError(const char *message);
void SDL_ExitWithErrorDestroy(SDL_Window *window, SDL_Renderer *rendu, const char *message);

void G_CreateBackground(SDL_Window *window, SDL_Renderer *renderer);

void SDL_DrawColor(SDL_Window *window, SDL_Renderer *renderer, const char *color);

SDL_Renderer * G_addPoint(SDL_Window *window, SDL_Renderer *renderer, const double x, const double y);
Bool G_actions(SDL_Window *window, SDL_Event event);

void screenShot(SDL_Window *window);
void messageBox(void);

#endif
