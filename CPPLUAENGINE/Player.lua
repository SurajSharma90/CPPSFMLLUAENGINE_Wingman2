Player = {}
Player.__index = Player

function Player:Create(x, y)

local this = 
{
	aura_sprite = cpp_newSprite(Player_Aura_Textures[2], x, y),
	cannon_sprite = cpp_newSprite(Player_Cannon_Texture, x, y),
	cockpit_sprite = cpp_newSprite(Player_Cockpit_Textures[1], x, y),
	left_wing_sprite = cpp_newSprite(Player_Left_Wing_Textures[1], x, y),
	right_wing_sprite = cpp_newSprite(Player_Right_Wing_Textures[1], x, y),	
	
	heading = Vector2:Create(0.0, 0.0),

	physics_component = nil
}

this.physics_component = Physics_Component:Create(this.cockpit_sprite, 0)

--REDO THIS!!!!!!!!! HARDCODED REMEMBER!!!!!!!!!!!!!!!!!!!!!
cpp_setSpriteOrigin(this.aura_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.cockpit_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.left_wing_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.right_wing_sprite, 100.0, 100.0)
cpp_setSpriteOrigin(this.cannon_sprite, 100.0, 100.0)
--REDO THIS!!!!!!!!! HARDCODED REMEMBER!!!!!!!!!!!!!!!!!!!!!

setmetatable(this, self)
return this

end

function Player:Move(dir_x, dir_y)

	self.physics_component:Move(dir_x, dir_y)

end

function Player:UpdateShipParts()
	
	--Position
	cpp_setPositionSprite(
		self.aura_sprite, 
		cpp_getPositionSpriteX(self.cockpit_sprite),
		cpp_getPositionSpriteY(self.cockpit_sprite)
	)
	
	cpp_setPositionSprite(
		self.cannon_sprite,
		cpp_getPositionSpriteX(self.cockpit_sprite),
		cpp_getPositionSpriteY(self.cockpit_sprite)
	)
	
	cpp_setPositionSprite(
		self.left_wing_sprite,
		cpp_getPositionSpriteX(self.cockpit_sprite) + self.heading:AngleRelativeTo(-170).x * (math.abs(self.physics_component.velocityX / 40) + math.abs(self.physics_component.velocityY / 40)),
		cpp_getPositionSpriteY(self.cockpit_sprite) + self.heading:AngleRelativeTo(-170).y * (math.abs(self.physics_component.velocityX / 40) + math.abs(self.physics_component.velocityY / 40))
	)

	cpp_setPositionSprite(
		self.right_wing_sprite,
		cpp_getPositionSpriteX(self.cockpit_sprite) + self.heading:AngleRelativeTo(170).x * (math.abs(self.physics_component.velocityX / 40) + math.abs(self.physics_component.velocityY / 40)),
		cpp_getPositionSpriteY(self.cockpit_sprite) + self.heading:AngleRelativeTo(170).y * (math.abs(self.physics_component.velocityX / 40) + math.abs(self.physics_component.velocityY / 40))
	)

	--Rotation

	cpp_rotateSprite(
		self.aura_sprite, 
		5
	)

	cpp_setSpriteRotation(
		self.cannon_sprite, 
		cpp_getSpriteRotation(self.cockpit_sprite)
	)

	cpp_setSpriteRotation(
		self.left_wing_sprite, 
		cpp_getSpriteRotation(self.cockpit_sprite)
	)

	cpp_setSpriteRotation(
		self.right_wing_sprite, 
		cpp_getSpriteRotation(self.cockpit_sprite)
	)

end

function Player:UpdatePhysicsComponent()

	self.physics_component:Update()

end

function Player:UpdateHeading()

	playerPos = Vector2:Create(cpp_getPositionSpriteX(), cpp_getPositionSpriteY())
	mousePos = Vector2:Create(cpp_getMousePosWorld().x, cpp_getMousePosWorld().y)
	
	self.heading = mousePos:Subtract(playerPos):Normalize()
	angle = math.deg(math.atan2(self.heading.y, self.heading.x)) + 90.0
	cpp_setSpriteRotation(self.cockpit_sprite, angle)

end

function Player:Update()

	self:UpdatePhysicsComponent()

	self:UpdateHeading()

	self:UpdateShipParts()
	
	cpp_setViewCenter(
		cpp_getPositionSpriteX(
			self.cockpit_sprite
		) + self.physics_component.velocityX / 10, 
		cpp_getPositionSpriteY(
			self.cockpit_sprite
		)  + self.physics_component.velocityY / 10
	)

end