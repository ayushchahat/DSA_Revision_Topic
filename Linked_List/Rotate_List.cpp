/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        int len=0;
        ListNode* tail=NULL;
        if(head==NULL){
            return NULL;
        }
        ListNode* curr=head;
        while(curr!=NULL){
            tail=curr;
            len++;
            curr=curr->next;
        }
        if(k%len==0){
            tail->next=NULL;
            return head;
        }
        tail->next=head;
        k=k%len;
        int cnt=len-k;
        ListNode* temp=head;
        while(cnt>1){
            temp=temp->next;
            cnt--;
        }
        head=temp->next;
        temp->next=NULL;
        return head;
    }
};