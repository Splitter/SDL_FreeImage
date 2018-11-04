#include <SDL/SDL.h>
#include "SDL_FreeImage.h"
#include <FreeImage.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


int SDL_FreeImage_LogEnabled = false;
FILE *SDL_FreeImage_FP=NULL;
char * SDL_FreeImage_Error = "No Error";

int  SDL_FreeImage_Log(int enable, char * path = NULL){
            if( enable ){
                SDL_FreeImage_LogEnabled = true;
                if(path){
                         if ((SDL_FreeImage_FP = fopen(path, "w")) == NULL){
                                 fprintf(stderr, "Cannot open %s\n", path);
                                 SDL_FreeImage_LogEnabled = false;
                                 FreeImage_SetOutputMessage(SDL_FreeImage_HandleFreeImageErrors);
                                 return false;
                                 }
                         else{
                              FreeImage_SetOutputMessage(SDL_FreeImage_HandleFreeImageErrorsInLog);
                              }
                         }
                else{
                     if ((SDL_FreeImage_FP = fopen("SDL_FreeImage.log", "w")) == NULL){
                                 fprintf(stderr, "Cannot open %s\n", "SDL_FreeImage.log");
                                 SDL_FreeImage_LogEnabled = false;
                                 FreeImage_SetOutputMessage(SDL_FreeImage_HandleFreeImageErrors);
                                 return false;
                                 }
                     else{
                          FreeImage_SetOutputMessage(SDL_FreeImage_HandleFreeImageErrorsInLog);
                          }
                     }
                }
            else{
                 SDL_FreeImage_LogEnabled = false;
                 if(SDL_FreeImage_FP){
                                      fclose(SDL_FreeImage_FP);
                                      }
                 FreeImage_SetOutputMessage(SDL_FreeImage_HandleFreeImageErrors);
                 return true;
                 }
            }

char * SDL_FreeImage_GetError(void){
            return SDL_FreeImage_Error;
            }
            
SDL_Surface * SDL_FreeImage_LoadSurface(char * fname){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\n\nEntering Load Function.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            FREE_IMAGE_FORMAT fif;
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Trying to Get file type.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
        	fif=FreeImage_GetFileType(fname, NULL);
        	
        
        	if(fif==FIF_UNKNOWN){
                if(SDL_FreeImage_LogEnabled){
                                             fprintf(SDL_FreeImage_FP,
                                                      "Unkown File Type, Trying to Get file type from filename.\n");
                                             fflush(SDL_FreeImage_FP);
                                                      }
        		fif = FreeImage_GetFIFFromFilename(fname);
        	}
        	if((fif !=FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)){
                if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Got File Type, Now Trying to Load Image : %s.\n",fname);
                                         fflush(SDL_FreeImage_FP);
                                                      }    
        		FIBITMAP * img = FreeImage_Load(fif, fname, 0);
        		
        		if(img!=NULL){
                        FreeImage_FlipVertical(img); 
                        if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Load Successful, Now Converting to surface");
                                         fflush(SDL_FreeImage_FP);
                                                      }      
        				unsigned int pitch= FreeImage_GetPitch(img);
        				unsigned int Rmask=FreeImage_GetRedMask(img);
        				unsigned int Gmask=FreeImage_GetGreenMask(img);
        				unsigned int Bmask=FreeImage_GetBlueMask(img);
        				unsigned int Amask=FreeImage_GetTransparencyCount(img);
                        unsigned int bpp=FreeImage_GetBPP(img);
        				unsigned char * data=FreeImage_GetBits(img);
        				unsigned int width = FreeImage_GetWidth(img);
        				unsigned int height = FreeImage_GetHeight(img);
        				printf("pitch : %d, R : %d, G : %d, B: %d, A: %d\n",pitch,Rmask,Gmask,Bmask,Amask);
        				return SDL_CreateRGBSurfaceFrom( data, width, height, 
                                                           bpp, pitch, Rmask, 
                                                         Gmask, Bmask, Amask);
                         
        		}
        		else{
                     if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Could not Load Image, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                    fprintf(stderr,"Arrgh! Could not Load File\n");
        			return NULL;
        		}
        	}
        	else{
                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unkown File Type, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                 fprintf(stderr,"Arrgh! Unkown file type\n");
                 return NULL;
                 }
			                                       
			                                       
            }
            

