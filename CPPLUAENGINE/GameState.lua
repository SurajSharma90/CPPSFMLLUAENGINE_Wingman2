require("RegisterCppFunctions")
require("Keyboard")
require("GameState_Textures")
require("Vector2")

require("Initialize_Components")

require("Player")

print("Start GameState!")

bgTex = cpp_newTexture("Textures/Backgrounds/spacebg.png")
cpp_setBackgroundTexture(bgTex)

player1 = Player:Create(0, 0)

--​You can do like this Suraj. void call_lua(auto& func, auto...args){func(args...);} MRPHD--
--​func(L, args...) in your case--

function update()

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

	player1:Update()

end

print("End GameState!")