#include "nxHumanGameView.h"

#include <nxCore/nxMM.h>

nxGameView* nxHumanGameView_new()
{
	nxGameView* res = (nxGameView*)nxMalloc(sizeof(nxGameView));

	res->init = nxHumanGameView_init;
	res->update = nxHumanGameView_update;
	res->draw = nxHumanGameView_draw;
	res->shutdown = nxHumanGameView_shutdown;

	return res;
}

nxInt nxHumanGameView_init(nxGameView* obj)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
	{ 
		return 0; 
	} 

	if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL ) 
	{ 
		return 0; 
	} 

	if( init_GL() == 0 ) 
	{ 
		return 0; 
	} 

	SDL_WM_SetCaption( "OpenGL Test", NULL ); 

	return 1;
}

void nxHumanGameView_update(nxGameView* obj)
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) 
	{ 
		if( event.type == SDL_QUIT ) 
		{ 
			//Fire a fucking close window event
		} 
	} 
}

void nxHumanGameView_draw(nxGameView* obj)
{
	glClear( GL_COLOR_BUFFER_BIT ); 
	glLoadIdentity();


//
	float SQUARE_WIDTH=100.0f;
	float SQUARE_HEIGHT=50.0f;
	float x = 10.0f;
	float y = 10.0f;
	glTranslatef( x, y, 0 );
	glBegin( GL_QUADS ); 
		glColor4f( 1.0, 1.0, 1.0, 1.0 );
		glVertex3f( 0, 0, 0 ); 
		glVertex3f( SQUARE_WIDTH, 0, 0 ); 
		glVertex3f( SQUARE_WIDTH, SQUARE_HEIGHT, 0 ); 
		glVertex3f( 0, SQUARE_HEIGHT, 0 ); 
	glEnd();
//
	SDL_GL_SwapBuffers();
}

nxInt init_GL()
{
	glClearColor( 0, 0, 0, 0 );
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );

	glMatrixMode( GL_MODELVIEW ); 
	glLoadIdentity();

	if( glGetError() != GL_NO_ERROR ) 
	{ 
		return 0; 
	}

	return 1;
}

void nxHumanGameView_shutdown(nxGameView* obj)
{
	nxFree(obj);
}