FIBITMAP * SDL_FreeImage_LoadFIBitmap(char * fname){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\n\nEntering Load Function.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            FREE_IMAGE_FORMAT fif;
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Trying to Get file type.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
        	fif=FreeImage_GetFileType(fname, NULL);
        	
        
        	if(fif==FIF_UNKNOWN){
                if(SDL_FreeImage_LogEnabled){
                                             fprintf(SDL_FreeImage_FP,
                                                      "Unkown File Type, Trying to Get file type from filename.\n");
                                             fflush(SDL_FreeImage_FP);
                                                      }
        		fif = FreeImage_GetFIFFromFilename(fname);
        	}
        	if((fif !=FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)){
                if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Got File Type, Now Trying to Load Image : %s.\n",fname);
                                         fflush(SDL_FreeImage_FP);
                                                      }    
        		FIBITMAP * img = FreeImage_Load(fif, fname, 0);
        		
        		if(img!=NULL){
                        //FreeImage_FlipVertical(img); 
                        if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Load Successful, Now returning FIBitmap.");
                                         fflush(SDL_FreeImage_FP);
                                                      }      
        				return img;
                         
        		}
        		else{
                     if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Could not Load Image, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                    fprintf(stderr,"Arrgh! Could not Load File\n");
        			return NULL;
        		}
        	}
        	else{
                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unkown File Type, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                 fprintf(stderr,"Arrgh! Unkown file type\n");
                 return NULL;
                 }
			                                       
			                                       
            }
            

unsigned DLL_CALLCONV
ReadProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fread(buffer, size, count, (FILE *)handle);
}

unsigned DLL_CALLCONV
WriteProc(void *buffer, unsigned size, unsigned count, fi_handle handle) {
	return fwrite(buffer, size, count, (FILE *)handle);
}

int DLL_CALLCONV
SeekProc(fi_handle handle, long offset, int origin) {
	return fseek((FILE *)handle, offset, origin);
}

long DLL_CALLCONV
TellProc(fi_handle handle) {
	return ftell((FILE *)handle);
}



SDL_Surface * SDL_FreeImage_LoadRWSurface(SDL_RWops *src, int freesrc){
            
            
            FILE * tfp=tmpfile();;
            long size;
            char buf[128];
            int count=0;
            
            // obtain file size:
            SDL_RWseek(src, 0, SEEK_SET);
            size = SDL_RWtell(src);
            SDL_RWseek(src, 0,SEEK_END);
            size = SDL_RWtell(src);
            SDL_RWseek(src, 0, SEEK_SET);
            
            int numchunks=size/128;
            for(int count=0; count<=numchunks; count++) {
		             SDL_RWread(src, buf, 128, 1);
                     fwrite(buf, 128, 1, tfp); 
	                 }
            
            fflush(tfp);
            fseek(tfp,0,SEEK_SET);
            FreeImageIO io;
            io.read_proc = ReadProc; // pointer to function that calls fread
            io.write_proc = WriteProc; // not needed for loading
            io.seek_proc = SeekProc; // pointer to function that calls fseek
            io.tell_proc = TellProc; // pointer to function that calls ftell
            
            
    		// find the buffer format
    		printf("now getting bitmap fif from handle\n");
    		FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)tfp, 0);
    
    		if(fif != FIF_UNKNOWN) {
                   printf("Known file type\n");
    			// load from the file handle
    			FIBITMAP *dib = FreeImage_LoadFromHandle(fif, &io, (fi_handle)tfp, 1);
                if (dib==NULL){
                               printf("Not able to create bitmap.\n");
                               return NULL;
                               }
                else{
                        FreeImage_FlipVertical(dib); 
                        if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Load Successful, Now Converting to surface");
                                         fflush(SDL_FreeImage_FP);
                                                      }      
        				unsigned int pitch= FreeImage_GetPitch(dib);
        				unsigned int Rmask=FreeImage_GetRedMask(dib);
        				unsigned int Gmask=FreeImage_GetGreenMask(dib);
        				unsigned int Bmask=FreeImage_GetBlueMask(dib);
        				unsigned int Amask=FreeImage_GetTransparencyCount(dib);
                        unsigned int bpp=FreeImage_GetBPP(dib);
        				unsigned char * data=FreeImage_GetBits(dib);
        				unsigned int width = FreeImage_GetWidth(dib);
        				unsigned int height = FreeImage_GetHeight(dib);
        				printf("pitch : %d, R : %d, G : %d, B: %d, A: %d\n",pitch,Rmask,Gmask,Bmask,Amask);
        				return SDL_CreateRGBSurfaceFrom( data, width, height, 
                                                           bpp, pitch, Rmask, 
                                                         Gmask, Bmask, Amask);
                         
        		}
        		
                if(freesrc){
                            SDL_FreeRW(src);
                            }
    			
    		    }
 		    else{
                     return NULL;
                }
    	      
     }     




