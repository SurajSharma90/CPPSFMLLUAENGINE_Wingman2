#include "pch.h"
#include "Game.h"

void Game::initWindow()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	this->window.create(
		sf::VideoMode::getDesktopMode(),
		"CPPLUAENGINE",
		sf::Style::Close | sf::Style::Titlebar, 
		settings);

	this->window.setFramerateLimit(144);
	//this->window.setVerticalSyncEnabled(true);
}

void Game::initView()
{
	this->view.setSize(static_cast<sf::Vector2f>(this->window.getSize()));
	this->view.setCenter(this->window.getDefaultView().getCenter());
}

void Game::initImgui()
{

}

void Game::initDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::initLua()
{
	this->L = luaL_newstate();

	luaL_openlibs(this->L);

	this->registerLuaFunctions();

	//Load first state
	int error = luaL_dofile(this->L, "MainMenuState.lua");
	if (error)
	{
		std::cout << lua_tostring(L, -1) << "\n";
		lua_pop(L, lua_gettop(L));
	}
}

void Game::registerLuaFunctions()
{
	lua_pushlightuserdata(this->L, this);
	lua_setglobal(this->L, "Game");

	lua_pushcfunction(this->L, closeWindow);
	lua_setglobal(this->L, "closeWindow");

	lua_pushcfunction(this->L, cpp_setViewCenter);
	lua_setglobal(this->L, "cpp_setViewCenter");

	lua_pushcfunction(this->L, luaDT);
	lua_setglobal(this->L, "luaDT");

	//lua_pushcfunction(this->L, cpp_time);
	//lua_setglobal(this->L, "cpp_time");

	lua_pushcfunction(this->L, setState);
	lua_setglobal(this->L, "setState");

	lua_pushcfunction(this->L, endState);
	lua_setglobal(this->L, "endState");

	lua_pushcfunction(this->L, newTexture);
	lua_setglobal(this->L, "newTexture");

	lua_pushcfunction(this->L, newSprite);
	lua_setglobal(this->L, "newSprite");
	
	lua_pushcfunction(this->L, cpp_getMousePosScreen);
	lua_setglobal(this->L, "cpp_getMousePosScreen");

	lua_pushcfunction(this->L, cpp_getMousePosWindow);
	lua_setglobal(this->L, "cpp_getMousePosWindow");

	lua_pushcfunction(this->L, cpp_getMousePosWorld);
	lua_setglobal(this->L, "cpp_getMousePosWorld");
	
	lua_pushcfunction(this->L, cpp_setBackgroundTexture);
	lua_setglobal(this->L, "cpp_setBackgroundTexture");
	
	lua_pushcfunction(this->L, moveSprite);
	lua_setglobal(this->L, "moveSprite");

	lua_pushcfunction(this->L, cpp_setSpritePosition);
	lua_setglobal(this->L, "cpp_setSpritePosition");

	lua_pushcfunction(this->L, cpp_getSpritePosition);
	lua_setglobal(this->L, "cpp_getSpritePosition");

	lua_pushcfunction(this->L, cpp_rotateSprite);
	lua_setglobal(this->L, "cpp_rotateSprite");

	lua_pushcfunction(this->L, cpp_setSpriteRotation);
	lua_setglobal(this->L, "cpp_setSpriteRotation");

	lua_pushcfunction(this->L, cpp_getSpriteRotation);
	lua_setglobal(this->L, "cpp_getSpriteRotation");

	lua_pushcfunction(this->L, cpp_setSpriteOrigin);
	lua_setglobal(this->L, "cpp_setSpriteOrigin");

	lua_pushcfunction(this->L, cpp_getSpriteOriginX);
	lua_setglobal(this->L, "cpp_getSpriteOriginX");

	lua_pushcfunction(this->L, cpp_getSpriteOriginY);
	lua_setglobal(this->L, "cpp_getSpriteOriginY");

	lua_pushcfunction(this->L, cpp_setSpriteScale);
	lua_setglobal(this->L, "cpp_setSpriteScale");

	lua_pushcfunction(this->L, cpp_getSpriteScale);
	lua_setglobal(this->L, "cpp_getSpriteScale");

	lua_pushcfunction(this->L, cpp_setSpriteTexture);
	lua_setglobal(this->L, "cpp_setSpriteTexture");

	lua_pushcfunction(this->L, keyPressed);
	lua_setglobal(this->L, "keyPressed");

	lua_pushcfunction(this->L, testFunc);
	lua_setglobal(this->L, "testFunc");
}

void Game::initBackground()
{
	this->background.setSize(static_cast<sf::Vector2f>(this->window.getSize()));
}

