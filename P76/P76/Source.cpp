#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

//30.29%

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> srcHash;
        // ��¼Ŀ���ַ���ÿ����ĸ���ִ���
        for (auto e: t)
            srcHash[e]++;
            
        int start = 0,i= 0;
        // ���ڼ�¼������ÿ����ĸ���ִ��� 
        unordered_map<char, int> destHash;
        int found = 0;
        int begin = -1, end = s.size(), minLength = s.size();
        for(start = i = 0; i < s.size(); i++){
            // ÿ��һ���ַ������ĳ��ִ�����1
            destHash[s.at(i)]++;
            // �����1������ַ�������������Ŀ�괮�и��ַ������������ҵ���һ��ƥ���ַ�
            if(destHash[s[i]] <= srcHash[s[i]]) found++;
            // ����ҵ���ƥ���ַ�������Ŀ�괮���ȣ�˵���ҵ���һ������Ҫ����Ӵ�    
            if(found == t.size()){
                // ����ͷû�õĶ�������û����ָ���ַ����ִ���������Ŀ�괮�г��ֵĴ������������ǳ��ִ�������1
                while(start < i && destHash[s[start]] > srcHash[s[start]]){
                    destHash[s[start]]--;
                    start++;
                }
                // ��ʱ��startָ����Ӵ���ͷ����ĸ���жϸ��Ӵ�����
                if(i - start < minLength){
                    minLength = i - start;
                    begin = start;
                    end = i;
                }
                // �ѿ�ͷ�����ƥ���ַ�����������ƥ���ַ�����1
                destHash[s[start]]--;
                found--;
                // �Ӵ���ʼλ�ü�1�����ǿ�ʼ����һ���Ӵ���
                start++;
            }
        }
        // ���beginû���޸Ĺ������ؿ�
        return begin == -1 ? "" : s.substr(begin,end - begin + 1);
    }
};


int main()
{
	Solution s;
	cout << s.minWindow("a", "b") << endl;
	return 0;
}