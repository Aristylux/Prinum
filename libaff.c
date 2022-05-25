#include "./headers/libaff.h"

/*
 * SDL_PrintVersion:
 * affiche dans le terminal la version sdl
 */
void SDL_PrintVersion(void)
{
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);
}

/*
 * SDL_Initialization:
 * initialise la bibliotheque SDL
 * initialise les fonts
 * initialise les images
 * initialise le rendu de la fenetre
 */
void SDL_Initialization(void)
{
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) // si plusieurs : (SDL_INIT_VIDEO SDL_INIT_AUDIO)
        SDL_ExitWithError("Initialisation SDL");

    // initialisation texte
    if (TTF_Init() != 0)
        SDL_ExitWithError("Initialisation TTF");
}

SDL_Window *SDL_InitializationWindow(SDL_Window *window)
{
    window = SDL_CreateWindow("graph", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, 0);
    if (window == NULL)
        SDL_ExitWithError("Creation fenetre echouee");
    return window;
}

SDL_Renderer *SDL_InitializationRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        SDL_ExitWithErrorDestroy(window, renderer, "Creation rendu echouee");
    return renderer;
}

/*
 * SDL_ExitWithError:
 * gestion des erreurs
 */
void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

/*
 * SDL_ExitWithErrorDestroy:
 * Detruit les elements (free) avant de quitter.
 */
void SDL_ExitWithErrorDestroy(SDL_Window *window, SDL_Renderer *renderer, const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

void G_CreateBackground(SDL_Window *window, SDL_Renderer *renderer)
{
    int h_win, w_win;
    SDL_GetRendererOutputSize(renderer, &w_win, &h_win);
    // SDL_Rect abs = {x, y, w, h};
    SDL_Rect abs = {0, h_win / 2, w_win, 1};
    SDL_Rect ord = {w_win / 2, 0, 1, w_win};

    // SDL_Color white = {255, 255, 255, 255};
    SDL_DrawColor(window, renderer, WHITE_SDL);

    if (SDL_RenderFillRect(renderer, &abs) != 0)
        SDL_ExitWithErrorDestroy(window, renderer, "rect abs");

    if (SDL_RenderFillRect(renderer, &ord) != 0)
        SDL_ExitWithErrorDestroy(window, renderer, "rect ord");

    SDL_RenderPresent(renderer);
}

// Couleur de tracé
// SDL_SetRenderDrawColor(rendu, rouge, vert, bleu, transparence[0 rien - 255 opaque])
void SDL_DrawColor(SDL_Window *window, SDL_Renderer *renderer, const char *color)
{
    unsigned int tab[4];
    for (unsigned int i = 0, a = 0; i < 12; i = i + 3)
    {
        tab[a] = chrToInt(color[i]) * 100 + chrToInt(color[i + 1]) * 10 + chrToInt(color[i + 2]);
        a++;
    }

    SDL_Color col = {tab[0], tab[1], tab[2], tab[3]};

    if (SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a) != 0)
        SDL_ExitWithErrorDestroy(window, renderer, "Unable to change color for rendering");
}

void G_addPoint(SDL_Window *window, SDL_Renderer *renderer, const double x, const double y)
{
    int h_win, w_win;
    SDL_GetRendererOutputSize(renderer, &w_win, &h_win);

    SDL_DrawColor(window, renderer, YELLOW_SDL);
    printf("(%f,%f) -> (%f,%f)\n", x, y, x + w_win / 2, y + h_win / 2);

    if (SDL_RenderDrawPointF(renderer, x + w_win / 2, y + h_win / 2) != 0)
        SDL_ExitWithError("Impossible de dessiner un point");
    /*
    SDL_DrawColor(window, renderer, RED_SDL);
    const unsigned int len_rect = 5;
    SDL_Rect pt = {(x - len_rect / 2) + w_win / 2, (y - len_rect / 2) + h_win / 2, len_rect, len_rect};
    if (SDL_RenderFillRect(renderer, &pt) != 0)
        SDL_ExitWithErrorDestroy(window, renderer, "rect point");
    */
    SDL_RenderPresent(renderer);
}

Bool G_actions(SDL_Window *window, SDL_Event event)
{
    Bool active = True;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            active = False;
            break;
        case SDL_MOUSEBUTTONDOWN:
            screenShot(window);
            break;
        default:
            break;
        }
    }
    return active;
}

// Un point
// SDL_RenderDrawPoint(rendu, x, y)
/*
void SDL_DrawPoint(SDL_Renderer * rendu, SDL_Color color, SDL_Point coordinates){
    SDL_DrawColor(rendu, color);
    if (SDL_RenderDrawPoint(rendu, coordinates.x, coordinates.y) != 0)
        SDL_ExitWithError("Impossible de dessiner un point");
}
*/

void screenShot(SDL_Window *window)
{
    SDL_Renderer *renderer = SDL_GetRenderer(window);

    int h_win, w_win;
    SDL_GetRendererOutputSize(renderer, &w_win, &h_win);

    SDL_Surface *sshot = SDL_CreateRGBSurface(0, w_win, h_win, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, "screenshot2.bmp");
    SDL_FreeSurface(sshot);
}