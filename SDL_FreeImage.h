#ifndef SDL_FREEIMAGE_H
#define SDL_FREEIMAGE_H

#include <SDL/SDL.h>
#include <FreeImage.h>


//// SDL_FreeImage_Log ///////
// Function to tell whether or not to create log files of processing
            //Implemented to aid in debugging
            //If enabled Internal Processing info is outputed to file specifid by path
            //If not you can use SDL_FreeImage_GetError to get error strings
            //If no path is specified and is enabled SDL_FreeImage.log will
                 // be created in the current working directory
            //Returns True if Enable/Disable successful
                      //Else Returns False
            //Note: all errors are sent to stderr whether enabled or not
            
int  SDL_FreeImage_Log(int enable, char * path );
            
//// SDL_FreeImage GerError //////
// Function returns char * representing the last reported FreeImage error
            //Returns FreeImage error if available 
                      //Note: if no FreeImage error occurs in the last function you call  
                             //This will still return the last FreeImage error to occur.
                      //Note: still works when logging enabled
                      //Note: all errors are still sent to stderr
                      
char * SDL_FreeImage_GetError(void);
     
//// SDL_FreeImage_LoadSurface//////
// Funtion opens an Image with FreeImage, converts to and returns SDL_Surface containing image
           //Takes in path to file as parameter.
           //Returns pointer to SDL_Surface if Successful
                     //Else Returns NULL
                     
SDL_Surface * SDL_FreeImage_LoadSurface(char * fname);

//// SDL_FreeImage_LoadFIBitmap//////
// Funtion opens an Image with FreeImage and returns FIBitmap Structure
           //Takes in path to file as parameter.
           //Returns pointer to FIBITMAP Structure if Successful
                     //Else Returns NULL
                     
FIBITMAP * SDL_FreeImage_LoadFIBitmap(char * fname);


//// SDL_FreeImage_LoadRWSurface /////
// Function takes in an SDL Rwops resourcem, converts and returns SDL surface of data
            //Takes in SDL_Rwops resource as 1st parameter
            //Integer as second parameter to tell whether to close resource when finished
            //Returns pointer to SDL_Surface if successful 
                      //Else returns NULL

SDL_Surface * SDL_FreeImage_LoadRWSurface(SDL_RWops *src, int freesrc);


//// SDL_FreeImage_LoadRWFIBitmap /////
// Function takes in an SDL Rwops resource, and returns FIBitmap Structure
            //Takes in SDL_Rwops resource as 1st parameter
            //Integer as second parameter to tell whether to close resource when finished
            //Returns pointer to FIBITMAP structure if successful 
                      //Else returns NULL

FIBITMAP * SDL_FreeImage_LoadRWFIBitmap(SDL_RWops *src, int freesrc);
            
//// SDL_FreeImage_SaveSurface//////
// Funtion saves out SDL surface based on filename extension using FreeImage
           //Takes in path to file as parameter as well as SDL_Surface to save
           //Returns True for Success False for Failure              
               
int SDL_FreeImage_SaveSurface(char * fname, SDL_Surface * Image);

//// SDL_FreeImage_Save//////
// Funtion saves out FIBITMAP structure based on filename extension using FreeImage
           //Takes in path to file as parameter as well as FIBITMAP to save
           //Returns True for Success False for Failure              
               
int SDL_FreeImage_SaveFIBitmap(char * fname, FIBITMAP * Image);

//// SDL_FreeImage_FIBitmapToSurf ///////
//  Function converts a FreeImage Bitmap structure into an SDL Surface
             //Takes in a FreeImage Bitmap Structure
             //Returns pointer to SDL surface if created successfully
                       //Else returns NULL
                       
SDL_Surface * SDL_FreeImage_FIBitmapToSurface( FIBITMAP * img);

                      
//// SDL_FreeImage_SurfToFIBitmap ///////
//  Function converts an SDL Surface into a FreeImage Bitmap structure
             //Takes in an SDL Surface
             //Returns pointer to FreeImage Bitmap structure if created successfully
                       //Else returns NULL           
                       
FIBITMAP * SDL_FreeImage_SurfaceToFIBitmap(SDL_Surface * Image);

//// SDL_FreeImage_HandleFreeImageErrorsInLog ///////
//// SDL_FreeImage_HandleFreeImageErrors ///////
// Internally used functions to handle FreeImage Errors 

void SDL_FreeImage_HandleFreeImageErrorsInLog(FREE_IMAGE_FORMAT fif,const char *message);
void SDL_FreeImage_HandleFreeImageErrors(FREE_IMAGE_FORMAT fif,const char *message);



#endif

