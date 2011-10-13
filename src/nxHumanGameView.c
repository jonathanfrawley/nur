#include "nxHumanGameView.h"

#include <nxCore/nxMM.h>
#include <nxCore/nxLog.h>
#include <nxCore/nxMath.h>
#include <nxEvent/nxEventManager.h>
#include <nxEvent/nxEventData.h>

static SDL_Surface* screen;
static nxSceneNode sceneNodes[NX_MAX_SCENENODES];
static nxUInt currentSceneNodeIdx;
static nxUInt playerId;

nxGameView* nxHumanGameView_new()
{
	nxGameView* res = (nxGameView*)nxMalloc(sizeof(nxGameView));

	res->init = nxHumanGameView_init;
	res->update = nxHumanGameView_update;
	res->draw = nxHumanGameView_draw;
	res->shutdown = nxHumanGameView_shutdown;

	screen = NX_NULL;
	for(int i = 0;i<NX_MAX_SCENENODES;i++)
	{
		sceneNodes[i].id = -1;
	}
	currentSceneNodeIdx = 0;

	playerId = -1;

	nxEventManager_addHandler(nxHumanGameView_handleEvent, (void*)res);

	return res;
}

nxInt nxHumanGameView_init(nxGameView* obj)
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) 
	{ 
		return 1; 
	} 

	if( (screen = SDL_SetVideoMode( NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, NX_SCREEN_BPP, SDL_OPENGL )) == 0 ) 
	{ 
		return 1; 
	} 

	if( init_GL() == 0 ) 
	{ 
		return 1; 
	} 

	SDL_WM_SetCaption( "OpenGL Test", NULL ); 

	return 0;
}

