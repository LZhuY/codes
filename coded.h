#include <string>
#include <vector>
#include <map>

using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};

struct TNode{
	int val;
	TNode* left;
	TNode* right;
	TNode(int v):val(v),left(NULL),right(NULL){}
};

class Solution{
public:

	int maxproduct_xx_1(vector<int>& nums) {
		int res=nums[0], pos=nums[0], neg=nums[0];
		bool reset = false;
		for(int i=1; i<nums.size(); i++){
			if(nums[i] == 0){
				reset = true;
				pos = nums[i];
			}else if(reset){
				pos = nums[i];
				neg = nums[i];
				reset = false;
			}else{
				int tmpPos=pos, tmpNeg=neg;
				pos = max( tmpPos, max(tmpPos*nums[i], tmpNeg*nums[i]));
				neg = min(tmpNeg, min(tmpPos*nums[i], tmpNeg*nums[i]));
			}
			res = max(res, pos);
		}
		return res;
    }

	vector<int> produceextself(vector<int> nums){
		int sz = nums.size();
		vector<int> result(sz, 0);
		vector<int> tmp1(sz, nums[0]);
		vector<int> tmp2(sz, nums[sz-1]);
		for(int i=1; i<sz; i++){
			tmp1[i] = nums[i]*tmp1[i-1];
		}
		for(int i=sz-2; i>=0; i--){
			tmp2[i] = nums[i]*tmp2[i+1];
		}
		
		for(int i=0; i<sz; i++){
			int l = i>0 ? tmp1[i-1] : 1;
			int r = i<sz-1? tmp2[i+1]:1;
			result[i] = l*r;
		}
		return result;
	}

	vector<int> spiralOrder_xx_1(vector<vector<int>>& matrix){
		int row = matrix.size();
		int cow = matrix[0].size();
		int top=0, bottom=row-1, left=0, right=cow-1, idx=0;
		vector<int> result(row*cow, 0);
		vector<int> dir(2,0); dir[0]=1, dir[1]=0;
		vector<int> cur(2,0); cur[0]=0, cur[1]=0;
		while( idx < row*cow ){
			result[idx] = matrix[cur[0]][cur[1]];
			if( cur[0] >= top && cur[0] <= bottom && cur[1] >= left && cur[1] <= right ){
				cur[0]=cur[0]+dir[0];
				cur[1]=cur[1]+dir[1];
			}else if(cur[0] < top){
				dir[0]=0, dir[1]=1;
				top--;
				cur[0]=top;
			}else if(cur[0] > bottom){
				dir[0]=0, dir[1]=-1;
				bottom++;
				cur[1]=bottom;
			}else if(cur[1] < left){
				dir[0]=1, dir[1]=0;
				left++;
				cur[1]=left;
			}else if(cur[1] > right){
				dir[0]=1,dir[1]=0;
				right--;
				cur[1]=right;
			}
			idx++;
		}
		return result;
	}

