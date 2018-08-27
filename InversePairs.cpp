class Solution {
public:
    int InversePairs(vector<int> data) {
        int n = data.size();
        return process(data, 0, n-1);
    }
    
    int process(vector<int>& data,int start,int end)
    {
        //�ݹ���ֹ����
        if(start >= end)
        {
            return 0;
        }
        
        // �鲢���򣬲����㱾���������
	    vector<int> copy(data); // ���鸱�������ڹ鲢����
        int mid=(start+end)>>1;
        int left=process(data, start, mid);
        int right=process(data, mid+1, end);
        
        int p=mid;//p��ʼ��Ϊǰ������һ�����ֵ��±�
        int q=end;//q��ʼ��Ϊ�������һ�����ֵ��±�
        int index=end;//����������±��ʼ��Ϊ���һλ
        int count=0;//��¼����Եĸ���
        
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
			data[i] = copy[i];//���¹鲢������������
	    }
 
        return (left+right+count);
    }
};