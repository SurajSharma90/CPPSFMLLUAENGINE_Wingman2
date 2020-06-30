require("RegisterCppFunctions")
require("Keyboard")
require("Mouse")
require("Vector2")
require("Timer")

require("Functions")
require("GameState_Textures")
require("Initialize_Components")

require("Player")

print("Start GameState!")

local keyTime = 0.0
local keyTimeMax = 100.0

local bgTex = cpp_newTexture("Textures/Backgrounds/spacebg.png")
cpp_setBackgroundTexture(bgTex)

local player1 = Player:Create(0, 0)

local timer = Timer:Create() 

--virus = cpp_newSprite(Virus_Texture, 0.0, 0.0)
--cpp_setSpriteScale(virus, 0.5, 0.5)

--​You can do like this Suraj. void call_lua(auto& func, auto...args){func(args...);} MRPHD--
--​func(L, args...) in your case--

function getKeyTime()

	if keyTime >= keyTimeMax then
		keyTime = 0.0
		return true
	end

	return false
end

function updateKeyTime()

	keyTime = keyTime + 625.0 * luaDT()

end

function updatePlayerMovement()

	if cpp_keyPressed(KEY_D) then
		player1:Move(1.0, 0.0)
	elseif cpp_keyPressed(KEY_A) then
		player1:Move(-1.0, 0.0)
	end

	if cpp_keyPressed(KEY_S) then
		player1:Move(0.0, 1.0)
	elseif cpp_keyPressed(KEY_W) then
		player1:Move(0.0, -1.0)
	end

end

function updatePlayerCosmetics()

	if cpp_keyPressed(KEY_Num1) and getKeyTime() then
		player1:CycleAuras()
	elseif cpp_keyPressed(KEY_Num2) and getKeyTime() then
		player1:CycleCockpits()
	elseif cpp_keyPressed(KEY_Num3) and getKeyTime() then
		player1:CycleLeftWings()
	elseif cpp_keyPressed(KEY_Num4) and getKeyTime() then
		player1:CycleRightWings()
	end

end

function update()

	updateKeyTime();

	updatePlayerMovement();

	updatePlayerCosmetics();

	local mousePosGridX = cpp_getMousePosWorld().x / 50;
	local mousePosGridY = cpp_getMousePosWorld().y / 50;

	if cpp_mousePressed(MOUSE_LEFT) then
		cpp_addTile(0, mousePosGridX, mousePosGridY, 0, 0, 0, 50, 50)
	end

	player1:Update()

end

print("End GameState!")