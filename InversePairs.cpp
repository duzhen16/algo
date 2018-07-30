class Solution {
public:
    int InversePairs(vector<int> data) {
        int n = data.size();
        return process(data, 0, n-1);
    }
    
    int process(vector<int>& data,int start,int end)
    {
        //递归终止条件
        if(start >= end)
        {
            return 0;
        }
        
        // 归并排序，并计算本次逆序对数
	    vector<int> copy(data); // 数组副本，用于归并排序
        int mid=(start+end)>>1;
        int left=process(data, start, mid);
        int right=process(data, mid+1, end);
        
        int p=mid;//p初始化为前半段最后一个数字的下标
        int q=end;//q初始化为后半段最后一个数字的下标
        int index=end;//辅助数组的下标初始化为最后一位
        int count=0;//记录逆序对的个数
        
        while(p>=start && q>=mid+1)
        {
            if(data[p]>data[q])
            {
                copy[index--]=data[p--];
                count+=q-mid;
            }
            else
            {
                copy[index--]=data[q--];
            }
        }
        
        while(p>=start)   copy[index--]=data[p--];
        while(q>=mid+1)   copy[index--]=data[q--];
        	
        for (int i = start; i <= end; i++)
        {
			data[i] = copy[i];//更新归并排序后的子数组
	    }
 
        return (left+right+count);
    }
};


