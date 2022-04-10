// Source : https://oj.leetcode.com/problems/add-two-numbers/
// Author : Hao Chen
// Date   : 2014-06-18

/**********************************************************************************
 *
 * You are given two linked lists representing two non-negative numbers.
 * The digits are stored in reverse order and each of their nodes contain a
 *single digit. Add the two numbers and return it as a linked list.
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 *
 **********************************************************************************/

/**
 * Definition for singly-linked list.
 * */
#include "base.h"
using namespace base;
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode(int x) : val(x), next(NULL) {}
// };
//
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        ListNode* head=new ListNode(-1);//存放结果的链表
        ListNode* h=head;//移动指针
        int sum=0;//每个位的加和结果
        bool carry=false;//进位标志
        while(l1!=NULL||l2!=NULL)
        {
            sum=0;
            if(l1!=NULL)
            {
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=NULL)
            {
                sum+=l2->val;
                l2=l2->next;
            }
            if(carry)
                sum++;
            h->next=new ListNode(sum%10);
            h=h->next;
            carry=sum>=10?true:false;
        }
        if(carry)
        {
            h->next=new ListNode(1);
        }
        printNode(head->next);
        return head->next;
    
    }

private:
    int getValueAndMoveNext(ListNode *&l) {
        int x = 0;
        if (l != NULL) {
            x = l->val;
            l = l->next;
        }
        return x;
    }
};


//bool printNode(Node *result) {
//    Node *p = result;
//    stack<int> s;
//    while (result != NULL && p != NULL) //入栈
//    {
//        cout << "val:" << p->val << endl;
//        s.push(p->val);
//        p = p->next;
//    }
//
//    while (!s.empty()) //出栈
//    {
//        cout << s.top() << " ";
//        s.pop();
//    }
//    return true;
//
//}
int main() {
    cout << "Please input first Node:\n";
    ListNode *l1 = nodeInit();
    cout << "Please input second Node:\n";

    ListNode *l2 = nodeInit();

    Solution sol;
    ListNode *result = sol.addTwoNumbers(l1, l2);
    printNode(result);
    return 0;
}