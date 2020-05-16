Vector2 = {}
Vector2.__index = Vector2

function Vector2:Create(_x, _y)

local this =
{
	x = _x,
	y = _y
}

setmetatable(this, self)
return this

end

function Vector2:Subtract(vec)

	return Vector2:Create(self.x - vec.x, self.y - vec.y)

end

function Vector2:Add(vec)

	return Vector2:Create(self.x + vec.x, self.y + vec.y)

end

function Vector2:Dot(vec)

	return (self.x * vec.x + self.y * vec.y)

end

function Vector2:Length()

	return math.floor(math.sqrt(math.pow(self.x, 2) + math.pow(self.y, 2)))

end

function Vector2:Normalize()

	length = self:Length()
	return Vector2:Create(self.x / length, self.y / length)

end

function Vector2:Angle(vec)

	return math.acos(self:Dot(vec))

end