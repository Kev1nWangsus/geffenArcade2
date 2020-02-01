// RootNode.h

#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "Node.h"
#include "Config.h"
#include "MenuScreen.h"
#include "SimpleButton.h"

class RootNode : public Node 
{
    public:
    RootNode(SDL_Renderer* renderer_in, Node* parentNode_in) : Node(renderer_in, parentNode_in)
    {
        // first make a screen
        MenuScreen* rootNodeScreen = createMenuScreen();
        MenuScreen* rootNodeScreen2 = createMenuScreen();

        ArcadeTexture* rootNodeScreenBackground = createImage(renderer_in, "rootNodeImages/rootNodeScreenBackground.png", true);
        rootNodeScreen->addTextureToScreen(rootNodeScreenBackground);

        ArcadeTexture* rootNodeScreenBackground2 = createImage(renderer_in, "rootNodeImages/rootNodeScreenBackground.png", true);
        rootNodeScreen2->addTextureToScreen(rootNodeScreenBackground2);

        ArcadeTexture* mainMenuText = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "Screen 1", 255, 255, 0);
        mainMenuText->setPosition(windowWidth /2 - mainMenuText->getWidth() / 2, windowHeight/2 - mainMenuText->getHeight()/2);

        rootNodeScreen->addTextureToScreen(mainMenuText);


        ArcadeTexture* mainMenuText2 = createSimpleText(renderer_in, "fonts/retro/italic.ttf", 100, "Screen 2", 255, 255, 0);
        mainMenuText2->setPosition(windowWidth /2 - mainMenuText2->getWidth() / 2, windowHeight/2 - mainMenuText2->getHeight()/2);

        rootNodeScreen2->addTextureToScreen(mainMenuText2);


        SimpleButton* button1 = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "go to screen 2", 255, 0, 0);
        button1->setButtonPosition(windowWidth /2 - button1->getWidth() / 2, windowHeight/2 - button1->getHeight()/2+ 100);
        button1->setButtonAction(createAction(MOVE_SCREENS, rootNodeScreen2));

        rootNodeScreen->addButtonToScreen(button1);

        SimpleButton* button2 = createSimpleTextButton(renderer_in, "fonts/pixel/classic.ttf", 30, "go to screen 1", 255, 0, 0);
        button2->setButtonPosition(windowWidth /2 - button2->getWidth() / 2, windowHeight/2 - button2->getHeight()/2+ 100);
        button2->setButtonAction(createAction(MOVE_SCREENS, rootNodeScreen));
        rootNodeScreen2->addButtonToScreen(button2);

        this->addScreen(rootNodeScreen);
        this->addScreen(rootNodeScreen2);

        this->setCurrentScreen(rootNodeScreen);

    }

};

#endif