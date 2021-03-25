#include <iostream>
#include <string>
#include <bits/stdc++.h>


using namespace std;

class Solution {
public:

struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
   
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        std::string::size_type sz;   // alias of size_t
        //get numbers as integers
        int l1Number = getListIntegers(l1);
        int l2Number = getListIntegers(l2);
        int result = l1Number+l2Number;
        //return digits as strings
        string resultString = convertIntToString(result);
        reverse(resultString.begin(), resultString.end());
        for(int i = 0; i < resultString.size(); i++){
            ListNode* returnList[i] = stoi(resultString[i],&sz);

        }
         return returnList;
    }
    
    int getListIntegers(ListNode* list){
        string number = "";
        std::string::size_type sz;
        for(int i = 0; i < list.size(); i++){
            number+=convertIntToString(list[i]);
        }
        reverse(number.begin(), number.end()); 
        return std::stoi(number,&sz);
    }
    
    string convertIntToString(int x){
        string number = "";
        char str[20];
        number += itoa(x, str, 10);
        return number;
    }
};