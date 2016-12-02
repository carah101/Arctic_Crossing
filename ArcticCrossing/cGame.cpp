/*
==================================================================================
cGame.cpp
==================================================================================
*/

#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureMgr* theTextureMgr = cTextureMgr::getInstance();
static cFontMgr* theFontMgr = cFontMgr::getInstance();
static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

cGame::cGame() //Constructor
{

}

cGame* cGame::getInstance() //Singleton Design Pattern
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}

void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();

	// Clear the buffer with a black background
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureMgr->setRenderer(theRenderer);
	theFontMgr->initFontLib();
	theSoundMgr->initMixer();

	//Store the textures
	textureName = { "theBackground", "theSeal" };
	texturesToUse = { "Images\\Background.png", "Images\\Seal.png" };
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureMgr->addTexture(textureName[tCount], texturesToUse[tCount]);
	}

	//Create textures for text
	fontList = { "icePixel" };
	fontsToUse = { "Fonts/ice_pixel-7.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontMgr->addFont(fontList[fonts], fontsToUse[fonts], 36);
	}
	gameTextList = {"Arctic Crossing"};

	theTextureMgr->addTexture("Title", theFontMgr->getFont("icePixel")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }));

	//Load game sounds
	soundList = { "music", "pickup", "splash", "gameOver", "nextback" };
	soundTypes = { MUSIC, SFX, SFX, SFX, SFX };
	soundsToUse = { "", "", "", "", "" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundMgr->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundMgr->getSnd("music")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureMgr->getTexture("theBackground"));
	spriteBkgd.setSpriteDimensions(theTextureMgr->getTexture("theBackground")->getTWidth(), theTextureMgr->getTexture("theBackground")->getTHeight());

	theSeal.setSpritePos({ 40, 560});
	theSeal.setTexture(theTextureMgr->getTexture("theSeal"));
	theSeal.setSpriteDimensions(theTextureMgr->getTexture("theSeal")->getTWidth(), theTextureMgr->getTexture("theSeal")->getTHeight());
	theSeal.setSealMotion({ 0, 0 });
}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//We get the time that passed since the last frame
		double elapsedTime = this->getElapsedSeconds();

		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());

	// Render the Title
	cTexture* tempTextTexture = theTextureMgr->getTexture("Title");
	SDL_Rect pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
	FPoint scale = { 1, 1 };
	tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
	// render the seal
	theSeal.render(theRenderer, &theSeal.getSpriteDimensions(), &theSeal.getSpritePos(), theSeal.getSpriteRotAngle(), &theSeal.getSpriteCentre(), theSeal.getSpriteScale());
	SDL_RenderPresent(theRenderer);
}
void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{

}


bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
			}
				break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
			}
				break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;
			case SDLK_DOWN:
			{
					if (theSeal.getSpritePos().x < (renderWidth - theSeal.getSpritePos().w))
					{
						theSeal.setSealMotion({ -50, 0 });
					}
			}
				break;

			case SDLK_UP:
			{
					if (theSeal.getSpritePos().x < (renderWidth - theSeal.getSpritePos().w))
					{
						theSeal.setSpriteTranslation({ 50, 0 });
					}
			}
				break;
			case SDLK_RIGHT:
			{
				   if (theSeal.getSpritePos().x < (renderWidth - theSeal.getSpritePos().w))
				   {
					   theSeal.setSpriteTranslation({ 0, 50 });
				   }
			}
				break;

			case SDLK_LEFT:
			{
				  if (theSeal.getSpritePos().x < (renderWidth - theSeal.getSpritePos().w))
			      {
					  theSeal.setSpriteTranslation({ 0, -50 });
				  }
			}
				break;
			case SDLK_SPACE:
			{
							   //theBullets.push_back(new cBullet);
							   //int numBullets = theBullets.size() - 1;
							   //theBullets[numBullets]->setSpritePos({ theRocket.getBoundingRect().x + theRocket.getSpriteCentre().x, theRocket.getBoundingRect().y + theRocket.getSpriteCentre().y });
							   //theBullets[numBullets]->setSpriteTranslation({ 2.0f, 2.0f });
							   //theBullets[numBullets]->setTexture(theTextureMgr->getTexture("bullet"));
							   //theBullets[numBullets]->setSpriteDimensions(theTextureMgr->getTexture("bullet")->getTWidth(), theTextureMgr->getTexture("bullet")->getTHeight());
							   //theBullets[numBullets]->setBulletVelocity({ 2.0f, 2.0f });
							   //theBullets[numBullets]->setSpriteRotAngle(theRocket.getSpriteRotAngle());
							   //theBullets[numBullets]->setActive(true);
							   //cout << "Bullet added to Vector at position - x: " << theRocket.getBoundingRect().x << " y: " << theRocket.getBoundingRect().y << endl;
			}
				theSoundMgr->getSnd("shot")->play(0);
				break;
			default:
				break;
			}

		default:
			break;
		}

	}
	return theLoop;
}


double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}
