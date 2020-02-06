// TetrisGame.cpp

#include "TetrisGame.h"

bool TetrisGame::moveLeft(std::vector<Entity*>& piece)
{
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();
        int nextCol = (x-getMovingEntities()[i]->getWidth())/(m->getSideSize()); 
        int nextRow = y/(m->getSideSize());
        if(nextCol < 0 
        ||
            m->getTiles()[nextRow][nextCol]->getState() == true)
        {
            return false;
        }
    }
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setXPos(getMovingEntities()[i]->getXPos() - getMovingEntities()[i]->getWidth());
    }
}
bool TetrisGame::moveRight(std::vector<Entity*>& piece)
{
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();
        int nextCol = (x+getMovingEntities()[i]->getWidth())/(m->getSideSize()); 
        int nextRow = y/(m->getSideSize());
        if(nextCol == m->getxDim()
        ||
        m->getTiles()[nextRow][nextCol]->getState() == true)
        {
            return false;
        }  
    }
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setXPos(getMovingEntities()[i]->getXPos() + getMovingEntities()[i]->getWidth()); 
    }    
}
bool TetrisGame::moveDown(std::vector<Entity*>& piece)
{
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();
        int nextCol = (x/(m->getSideSize())); 
        int nextRow = (y+getMovingEntities()[i]->getHeight())/(m->getSideSize());
        if(nextRow == m->getyDim()
        ||
            m->getTiles()[nextRow][nextCol]->getState() == true)
        {
            return false;
        }
    }
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setYPos(getMovingEntities()[i]->getYPos() + getMovingEntities()[i]->getHeight());
    }
}

bool TetrisGame::moveUp(std::vector<Entity*>& piece)
{
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        int x = getMovingEntities()[i]->getXPos();
        int y = getMovingEntities()[i]->getYPos();
        int nextCol = (x/(m->getSideSize())); 
        int nextRow = (y-getMovingEntities()[i]->getHeight())/(m->getSideSize());
        if(nextRow < 0
        ||
            m->getTiles()[nextRow][nextCol]->getState() == true)
        {
            return false;
        }
    }
    for (int i = 0; i < getMovingEntities().size(); i++)
    {
        getMovingEntities()[i]->setYPos(getMovingEntities()[i]->getYPos() - getMovingEntities()[i]->getHeight());
    }
}

void TetrisGame::addPiece(std::string path, point tlc, std::vector<std::vector<int> > piece)
{
    for(int row = 0; row < piece.size(); row++)
    {
        for(int col = 0; col < piece[row].size(); col++)
        {
            if(piece[row][col] == 1)
            {
                if(m->getTiles()[(tlc.y+row)][(tlc.x+col)]->getState() == true)
                {
                    setGameState(false);
                    return;
                }
                ArcadeTexture* newArcadeTexture = new ArcadeTexture;
                newArcadeTexture->setRenderer(m->getRenderer());
                newArcadeTexture->loadFromFile(path);
                newArcadeTexture->isEntireDestination = false;
                newArcadeTexture->setSize(m->getTiles()[row][col]->getWidth(), m->getTiles()[row][col]->getHeight());
                newArcadeTexture->setPosition(m->getSideSize()*(tlc.x+col), m->getSideSize()*(tlc.y+row));
                Tile* newPiece = new Tile;
                newPiece->setGameObjectTexture(newArcadeTexture);
                newPiece->setState(true);
                addEntity(newPiece);
                addMovingEntity(newPiece);
            }
        }
    }
}

void TetrisGame::setMap(Map* m_in)
{
    // need to add all entities in map to the entity list
    m = m_in;
    for(int row = 0; row < (m->getTiles()).size(); row++)
    {
        for(int col = 0; col < (m->getTiles())[row].size(); col++)
        {
            addEntity((m->getTiles())[row][col]);
        }
    }
}

Action TetrisGame::update (SDL_Event* event)
{
    // first check if it is a new game
    if (getIsNewGame())
	{
		newGame();
	}

    // create a default action to return
	Action newAction = { DO_NOTHING, nullptr };

    if(event)
    {
        if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_DOWN)
        {
            moveDown(getMovingEntities());
        }
        else if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_UP)
        {
            moveUp(getMovingEntities());
        }
        else if ((*event).type == SDL_KEYDOWN && (*event).key.keysym.sym == SDLK_LEFT)
        {
            moveLeft(getMovingEntities());
        }
        else if ((*event).type == SDL_KEYDOWN &&(*event).key.keysym.sym == SDLK_RIGHT)
        {
            moveRight(getMovingEntities());
        }
    }
    // execute the game logic
	logic();
	return newAction;
}

void TetrisGame::newGame()
{
     addPiece("brickBreakerNodeImages/yellowBrickTexture.png", {0,0}, pieces.at(1));
     setisNewGame(false);
}
void TetrisGame::logic(){}