FIBITMAP * SDL_FreeImage_LoadRWFIBitmap(SDL_RWops *src, int freesrc){
            
            
            FILE * tfp=tmpfile();;
            long size;
            char buf[128];
            int count=0;
            
            // obtain file size:
            SDL_RWseek(src, 0, SEEK_SET);
            size = SDL_RWtell(src);
            SDL_RWseek(src, 0,SEEK_END);
            size = SDL_RWtell(src);
            SDL_RWseek(src, 0, SEEK_SET);
            
            int numchunks=size/128;
            for(int count=0; count<=numchunks; count++) {
		             SDL_RWread(src, buf, 128, 1);
                     fwrite(buf, 128, 1, tfp); 
	                 }
            
            fflush(tfp);
            fseek(tfp,0,SEEK_SET);
            FreeImageIO io;
            io.read_proc = ReadProc; // pointer to function that calls fread
            io.write_proc = WriteProc; // not needed for loading
            io.seek_proc = SeekProc; // pointer to function that calls fseek
            io.tell_proc = TellProc; // pointer to function that calls ftell
            
            
    		// find the buffer format
    		printf("now getting bitmap fif from handle\n");
    		FREE_IMAGE_FORMAT fif = FreeImage_GetFileTypeFromHandle(&io, (fi_handle)tfp, 0);
    
    		if(fif != FIF_UNKNOWN) {
                   printf("Known file type\n");
    			// load from the file handle
    			FIBITMAP *dib = FreeImage_LoadFromHandle(fif, &io, (fi_handle)tfp, 1);
                if (dib==NULL){
                               printf("Not able to create bitmap.\n");
                               return NULL;
                               }
                else{
                        //FreeImage_FlipVertical(dib); 
                        if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Load Successful.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }      
                        if(freesrc){
                             if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Freeing up SDL_Rwops object.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }  
                            SDL_FreeRW(src);
                            }
                         if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Returning Image.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }  
        				return dib;
                         
        		}
        		
                
    			
    		    }
 		    else{
                      if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unkown File type, returning NULL.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }  
                     return NULL;
                }
    	      
     }     
            
 
int SDL_FreeImage_SaveSurface(char * fname, SDL_Surface * Image){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\nEntering Save Function.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }                
            FREE_IMAGE_FORMAT fif;
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Trying to get file type.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            fif=FreeImage_GetFileType(fname, NULL);
            if(fif==FIF_UNKNOWN){
                                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unkown File Type, Trying to Get file type from filename.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                                 fif = FreeImage_GetFIFFromFilename(fname);
          	                      }
        	if((fif !=FIF_UNKNOWN) && FreeImage_FIFSupportsWriting(fif)){ 
                    if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Got File Type, Now Trying to convert");
                                         fflush(SDL_FreeImage_FP);
                                                      } 
                    FIBITMAP * img = FreeImage_ConvertFromRawBits((BYTE*)Image->pixels, 
                                                 Image->w, Image->h, Image->pitch,
                                                 Image->format->BitsPerPixel, 
                                                 Image->format->Rmask, 
                                                 Image->format->Gmask, 
                                                 Image->format->Bmask, 
                                                 true);
                	if(img){
                            FreeImage_FlipVertical(img); 
                            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Converted, Now Trying to Save Image : %s.\n",fname);
                                         fflush(SDL_FreeImage_FP);
                                                      } 
                			WORD bpp = FreeImage_GetBPP(img);
                			if(FreeImage_FIFSupportsExportBPP(fif,bpp))
                			{
                				BOOL rv = FreeImage_Save(fif, img, fname, NULL);
                				if(rv){
                                       if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Save Sucessful, Returning\n");
                                         fflush(SDL_FreeImage_FP);
                                                      } 
                                       return rv;
                                       }
                                else{
                                     if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Save Failed, Returning\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                                     fprintf(stderr,"Arrgh! Could not save file\n");
                                     return rv;
                                     }
                			} 
                			else{
                                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Save failed, Does Not Support BPP export, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                                 fprintf(stderr,"Arrgh! Does not support BPP export\n");  
                                 }    
                      }
                    else{
                         if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Could not convert, Returning\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                         fprintf(stderr,"Arrgh! Could not Convert!\n");
                         return false;
                    }
                    }
            else{
                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unknown File Type from name, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                 fprintf(stderr,"Arrgh! Unkown file type\n");
                 return false;        
                 }               
            
            }

            
