--Player
function file_exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

-- get all lines from a file, returns an empty 
-- list/table if the file does not exist
function lines_from(file)
  local f = io.open(file)

  local indices = {}
  for line in io.lines(file) do
    table.insert(indices, cpp_newTexture(line))
  end

  f:close()

  return indices
end

Player_Aura_Textures = lines_from("Textures/Accessories/Auras/auras.txt")

Player_Cockpit_Textures = lines_from("Textures/Accessories/Cockpits/cockpits.txt")

Player_Left_Wing_Textures = lines_from("Textures/Accessories/Left_Wings/left_wings.txt")

Player_Right_Wing_Textures = lines_from("Textures/Accessories/Right_Wings/right_wings.txt")

Player_Cannon_Texture = cpp_newTexture("Textures/Guns/gun01.png")