#include "nxHumanGameView.h"


static SDL_Surface* screen;
static nxSceneNode sceneNodes[NX_MAX_SCENENODES];
static nxUInt currentSceneNodeId;
static nxUInt playerId;

nxGameView* nxHumanGameView_new()
{
	nxGameView* res = (nxGameView*)nxMalloc(sizeof(nxGameView));

	res->init = nxHumanGameView_init;
	res->update = nxHumanGameView_update;
	res->draw = nxHumanGameView_draw;
	res->shutdown = nxHumanGameView_shutdown;

	screen = NX_NULL;
	for(int i = 0; i<NX_MAX_SCENENODES ;i++)
	{
		nxSceneNode_init(&sceneNodes[i]);
	}
	currentSceneNodeId = 0;

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

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
     
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);
     
    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
     
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if( (screen = SDL_SetVideoMode( NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, NX_SCREEN_BPP, SDL_OPENGL )) == 0 ) 
	{ 
		return 1; 
	} 

	if( init_GL() == 0 ) 
	{ 
		return 1; 
	} 

    if( nxHumanGameView_initAudio(obj) )
    {
        return 1;
    }

	SDL_WM_SetCaption( "pmuj", NULL ); 

	return 0;
}

void nxHumanGameView_update(nxGameView* obj, nxUInt deltaMilliseconds)
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
            else if (event.key.keysym.sym == SDLK_SPACE)
			{
                nxFireEventData evtData = {playerId};
				nxEvent ev = {NX_EVT_FIRE, (void*)&evtData};
				nxEventManager_triggerEvent(ev);
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

    //Now update the times of nodes
	for(int i = 0 ; i < NX_MAX_SCENENODES ; i++)
	{
		if(sceneNodes[i].valid)
        {
            if(sceneNodes[i].moving)
            {
                sceneNodes[i].animTime += deltaMilliseconds;
                //printf("ime is : %d \n", sceneNodes[i].animTime);

                if(sceneNodes[i].animTime >= sceneNodes[i].maxAnimTime)
                {
                    sceneNodes[i].animTime = 0;
                }
            }
            else
            {
                sceneNodes[i].animTime = 0;
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
		if(sceneNodes[i].valid)
        {
			glPushMatrix();
			nxHumanGameView_drawSceneNode(&sceneNodes[i]);
			glPopMatrix();
		}
	}

    /*
	//do test
	glBegin( GL_LINES ); 
		glColor4f( 1.0, 0.0, 0.0, 1.0 );
		glVertex3f( 0, 0, 0 ); 
		glVertex3f( NX_SCREEN_WIDTH, NX_SCREEN_HEIGHT, 0 ); 
		glVertex3f( 0, NX_SCREEN_HEIGHT, 0 ); 
		glVertex3f( NX_SCREEN_WIDTH, 0, 0 ); 
	glEnd();
	//end test
    */

	SDL_GL_SwapBuffers();
}

nxInt init_GL()
{
    glEnable( GL_TEXTURE_2D );

    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendFunc(GL_DST_COLOR,GL_ZERO);

	//glClearColor( 0, 0, 0, 0 );
	glClearColor( 1, 1, 1, 1 );
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

nxInt nxHumanGameView_initAudio(nxGameView* obj)
{
    ALuint soundBuffer;

    int argc = 0;
    char** argv = 0;
    alutInit (&argc, argv);

    //soundBuffer = alutCreateBufferHelloWorld (); 
    soundBuffer = alutCreateBufferFromFile("../media/audio/jump.wav");
    alGenSources(1, &obj->soundSources[0]);
    alSourcei(obj->soundSources[0], AL_BUFFER, soundBuffer);

	return 0;
}

void nxHumanGameView_shutdown(nxGameView* obj)
{
	nxFree(obj);
    nxTextureLoader_shutdown();
    alutExit (); 
}

void nxHumanGameView_handleEvent(nxEvent evt, void* vobj)
{
	nxGameView* obj = (nxGameView*) vobj;

	if(evt.type == NX_EVT_CREATEENT)
	{
        int id = currentSceneNodeId++;
		nxCreateEntityEventData* castData = (nxCreateEntityEventData*)evt.data;

        //printf("id is : %d, type is %d \n", id, castData->entity.type);

		//Now create a scenenode object from the entity object
		sceneNodes[id].id = castData->entity.id;
		sceneNodes[id].valid = 1;
		sceneNodes[id].pos = castData->entity.pos;
		sceneNodes[id].rot = castData->entity.rot;
        sceneNodes[id].width = castData->entity.width;
        sceneNodes[id].height = castData->entity.height;
        sceneNodes[id].hasTex = 0; //Default to having no tex
        sceneNodes[id].animTime = 0;
        sceneNodes[id].moving = 0;

		switch(castData->entity.type)
		{
			case NX_ENT_PLAYER:
				playerId = castData->entity.id;
				sceneNodes[id].type = NX_SN_PLAYER;
                sceneNodes[id].crouchingTexId = nxTextureLoader_loadImageFromFilename("../media/tex/man_crouching.png");
                sceneNodes[id].standingTexId = nxTextureLoader_loadImageFromFilename("../media/tex/man_still.png");
                sceneNodes[id].texId = sceneNodes[id].standingTexId;
                sceneNodes[id].animTexIds[0] = nxTextureLoader_loadImageFromFilename("../media/tex/man_walking_0.png");
                sceneNodes[id].animTexIds[1] = nxTextureLoader_loadImageFromFilename("../media/tex/man_walking_1.png");
                sceneNodes[id].hasTex = 1;
                sceneNodes[id].animFrameTime = 200;
                sceneNodes[id].maxAnimTime = 400;
				break;
			case NX_ENT_PLATFORM:
				sceneNodes[id].type = NX_SN_PLATFORM;
                sceneNodes[id].height = castData->entity.height+1;
				break;
			case NX_ENT_BULLET:
				sceneNodes[id].type = NX_SN_BULLET;
                sceneNodes[id].texId = nxTextureLoader_loadImageFromFilename("../media/tex/bullet_0.png");
                sceneNodes[id].hasTex = 1;
				break;
			case NX_ENT_FIKE:
				sceneNodes[id].type = NX_SN_FIKE;
                sceneNodes[id].texId = nxTextureLoader_loadImageFromFilename("../media/tex/fike.png");
                sceneNodes[id].hasTex = 1;
				break;
			default:
				break;
		}
	}
	else if(evt.type == NX_EVT_UPDATEENT)
	{
		nxUpdateEntityEventData* castData = (nxUpdateEntityEventData*)evt.data;

		//printf("castData->entity.pos with id %d : <%f,%f>\n", castData->entity.id, castData->entity.pos.x, castData->entity.pos.y);

		sceneNodes[castData->entity.id].pos = castData->entity.pos;
		sceneNodes[castData->entity.id].rot = castData->entity.rot;
		sceneNodes[castData->entity.id].reversed = castData->entity.reversed;
		sceneNodes[castData->entity.id].moving = castData->entity.moving;
	}
    else if(evt.type == NX_EVT_STARTMOVEUP) 
    {
        //Play sound now.
    //    alSourcePlay (obj->soundSources[0]);
    }
    else if(evt.type == NX_EVT_CROUCH) 
    {
		nxCrouchEventData* castData = (nxCrouchEventData*)evt.data;
		sceneNodes[castData->entityId].texId = sceneNodes[castData->entityId].crouchingTexId;
    }
    else if(evt.type == NX_EVT_UNCROUCH) 
    {
		nxUnCrouchEventData* castData = (nxUnCrouchEventData*)evt.data;
		sceneNodes[castData->entityId].texId = sceneNodes[castData->entityId].standingTexId;
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
	nxFloat y = NX_SCREEN_HEIGHT - node->pos.y; //Conversion between physics and graphics coords
//	nxFloat rot = node->rot;
    nxFloat rot = -nxMath_radToDeg(node->rot);

    if(node->hasTex)
    {
        glEnable( GL_TEXTURE_2D );
        if(node->moving)
        {
            //printf(" id %d node->animTime %d node->animFrameTime %d \n", node->id, node->animTime, node->animFrameTime);
            nxUInt frame = node->animTime / node->animFrameTime;

            /*
            printf("node->animTime is : %d", node->animTime);
            printf("node->animFrameTime is : %d", node->animFrameTime);
            printf("frame is : %d", frame);
            */
            //TODO:Move between tex ids based on time.
            glBindTexture(GL_TEXTURE_2D, node->animTexIds[frame]);
        }
        else
        {
            // load the texture
            glBindTexture(GL_TEXTURE_2D, node->texId);
        }
    }
    else
    {
        glDisable( GL_TEXTURE_2D );
    }

	switch(node->type)
	{
		case(NX_SN_PLAYER):
			glTranslatef( x, y, 0 );
			//glTranslatef( x+NX_PLAYER_HALFWIDTH, y+NX_PLAYER_HALFHEIGHT, 0 );
			//glRotatef( nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
			glRotatef( rot, 0.0f, 0.0f, 1.0f );
            glColor4f( 1.0, 1.0, 1.0, 1.0 );
            if(! node->reversed )
            {
                glBegin( GL_QUADS ); 
                    glTexCoord2f( 0.0f, 0.0f ); 
                    glVertex3f( -NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 );
                    glTexCoord2f( 0.0f, 1.0f ); 
                    glVertex3f( -NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 				
                    glTexCoord2f( 1.0f, 1.0f ); 
                    glVertex3f( NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 
                    glTexCoord2f( 1.0f, 0.0f );  
                    glVertex3f( NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 ); 
                glEnd();
            }
            else
            {
                glBegin( GL_QUADS ); 
                    glTexCoord2f( 1.0f, 0.0f );  
                    glVertex3f( -NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 );
                    glTexCoord2f( 1.0f, 1.0f ); 
                    glVertex3f( -NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 				
                    glTexCoord2f( 0.0f, 1.0f ); 
                    glVertex3f( NX_PLAYER_HALFWIDTH, NX_PLAYER_HALFHEIGHT, 0 ); 
                    glTexCoord2f( 0.0f, 0.0f ); 
                    glVertex3f( NX_PLAYER_HALFWIDTH, -NX_PLAYER_HALFHEIGHT, 0 ); 
                glEnd();
            }
			break;
		case(NX_SN_PLATFORM):
            {
            nxFloat halfWidth = node->width * 0.5f;
            nxFloat halfHeight = node->height * 0.5f;
			glTranslatef( x+halfWidth, y+halfHeight, 0 );
			//glRotatef( nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
			glRotatef( rot, 0.0f, 0.0f, 1.0f );
            glColor4f( 1.0f, 0.41, 0.7, 1.0 );
            glBegin( GL_QUADS ); 
                glTexCoord2f( 0.0f, 0.0f ); 
                glVertex3f( -halfWidth, -halfHeight, 0 );
                glTexCoord2f( 0.0f, 1.0f ); 
                glVertex3f( -halfWidth, halfHeight, 0 ); 				
                glTexCoord2f( 1.0f, 1.0f ); 
                glVertex3f( halfWidth, halfHeight, 0 ); 
                glTexCoord2f( 1.0f, 0.0f );  
                glVertex3f( halfWidth, -halfHeight, 0 ); 
            glEnd();
			break;
            }
		case(NX_SN_BULLET):
            {
            nxFloat halfWidth = node->width * 0.5f;
            nxFloat halfHeight = node->height * 0.5f;
			glTranslatef( x+halfWidth, y+halfHeight, 0 );
			//glRotatef( nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
			glRotatef( rot, 0.0f, 0.0f, 1.0f );
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
            glBegin( GL_QUADS ); 
                glTexCoord2f( 0.0f, 0.0f ); 
                glVertex3f( -halfWidth, -halfHeight, 0 );
                glTexCoord2f( 0.0f, 1.0f ); 
                glVertex3f( -halfWidth, halfHeight, 0 ); 				
                glTexCoord2f( 1.0f, 1.0f ); 
                glVertex3f( halfWidth, halfHeight, 0 ); 
                glTexCoord2f( 1.0f, 0.0f );  
                glVertex3f( halfWidth, -halfHeight, 0 ); 
            glEnd();
			break;
            }
        case(NX_SN_FIKE):
            {
                nxFloat halfWidth = node->width * 0.5f;
                nxFloat halfHeight = node->height * 0.5f;
                
                //glTranslatef( x+halfWidth, y+halfHeight, 0 );
                glTranslatef( x, y, 0 );
                //glRotatef( -nxMath_radToDeg(rot), 0.0f, 0.0f, 1.0f );
                glRotatef( rot, 0.0f, 0.0f, 1.0f );
                glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
                glBegin( GL_QUADS ); 
                    glTexCoord2f( 0.0f, 0.0f ); 
                    glVertex3f( -halfWidth, -halfHeight, 0 );
                    glTexCoord2f( 0.0f, 1.0f ); 
                    glVertex3f( -halfWidth, halfHeight, 0 ); 				
                    glTexCoord2f( 1.0f, 1.0f ); 
                    glVertex3f( halfWidth, halfHeight, 0 ); 
                    glTexCoord2f( 1.0f, 0.0f );  
                    glVertex3f( halfWidth, -halfHeight, 0 ); 
                glEnd();
                break;
            }
        default:
            {
                NX_ASSERT(0 && "SN definition not found.");
            }
    }
}
