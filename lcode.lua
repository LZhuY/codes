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

function canwin464(maxNum, target)
	local dp = {}
	for i=1, maxNum do 
		table.insert(dp, {val=i, use={[i]=i},idx={i}})
	end
	for i=1, target do
		local tmp = {}
		for k,v in pairs(dp) do
			for j=1, maxNum do
				if not v.use[j] then
					local item = tcopy(v)
					item.use[j] = j
					item.val = item.val + j
					table.insert(item.idx, j)
					if item.val >= target then
						return i%2, item
					end
					table.insert(tmp, item)
				end
			end
		end
		dp = tmp
	end
end

local res, item = canwin464(10, 19)
print (res == 1 and "win" or "lose")
for k,v in ipairs(item.idx) do 
	print(k,v)
end