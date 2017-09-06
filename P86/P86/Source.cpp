#include <iostream>
#include <string>
#include <vector>

using namespace std;

//��������
//���⣺����һ���������һ��x����������С��x�ķŵ�ǰ�棬���ڵ���x�ķŵ����棬ÿ����Ԫ�ص�ԭʼ���λ�ò��䡣
//
//˼·����ʵ�ܼ򵥣�����һ��������С��x�Ķ��ҵ�head1�󣬰Ѵ��ڵ���x�Ķ��ŵ�head2������ٰѴ��ڵ��ڵ�����ҵ�С������ĺ���Ϳ����ˡ�
//
//����ⲻ�ѣ���Ҫ�Ǹ�����Ϥָ���ͬѧѧϰ������

//26.83%

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
		ListNode* head1 = nullptr;
		ListNode* head2 = nullptr;
		ListNode* rtValue = nullptr;

		ListNode* ptr = head;
		while (ptr != nullptr)
		{
			if (ptr->val < x)
			{
				if (head1 == nullptr)
				{
					head1 = new ListNode(ptr->val);
				}
				else
				{
					ListNode* node = new ListNode(ptr->val);
					ListNode* link = head1;
					while (link->next != nullptr)
						link = link->next;
					link->next = node;
				}
			}
			else
			{
				if (head2 == nullptr)
				{
					head2 = new ListNode(ptr->val);
				}
				else
				{
					ListNode* node = new ListNode(ptr->val);
					ListNode* link = head2;
					while (link->next != nullptr)
						link = link->next;
					link->next = node;
				}
			}

			ptr = ptr->next;
		}

		ListNode *link = head;
		while (link != nullptr)
		{
			ListNode* tmp = link;
			link = link->next;

			delete tmp;
		}

		ListNode *linkage = head1;
		while (linkage && linkage->next != nullptr)
		{
			linkage = linkage->next;
		}
		if (linkage == nullptr)
			rtValue = head2;
		else
		{
			linkage->next = head2;
			rtValue = head1;
		}

		return rtValue;
	}
};