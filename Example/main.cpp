#include <cstdlib>
#include <iostream>
#include <SDL/SDL.h>
#include "SDL_FreeImage.h"

//Easy hack to get around the whole SDL_Main
#ifdef main
#undef main
#endif
//Function to create an SDL screen surface
           //Just implemented to get the SDL initialization out of main.
bool CreateScreen(int width,int height);

//A function to handle all events with SDL, keyboard, mouse, etc....
void handle_events();

//Declare Screen surface globally so both the create screen and main can see
SDL_Surface* Screen;


int main(int argc, char *argv[])
{
    //SDL_Rect structure to aid in blitting to screen
    SDL_Rect rect;
    
    //Passing 1 as first parameter to this function enables logging
              //The Null as the second means the log will be created in current working directory    
    SDL_FreeImage_Log(1, NULL);
    
    //Now create a screen with a width of 600 and height of 450
    if(!CreateScreen(600,450))
                        return 0;
                        
    ///First Load an image to a surface from an SDL resource structure using the LoadRW function, JPEG.                    
    SDL_Surface *image;
    image=SDL_FreeImage_LoadRWSurface(SDL_RWFromFile("apple.jpg", "rb"), 1);
    rect.x = rect.y = 0;
    rect.w = 200;
    rect.h = 160;
	SDL_BlitSurface(image, NULL, Screen, &rect);
	
	
	/// Next we Load an image to a surface from the image file itself, PNG.
	SDL_Surface *image2;
    image2=SDL_FreeImage_LoadSurface("car.png");
    rect.x = 0;
    rect.y = 200;
    rect.w = 200;
    rect.h = 160;
	SDL_BlitSurface(image2, NULL, Screen, &rect);
	
    ///Load an image into an FIBITMAP structure calling the normal LoadFIBitmap function
        //then convert it to an SDL surface using the FIBitmapToSurface Function
    FIBITMAP * temp;
	temp = SDL_FreeImage_LoadFIBitmap("banner.psd");
	rect.x = 200;
    rect.y = 0;
    rect.w = 200;
    rect.h = 160;
    SDL_Surface *temp2;
    temp2=SDL_FreeImage_FIBitmapToSurface(temp);
	SDL_BlitSurface(temp2, NULL, Screen, &rect);
	
	///Load an image into an FIBITMAP structure from an SDL_Rwops structure. 
        //then convert it to an SDL surface using the FIBitmapToSurface Function
    FIBITMAP * temp3;
	temp3 = SDL_FreeImage_LoadRWFIBitmap(SDL_RWFromFile("banner.psd", "rb"), 1);
	rect.x = 200;
    rect.y = 200;
    rect.w = 200;
    rect.h = 160;
    SDL_Surface *temp4;
    temp4=SDL_FreeImage_FIBitmapToSurface(temp3);
	SDL_BlitSurface(temp4, NULL, Screen, &rect);
	




	//Flip the screen to show on the monitor. 
    SDL_Flip(Screen);
    
    
    //// Now use the SaveSurface function to save contents of screen surface out to image file, BMP
    FIBITMAP * temp5;
    SDL_FreeImage_SaveSurface("screen.bmp", Screen);
	
    ///Then Use the SurfaceToFIBitmap to convert the screen surface into an FIBITMAP structure
       // So we can save the image out using the SaveFIBitmap function.TGA
    temp5=SDL_FreeImage_SurfaceToFIBitmap(Screen);
    SDL_FreeImage_SaveFIBitmap("screen2.tga",temp5);
    while(true){
                handle_events(); 
                }
    //Should never reach here but for formality.
    return EXIT_SUCCESS;
}


bool CreateScreen(int width, int height){
    
    int mainwin_bpp;	//bits per pixel
    int mainwin_flags;	//flags for creating the window
    int mainwin_width=width;  //main window width
    int mainwin_height=height; //main window height

        	
	//initialize sdl video info structure
	const SDL_VideoInfo* info = NULL;
		
	//return value from function calls
	int rv;
	
	//start up SDL video system
	rv = SDL_Init(SDL_INIT_VIDEO);
	if( rv < 0 )
		return false;
	
	
	//Use SDL to get Video capabilities
	info = SDL_GetVideoInfo();
	
	if( !info )
		return false;
		
	//fetch the bpp from what SDL gave us
	mainwin_bpp = info->vfmt->BitsPerPixel;
	//set main win flags according to what we want
	mainwin_flags =  SDL_SWSURFACE|SDL_ANYFORMAT;
	
	//actually create the window / screen surface
	Screen = SDL_SetVideoMode(mainwin_width,mainwin_height,mainwin_bpp,mainwin_flags);
	if( !Screen )
		return false;
	return true;
    
}


void handle_events(){
	SDL_Event ev;		//the event
	int rv;			//return value
	
	rv = SDL_PollEvent(&ev);
	while( rv != 0 ){	
		if( ev.type == SDL_QUIT){
			//user clicked close box.
			//then exit program
			exit(0);
		}	
		rv = SDL_PollEvent(&ev);
		
	} //end while there is no more events
}	



