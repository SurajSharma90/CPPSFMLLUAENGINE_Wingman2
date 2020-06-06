Timer = {}
Timer.__index = Timer

function Timer:Create(_max)

	local this = 
	{
		start = 0,
		max = _max
	}
	
	setmetatable(this, self)
	return this

end

function Timer:Restart()

	local diff = os.difftime(os.time, self.start)
	self.start = os.time()
	return diff

end

function Timer:GetElapsedTime()
	
	local diff = os.difftime(os.time(), self.start)
	return diff

end