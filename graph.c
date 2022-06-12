#include "./headers/graph.h"

int openGraph(Q_PrimeNumbers *prime_numbers_queue)
{
    printf("open\n");
    SDL_PrintVersion();

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    
    SDL_Initialization();
    window = SDL_InitializationWindow(window);
    renderer = SDL_InitializationRenderer(window, renderer);
    SDL_SetWindowTitle(window, "unamed_graph");

    G_CreateBackground(window, renderer);
    
    PrimeNumber *Element = prime_numbers_queue->first;
    double max_x = 0, min_x = 0, max_y = 0, min_y = 0;
    while (Element != NULL)
    {
        if (Element->coord_cartesian.x > max_x)
            max_x = Element->coord_cartesian.x;

        if(Element->coord_cartesian.x < min_x)
            min_x = Element->coord_cartesian.x;

        if (Element->coord_cartesian.y > max_y)
            max_y = Element->coord_cartesian.y;
        
        if(Element->coord_cartesian.y < min_y)
            min_y = Element->coord_cartesian.y;

        Element = Element->next;
    }
    printf("x : min = %lf, max = %lf\ny : min = %lf, max = %lf\n", min_x, max_x, min_y, max_y);
    if(min_x < 0)
        min_x = min_x * (-1);
    if(min_y < 0)
        min_y = min_y * (-1);
    
    double tab[4];
    tab[0] = min_x;
    tab[1] = max_x;
    tab[2] = min_y;
    tab[3] = max_y;

    //showArrayD(tab, 4);
    double val_max = maxArray(tab, 4);
    printf("value max = %lf\n", val_max);
    double divid = val_max / (1000 / 2); //1000 is heigth of the window


    Element = prime_numbers_queue->first;
    while (Element != NULL)
    {
        renderer = G_addPoint(window, renderer, Element->coord_cartesian.x/divid, Element->coord_cartesian.y/divid);
        Element = Element->next;
    }
    SDL_RenderPresent(renderer);

    Bool graph_open = True;
    while (graph_open)
    {
        SDL_Event event;
        graph_open = G_actions(window, event);
        SDL_Delay(20);  //pour eviter d'avoir 100% d'utilisation CPU
    }

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
