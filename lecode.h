#include <vector>
#include <map>

using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
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

	vector<int> findDuplicates_442(vector<int>& nums){
		int tmp = nums.size();

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
}
