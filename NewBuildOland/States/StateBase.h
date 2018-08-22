#pragma once

#include "SFML/Graphics.hpp"
#include "../Utils/AssetManager.h"

class Game;

class StateBase
{
public:
	StateBase(Game& game);
	virtual ~StateBase();

	virtual void handleInput() = 0;
	virtual void update(float dt, bool focused) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void handleEvent(sf::Event &event);
	virtual void onStop();
	inline AssetManager* getAssetManager() { return &assetManager; };
	virtual void initAssets();

    Game* getGame();
protected:
	Game *game = nullptr;

    AssetManager assetManager;
};