int SDL_FreeImage_SaveFIBitmap(char * fname, FIBITMAP * Image){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\nEntering Save Function.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }                
            FREE_IMAGE_FORMAT fif;
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Trying to get file type.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            fif=FreeImage_GetFileType(fname, NULL);
            if(fif==FIF_UNKNOWN){
                                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unkown File Type, Trying to Get file type from filename.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                                 fif = FreeImage_GetFIFFromFilename(fname);
          	                      }
        	if((fif !=FIF_UNKNOWN) && FreeImage_FIFSupportsWriting(fif)){ 
                    if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Got File Type, now Attempting to save.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      } 
                    					
					WORD bpp = FreeImage_GetBPP(Image);
					if(FreeImage_FIFSupportsExportBPP(fif,bpp))
					{
						BOOL rv = FreeImage_Save(fif, Image, fname, NULL);
						if(rv){
							   if(SDL_FreeImage_LogEnabled){
								 fprintf(SDL_FreeImage_FP,
										 "Save Sucessful, Returning\n");
								 fflush(SDL_FreeImage_FP);
											  } 
							   return rv;
							   }
						else{
							 if(SDL_FreeImage_LogEnabled){
								 fprintf(SDL_FreeImage_FP,
										 "Save Failed, Returning\n");
								 fflush(SDL_FreeImage_FP);
											  }
							 fprintf(stderr,"Arrgh! Could not save file\n");
							 return rv;
							 }
					} 
					else{
						 if(SDL_FreeImage_LogEnabled){
								 fprintf(SDL_FreeImage_FP,
										 "Save failed, Does Not Support BPP export, Returning.\n");
								 fflush(SDL_FreeImage_FP);
											  }
						 fprintf(stderr,"Arrgh! Does not support BPP export\n");  
						 }    
                      
                    }
            else{
                 if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "Unknown File Type from name, Returning.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
                 fprintf(stderr,"Arrgh! Unkown file type\n");
                 return false;        
                 }               
            
            }




SDL_Surface * SDL_FreeImage_FIBitmapToSurface( FIBITMAP * dib){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\nEntering FIBitmapToSurf and returning conversion results.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            FreeImage_FlipVertical(dib); 
			unsigned int pitch= FreeImage_GetPitch(dib);
  	        unsigned int Rmask=FreeImage_GetRedMask(dib);
  	        unsigned int Gmask=FreeImage_GetGreenMask(dib);
  	        unsigned int Bmask=FreeImage_GetBlueMask(dib);
			unsigned int Amask=FreeImage_GetTransparencyCount(dib);
            unsigned int bpp=FreeImage_GetBPP(dib);
        	unsigned char * data=FreeImage_GetBits(dib);
        	unsigned int width = FreeImage_GetWidth(dib);
        	unsigned int height = FreeImage_GetHeight(dib);
        	printf("pitch : %d, R : %d, G : %d, B: %d, A: %d\n",pitch,Rmask,Gmask,Bmask,Amask);
        	return SDL_CreateRGBSurfaceFrom( data, width, height, 
                                                           bpp, pitch, Rmask, 
                                                         Gmask, Bmask, Amask);                                          
           }
           
           
           
FIBITMAP * SDL_FreeImage_SurfaceToFIBitmap(SDL_Surface * Image){
            if(SDL_FreeImage_LogEnabled){
                                         fprintf(SDL_FreeImage_FP,
                                                 "\n\nEntering SurfToFIBitmap, returning conversion results.\n");
                                         fflush(SDL_FreeImage_FP);
                                                      }
            FIBITMAP * dib= FreeImage_ConvertFromRawBits((BYTE*)Image->pixels, 
                                                 Image->w, Image->h, Image->pitch,
                                                 Image->format->BitsPerPixel, 
                                                 Image->format->Rmask, 
                                                 Image->format->Gmask, 
                                                 Image->format->Bmask, 
                                                 true);
            FreeImage_FlipVertical(dib); 
            return dib;
           }
            
            
void SDL_FreeImage_HandleFreeImageErrorsInLog(FREE_IMAGE_FORMAT fif,const char *message){
            fprintf(SDL_FreeImage_FP,"FreeImage Error: %s\n",message);
            fflush(SDL_FreeImage_FP);
            fprintf(stderr,"FreeImage Error: %s\n",message);
            fflush(stderr);
            SDL_FreeImage_Error = (char *) malloc(strlen(message) + 1);
            if (SDL_FreeImage_Error!=NULL){
                                           strcpy(SDL_FreeImage_Error, message);
                                           }
            }
            
            
void SDL_FreeImage_HandleFreeImageErrors(FREE_IMAGE_FORMAT fif,const char *message){
            fprintf(stderr,"FreeImage Error: %s\n",message);
            fflush(stderr);
            SDL_FreeImage_Error = (char *) malloc(strlen(message) + 1);
            if (SDL_FreeImage_Error!=NULL){
                                           strcpy(SDL_FreeImage_Error, message);
                                           }
            }
            
