//
//
//

#include<SDL/SDL.h>
#include<string>

using namespace std;

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    =  32;

SDL_Surface* load_image( string filename )
{
  //Temporary storage for image that is loaded
  SDL_Surface* loadedImage = NULL;

  //Optimized image that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = SDL_LoadBMP( filename.c_str() );
  if( loadedImage )
  {
    //Create an optimized image
    optimizedImage = SDL_DisplayFormat( loadedImage );

    //Free old image.
    SDL_FreeSurface( loadedImage );
  }

  //return optimized image
  return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
  //Make a temporary surface to hold the offsets
  SDL_Rect offset;

  //Give offsets to the rectangle
  offset.x = x;
  offset.y = y;

  //Blit the surface
  SDL_BlitSurface( source, NULL, destination, &offset );
}

int main( int argc, int **argv )
{
  SDL_Surface* message    = NULL;
  SDL_Surface* background = NULL;
  SDL_Surface* screen     = NULL;

  //Start SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return 1;

  //Set up screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  if( !screen )
    return 1;

  //Set the window caption
  SDL_WM_SetCaption( "Hello World", NULL );

  //Load Image
  message = load_image( "hello.bmp" );
  background = load_image( "background.bmp" );

  //Apply background to screen
  apply_surface(   0,   0, background, screen );
  apply_surface( 320,   0, background, screen );
  apply_surface(   0, 240, background, screen );
  apply_surface( 320, 240, background, screen );

  //Apply image to screen
  apply_surface( 180, 140, message, screen );

  //Update screen
  if( SDL_Flip( screen ) == -1 )
    return 1;

  //Pause
  SDL_Delay( 2000 );

  //Free the loaded surface
  SDL_FreeSurface( message );
  SDL_FreeSurface( background );

  //Quit SDL
  SDL_Quit();

  return 0;
}
