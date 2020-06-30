Player = {}
Player.__index = Player

function Player:Create(x, y)

local this = 
{
	aura_index = 1,
	cockpit_index = 1,
	left_wing_index = 1,
	right_wing_index = 1,
	aura_sprite = cpp_newSprite(Player_Aura_Textures[1], x, y),
	body_sprite = cpp_newSprite(Player_Body_Textures[1], x, y),
	cannon_sprite = cpp_newSprite(Player_Cannon_Texture, x, y),
	cockpit_sprite = cpp_newSprite(Player_Cockpit_Textures[1], x, y),
	left_wing_sprite = cpp_newSprite(Player_Left_Wing_Textures[1], x, y),
	right_wing_sprite = cpp_newSprite(Player_Right_Wing_Textures[1], x, y),
	
	heading = Vector2:Create(0.0, 0.0),

	physics_component = nil
}

local scale = 0.8
cpp_setSpriteScale(this.aura_sprite, scale, scale)
cpp_setSpriteScale(this.body_sprite, scale, scale)
cpp_setSpriteScale(this.cannon_sprite, 0.9, 0.9)
cpp_setSpriteScale(this.cockpit_sprite, scale, scale)
cpp_setSpriteScale(this.left_wing_sprite, scale, scale)
cpp_setSpriteScale(this.right_wing_sprite, scale, scale)

this.physics_component = Physics_Component:Create(this.body_sprite, 0)

--REDO THIS!!!!!!!!! HARDCODED REMEMBER!!!!!!!!!!!!!!!!!!!!!
cpp_setSpriteOrigin(this.aura_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.body_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.cockpit_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.left_wing_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.right_wing_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.cannon_sprite, 100.0, 100.0)
--REDO THIS!!!!!!!!! HARDCODED REMEMBER!!!!!!!!!!!!!!!!!!!!!

setmetatable(this, self)
return this

end

function Player:CycleAuras()

	self.aura_index = self.aura_index + 1;
	
	if self.aura_index > #Player_Aura_Textures then
		self.aura_index = 1
	end

	cpp_setSpriteTexture(self.aura_sprite, Player_Aura_Textures[self.aura_index])

end

function Player:CycleCockpits()

	self.cockpit_index = self.cockpit_index + 1;
	
	if self.cockpit_index > #Player_Cockpit_Textures then
		self.cockpit_index = 1
	end

	cpp_setSpriteTexture(self.cockpit_sprite, Player_Cockpit_Textures[self.cockpit_index])

end

function Player:CycleLeftWings()

	self.left_wing_index = self.left_wing_index + 1;
	
	if self.left_wing_index > #Player_Left_Wing_Textures then
		self.left_wing_index = 1
	end

	cpp_setSpriteTexture(self.left_wing_sprite, Player_Left_Wing_Textures[self.left_wing_index])

end

function Player:CycleRightWings()

	self.right_wing_index = self.right_wing_index + 1;
	
	if self.right_wing_index > #Player_Right_Wing_Textures then
		self.right_wing_index = 1
	end

	cpp_setSpriteTexture(self.right_wing_sprite, Player_Right_Wing_Textures[self.right_wing_index])

end
	
function Player:Move(dir_x, dir_y)

	self.physics_component:Move(dir_x, dir_y)

end

function Player:UpdateShipParts()
	
	--Position
	local x = cpp_getSpritePosition(self.body_sprite).x
	local y = cpp_getSpritePosition(self.body_sprite).y

	cpp_setSpritePosition(
		self.aura_sprite, 
		x,
		y
	)

	local cockpit_modifer = 90
	cpp_setSpritePosition(
		self.cockpit_sprite, 
		x - self.heading:AngleRelativeTo(180).x * (math.abs(self.physics_component.velocityX / cockpit_modifer) + math.abs(self.physics_component.velocityY / cockpit_modifer)),
		y - self.heading:AngleRelativeTo(180).y * (math.abs(self.physics_component.velocityX / cockpit_modifer) + math.abs(self.physics_component.velocityY / cockpit_modifer))
	)
	
	cpp_setSpritePosition(
		self.cannon_sprite,
		x,
		y
	)
	
	local wing_modifer = 50
	cpp_setSpritePosition(
		self.left_wing_sprite,
		x + self.heading:AngleRelativeTo(-170).x * (math.abs(self.physics_component.velocityX / wing_modifer) + math.abs(self.physics_component.velocityY / wing_modifer)),
		y + self.heading:AngleRelativeTo(-170).y * (math.abs(self.physics_component.velocityX / wing_modifer) + math.abs(self.physics_component.velocityY / wing_modifer))
	)

	cpp_setSpritePosition(
		self.right_wing_sprite,
		x + self.heading:AngleRelativeTo(170).x * (math.abs(self.physics_component.velocityX / wing_modifer) + math.abs(self.physics_component.velocityY / wing_modifer)),
		y + self.heading:AngleRelativeTo(170).y * (math.abs(self.physics_component.velocityX / wing_modifer) + math.abs(self.physics_component.velocityY / wing_modifer))
	)

	--Rotation

	cpp_rotateSprite(
		self.aura_sprite, 
		5
	)

	cpp_setSpriteRotation(
		self.cockpit_sprite, 
		cpp_getSpriteRotation(self.body_sprite)
	)

	cpp_setSpriteRotation(
		self.cannon_sprite, 
		cpp_getSpriteRotation(self.body_sprite)
	)

	cpp_setSpriteRotation(
		self.left_wing_sprite, 
		cpp_getSpriteRotation(self.body_sprite)
	)

	cpp_setSpriteRotation(
		self.right_wing_sprite, 
		cpp_getSpriteRotation(self.body_sprite)
	)

end

function Player:UpdatePhysicsComponent()

	self.physics_component:Update()

end

function Player:UpdateHeading()

	local playerPos = Vector2:Create(cpp_getSpritePosition(self.body_sprite).x, cpp_getSpritePosition(self.body_sprite).y)
	local mousePos = Vector2:Create(cpp_getMousePosWorld().x, cpp_getMousePosWorld().y)
	
	self.heading = mousePos:Subtract(playerPos):Normalize()
	local angle = math.deg(math.atan2(self.heading.y, self.heading.x)) + 90.0
	cpp_setSpriteRotation(self.body_sprite, angle)

end

function Player:Update()

	self:UpdatePhysicsComponent()

	self:UpdateHeading()

	self:UpdateShipParts()
	
	cpp_setViewCenter(
		cpp_getSpritePosition(
			self.body_sprite
		).x + self.physics_component.velocityX / 10, 
		cpp_getSpritePosition(
			self.body_sprite
		).y  + self.physics_component.velocityY / 10
	)

end