	int maxlengthkk(string s){
		stack<int> sta;
		vector<int> idx(s.size(), 0);
		int maxLen=0, tmpLen=0;
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			if( c == '(')
				sta.push(-i);
			else if( !sta.empty() ){
				int tmp = sta.top();
				sta.pop();
				idx[i] = 1;
				idx[-tmp]=1;
			}
		}
		for(int i=0; i<idx.size(); i++){
			if(idx[i] == 1){
				tmpLen++;
				maxLen = max(maxLen,tmpLen);
			}else
				tmpLen=0;
		}
		return maxLen;
	}

	int rangeSum_xx303(vector<int>& nums, int l, int r){
		vector<int> sums(nums.size(), 0);
		for(int i=0; i<nums.size(); i++){
			sums[i] = i == 0 ? nums[i] : nums[i]+sums[i-1];
		}
		return sums[r]-(l>0?s[l-1]:0);
	}

	int integerBreakerxx343(int n){
		vector<int> maxm(n+10, 0);
		maxm[0]=0, maxm[1]=0, maxm[2]=2, maxm[3]=3, maxm[4]=4, maxm[5]=6, maxm[6]=9, maxm[7]=12, maxm[8]=18;
		if(n==2)
			return 1;
		if(n==3)
			return 2;
		if(n<=8)
			return maxm[n];
		for(int i=8; i<=n; i++){
			int m = i/2;
			for(int j=2; j<=m; j++){
				int other = i-j;
				int sum = maxm[other]*maxm[j];
				maxm[i] = max(maxm[i], sum);
			}
		}
		return maxm[n];
	}

	// 0 <= i < 10^n
	int countnumberwithuniquedigist357(int n){
		if(n == 1)
			return 10;
		vector<int> dp(n, 0);
		dp[0] = 1, dp[1]=10;
		for(int i=2; i<=n; i++){
			dp[i] = (10-1)*dp[i-1];
		}
		return dp[n];
	}

	int checkCountnumberwithuniquedigist357(int n){
		int count = 0;
		set<int> digits;
		int maxNum = pow(10, n);
		for(int i=0; i<maxNum; i++){
			digits.clear();
			int tmpNum = i;
			if(tmpNum == 0){
				count++;
				continue;
			}
			bool diff = true;
			while(tmpNum > 0){
				int digit = tmpNum%10;
				tmpNum = tmpNum/10;
				auto res = digits.insert(digit);
				if(!res.second){
					diff = false;
					break;
				}
			}
			if(diff)
				count++;
		}
		return count;
	}

	int taowamaxlevel(vector<pair<int,int>>& nums){
		sort(nums.begin(), nums.end(), [](const pair<int,int>& a, const pair<int,int>& b){ return a.first*a.second > b.first*b.second; });
		int maxLevel = 0;
		vector<int> dp(nums.size(), 1);
		for(int i=0; i<nums.size(); i++){
			for(int j=i-1; j>=0; j--){
				if(nums[i].first >= nums[j].first && nums[i].second >= nums[j].second){
					dp[i] = max( dp[i], dp[j]+1 );
					maxLevel = max(maxLevel, dp[i]);
				}
			}
		}
		return maxLevel;
	}

	vector<int> largestdiviablesubarray368(vector<int>& nums){
		sort(nums.begin(), nums.end(), [](const int a, const int b){ return a<b; });
		vector<vector<int>> results;
		for(int i=0; i<nums.size(); i++){
			bool bHit = false;
			for(auto& item : results){
				if( nums[i]%item.back() == 0 ){
					bHit = true;
					item.push_back(nums[i]);
				}
			}
			if(!bHit){
				results.push_back(vector<int>(1, nums[i]));
			}
		}
		vector<int>* ptr = NULL;
		for(auto& item : results){
			if( ptr == NULL || ptr->size() < item.size() )
				ptr = &item;
		}
		return *ptr;
	}

	int minicostjudegenum375(int n){
		vector<pair<int,int>> nums(n+1, std::pair<int,int>(INT_MAX,0));
		if(n <= 3) 
			return n-1;
		nums[0]=std::pair<int,int>(0,0);
		nums[1]=std::pair<int,int>(0,0);
		nums[2]=std::pair<int,int>(1,1);
		nums[3]=std::pair<int,int>(2,1);
		for(int i=4; i<=n; i++){
			for(int j=1; j<=i-j; j++){
				int tmp = j + nums[j-1].first + nums[i-j].first + nums[i-j].second*(j);
				if(tmp < nums[i].first){
					nums[i].first = tmp;
					nums[i].second = nums[i-j].second + nums[j].second + 1;
				}
			}
		}
		return nums[n].first;
	}

	int minpathlen120x( vector<vector<int>>& trigle ){
		int maxPath = 0;
		for( int i=0; i<trigle.size(); i++ ){
			for(int j=0; j<trigle[i].size(); j++){
				trigle[i][j] = trigle[i][j] > 0 ? -trigle[i][j] : trigle[i][j];
				int top = i-1, left = j-1, right = j;
				if( top >= 0){
					int tmp = trigle[i][j];
					if(left >= 0 )
						tmp = tmp+trigle[top][left];
					if(right < trigle[top].size()){
						tmp = min(tmp, trigle[i][j]+trigle[top][left]);
					}
					trigle[i][j] = tmp;
					maxPath = min(maxPath, trigle[i][j]);
				}
			}
		}
		return maxPath*-1;
	}

	int wigglemaxlen376xx(vector<int>& nums){

	}

	int numTrees96(int n) { //G(n) = G(j-1)*G(n-j) (1<=j<=n)
		vector<int> dp(n+1, 0);
		dp[0]=dp[1]=1;
		for(int i=2; i<=n; i++){
			for(int j=1; j<=i; j++){
				dp[i] += dp[j-1]*dp[i-j];
			}
		}
		return dp[n];
	}

	vector<string> wordbreak140(string s, vector<string>& wordDick){
		vector<string> results;
		map<int, vector<vector<int>>> breakIndex;
		vector<bool> dp(s.size()+1, false);
		dp[0] = true;
		for(int i=1; i<=s.size(); i++){
			for(auto& tmp : wordDick){
				int len = tmp.size();
				if( i<len || !dp[i-len] || s.substr(i-len, len) != tmp )
					continue;
				dp[i] = true;
				for( auto paths : breakIndex[i-len] ){
					for(auto path : paths){
						path.push_back(i);
						breakIndex[i].push_back(path);
					}
				}
			}
		}
		for(auto& paths : breakIndex){
			for(auto& path : paths){
				string tmpStr;
				int lastIdx = 0;
				for(auto idx : path){
					if(idx ==0)
						continue;
					tmpStr.append(s.substr(lastIdx, idx));
					tmpStr.append(' ');
					lastIdx = idx;
				}
				results.push_back(tmpStr);
			}
		}
		return results;
	}

	bool issubstring392(string s, string t){
		int lastIdx = 0;
		bool hit = false;
		for(int i=0; i<s.size(); i++){
			hit = false;
			for(int j=lastIdx; j<t.size(); j++){
				if(s[i] == t[j]){
					lastIdx = j+1;
					hit = true;
					break;
				}
			}
			if(!hit)
				return false;
		}
		return true;
	}

    bool caniwin(int maxChoosableInteger, int desiredTotal) {
        if (maxChoosableInteger >= desiredTotal) 
        	return true;
        if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) 
        	return false;
        unordered_map<int, bool> m;
        return canwin(maxChoosableInteger, desiredTotal, 0, m);
    }
    bool canwin(int length, int total, int used, unordered_map<int, bool>& m) {
        if (m.count(used)) 
        	return m[used];
        for (int i = 0; i < length; ++i) {
            int cur = (1 << i);
            if ((cur & used) == 0) {
                if (total <= i + 1 || !canwin(length, total - (i + 1), cur | used, m)) {
                    m[used] = true;
                    return true;
                }
            }
        }
        m[used] = false;
        return false;
    }

    bool caniwin2(int maxChoosableInteger, int desiredTotal) {
        maxn = maxChoosableInteger;
        if(maxn >= desiredTotal) 
        	return true;
        if((1 + maxn) * maxn / 2 < desiredTotal)
        	return false;
        return canwin2(desiredTotal, 0, maxn);
    }
    bool canwin2(int target, int visited, int maxn) {
        if(m.count(visited)) 
        	return m[visited];
        for(int i = 1; i <= maxn; i++) {
            int mask = (1 << i); // 被动动数 << or >> 移动位数
            if( (mask & visited) == 0 && (i >= target || canwin2(target - i, mask | visited, maxn) == false)) {
                m[visited] = true;
                return true;
            }
        }
        m[visited] = false;
        return false;
    }

	void findtargetsumwayHelp(int sum, vector<int>& nums, int idx, int target, int& cnt){
		if(idx >= nums.size())
			return;
		int leftSum = sum( nums.begin()+idx, nums.end() );
		if(sum + leftSum < target || sum - leftSum > target )
			return;
		if(sum + nums[idx] == target)
			cnt++;
		findtargetsumwayHelp(sum+nums[idx], nums, idx+1, target, cnt);

		if(sum - nums[idx] == target)
			cnt++;
		findtargetsumwayHelp(sum-nums[idx], nums, idx+1, target, cnt);
	}

	int findtargetsumway494(vector<int>& nums, int target){ // dps
		int cnt = 0;
		findtargetsumwayHelp(0, nums, 0, target, cnt);
		return cnt;
	}

	void diffwaysumtotargetHelp(vector<int, vector<vector<int>>>& paths, vector<int>& nums, int target, vector<int> path, int curSum){
		if(curSum > target)
			return;
		for(int i=0; i<nums.size(); i++){
			int tmpSum = curSum+nums[i];
			if(tmpSum == target){
				path.push_back(nums[i]);
				paths.push_back(path);
			}else if( tmpSum > target ){
				continue;
			}else{
				diffwaysumtotargetHelp(paths, nums, target, path, tmpSum);
			}
		}
	}

	vector<vector<int>> diffwaysumtotarget377(vector<int>& nums, int target){
		vector<int, vector<vector<int>>> paths;
		diffwaysumtotargetHelp(paths, nums, target, vector<int>(), 0);
		return paths;
	}

	bool canPartitionKsubset698(vector<int>& nums, int k){
		int totalSum = sum(nums.begin(), nums.end());
		int eachSetSum = totalSum/k;
		sort(nums.begin(), nums.end());
		if(k > nums.size())
			return false;
		int cnt = 0;

		while(true){
			vector<int> sumPath(eachSetSum+1, -1);
			sumPath[0] = 0;
			for(int i=1; i<=eachSetSum; i++){
				for(int j=0; j<nums.size(); j++){
					int tmpVal = nums[j];
					if(tmpVal != 0)
						continue;
					if( (i-tmpVal) >= 1 && sumPath[i-tmpVal] != -1 ){
						sumPath[i] = i-tmpVal;
					}
				}
			}
			if(sumPath[eachSetSum] != -1){
				int curIdx = sumPath[eachSetSum];
				while(curIdx >= 1){
					nums[curIdx] = 0;
					curIdx = sumPath[curIdx];
				}
				cnt++;
			}
		}
		return cnt == k;
	}

	int wiggleMaxLength376(int[] nums) {
        int n = nums.length;
        if(n <= 1)
            return n;
        int result = nums[0] != nums[1] ? 2:1;
        int flag = nums[1] - nums[0];
        for(int i=2;i<nums.length;i++){
            if((nums[i] - nums[i-1]) * flag < 0 || (flag==0 && (nums[i] - nums[i-1]) != 0)){
                result ++;
                flag = nums[i] - nums[i-1];
            }
        }
        return result;
    }
};