void nxHumanGameView_update(nxGameView* obj)
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) 
	{ 
		if( event.type == SDL_QUIT ) 
		{ 
			nxEvent endGameEvent = {NX_EVT_ENDGAME, NX_NULL};
			nxEventManager_triggerEvent(endGameEvent);
		} 
		else if (event.type == SDL_KEYDOWN)
		{
			//HERE, need to use malloc
			nxMovementEventData evtData = {playerId};

			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				nxEvent endGameEvent = {NX_EVT_ENDGAME, (void*)NX_NULL};
				nxEventManager_triggerEvent(endGameEvent);
			}
			else if (event.key.keysym.sym == SDLK_f)
			{
				if (event.key.keysym.mod & KMOD_CTRL)
				{
					nxHumanGameView_toggleFullscreen(obj);
				}
			}
			else if(event.key.keysym.sym == SDLK_w)
			{
				nxEvent evt = {NX_EVT_STARTMOVEUP, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_a)
			{
				nxEvent evt = {NX_EVT_STARTMOVELEFT, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_s)
			{
				nxEvent evt = {NX_EVT_STARTMOVEDOWN, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_d)
			{
				nxEvent evt = {NX_EVT_STARTMOVERIGHT, &evtData};
				nxEventManager_triggerEvent(evt);
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			nxMovementEventData evtData = {playerId};
			if(event.key.keysym.sym == SDLK_w)
			{
				nxEvent evt = {NX_EVT_ENDMOVEUP, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_a)
			{
				nxEvent evt = {NX_EVT_ENDMOVELEFT, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_s)
			{
				nxEvent evt = {NX_EVT_ENDMOVEDOWN, &evtData};
				nxEventManager_triggerEvent(evt);
			}
			else if(event.key.keysym.sym == SDLK_d)
			{
				nxEvent evt = {NX_EVT_ENDMOVERIGHT, &evtData};
				nxEventManager_triggerEvent(evt);
			}
		}
	}
}

void nxHumanGameView_draw(nxGameView* obj)
{
	glClear( GL_COLOR_BUFFER_BIT ); 
	glLoadIdentity();

	for(int i = 0 ; i < NX_MAX_SCENENODES ; i++)
	{
		if(sceneNodes[i].id == -1)
		{
			continue;
		}
		else
		{
			glPushMatrix();
			nxHumanGameView_drawSceneNode(&sceneNodes[i]);
			glPopMatrix();
		}
	}

	//do test
	glBegin( GL_LINES ); 
		glColor4f( 1.0, 0.0, 0.0, 1.0 );
		glVertex3f( 0, 0, 0 ); 
		glVertex3f( NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, 0 ); 
		glVertex3f( 0, NX_SCREEN_HEIGHT, 0 ); 
		glVertex3f( NX_SCREEN_WIDTH, 0, 0 ); 
	glEnd();
	//end test

	SDL_GL_SwapBuffers();
}

nxInt init_GL()
{
	glClearColor( 0, 0, 0, 0 );
	glMatrixMode( GL_PROJECTION ); 
	glLoadIdentity(); 
	glOrtho( 0, NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, 0, -1, 1 );

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

void nxHumanGameView_handleEvent(nxEvent evt, void* vobj)
{
	nxGameView* obj = (nxGameView*) vobj;

	if(evt.type == NX_EVT_CREATEENT)
	{
		nxCreateEntityEventData* castData = (nxCreateEntityEventData*)evt.data;

		//Now create a scenenode object from the entity object
		sceneNodes[currentSceneNodeIdx].id = castData->entity.id;
		sceneNodes[currentSceneNodeIdx].pos = castData->entity.pos;
		sceneNodes[currentSceneNodeIdx].rot = castData->entity.rot;

		switch(castData->entity.type)
		{
			case NX_ENT_PLAYER:
				playerId = castData->entity.id;
				sceneNodes[currentSceneNodeIdx].type = NX_SN_PLAYER;
				break;
			case NX_ENT_BALL:
				sceneNodes[currentSceneNodeIdx].type = NX_SN_BALL;
				break;
			default:
				break;
		}

		currentSceneNodeIdx++;
	}
	else if(evt.type == NX_EVT_UPDATEENT)
	{
		nxUpdateEntityEventData* castData = (nxUpdateEntityEventData*)evt.data;

		sceneNodes[castData->entity.id].pos = castData->entity.pos;
		sceneNodes[castData->entity.id].rot = castData->entity.rot;
	}
}

void nxHumanGameView_toggleFullscreen()
{
	SDL_WM_ToggleFullScreen(screen);
}

void nxHumanGameView_drawSceneNode(nxSceneNode* node)
{
	//float x = 10.0f;
	//float y = 10.0f;
	nxFloat x = node->pos.x;
	nxFloat y = node->pos.y;
	nxFloat rot = node->rot;
	switch(node->type)
	{
		case(NX_SN_PLAYER):
			glTranslatef( x, y, 0 );
			glRotatef( nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
			glBegin( GL_QUADS ); 
				glColor4f( 1.0, 1.0, 1.0, 1.0 );
				glVertex3f( -NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 ); 
				glVertex3f( -NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 
				glVertex3f( NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 
				glVertex3f( NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 ); 
				/*
				glVertex3f( 0, 0, 0 ); 
				glVertex3f( NX_PLAYER_HALFWIDTH*2, 0, 0 ); 
				glVertex3f( NX_PLAYER_HALFWIDTH*2, NX_PLAYER_HALFHEIGHT*2, 0 ); 
				glVertex3f( 0, NX_PLAYER_HALFHEIGHT*2, 0 ); 
				*/
			glEnd();
			break;
		case(NX_SN_BALL):
			glTranslatef( x, y, 0 );
			glRotatef( nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
			glBegin( GL_QUADS ); 
				glColor4f( 1.0, 1.0, 1.0, 1.0 );
				glVertex3f( -NX_BALL_HALFWIDTH, -NX_BALL_HALFHEIGHT, 0 ); 
				glVertex3f( -NX_BALL_HALFWIDTH, NX_BALL_HALFHEIGHT, 0 ); 
				glVertex3f( NX_BALL_HALFWIDTH, NX_BALL_HALFHEIGHT, 0 ); 
				glVertex3f( NX_BALL_HALFWIDTH, -NX_BALL_HALFHEIGHT, 0 ); 
			glEnd();
			break;
	}
}
