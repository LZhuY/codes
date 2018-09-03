function tcopy(tb)
	local tmp = {}
	for k,v in pairs(tb) do
		if type(v) == "number" then
			tmp[k]=v
		elseif type(v) == "table" then
			tmp[k] = tcopy(v)
		end
	end
	return tmp
end