
--* all . 
function processNext(s)
	local nextTb = {}
	local i = 0
	local n = -1
	local len = #s
	while i < len do
		if n == -1 or s[i] == s[n] then
			n = n + 1
			nextTb[i] = n
			i = i + 1
		elseif n>=1 then
			n = nextTb[n-1]
		else
			nextTb[i] = 0
			i = i+1
		end
	end
	return nextTb
end

function matchPatter(s, p)
	local nextTb = processNext(p)
	local sLen = #s-1
	local pLen = #p-1
	local jIndex = 0
	local iIndex = 0
	for i=0, sLen do 
		if s[i] == p[jIndex] then
			i = i + 1
			jIndex = jIndex + 1
			iIndex = i
		else
			jIndex = nextTb[jIndex]
		end
	end
	if jIndex == pLen then
		return iIndex - jIndex
	end
	return -1
end

local index = matchPatter( {[0]='a','b','c','d'}, {[0]='b', 'c', 'd'} )
print(index)


function ismatch(s, p)
	local dp={}
	local sLen = #s 
	local pLen = #p 
	for i=1, sLen do 
		for j=1, pLen do 
			dp[i] = dp[i] or {}
			local match = p[j] == '*' or p[j] == '.' or p[j] == s[i]
			if i>1 and j>1 then
				dp[i][j] = dp[i-1][j-1] and match
			else
				dp[i][j] = match
			end
		end
	end
	return dp[sLen][pLen]
end

