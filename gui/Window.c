#include <stdio.h>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "Window.h"

SDL_Surface *screen;
SDL_Event event;

int main(int argc, char *arvg[])
{
    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
    SDL_WM_SetCaption("Window","Window");
    SDL_Surface *idle, *enabled, *back, *head;
    idle =SDL_LoadBMP("idle.bmp"); 
    enabled = SDL_LoadBMP("enabled.bmp");

    back = SDL_LoadBMP("sliderback.bmp");
    head = IMG_Load("sliderfront.png");
    SDL_SetAlpha(head, SDL_SRCALPHA, 128);
    Button1 = CreateButton("test", 200, 200, 48, 48, enabled, idle) ;
    Slider1 =CreateSlider("slider test", 300,150, 20,100, back, head); 
    int done = 0;
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                done =1;
            }
        }
        if (event.button.button == SDL_BUTTON_LEFT && event.button.type == SDL_MOUSEBUTTONDOWN)
        {
            printf("Mouse x : %i, y  : %i \n", event.button.x, event.button.y);
            SDL_GetMouseState(&event.button.x, &event.button.y);
            if (inButton(Button1 , event.button.x, event.button.y)) Button1.state = ( Button1.state == 1 ? 0 : 1); 
            //if (inSlider(Slider1, event.button.x, event.button.y)) Slider1.headpos.y = event.button.y - Slider1.headpos.h/2; 
            if (inSlider(Slider1, event.button.x, event.button.y)) Slider1.state = 1;
                
                event.button.button = 0;
                    }
        if(event.button.button == SDL_BUTTON_LEFT && event.button.type == SDL_MOUSEBUTTONUP)
        {
            if (inSlider(Slider1, event.button.x, event.button.y)) Slider1.state = 0;
        }
        
        if(Slider1.state  && inSlider(Slider1, event.button.x, event.button.y)) Slider1.headpos.y = event.button.y - Slider1.headpos.h/2;  
             
                    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format,50,50,50));
                    Button1.current =( Button1.state == 1 ? Button1.img1 : Button1.img0);  
                    SDL_BlitSurface(Button1.current, NULL, screen, &Button1.pos);
                    SDL_BlitSurface(Slider1.back, NULL, screen, &Slider1.pos);
                    SDL_BlitSurface(Slider1.head, NULL, screen, &Slider1.headpos); 
                    
                    SDL_Flip(screen);

                    }
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}