Game::Game()
{
	this->initWindow();
	this->initView();
	this->initDt();
	this->initLua();
	this->initBackground();

	//REMOVE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!! FOR TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	this->tileMaps.push_back(new TileMap(50, 5, 5, 1));
	this->tileMaps[0]->addTile(0, 0, 0, sf::IntRect(0, 0, 50, 50));
	this->tileMaps[0]->addTile(0, 1, 0, sf::IntRect(0, 51, 50, 50));
	this->tileMaps[0]->addTile(1, 2, 0, sf::IntRect(0, 102, 50, 50));
}

Game::~Game()
{
	lua_close(this->L);

	for (auto& i : this->sprites)
		delete i;

	for (auto& i : this->textures)
		delete i;

	for (auto& i : this->tileMaps)
		delete i;
}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

void Game::updatePollWindowEvents()
{
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}
}

void Game::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(this->window);
	this->mousePosWorld = this->window.mapPixelToCoords(this->mousePosWindow);
}

void Game::updateStates()
{
	lua_getglobal(this->L, "update");

	int error =  lua_pcall(this->L, 0, 0, 0);
	if (error)
	{
		std::cout << lua_tostring(this->L, -1) << "\n";
		lua_pop(this->L, lua_gettop(this->L));
	}
}

void Game::updateTilemaps()
{
	for (auto& map : this->tileMaps)
		map->update();
}

void Game::update()
{
	this->updatePollWindowEvents();

	this->updateMousePositions();

	this->updateStates();

	this->updateTilemaps();
}

void Game::renderBackground()
{
	this->window.draw(this->background);
}

void Game::renderSprites()
{	
	for (auto* sprite : this->sprites)
	{
		this->window.draw(*sprite);
	}
}

void Game::renderTilemaps()
{
	for (auto& map : this->tileMaps)
		map->render(this->window);
}

void Game::render()
{
	this->window.clear();

	this->window.setView(this->view);
	this->renderBackground();
	
	this->renderTilemaps();

	this->renderSprites();

	this->window.display();
}

void Game::run()
{
	this->dt = this->dtClock.restart().asSeconds();

	this->update();
	this->render();
}

int Game::closeWindow(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	game->window.close();

	return 0;
}

int Game::cpp_setViewCenter(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	float pos_x = lua_tonumber(L, 1);
	float pos_y = lua_tonumber(L, 2);

	game->view.setCenter(pos_x, pos_y);

	return 0;
}

int Game::luaDT(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	lua_pushnumber(L, game->dt);

	return 1;
}

int Game::cpp_time(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	lua_pushinteger(L, game->globalClock.getElapsedTime().asMilliseconds());

	return 1;
}

int Game::setState(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	std::string state = lua_tostring(L, -2); //TOP OF STACK!!!

	int error = luaL_dofile(L, state.c_str());
	if (error)
	{
		std::cout << lua_tostring(L, -1) << "\n";
		lua_pop(L, lua_gettop(L));
	}

	return 0;
}

int Game::endState(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	//Cleanup of old state

	//Load new state
	std::string state = lua_tostring(L, -2); //TOP OF STACK!!!

	int error = luaL_loadfile(L, state.c_str()) | lua_pcall(L, 0, 0, 0);
	if (error)
	{
		std::cout << lua_tostring(L, -1) << "\n";
		lua_pop(L, lua_gettop(L));
	}

	return 0;
}

int Game::cpp_getMousePosScreen(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	lua_createtable(L, 2, 0);
	lua_pushinteger(L, game->mousePosScreen.x); lua_setfield(L, -2, "x");
	lua_pushinteger(L, game->mousePosScreen.y); lua_setfield(L, -2, "y");

	return 1;
}

int Game::cpp_getMousePosWindow(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	lua_createtable(L, 2, 0);
	lua_pushinteger(L, game->mousePosWindow.x); lua_setfield(L, -2, "x");
	lua_pushinteger(L, game->mousePosWindow.y); lua_setfield(L, -2, "y");

	return 1;
}

int Game::cpp_getMousePosWorld(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	lua_createtable(L, 2, 0);
	lua_pushinteger(L, static_cast<int>(game->mousePosWorld.x)); lua_setfield(L, -2, "x");
	lua_pushinteger(L, static_cast<int>(game->mousePosWorld.y)); lua_setfield(L, -2, "y");

	return 1;
}

int Game::cpp_setBackgroundTexture(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int texture_index = lua_tointeger(L, 1);

	game->background.setTexture(game->textures[texture_index]);

	return 0;
}

