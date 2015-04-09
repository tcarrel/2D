//
//
//

#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<string>

using namespace std;


//Screen attributes
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    =  32;


//The surfaces
SDL_Surface* image      = NULL;
SDL_Surface* background = NULL;
SDL_Surface* screen     = NULL;

//Event structure that will be used
SDL_Event event;

SDL_Surface* load_image( string filename )
{
  //Temporary storage for image that is loaded
  SDL_Surface* loadedImage = NULL;

  //Optimized image that will be used
  SDL_Surface* optimizedImage = NULL;

  //Load the image
  loadedImage = IMG_Load( filename.c_str() );
  if( loadedImage )
  {
    //Create an optimized image
    optimizedImage = SDL_DisplayFormat( loadedImage );

    //Free old image.
    SDL_FreeSurface( loadedImage );

    if( !optimizedImage )
    {
      Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 255, 255 );
      SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    }
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

bool init()
{
  //Start SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    return false;

  //Set up screen
  screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
  if( !screen )
    return false;

  //Set the window caption
  SDL_WM_SetCaption( "Event test", NULL );

  return true;
}

bool load_files()
{
  //Load the image
  image = load_image( "guy.png" );

  if( !image )
    return false;

  return true;
}

void clean_up()
{
  SDL_FreeSurface( image );
  SDL_FreeSurface( background );

  SDL_Quit();
}

int main( int argc, int **argv )
{
  //Make sure program waits for quit
  bool quit = false;

  if( !init() )//&& !load_files() )
    return 1;

  background = load_image( "grassy_field.png" );
  image = load_image( "guy.bmp" );
  if( !background || !image )
    return 1;

  apply_surface( 0, 0, background, screen );
  apply_surface( 240, 300, image, screen );

  if( SDL_Flip( screen ) == -1 )
    return 1;

  while( !quit )
  {
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
      { 
        //Quit the program
        quit = true;
      }
    }
  }

  clean_up();

  return 0;
}
