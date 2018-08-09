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
		int maxCnt = 0;
		int cnt = 0;
		for(int i=0; i<nums.size(); i++){
			if(nums[i] == 1)
				cnt++;
			else{
				if(cnt > maxCnt)
					maxCnt = cnt;
				cnt=0;
			}
		}
		if(cnt > maxCnt)
			maxCnt = cnt;
		return maxCnt;
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

	int xx_kmpsearch_xx(string s, string t){
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
				//next[j]即为j所对应的next值      
				j = next[j];
			}
		}
		if (j == pLen)
			return i - j;
		else
			return -1;
	}

	string countAndSay_xx(int n){

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


	void removeNthfromEnd_xx_1(ListNode* node, int n){
		vector<ListNode*> nodes(n, NULL);
		ListNode* tmpNode = node;
		while(tmpNode != NULL){
			nodes.push_back(tmpNode);
			tmpNode = tmpNode->next;
		}
		if(nodes.size() < n)
			return;
		auto node2Remove = nodes.end()-n;
		if( node2Remove == nodes.begin()){
			node = node->next;
		}else{
			auto beforeNode2Remove = node2Remove-1;
			(*beforeNode2Remove)->next = (*node2Remove)->next;
		}
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

		if(l1 != NULL)
			tmpHead->next = l1;
		else if(l2 != NULL)
			tmpHead->next = l2;
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
		}
		return true;
	}

	bool istwolisthascyc_xx_1(ListNode* head1, ListNode* head2){
		ListNode* p1 = head1, *p2 = head2;
		for(int i=0; i<100000000; i++){
			for(int j=0; j<3; j++){
				p1 = p1->next;
				if(p1 == NULL)
					return false;
			}

			p2 = p2->next;
			if(p2 == NULL){
				return false;
			}
			if(p1 == p2)
				return true;
		}
		return false;
	}


	int maxdeeptree_xx_1(TNode* t){
		if(t == NULL)
			return 0;
		int md = maxdeeptree_xx_1_help(t)-1;
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

	bool isnormaltree_xx_1(TNode* t){
		int val = t->val;
		if(t->left && t->right){
			if( val < t->left->val || val > t->right->val )
				return false;
		}
		bool left = true, right = true;
		if( t->left )
			left = isnormaltree_xx_1(t->left);
		if(t->right)
			right = isnormaltree_xx_1(t->right);
		return left && right;
	}
}