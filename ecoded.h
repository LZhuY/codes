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
		stack<char> sta;
		vector<int> idx(s.size(), 0);
		int maxLen=0, tmpLen=0;
		for(int i=0; i<s.size(); i++){
			char c = s[i];
			if( c == '(')
				sta.push(c);
			else if( c == ')' && sta.empty() ){
			}else{
				char lc = sta.top();
				sta.pop();
				if( lc == '('){
					idx[i] = 1;
				}
			}
		}
		for(int i=0; i<idx.size(); i++){
			if(idx[i] == 1){
				tmpLen++;
				maxLen = max(maxLen,tmpLen*2);
			}else
				tmpLen=0;
		}
		return maxLen;
	}
};
