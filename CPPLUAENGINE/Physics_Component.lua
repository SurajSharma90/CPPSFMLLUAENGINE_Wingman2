Physics_Component = {}
Physics_Component.__index = Physics_Component

function Physics_Component:Create(_sprite, _hitbox)

	local this =
	{
		sprite = _sprite,
		hitbox = _hitbox,
		velocityMax = 800.0,
		velocityMin = 8.0,
		velocityX = 0.0,
		velocityY = 0.0,
		acceleration = 1700.0,
		deceleration = 100.0,
		drag = 0.98
	}

	setmetatable(this, self)
	return this

end

function Physics_Component:Move(dir_x, dir_y)

	--Update acceleration depending on direction
	self.velocityX = self.velocityX + (cpp_luaDT() * dir_x * self.acceleration)
	self.velocityY = self.velocityY + (cpp_luaDT() * dir_y * self.acceleration)

	--Limit velocity
	if math.abs(self.velocityX) > self.velocityMax then
		self.velocityX = self.velocityMax * (self.velocityX > 0.0 and 1.0 or -1.0) -- SUPA CLEAN WAY OF TERNARY OPERATOR
	end

end

function Physics_Component:Update()

	--Update deceleration
	
	self.velocityX = self.velocityX * self.drag
	self.velocityY = self.velocityY * self.drag

	if math.abs(self.velocityX) < self.velocityMin  then
		self.velocityX = 0.0
	end
	if math.abs(self.velocityY) < self.velocityMin  then
		self.velocityY = 0.0
	end

	--if math.abs(self.velocityX) > 0.0 then
	--	self.velocityX = self.velocityX + (cpp_luaDT() * self.deceleration) * (self.velocityX < 0.0 and 1.0 or -1.0) -- SUPA CLEAN WAY OF TERNARY OPERATOR
	--end
	--
	--if math.abs(self.velocityY) > 0.0 then
	--	self.velocityY = self.velocityY + (cpp_luaDT() * self.deceleration) * (self.velocityY < 0.0 and 1.0 or -1.0) -- SUPA CLEAN WAY OF TERNARY OPERATOR
	--end
	
	cpp_moveSprite(self.sprite, self.velocityX * cpp_luaDT(), self.velocityY * cpp_luaDT())

end