int Game::newTexture(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	std::string texture_file = lua_tostring(L, -2);

	sf::Texture* temp = new sf::Texture();
	if (!temp->loadFromFile(texture_file))
		std::cout << "! ERROR: COULD NOT OPEN TEXTURE FILE " << texture_file << "\n";
	else
		game->textures.push_back(temp);

	lua_pushinteger(L, game->textures.size() - 1);

	return 1;
}

int Game::newTextureBatch(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	std::string texture_batch_file = lua_tostring(L, -2);

	sf::Texture* temp = new sf::Texture();
	if (!temp->loadFromFile(texture_batch_file))
		std::cout << "! ERROR: COULD NOT OPEN TEXTURE FILE " << texture_batch_file << "\n";
	else
		game->textures.push_back(temp);

	lua_pushinteger(L, game->textures.size() - 1);

	return 1;
}

int Game::newSprite(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	//Texture
	int texture_index = lua_tonumber(L, 1);
	
	//Position
	float pos_x = lua_tonumber(L, 2);
	float pos_y = lua_tonumber(L, 3);

	game->sprites.push_back(new sf::Sprite());
	game->sprites.back()->setPosition(pos_x, pos_y);
	
	try
	{
		game->sprites.back()->setTexture(*game->textures[texture_index]);
	}
	catch (char* e)
	{
		std::cout << "! ERROR: " << e << "\n";
	}
	
	lua_pushinteger(L, game->sprites.size() - 1);

	return 1;
}

int Game::moveSprite(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	float pos_x = lua_tonumber(L, 2);
	float pos_y = lua_tonumber(L, 3);

	game->sprites[sprite_index]->move(pos_x, pos_y);

	return 0;
}

int Game::cpp_setSpritePosition(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	float pos_x = lua_tonumber(L, 2);
	float pos_y = lua_tonumber(L, 3);

	game->sprites[sprite_index]->setPosition(pos_x, pos_y);

	return 0;
}

int Game::cpp_getSpritePosition(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	lua_createtable(L, 2, 0);
	lua_pushinteger(L, game->sprites[sprite_index]->getPosition().x); lua_setfield(L, -2, "x");
	lua_pushinteger(L, game->sprites[sprite_index]->getPosition().y); lua_setfield(L, -2, "y");

	return 1;
}

int Game::cpp_rotateSprite(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	float angle = lua_tonumber(L, 2);

	game->sprites[sprite_index]->rotate(angle);

	return 0;
}

int Game::cpp_setSpriteRotation(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	float angle = lua_tonumber(L, 2);

	game->sprites[sprite_index]->setRotation(angle);

	return 0;
}

int Game::cpp_getSpriteRotation(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	lua_pushnumber(L, game->sprites[sprite_index]->getRotation());

	return 1;
}

int Game::cpp_setSpriteOrigin(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	float ori_x = lua_tonumber(L, 2);
	float ori_y = lua_tonumber(L, 3);

	game->sprites[sprite_index]->setOrigin(ori_x, ori_y);

	return 0;
}

int Game::cpp_getSpriteOriginX(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	lua_pushinteger(L, game->sprites[sprite_index]->getOrigin().x);

	return 1;
}

int Game::cpp_getSpriteOriginY(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	lua_pushinteger(L, game->sprites[sprite_index]->getOrigin().y);

	return 1;
}

int Game::cpp_setSpriteScale(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	float scale_x = lua_tonumber(L, 2);
	float scale_y = lua_tonumber(L, 3);

	game->sprites[sprite_index]->setScale(scale_x, scale_y);

	return 0;
}

int Game::cpp_getSpriteScale(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);

	lua_createtable(L, 2, 0);
	lua_pushnumber(L, game->sprites[sprite_index]->getScale().x); lua_setfield(L, -2, "x");
	lua_pushnumber(L, game->sprites[sprite_index]->getScale().y); lua_setfield(L, -2, "y");

	return 1;
}

int Game::cpp_setSpriteTexture(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	int sprite_index = lua_tointeger(L, 1);
	int texture_index = lua_tointeger(L, 2);

	game->sprites[sprite_index]->setTexture(*game->textures[texture_index]);

	return 0;
}

int Game::keyPressed(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);

	const int code = lua_tointeger(L, 1);
	lua_pushboolean(L, sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code)));

	return 1;
}

int Game::testFunc(lua_State* L)
{
	lua_getglobal(L, "Game");
	Game* game = (Game*)lua_touserdata(L, -1);
	
	std::cout << lua_tostring(L, -3) << " " << lua_tostring(L, -2) << "\n";
	//std::cout << lua_tostring(L, 1) << " " << lua_tostring(L, 2) << "\n";

	std::cout << " Stack Size" << lua_gettop(L) << "\n";

	return 0;
}
