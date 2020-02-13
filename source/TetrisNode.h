// TetrisNode.h

	#include "Node.h"
	#include "Config.h"
	#include "TetrisGame.h"
	
	class TetrisNode : public Node
	{
		public: 
			TetrisNode(SDL_Renderer* renderer_in, Node* parentNode_in): Node(renderer_in, parentNode_in)
			{
				// Create the GameScreen
				TetrisGame* game = new TetrisGame;

				// Add a background image
				game->addTextureToScreen(createImage(renderer_in, "brickBreakerNodeImages/tetrisScreen.png", true));

				Map* newMap = new Map(30,10,16,renderer_in);
				// each  outer bracket is the row and each inner is the column

				std::vector<std::vector<int> > LPiece =
				{
					{ 1,0,0 },
					{ 1,0,0 },
					{ 1,1,0 }
				};
				game->pieces = {LPiece};
				game->setMap(newMap);

				game->setisNewGame(true);
				game->setGameState(true);
	
				this->addScreen(game);
				this->setCurrentScreen(game);
			}
	};