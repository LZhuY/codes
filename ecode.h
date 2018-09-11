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
	vector<vector<int>> fourSum(vector<int>& nums, int target){
		vector<vector<int>> results;
		int sz = nums.size();
		if(sz < 4)
			return results;
		sort(nums.begin(), nums.end());
		int left = 0;
		int right = left+3;
		for(left=0; left <= sz-3; left++, right=left+3){
			if(left > 0 && nums[left] == nums[left-1])
				continue;
			int sum1 = nums[left]+nums[left+1]+nums[left+2];
			for(int i=right; i<=sz; i++){
				int sum = sum1 + nums[i];
				if(sum == target){
					vector<int> tmp;
					tmp.push_back(nums[left]);
					tmp.push_back(nums[left+1]);
					tmp.push_back(nums[left+2]);
					tmp.push_back(nums[i]);
					results.push_back(tmp);
				}
			}
		}
		return results;
	}

	vector<vector<int>> fourSum1(vector<int>& nums, int target){
		vector<vector<int>> results;
		int sz = nums.size();
		if(sz < 4)
			return results;

		sort(nums.begin(), nums.end());

		for(int l1=0; l1<sz-3; l1++){
			if(l1 > 0 && nums[l1] == nums[l1-1])
				continue;
			int target1 = target - nums[l1];

			for(int l2=l1+1, l2<sz-2; l2++){
				if(l2 > l1+1 && nums[l2]==nums[l2-1])
					continue;
				int target2 = target1 - nums[l2];

				for(int l3=l2+1, l4=sz; l3<l4; ){
					int twoSum = nums[l3]+nums[l4];
					if(twoSum == target2){
						int arr[4] = {nums[l1], nums[l2], nums[l3], nums[l4]};
						results.push_back(vector<int>(arr, arr+4));
						l3++; l4--;
						while( l3 < l4 && nums[l3] == nums[l3-1] ) l3++;
						while(l3 < l4 && nums[l4] == nums[l4+1]) l4--;
					}else if(twoSum > target2){
						l4--;
						while(l3 < l4 && nums[l4] == nums[l4+1]) l4--;
					}else
						l3++;
						while(l3 < l4 && nums[l3] == nums[l3-1]) l3++;
				}
			}
		}
		return results;
	}

	int removeElement_27_1(vector<int>& nums, int val){
		int sz = nums.size();
		if(sz == 0)
			return;
		int left=0;
		while(left < sz && nums[left] ~= val) left++;
		for(int i=left+1; i<sz; i++){
			if(nums[i] == val)
				continue;
			nums[left++] = nums[i];
		}
		return left;
	}

	vector<vector<int>> transpose_867_1(vector<vector<int>>& A){
		vector<vector<int>> tmpA(1000, vector<int>(1000, 0));
		if(A.size() <= 0)
			return tmpA;
		for(int row=0; row<A.size(); row++){
			for(int cow=0; cow<A[0].size(); cow++){
				if(row == cow)
					continue;
				tmpA[cow][row] = A[row][cow];
			}
		}
		return tmpA;
	}

	int findLengthOfLCIS_485(vector<int>& nums){
		int sz = nums.size();
		if(sz == 0 || sz == 1)
			return sz;
		vector<int> tmpLengths(sz, 1);
		for(int i=1; i<sz; i++){
			for(int j=i-1; j>=0; j++){
				if(nums[i] > nums[j]){
					tmpLengths[i] = tmpLengths[j]+1;
					break;
				}
			}
		}
		return tmpLengths[sz-1];
	}

	int minCostClimbingStairs_746_1(vector<int>& cost){
		int sz = cost.size();
		vector<int> tmpCost(sz, 0);
		for(int i=0; i<sz; i++){
			if(i <= 1){
				tmpCost[i] = cost[i];
			}
			else{
				tmpCost[i] = min(tmpCost[i-1], tmpCost[i-2]) + cost[i];
			}
		}
		return min(tmpCost[sz-1], tmpCost[sz-2]);
	}

	int minCostClimbingStairs_746_2(vector<int>& cost){
		int sz = cost.size();
		int min1[2] = {cost[0], cost[1]};
		for(int i=2; i<sz; i++){
			min1[ i%2 ] = min(min1[0], min1[1]) + cost[i];
		}
		return min(min1[0], min1[1]);
	}

	bool containsDuplicate(vector<int>& nums){
		set<int> iset();
		for(auto iter=nums.begin(); iter!=nums.end(); iter++){
			auto res = iset.insert(*iter);
			if(res.first)
				return true;
		}
		return false;
	}

	/*n^2*/
	int maxArea_11(vector<int>& height){
		int max = 0;
		for(int i=0; i<height.size(); i++){
			for(int j=i+1; j<height.size(); j++){
				int area = (j-i)*min(height[i], height[j]);
				max = area > max ? area : max;
			}
		}
		return max;
	}

	/* logn */
	int maxArea_11_2(vector<int>& height){
        int maxV = 0;
        int x = height.size()-1;
        int y = 0;
        while(x!=y){
        	if(height[x]>height[y]){
        		maxV = max(maxV, height[y]*(x-y));
        		y=y+1;
        	}else{
        		maxV = max(maxV, height[x]*(x-y));
        		x=x-1;
        	}
        }
        return maxV;
    }

    int findMin_153(vector<int>& nums){
		int left = 0, right = nums.size()-1;
		if(nums[left] > nums[right]){
			while(left < right){
				int m = left + int( (right-left)/2 );
				if(nums[left] < nums[m])
					left = m;
				else if(nums[right] > nums[m])
					right = m;
				else
					return min(nums[left], nums[right]);
			}
		}else{
			return nums[left];
		}
    }

	vector<int> searchRange_34(vector<int>& nums, int target){
		vector<int> result(2,-1);
		int left = 0, right = nums.size();
		while(left < right){	

		}	
	}

	int numSubarrayBoundedMax_795(vector<int>& A, int L, int R){
		int result = 0;
		for(int i=0; i<A.size(); i++){
			int tmpMax = 0;
			for(int j=i; j>=0; j--)
			{
				tmpMax = max(tmpMax, A[j]);
				if(tmpMax >= L && tmpMax <= R)
					result ++;
				else
					break;
			}
		}
		return result;
	}

	vector<int> findDuplicates_442_1(vector<int>& nums){
		vector<int>results;
		set<int> sets;
		for(int i=0; i<nums.size(); i++){
			auto res = sets.insert(nums[i]);
			if(res->)
		}
		return results;
	}

	// when find a number i, flip the number at position i-1 to negative. 
	// if the number at position i-1 is already negative, i is the number that occurs twice
	vector<int> findDuplicates_442(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i < nums.size(); ++i) {
			int index = abs(nums[i])-1;
			if (nums[index] < 0)
				res.push_back(index+1);
			nums[index] = -nums[index];
		}
		return res;
	}

	int arrayNesting(vector<int>& nums){

	}

	void rever(ListNode* head, ListNode* tail){
		ListNode* p1 = head;
		ListNode* p2 = p1->next;
		if(p2 == tail){
			p2->next = p1;
			return;
		}
		ListNode* p3 = p2->next;
		while(true){
			p2->next = p1;
			if(p2 == tail)
				break;
			p1 = p2;
			p2 = p3;
			p3 = p3->next;
		}
	}

	ListNode* reverseKGroup_25(ListNode* head, int k){
		if(head == NULL || k <= 1)
			return head;
		ListNode* newHead = new ListNode(0);
		newHead->next = head;
		ListNode* tmpHead = head;
		ListNode* beforeHead = newHead;
		while(true){
			ListNode* pHead=NULL, *pTail=NULL;
			for(int i=0; i<k; i++){
				if(i == 0)
					pHead = tmpHead;
				else if(i == k-1)
					pTail = tmpHead;
				tmpHead = tmpHead->next;
				if(tmpHead == NULL)
					break;
			}

			if(tmpHead == NULL)
				break;
			rever(pHead, pTail);
			beforeHead->next = pTail;
			pHead->next = tmpHead;
			beforeHead = pHead;
		}
		head = newHead->next;
		return head;
	}

	int majorityElement_169_1(vector<int>& nums){

	}

	int majorityElement_169_2(vector<int>& nums){
		int major=num[0], count = 1;
        for(int i=1; i<num.length;i++){
            if(count==0){
                count++;
                major=num[i];
            }else if(major==num[i]){
                count++;
            }else count--;
        }
        return major;
	}

	int majorityElement(vector<int>& nums) {
        return majority(nums, 0, nums.size() - 1);
    }

    int majority(vector<int>& nums, int left, int right) {
        if (left == right) return nums[left];
        int mid = left + ((right - left) >> 1);
        int lm = majority(nums, left, mid);
        int rm = majority(nums, mid + 1, right);
        if (lm == rm) return lm;
        return count(nums.begin() + left, nums.begin() + right + 1, lm) > count(nums.begin() + left, nums.begin() + right + 1, rm) ? lm : rm;
    }

	bool searchMatrix_240_1(vector<vector<int>>& matrix, int target){
		if(matrix.empty())
			return false;
		if(matrix[0].empty())
			return false;
		int row = 0, cow = matrix[0].size()-1;
		while( true ){
			int tmp = matrix[row][cow];
			if(tmp == target)
				return true;
			else if(tmp > target){
				row--;
				if(row < 0)
					break;
			}else{
				cow++;
				if(cow == matrix.size())
					break;
			}
		}
		return false;
	}

	bool searchMatrix_240(vector<vector<int>>& matrix, int target){
		//行左到右升,列上到下升
		for(int i=0; i<matrix.size(); i++){
			vector<int>& row = matrix[i];
			int left=0, right = row.size()-1;
			if( target ==  row[left] || target == row[right])
				return true;
			if(target < row[left] || target > row[right])
				continue;
			int index = bindSearch(row, target);
			if(index != -1)
				return true;
		}
		return false;
	}

	int bindSearch(vector<int>& nums, int target){
		int left = 0, right = nums.size()-1;
		while( left < right ){
			int m = left + (right-left)>>1;
			if( target == nums[m] ){
				return m;
			}else if(target > nums[m]){
				left = m+1;
			}else{
				right = m-1;
			}
		}
		return -1;
	}

	vector<int> diffWayToCompute_241_1(string input){

	}

	int removeDuplicates_xx(vector<int>& nums) {
		int target = 0;
		bool start = false;
		for(auto iter=nums.begin(); iter!=nums.end(); ){
			if(! start){
				target = *iter;
				iter++;
				start = true;
			}else if( target == *iter ){
				iter = nums.erase(iter);
			}else{
				target = *iter;
				iter++;
			}
		}
		return nums.size();
	}

	int singleNumber_xx_1(vector<int>& nums){
		int tmp = 0;
		for(int i=0; i<nums.size(); i++){
			tmp = tmp ^ nums[i];
		}
		return tmp;
	}

	vector<int> intersect_xx(vector<int>& nums1, vector<int>& nums2){
		map<int, int> counter;
		for(auto iter=nums1.begin(); iter!=nums1.end(); iter++){
			counter[*iter] = counter[*iter]+1;
		}
		vector<int> result;
		for(auto iter=nums2.begin(); iter!=nums2.end(); iter++){
			if(counter[*iter] > 0){
				result.push_back(*iter);
				counter[*iter]--;
			}
		}
		return result;
	}

	vector<int> plusOne_xx(vector<int>& digits){
		int right = digits.size()-1, plus=0;

		digits[right] = digits[right]+1;
		for(int i=right; i>=0; i--){
			digits[i] = digits[i]+plus;
			plus = digits[i]/10;
			digits[i] = digits[i]%10;
			if(plus == 0)
				break;
		}
		return digits;
	}

	void moveZeroes_xx(vector<int>& nums){
		int left=0, right=0;
		for(int i=0; i<nums.size(); ){
			if(nums[i] == 0 && left != -1){
				left = i;
				i++;
				continue;
			}
			if(nums[i] != 0 && left != -1){
				swap(nums[i], nums[left]);
				i = left;
				left = -1;
				continue;
			}
			i++;
		}
	}

	vector<int> twoSum_xx(vector<int>& nums, int target) {
		int arr[2]={-1};
		for(int i=0; i<nums.size(); i++){
			for(int j=i+1; j<nums.size(); j++){
				if(nums[i]+nums[j] == target){
					arr[0]=i, arr[1] = j;
					return vector<int>(arr, arr+2);
				}
			}
		}
		return vector<int>(arr, arr+2);
	}

	bool isValidSudoku_xx(vector<vector<char>>& board){
		int arr1[9]['9'+1]={{0}};
		int arr2[9]['9'+1]={{0}};
		int arr3[9]['9'+1]={{0}};
		for(int i=0; i<9; i++){
			for(int j=0; j<9; j++){
				int c = board[i][j];
				arr1[i][c]++;
				if( c != '.' && arr1[i][c] > 1 )
					return false;
				arr2[j][c]++;
				if( c !='.' && arr2[j][c] > 1 )
					return false;
				int index = int(j/3)*3 + ceil(i/3);
				arr3[index][c]++;
				if(c != '.' && arr3[index][c] > 1)
					return false;
			}
		}
		return true;
	}

	int NextPos(int i, int cnt, int step, int& row, int& cow, int k){
		switch(k){
			case 0:
				row = row+cnt;
				cow = step-1;
			case 1:
				cow = cow-cnt;
				row = step-1;
			case 2:
				row = row+cnt;
				cow = i;
			case 3:
				cow = cow + cnt;
				row = i;
		}
	}

	void rotate_xx(vector<vector<int>>& matrix){
		int n = matrix.size();
		int loop = floor(n/2);
		for(int i=0; i<loop; i++){
			int step = n - i;
			for(int j=i; j<step; j++){
				int cnt = j-i;
				int tmpRow = i, tmpCow = j;
				int tmp = matrix[tmpRow][tmpCow];
				for(int k=0; k<4; k++){
					NextPos(i, cnt, step, tmpRow, tmpCow, k);
					int tmp1 = matrix[tmpRow][tmpCow];
					matrix[tmpRow][tmpCow] = tmp;
					tmp = tmp1;
				}	
			}
		}
	}

	int maxProfit_xx(vector<int>& prices){
		int profit=0;
		for(int i=1; i < prices.size(); i++){
			if(prices[i] > prices[i-1]){
				profit += (prices[i]-prices[i-1]);
			}
		}
		return profit;
	}

	int maxProfit_xx_1(vector<int>& prices){
		int minVal = INT_MAX;
		int maxProfit = 0;
		for(int i=0; i<prices.size(); i++){
			maxProfit = max( prices[i]-minVal, maxProfit );
			minVal = min(minVal, prices[i]);
		}
		return maxProfit;
	}

	void rotate_xx_array_1(vector<int>& nums, int k){
		for(int i=0; i<k; i++){
			int v = nums.back();
			nums.pop_back();
			nums.insert(nums.begin(), v);
		}
	}

	string reverseString_xx(string s){
		int sz = s.size();
		for(int i=0, j=sz-1; i<j; i++,j--){
			char c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
		return s;
	}

	int revers_int_xx(int x){
		int result = 0;
		if(x ==0 )
			return 0;
		int sym = x > 0 ? 1 : -1;
		x = abs(x);
		while( x > 0){
			int i = x%10;
			x = x/10;
			if(result > (INT_MAX-i)/10 ){
				return 0;
			}
			result = result*10+i;
		}
		result *= sym;
		return result;
	}

	int firstUniqChar_xx_1(string s){
		int arr['z'+1] = {0};
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			arr[c]++;
		}
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			if(arr[c] == 1)
				return i;
		}
		return -1;
	}

	bool isAnagram_xx_1(string s, string t){
		if(s.size() == 0 || t.size() == 0 || (s.size() != t.size()) )
			return false;
		int diff[2] = {-1};
		int index = 0;
		for(int i=0; i<s.size(); i++){
			if(s[i] != t[i]){
				diff[index] = i;
				index++;
				if(index > 1)
					return false;
			}
		}
		if(s[diff[0]] == t[diff[1]] && s[diff[1]] == t[diff[0]])
			return true;
		return false;
	}

	bool isPalindrome_xx_1(string s){
		int sz = s.size();
		if(sz == 0)
			return false;
		for(int i=0, j=sz-1; i<j; j--,i++){
			if(s[i] != s[j])
				return false;
		}
		return true;
	}

	int mmm_atoi_xx_1(string str){
		int smy = str[0] == '-' ? -1 : 1;
		int result = 0;
		for(int i=0; i<str.size(); i++){
			if(str[i] == ' ')
				continue;
			if( str[i] != '-' && str[i] != '+' && !( str[i] >= '0' && str[i] <= '9' ) )
				return result*smy;
			int val = str[i] - '0';
			if(result > (MAX_INT-val)/10){
				return smy == -1 ? MIN_INT : MAX_INT;
			}
			result = result*10+val;
		}
		return result;
	}


	int xx_m_strstr_1(string s, string t){
		if(t.empty())
			return 0;
		for(int i=0; i<s.size(); i++){
			bool fitall = false;
			for(int j=0; j<t.size(); j++){
				if( (i+j) < s.size() && t[j] == s[i+j]){
					fitall = j==(t.size()-1) ? true : false;
					continue;
				}
				else
					break;
			}
			if(fitall)
				return i;
		}
		return -1;
	}

	// jjabababcdabababca
	//         abababca
	//char:  | a | b | a | b | a | b | c | a |
	//index: | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 
	//value: | 0 | 0 | 1 | 2 | 3 | 4 | 0 | 1 |
	//next 数组各值的含义：代表当前字符之前的字符串中，有多大长度的相同前缀后缀。例如如果next [j] = k，代表j 之前的字符串中有最大长度为k 的相同前缀后缀。
	vector<int> kmpProcess(string& needle) { //kmp next 
		int n = needle.length();
		vector<int> lps(n, 0);
		for (int i = 1, len = 0; i < n; ) {
			if (needle[i] == needle[len]) {
			    lps[i++] = ++len;
			} else if (len) {
			    len = lps[len - 1];
			} else {
				lps[i++] = 0;
			}
		}
		return lps;
	}

	int xx_kmpsearch_xx(string s, string p){
		int i = 0;
		int j = 0;
		int sLen = strlen(s);
		int pLen = strlen(p);
		while (i < sLen && j < pLen)
		{
			//①如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++    
			if (j == -1 || s[i] == p[j])
			{
				i++;
				j++;
			}
			else
			{
				//②如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]   
				j = next[j]; //当匹配失败时，模式串向右移动的位数为：失配字符所在位置 - 失配字符对应的next 值
			}
		}
		if (j == pLen)
			return i - j;
		else
			return -1;
	}

	string longestCommonPrefix_xx_1(vector<string>& strs){
		string common;
		int i = 0;
		while( true ){
			char c;
			bool same = true;
			for(int k=0; k<strs.size(); k++){
				if( i >= strs[k].size() ){
					same = false;
					break;
				}
				if(k == 0){
					c = strs[k][i];
					continue;
				}
				if( c != strs[k][i]){
					same = false;
					break;
				}
			}
			if( !same )
				break;
			else
				common.append(1, c);
			i++;
		}
		return common;
	}


	ListNode* removeNthfromEnd_xx_1(ListNode* node, int n){
		vector<ListNode*> nodes(n, NULL);
		ListNode* tmpNode = node;
		while(tmpNode != NULL){
			nodes.push_back(tmpNode);
			tmpNode = tmpNode->next;
		}
		if(nodes.size() < n)
			return node;
		auto node2Remove = nodes.end()-n;
		if( node2Remove == nodes.begin()){
			node = node->next;
		}else{
			auto beforeNode2Remove = node2Remove-1;
			(*beforeNode2Remove)->next = (*node2Remove)->next;
		}
		return node;
	}

	ListNode* reverseListNode_xx_1(ListNode* head){
		ListNode* newHead=NULL;
		reverse_help_xx_1(head, newHead);
		return newHead;
	}

	ListNode* reverse_help_xx_1(ListNode* node, ListNode*& newHead){
		if(node->next == NULL){
			newHead = node;
			return node;
		}
		ListNode* next = reverse_help_xx_1(node, newHead);
		next->next = node;
		return node;
	}

	ListNode* build_listnode_xx_1(vector<int>& nums){
		ListNode* head = new ListNode(0);
		ListNode* tmpHead = head;
		for(int i=0; i<nums.size(); i++){
			if(i == 0){
				head.val = nums[i];
			}else{
				ListNode* tmpNode = new ListNode(nums[i]);
				tmpHead->next = tmpNode;
				tmpHead = tmpHead->next;
			}
		}
		return head;
	}

	vector<int> build_huifenlist(int n){
		vector<int> nums;
		int m = n/2;
		for(int i=0; i<n; i++){
			int val = i%m;
			nums.push_back(val);
		}
		return nums;
	}

	ListNode* mergettwolist_xx_1(ListNode* l1, ListNode* l2){
		ListNode* head = NULL;
		ListNode* tmpHead = NULL;
		while(l1 != NULL && l2 != NULL){
			if( l1->val > l2->val ){
				if(head == NULL){
					head = l2;
					tmpHead = l2;
				}else{
					tmpHead->next = l2;
					tmpHead = tmpHead->next;
				}
				l2 = l2->next;
			}else{
				if(head == NULL){
					head = l1;
					tmpHead = l1;
				}else{
					tmpHead->next = l1;
					tmpHead = tmpHead->next;
				}
				l1 = l1->next;
			}
		}

		if(l1 != NULL){
			if(tmpHead != NULL){
				tmpHead->next = l1;
			}else{
				tmpHead = l1;
				head = tmpHead;
			}
		}

		if(l2 != NULL){
			if(tmpHead != NULL){
				tmpHead->next = l2;
			}else{
				tmpHead = l2;
				head = tmpHead;
			}
		}

		return head;
	}

	bool islistnodeishuifen_xx_1(ListNode* head){
		vector<int> nums;
		while(head != NULL){
			nums.push_back(head->val);
			head = head->next;
		}

		int sz = nums.size();
		if(sz == 0)
			return true;
		int left = 0, right = sz-1;
		while( left < right ){
			if( nums[left] != nums[right] )
				return false;
			left++;
			right--;
		}
		return true;
	}

	bool istwolisthascyc_xx_1(ListNode* head){
		ListNode* p1 = head, *p2 = head;
		for(int i=0; i<100000000; i++){
			for(int j=0; j<3; j++){
				if(p1 == NULL)
					return false;
				p1 = p1->next;
			}

			if(p2 == NULL || p1 == NULL){
				return false;
			}
			p2 = p2->next;
			if(p1 == p2)
				return true;
		}
		return false;
	}


	int maxdeeptree_xx_1(TNode* t){
		if(t == NULL)
			return 0;
		int md = maxdeeptree_xx_1_help(t);
		return md;
	}

	int maxdeeptree_xx_1_help(TNode* t){
		int left = 0, right =0;
		if( t->left != NULL )
			left = maxdeeptree_xx_1_help(t->left);
		if(t->right != NULL)
			right = maxdeeptree_xx_1_help(t->right);

		return max(left, right)+1;
	}

	bool isValidBST_xx_1(TNode* t, int rootVal){
		if(t == NULL)
			return true;
		int val = t->val;
		if(t->left && val <= t->left->val)
			return false;
		if(t->right && val >= t->right->val)
			return false;
		bool left = true, right = true;
		if( t->left )
			left = isnormaltree_xx_1(t->left);
		if(t->right)
			right = isnormaltree_xx_1(t->right);
		return left && right;
	}


	bool ismirtree_xx_1(TNode* t){
		vector<TNode*> tnodes(1, t);
		vector<TNode*> tmptnodes;
		while( !tnodes.empty() ){
			tmptnodes.clear();
			for(auto iter=tnodes.begin(); iter!=tnodes.end(); iter++){
				tmptnodes.push_back( *iter );
			}

			int left = 0, right = tmptnodes.size()-1;
			while(left < right){
				if(tmptnodes[left]->val != tmptnodes[right]->val)
					return false;
				left++;
				right--;
			}
			tmptnodes.clear();
			for(auto iter=tnodes.begin(); iter!=tnodes.end(); iter++){
				if( (*iter)->left == NULL && (*iter)->right == NULL)
					continue;

				if( (*iter)->left != NULL && (*iter)->right != NULL){
					tmptnodes.push_back( (*iter)->left );
					tmptnodes.push_back( (*iter)->right );
					continue;
				}
				return false;
			}

			tnodes = tmptnodes;
		}
		return true;
	}

	vector<vector<int>> leveltravel_xx_1(TNode* t){
		vector<TNode*> nodes(1, t);
		vector<vector<int>> results;
		while( !nodes.empty() ){
			vector<TNode*> tmpnodes;
			vector<int> levelResult;
			for(auto iter=nodes.begin(); iter!=nodes.end(); iter++){
				levelResult.push_back( (*iter)->val);

				if( (*iter)->left != NULL)
					tmpnodes.push_back( (*iter)->left);
				if( (*iter)->right != NULL)
					tmpnodes.push_back( (*iter)->right);
			}
			if(!levelResult.empty())
				results.push_back(levelResult);
			nodes = tmpnodes;
		}
		return results;
	}

	bool canJump_xx_1(vector<int>& nums){
		vector<vector<int> maps(nums.size(), vector<int>(nums.size(), -1));
		maps[0][0] = 1;
		for(int i=0; i<nums.size(); i++){
			int val = nums[i];
			for(int j=i; j<nums.size(); j++){
				if(maps[i][j] == -1)
					break;
				if(val >= j-i)
					maps[i][j] = 1;
			}
		}
		return maps[nums.size()-1][nums.size()-1] == 1
	}

	int ccpx(int i){
		int result = 1;
		for(int j=1; j<=i; j++)
			result *= j;
		return result;
	}

	int uniqPath_xx_1(int m, int n){
		int maxVal = max(m,n);
		maxVal ++;
		int minVal = min(m,n);
		return ccpx(maxVal)/(ccpx(min)*ccpx(maxVal-minVal)) ;
	}

	int uniqPath_xx_2(int m, int n){
		int[][] nums = new int[m][n];
        for (int i = 0 ;i < m;i++) {
            for (int j = 0; j < n; j++) {
                if(i == 0 || j == 0)
                    nums[i][j] = 1;
                else
                    nums[i][j] = nums[i - 1][j] + nums[i][j - 1];
            }
        }
        return nums[m - 1][n - 1];
	}

	int coinChange_xx_1(vector<int>& nums, int target){
		int arr[target] = {target}, arr[0] = 1;
		for(int i=0; i<target; i++){
			for(auto iter=nums.begin(); iter!=nums.end(); iter++){
					arr[i+(*iter)] = min(arr[i+(*iter)], arr[i]+1 );
			}
		}
		return arr[target] >= target ? -1 : arr[target];
	}

	int climbStairs(int n) {
		vector<int> arr(n+1, 0);
		arr[0]=0, arr[1]=1, arr[2]=2;
		for(int i=3; i<=n; i++)
			arr[i] = arr[i-1]+arr[i-2];
		return arr[n];
    }

    int maxsubarray_xx_1(vector<int>& nums) {
		int maxSun = INT_MIN;
		int tmpSun = 0;
		for(int i=0; i<nums.size(); i++){
			tmpSun += nums[i];
			maxSun = max(maxSun, tmpSun);
			if(tmpSun <= 0)
				tmpSun = 0;
		}
		return maxSun;
    }

    int rob_xx_1(vector<int> nums){
		int sz = nums.size();
		if(sz == 0)
			return 0;
		vector<int> vals(sz*2, 0);
		for(int i=0; i<sz; i++){
			vals[i*2] =  i == 0 ? 0 : max(vals[(i-1)*2], vals[(i-1)*2+1]);
			vals[i*2+1] = i == 0 ? nums[i] : nums[i]+vals[(i-1)*2];
		}
		return max(vals[(sz-1)*2], vals[(sz-1)*2+1]);
    }

	vector<vector<int>> threesum_xx_1(vector<int>& nums){
		vector<vector<int>> result;
		int sz = nums.size();
		if(sz < 3)
			return result;
		sort(nums.begin(), nums.end());
		for(int i=0; i<sz; ){
			if( (i+1) < sz && nums[i] == nums[i+1]){
				i++;
				continue;
			}
			int target = -nums[i];
			int left = i+1;
			int right = sz-1;
			while( left < right ){
				while( (left+1) < right && nums[left] == nums[left+1] ) left++;
				while( (right-1) > left && nums[right] == nums[right-1]) right--;
				if(left >= right)
					break;
				if(nums[left]+nums[right] == target){
					int arr[3] = {target*-1, nums[left], nums[right]};
					result.push_back(vector<int>(arr, arr+3));
					left++; right--;
				}else if(nums[left]+nums[right] < target){
					left++;
				}else
					right--;
			}
		}
		return result;
	}

	void setzeroes_xx_1(vector<vector<int>>& matrix){
		int row = matrix.size();
		if(row == 0)
			return;
		int cow = matrix[0].size();

		vector<int> rowNeed2SetZero(row, 0);
		vector<int> cowNeed2SetZero(cow, 0);
		for(int i=0; i<row; i++){
			for(int j=0; j<cow; j++){
				if( matrix[i][j] == 0 ){
					rowNeed2SetZero[i] = 1;
					cowNeed2SetZero[j] = 1;
				} 
			}
		}

		for(int i=0; i<row; i++){
			if( rowNeed2SetZero[i] == 1 ){
				for(int j=0; j<cow; j++)
					matrix[i][j] = 0;
			}
		}

		for(int j=0; j<cow; j++){
			if( cowNeed2SetZero[j] == 1 ){
				for(int i=0; i<row; i++)
					matrix[i][j] = 0;
			}
		}
	}

	int getgroupkey(string str){
		int key = 0;
		for(int i=0; i<str.size(); i++)
			key += str[i];
		return key;
	}

	vector<vector<string>> groupaabbcc_xx_1(vector<string>& strs){
		map<string, vector<string>> strmap;
		map<string, map<char, int>> strhash;
		for(int i=0; i<strs.size(); i++){
			string str = strs[i];

			map<char, int> tmpMap;
			for(int j=0; j<str.size(); j++){
				tmpMap[str[j]]++;
			}

			if( i == 0 ){
				vector<string> tmpvec(1, str);
				strmap.insert( std::pair<string, vector<string>>(str, tmpvec) );
				strhash.insert( std::pair<string, map<char,int>>(str, tmpMap) );
				continue;
			}

			bool tmpMatch = true;
			for(auto iter=strhash.begin(); iter!=strhash.end(); iter++){
				map<char, int>& tmpHash = iter->second;
				if(tmpHash.size() != tmpMap.size()){
					tmpMatch = false;
					continue;
				}

				tmpMatch = true;
				for(auto citer=tmpMap.begin(); citer!=tmpMap.end(); citer++){
					char c = citer->first;
					int cnt = citer->second;
					if( tmpHash[c] != cnt ){
						tmpMatch = false;
						break;
					}
				}

				if(tmpMatch){
					strmap[iter->first].push_back(str);
					break;
				}
			}
			if(!tmpMatch){
				vector<string> tmpvec(1, str);
				strmap.insert( std::pair<string, vector<string>>(str, tmpvec) );
				strhash.insert( std::pair<string, map<char,int>>(str, tmpMap) );
			}
		}
		vector<vector<string>> result;
		for(auto iter=strmap.begin(); iter!=strmap.end(); iter++){
			result.push_back( iter->second );
		}
		return result;
	}

	string noreplacesubstr_xx_1(string str){
		int maxLen = 0;
		int tmpLen = 0;
		map<char, int> charmap;
		for(int i=0; i<str.size(); ){
			char c = str[i];
			if(charmap[c] != 0){
				maxLen = max(maxLen, tmpLen);
				tmpLen = i - charmap[c]-1;
				i = charmap[c]+1;
				charmap.clear();
			}else{
				charmap[c] = i;
				tmpLen++;
				i++;
			}
		}
		maxLen = max(maxLen, tmpLen);
		return maxLen;
	}

	int getstrhashcode(string str){
		int arr1[26] = {101,123,456,1000,4567,908,79,3888,12222,5667,2342,8090,6789,6123,43,1,2999,8126,44444,88888,99999,1111,2222,3333,66,88};
		//int arr2[26] = {100000,4563,97878,8667,453434,9808,12,5683,1242,5684,235423,80190,656789,896,457,1989,12999,18126,144444,188888,199999,21111,12222,13333,166,188};
		int code = 0;
		code += str.size()*1000000;
		for(int i=0; i<str.size(); i++){
			code += arr1[str[i]-'a'];
			//code += arr2[str[i]-'a']
		}
		return code;
	}

	vector<vector<string>> groupstrhash_xx_1(vector<string>& strs){
		map<int, vector<string>> strmap;
		map<int, map<int, int>> hashmap; 
		for(int i=0; i<strs.size(); i++){
			strmap[getstrhashcode(strs[i])].push_back(strs[i]);
		}
		vector<vector<string>> result;
		for(auto iter=strmap.begin(); iter!=strmap.end(); iter++){
			result.push_back(iter->second);
		}
		return result;
	}

	int lengthoflongestsubstr_xx_1(string str){
		map<char, int> charmap;
		int tmplen = 0;
		int maxlen = 0;
		for(int i=0; i<str.size(); ){
			char c = str[i];
			int idx = charmap[c];
			if(idx == 0){
				tmpLen ++;
				maxLen = max(maxLen, tmpLen);
				charmap[str[i]] = i;
				i++;
			}else{
				tmpLen = 0;
				i = idx+1;
				charmap.clear();
			}
		}
		return maxLen;
	}

	string longgestpaling_xx_1(string str){
		int maxLen = 0, tmpLen = 1, sz = str.size();
		int m = sz/2;
		for(int i=m; i<sz; i++){
			int left = i-1, right = i+1;
			if( (sz-i)*2+1 <= maxLen )
				break;
			while( right < sz ){
				if(str[left] == str[right]){
					tmpLen += 2;
					left--;
					right++;
				}else
					break;
			}
			maxLen = max(maxLen, tmpLen);
			tmpLen = 1;
		}

		for(int i=m-1; i>0; i--){
			int left = i-1, right = i+1;
			if( (i-1)*2+1 <= maxLen)
				break;
			while( left >=0 ){
				if( str[left] == str[right] ){
					tmpLen+=2;
					left--;
					right++;
				}else
					break;
			}
			maxLen = max(maxLen, tmpLen);
			tmpLen = 1;
		}
		return maxLen;
	}


	bool increasingTriplet_xx_1(vector<int>& nums){
		int m1=INT_MAX, m2=INT_MAX;
		for(int i=0; i<nums.size(); i++){
			if(m1 > nums[i])
				m1 = nums[i];
			else{
				if(m2>nums[i])
					m2=nums[i];
				else
					return true;
			}
		}
		return false;
	}

	ListNode* addtxwonumber_xx_1(ListNode* l1, ListNode* l2){
		ListNode* tail = new ListNode(0);
		vector<ListNode*> vl1;
		vector<ListNode*> vl2;

		while( l1 != NULL ){
			vl1.push_back(l1);
			l1 = l1->next;
		}
		while( l2 != NULL ){
			vl2.push_back(l2);
			l2 = l2->next;
		}

		int up = 0;
		int sz1 = vl1.size()-1;
		int sz2 = vl2.size()-1;
		while( sz1 >= 0 && sz2 >= 0 ){
			int val = vl1[sz1]->val + vl2[sz2]->val+up;
			up = int(val/10);
			val = val % 10;
			tail->val = val;
			ListNode* tmp = new ListNode(0);
			tmp->next = tail;
			tail = tmp;
			sz1 --;
			sz2 --;
		}

		while( sz1 >= 0 ){
			int val = vl1[sz1]->val + up;
			up = int(val/10);
			val = val % 10;
			tail->val = val;
			ListNode* tmp = new ListNode(0);
			tmp->next = tail;
			tail = tmp;
			sz1--;
		}

		while( sz2 >= 0 ){
			int val = vl2[sz2]->val + up;
			up = int(val/10);
			val = val % 10;
			tail->val = val;
			ListNode* tmp = new ListNode(0);
			tmp->next = tail;
			tail = tmp;
			sz2--;
		}
		if(tail->val ==0)
			tail = tail->next;
		if(up > 0){
			ListNode* tmp = new ListNode(up);
			tmp->next = tail;
			tail = tmp;
		}
		return tail;
	}

	ListNode* oddEventList_xx_1(ListNode* list){
		vector<ListNode*> l1;
		vector<ListNode*> l2;

		ListNode* tmp = list;
		while( tmp){
			l1.push_back(tmp);
			tmp = tmp->next;
			if( tmp )
				tmp = tmp->next;
			else
				break;
		}
		tmp = list->next;
		if(tmp == NULL)
			return list;
		while(tmp){
			l2.push_back(tmp);
			tmp = tmp->next;
			if(tmp)
				tmp = tmp->next;
			else
				break;
		}

		for(auto ptr=l1.begin(); ptr!=l1.end(); ptr++){
			(*ptr)->next = NULL;
		}

		for(auto ptr=l2.begin(); ptr!=l2.end(); ptr++){
			(*ptr)->next = NULL;
		}


		for(int i=1; i<l1.size(); i++){
			l1[i-1]->next = l1[i];
		}

		for(int i=1; i<l2.size(); i++){
			l2[i-1]->next = l2[i];
		}
		l1[l1.size()-1]->next = l2[0];
		return list;
	}

	ListNode* sameptr_xx_1(ListNode* l1, ListNode* l2){
		int len1 = 0, len2 = 0;
		ListNode* tmp1 = l1, *tmp2 = l2;
		while( tmp1 ){
			len1 ++;
			tmp1 = tmp1->next;
		}

		while( tmp2 ){
			len2 ++;
			tmp2 = tmp2->next;
		}

		if(len1 > len2)
			len1 = len1-len2;
		else if (len2 > len1)
			len2 = len2-len1;
		else{
			len2=0, len1=0;
		}


		tmp1=l1, tmp2=l2;
		while( len1 > 0 ){
			tmp1=tmp1->next;
			len1--;
		}
		while(len2>0){
			tmp2 = tmp2->next;
			len2--;
		}

		while( tmp1 && tmp2 ){
			if(tmp1 == tmp2)
				return tmp1;
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		return NULL;
	}

	vector<int> inordertraveral_xx_tree_1(TNode* t){
		vector<int> result;
		if(t == NULL)
			return result;
		inordertraveral_help(nums, t);
		return result;
	}

	void inordertraveral_help(vector<int>& nums, TNode* t){
		nums.push_back( t->val );
		if( t->left )
			inordertraveral_help(nums, t->left);
		if( t->right )
			inordertraveral_help(nums, t->right);
	}

	vector<int> zordertraval_tree_1(TNode* t){
		vector<int> result;
		vector<TNode*> level1(1,t);
		vector<TNode*> level2;
		int dir = 1;

		while(true){
			if( dir  == 1){
				level2.clear();
				for(auto iter=level1.begin(); iter!=level1.end(); iter++){
					result.push_back( (*iter)->val );
					if( (*iter)->left )
						level2.push_back( (*iter)->left);

					if( (*iter)->right )
						level2.push_back( (*iter)->right );
				}
				if(level2.empty())
					break;
				dir = 2;
			}else{
				level1.clear();
				for(int j=level2.size()-1; j>=0; j--){
					TNode* ptr = level2[j];
					result.push_back( ptr->val );
					if( ptr->right )
						level1.push_back(ptr->right);
					if(ptr->left)
						level1.push_back(ptr->left);
				}
				if(level1.empty())
					break;
				dir = 1;
			}
		}
	}

	vector<string> matchpatter_xx_1(vector<string> strs, string patter){
		vector<string> result;
		int pattersz = patter.size();
		for(int i=0; i<strs.size(); i++){
			string tmpstr = strs[i];
			map<char, char> charmap1;
			map<char, char> charmap2;
			if(tmpstr.size() != pattersz)
				continue;

			bool match = true;
			for(int j=0; j<patter.size(); j++){
				char c1 = tmpstr[j];
				char c2 = patter[j];
				if( charmap1.find(c1) == charmap1.end() && charmap2.find(c2) == charmap2.end() ){
					charmap1[c1] = c2;
					charmap2[c2] = c1;
				}else if(charmap1.find(c1) != charmap1.end() && charmap2.find(c2) != charmap2.end()){
					if(charmap1[c1] != c2 || c1 != charmap2[c2]){
						match = false;
						break;
					}
				}else{
					match = false;
					break;
				}
			}
			if(match)
				result.push_back(tmpstr);
		}
		return result;
	}

	vector<int> exchangecandi_xx_1(vector<int>& nums1, vector<int>& nums2){
		int total = 0, sum1=0, sum2=0;
		for(auto iter=nums1.begin(); iter!=nums1.end(); iter++){
			total += (*iter);
			sum1 += (*iter);
		}

		for(auto iter=nums2.begin(); iter!=nums2.end(); iter++ ){
			total += (*iter);
			sum2 += (*iter);
		}

		vector<int> result(2,0);
		if(sum1 == sum2)
			return result;

		int avg = total/2;
		int targe1 = sum1-avg, target2 = sum2-avg;
		for(int i=0; i<nums1.size(); i++){
			for(int j=0; j<nums2.size(); j++){
				if( nums1[i]-nums2[j] == targe1 ){
					result[0] = nums1[i], result[1] = nums2[j];
					break;
				}
			}
		}
		return result;
	}


	void treeinserthelp(TNode* t, int v){			
		if(t->val > v){
			if(t->left == NULL)
				t->left = new TNode(v);
			else
				treeinserthelp(t->left, v);
		}else{
			if(t->right == NULL)
				t->right = new TNode(v);
			else
				treeinserthelp(t->right, v);
		}
	}

	TNode* buildBindTree(vector<int>& nums){
		TNode* root = NULL;
		for(int i=0; i<nums.size(); i++){
			if(root == NULL){
				root = new TNode(nums[i]);
				continue;
			}
			treeinserthelp(root, nums[i]);
		}
		return root;
	}

	void kthsmallitem_help(vector<int>& nums, TNode* t){
		if(nums.size() >= 3)
			return;

		if(t->left)
			kthsmallitem_help(nums, t->left);
		
		nums.push_back(t->val);

		if(t->right)
			kthsmallitem_help(nums, t->right);

	}

	int kthsmallitem_tree_x_1(TNode* t){
		vector<int> nums;
		kthsmallitem_help(nums, t);
		return nums[2];
	}

	int numIslands_xx_1(vector<vector<char>>& grid){
		struct Point{
			int x;
			int y;
			Point(int x_, int y_):x(x_),y(y_){}
			Point(Point& rhs){ x=rhs.x; y=rhs.y; }
		};

		int row = grid.size();
		if(row == 0)
			return 0;
		int cow = grid[0].size();
		if(cow == 0)
			return 0;

		vector<Point> lrud(4, Point(0,0));
		lrud[0].x = 0, lrud[0].y=-1, lrud[1].x=0, lrud[1].y=1;
		lrud[2].x = -1, lrud[2].y=0, lrud[3].x=1, lrud[3].y=0;

		int landino = 2;
		for(int i=0; i<row; i++){
			for(int j=0; j<cow; j++){
				if(grid[i][j] == 1){
					stack<Point> tack;
					tack.push(Point(i,j));
					while(!tack.empty()){
						Point p = tack.top();
						tack.pop();
						grid[p.x][p.y] = landino;
						for(auto dir=lrud.begin(); dir!=lrud.end(); dir++){
							int tmpx = p.x+(*dir).x , tmpy = p.y+(*dir).y;
							if( tmpx >=0 && tmpx < row && tmpy >= 0 && tmpy < cow ){
								if(grid[tmpx][tmpy] == 1){
									tack.push( Point(tmpx, tmpy) );
								}
							}
						}
					}
					landino++;
				}
			}
		}
		 return landino-2;
	}

	vector<int> exchangecandi_xx_2(vector<int>& nums1, vector<int>& nums2){
		int sum1=0, sum2=0;
		for(auto iter=nums1.begin(); iter!=nums1.end(); iter++){
			sum1 += (*iter);
		}

		for(auto iter=nums2.begin(); iter!=nums2.end(); iter++ ){
			sum2 += (*iter);
		}

		vector<int> result(2,0);
		if(sum1 == sum2)
			return result;

		int target = (sum1-sum2)/2;

		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		if(target > 0){
			int maxIdx=nums1.size()-1, minIdx=0;
			while( maxIdx >= 0 && minIdx < nums2.size() ){
				int diff = nums1[maxIdx]-nums2[minIdx];
				if(diff == target){
					result[0]=nums1[maxIdx], result[1]=nums2[minIdx];
					break;
				}else if(diff > target){
					maxIdx--;
				}else{
					minIdx++;
				}
			}
		}else{
			target *= -1;
			int maxIdx=nums2.size()-1, minIdx=0;
			while( maxIdx >= 0 && minIdx < nums1.size() ){
				int diff = nums2[maxIdx]- nums1[minIdx];
				if( diff == target ){
					result[0]=nums1[minIdx], result[1]=nums2[maxIdx];
					break;
				}else if( diff > target ){
					maxIdx--;
				}else{
					minIdx++;
				}
			}
		}

		return result;
	}

	int dificmaxproduce_xx_1(vector<int>& nums){
		int tmpVal=1, maxVal = INT_MIN;
		for(int i=0; i<nums.size(); i++){
			tmpVal *= nums[i];
			maxVal = max(maxVal, tmpVal);
			if(tmpVal == 0)
				tmpVal = 1;
		}
		return maxVal;
	}



	int bestwaytobuyandsale_xx_1(vector<int>& nums){
		int minPrice = INT_MAX, maxPrice = INT_MIN, lastDay = -2, maxProfit=0;
		bool buyFlat = false;
		for(int i=0; i<nums.size(); i++){
			if( (i-lastDay) > 1 && minPrice > nums[i] ){
				minPrice = nums[i];
				maxPrice = INT_MIN;
				buyFlat = true;
				continue;
			}
			if( buyFlat && (nums[i] > maxPrice || i == nums.size()-1)  ){
				maxPrice = nums[i];
				lastDay = i;
			}else if(maxPrice > minPrice){
				maxProfit += (maxPrice-minPrice);
				minPrice = INT_MAX, maxPrice = INT_MIN;
				buyFlat = false;
			}
		}
		return maxProfit;
	}

	int minspit(int n, bool& m){
		for(int i=1; i<=n; i++){
			int val = i*i;
			if( val == n ){
				m = true;
				return i;
			}
			else if(val > n){
				m = false;
				return i-1;
			}
		}
	}

	int mincountsum_x(int n){
		bool m = false;
		map<int, int> mincount;
		for(int i=1; i<=n; i++){
			int minspit = minspit(i, m);
			if( m )
				mincount[i] = 1;
			else
				mincount[i] = 0;
		}
		return mincount[n];
	}

	bool isscstrtree(string s, string p){ //字符转换
		int sz = s.size();
		if(sz != p.size())
			return false;
		if(sz == 0)
			return true;
		if(sz == 1)
			return s[0] == p[0];
		if(sz == 2)
			return (s[0]==p[0] && s[1]==p[1]) || (s[0]==p[1] && s[1]==p[0]);
		if(s == p)
			return true;
		for(int i=0;i<sz-1; i++){
			bool res1 = isscstrtree( s.substr(0, i+1), p.substr(0, i+1) ) && isscstrtree( s.substr(i+1, sz-i-1), p.substr( i+1, sz-i-1 ) );
			bool res2 = isscstrtree( s.substr(0, i+1), p.substr(sz-1-i, i+1)) && isscstrtree( s.substr(i+1, sz-i-1), p.substr(0, sz-i-1) );
			if( res1 || res2  )
				return true;
		}
		return false;
	}

	vector<TNode*> generateTreesHelp(int start, int end){
		vector<TNode*> trees;
		if( start > end ){
			trees.push_back(NULL);
			return trees;
		}
		for(int i=start; i<=end; i++){
			vector<TNode*> left = generateTreesHelp(start, i-1);
			vector<TNode*> right = generateTreesHelp(i+1, end);
			for(auto lIter : left){
				for(auto rIter : right ){
					TNode* root = new TNode(i);
					root->left = lIter; //auto aiter 与 vector<TNode*>::iterator iter 的区别 aiter == *iter
					root->right = rIter;
					trees.push_back(root);
				}
			}
		}
		return trees;
	}

	vector<TNode*> generateTrees(int n) { //不同的二叉查找树
		return generateTreesHelp(1, n);
	}

	//动态规划：dp(i,j)表示S前i个字符串中T的前j个字符串出现的次数，那么 
	//如果S[i]!=T[j]，则dp(i,j)=dp(i-1,j) 
	//否则dp(i,j)=dp(i-1,j)+dp(i-1,j-1)
	
	int numDistinct(string s, string t) {
		int sSize = s.size(), tSize = t.size();
		vector< vector<int> > dp(sSize, vector<int>(tSize, 0));
		for(int i=0; i<sSize; i++){
			for(int j=0; j<tSize; j++){
				if(i>0)
					dp[i][j] = dp[i-1][j];
				if( s[i] == t[j] ){
					if(i>0 && j>0)
						dp[i][j] += dp[i-1][j-1];
					else if(j == 0)
						dp[i][j] += 1;
				}
			}
		}
		return dp[sSize-1][tSize-1];
	}


	/*这种方法是以一个字符为中心，向两边扩展，如果是回文串就更新最小分割次数，
	但是回文串可能是偶数个，也可能是奇数个。所以需要考虑以当前字符为中心，
	或者以当前字符以及当前字符下一个字符共同为中心，进行两边扩展。如果为回文串，
	则更新最小分割数 代码如下
	*/
    int minCut(string s) {
        if(s.size()==0) 
        	return 0;
        int len=s.size();
        vector<int> nums(len+1,0);
        for(int i=0;i<=len;i++) 
        	nums[i]=i-1;
        for(int i=1; i<=len; i++){
            for(int j=0; j<i && i+j<=len && s[i-j-1]==s[i+j-1]; j++){
                nums[i+j]=min(nums[i+j], nums[i-j-1]+1);
            }
            for(int j=0; i-j>0 && i+j+1<=len && s[i-1]==s[i] && s[i-j-1]==s[i+j]; j++){
                nums[i+j+1]=min(nums[i+j+1], nums[i-j-1]+1);
            }
        }
        return nums[len];
    }

	vector<string> splitstr140Help(vector<string>& dict, string s, int cidx, int sidx, vectot<string>& results){
		vector<string> reuslts;
		for(int i=idx; i<dict.size(); i++){
			string& tmpStr = dict[i];
			int tmpSize = tmpStr.size();
			if(s.substr(0, tmpSize) == tmpStr){
				if(s.size() == tmpSize){
					results.push_back(s);
				}else{
					splitstr140Help(dict, s.substr(tmpSize-1, s.size()-tmpSize), 0);
					splitstr140Help(dict, s, i);
				}
			}
		}
	}

	vector<string> splitstr140(vector<string>& dict, string s){
		vector<string> results;
		splitstr140Help(dict, s, 0, 0, results);
		return results;
	}

	/*
	最大面积
		maxArea = max(dp[i][j-1],dp[i-1][j],dp[i][j], dp[i][j]+dp[i][j-1], dp[i][j]+dp[i-1][j])
	 */
	








	int combnumoftarget377(vector<int>& nums, int target){
		sort(nums.begin(), nums.end());
		vector<int> dp(target+1, 0);
		dp[0] = 1;
		for(int i=1; i<=target; i++){
			for( auto iter : nums ){
				if( i>=iter ){
					dp[i] += dp[i-iter];
				}
			}	
		}
		return dp[target];
	}

	int combnumoftarget377x(vector<int>& nums, int target){
		vector<int> dp(target+1, 0);
		dp[0] = 1;
		map<int,int> tmpMap;
		stack<int> sta;
		sta.push(0);
		while( !sta.empty() ){
			int tmpNum = sta.top();
			sta.pop();
			tmpMap[tmpNum] = 0;
			for(auto iter : nums){
				if(tmpNum+iter <= target){
					dp[tmpNum+iter] += dp[tmpNum];
					if(tmpNum+iter < target){
						int res = tmpMap[tmpNum+iter];
						if(res == 0){
							sta.push(tmpNum+iter);
							tmpMap[tmpNum+iter] = 1;
						}
					}
				}
			}
		}
		return dp[target];
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

	bool issubstring392x(string s, string t){
		int sIdx=0, tIdx=0, sSize=s.size(), tSize=t.size();
		while(sIdx < sSize && tIdx < tSize){
			if(s[sIdx] == t[tIdx])
				sIdx++;
			tIdx++;
		}
		return sIdx == sSize;
	}

	int splitarray410(vector<int>& nums, int m){
		int maxNum=0, sum=0;
		for(auto iter : nums){
			maxNum = max(maxNum, iter);
			sum += iter;
		}
		int res = bindSearch410(nums, m, maxNum, sum);
		return res;
	}

	long bindSearch410(vector<int>& nums, int m, long low, long height){
		int res = height;
		while( height > low ){
			long mid = (low+height)/2;
			if(isvalid410(nums, m, mid)){
				low = mid;
				res = mid;
			}
			else
				low = mid;
		}
		return res;
	}

	bool isvalid410(vector<int>& nums, int m, int val){
		int count=0, tmpSum=0;
		for( int i=0; i<nums.size(); i++ ){
			tmpSum += nums[i];
			if(tmpSum >= val){
				tmpSum = 0;
				count ++;
				if(count >= m && i < nums.size()-1)
					return false;
			}
		}
		return true;
	}

	//dp[i][j] = Math.max(1 + dp[i-count[0]][j-count[1]], dp[i][j]);
	int findmaxform474(vector<string>& strs, int m, int n){
		vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
		for(auto str : strs){
			map<char,int> counts = countchar(str);
			for(int i=m; i>=counts['1']; i--){
				for(int j=n; j>=counts['0']; j--){
					dp[i][j] = max( dp[i][j], 1+dp[i-counts['1']][j-counts[j-counts['0']]] );
				}
			}
		}
		return dp[m][n];
	}

	map<char,int> countchar(string& str){
		map<char, int> counts;
		for(int i=0; i<str.size(); i++){
			counts[str[i]]++;
		}
		return counts;
	}

	bool checksubarray523(vector<int>& nums, int k){
		map<int, bool> sumMap;
		for(auto num : nums){
			if(num % k == 0)
				return true;
			map<int, bool> tmpMap = sumMap;
			for(auto tmp : tmpMap){
				sumMap[tmp->first+num] = true;
				if( (tmp->first+num) % k == 0)
					return true;
			}
			sumMap[num] = true;
		}
		return false;
	}

	bool predictionwinerHelp486(vector<int>& nums, int sum1, int sum2,int left, int right, bool who){
		if(right < left)
			return sum1>sum2;
		if(who){
			bool left = predictionwinerHelp486(nums, sum1+nums[left], sum2, left+1, right, !who);
			bool right = predictionwinerHelp486(nums, sum1+nums[right], sum2, right-1, !who);
			return left || right;
		}else{
			bool left = predictionwinerHelp486(nums, sum1, sum2+nums[left], left+1, right, !who);
			bool right = predictionwinerHelp486(nums, sum1, sum2+nums[right], right-1, !who);
			return left||right;
		}
	}
	bool predictionwiner486(vector<int>& nums){
		return predictionwinerHelp486(nums, 0, 0, 0, nums.size()-1, true);
	}
};
 