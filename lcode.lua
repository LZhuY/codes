
function tbsize(tb)
	local num = 0
	for k,v in pairs(tb) do
		num = num + 1
	end
	return num
end

function tbsum(tb)
	local sum = 0
	for k,v in pairs(tb) do 
		sum = sum + v
	end
	return sum
end

function fourSum1(result, nums, target)
	local tmpMap={}
	local sum = 0
	local sz = #nums
	for index1=1, sz-3 do
		sum = nums[index1]
		for index2=index1+1, sz-2 do
			sum = sum + nums[index2]
			for index3=index2+1, sz-1 do
				sum = sum + nums[index3]
				for index4=index3+1, sz do
					sum = sum + nums[index4] 
					if sum == target then
						local tmp = {nums[index1], nums[index2], nums[index3], nums[index4]}
						if not tmpMap[table.concat(tmp,"_")] then
							table.insert(result, {nums[index1], nums[index2], nums[index3], nums[index4]})
						end
					end
					sum = sum - nums[index4]
				end
				sum = sum - nums[index3]
			end
			sum = sum - nums[index2]
		end
		sum = 0
	end
end

result = {}
fourSum1(result, {1,0,-1,0,-2,2}, 0)
for k,v in pairs(result) do 
	print(table.concat(v, " "))
end

function judgetwolisthascyc(l1, l2){
	
}
