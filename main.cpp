//
//  main.cpp
//  Test
//
//  Created by 程志彬 on 2020/3/16.
//  Copyright © 2019 程志彬. All rights reserved.
//

#include<stdio.h>
#include <string>
using namespace std;
//第一题
/*
 array:整形数组
 len:整形数组长度
 return:第一个重复元素的下标 不存在重复元素return -1
 */
int getFirstDoubleIndex(int *array,int len)
{
    int maxIndex = 0;
    int minIndex = 0;
    for(int curIndex=1;curIndex<len;curIndex++)
    {
        if(array[curIndex] < array[minIndex])
        {
            minIndex = curIndex;
        }
        else if(array[curIndex] == array[minIndex])
        {
            return minIndex;
        }
        else if(array[curIndex] > array[maxIndex])
        {
            maxIndex = curIndex;
        }
        else if(array[curIndex] == array[maxIndex])
        {
            return maxIndex;
        }
        else
        {
            for (int preIndex = 0;preIndex <= curIndex-1;preIndex++)
            {
                if(array[curIndex] == array[preIndex])
                {
                    return preIndex;
                }
            }
        }
    }
    return -1;
}
//第二题
void sortArray(int *array, int left, int right)
{
    if (left < right)
    {
        int i = left, j = right, x = array[left];
        while (i < j)
        {
            while(i < j && array[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                array[i++] = array[j];
            
            while(i < j && array[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                array[j--] = array[i];
        }
        array[i] = x;
        sortArray(array, left, i - 1); // 递归调用
        sortArray(array, i + 1, right);
    }
}
/*
 array1 array2  两个数组
 len1 len2  两个数组长度
 target 目标
 return : 1 存在 0不存在
 */
int getArrayAddEqualTarget(int *array1,int len1,int *array2,int len2,int target)
{
    sortArray(array1, 0, len1-1);
    sortArray(array2, 0, len2-1);
    int array1Index = 0;
    int array2Index = len2-1;
    int numAdd = 0;
    /*两个数组反向相加*/
    for(;array1Index<len1;array1Index++)
    {
        for(;array2Index>=0;array2Index--)
        {
            numAdd = array1[array1Index]+array2[array2Index];
            if(numAdd == target)
            {
                return 1;
            }
            else if(numAdd > target)
            {
                
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}
//第三题
typedef struct{
    char c;
    bool isEnd;
} CharData;

typedef struct node{
    CharData *charData;
    struct node *childs[26];
} CharNode;
char changeChar(char c)
{
    if(c >= 'A' && c <= 'Z')
    {
        c += 'a' - 'A';
    }
    return c;
}
CharNode *newCharNode()
{
    CharNode *ptr = (CharNode *)malloc(sizeof(CharNode));
    CharData *charData = (CharData *)malloc(sizeof(CharData));
    charData->c = 0;
    charData->isEnd = false;
    ptr->charData = charData;
    for(int i=0;i<26;i++)
    {
        ptr->childs[i] = NULL;
    }
    return ptr;
}
void freeNode(CharNode *ptr)
{
    if(ptr == NULL)
    {
        return;
    }
    for(int i=0;i<26;i++)
    {
        freeNode(ptr->childs[i]);
    }
    free(ptr->charData);
    free(ptr);
}
/*将给定的字符串解析为多叉树，返回头指针
 例如：che,chen,joy
 会生成多叉树
           head
        c       j
     h            o
   e(isEnd=true)   y(isEnd=true)
 n(isEnd=true)
*/
CharNode* analyseStr(const string &str)
{
    CharNode *head = newCharNode();
    CharNode *curPtr = head;
    const char* pStr = str.c_str();
    int curIndex = 0;
    int childIndex = 0;
    char curChar = pStr[curIndex];
    while(curChar != '\0')
    {
        curChar = changeChar(curChar);
        if(curChar >= 'a' && curChar <= 'z')
        {
            childIndex = curChar - 'a';
            if(curPtr->childs[childIndex] == NULL)
            {
                CharNode *newPtr = newCharNode();
                newPtr->charData->c = curChar;
                curPtr->childs[childIndex] = newPtr;
                curPtr = newPtr;
            }
            else
            {
                curPtr = curPtr->childs[childIndex];
            }
            if(pStr[curIndex+1] == '\0')
            {
                curPtr->charData->isEnd = true;
            }
        }
        else if(curChar == ',')
        {
            curPtr->charData->isEnd = true;
            curPtr = head;
        }
        curChar = pStr[++curIndex];
    }
    return head;
}
/*
 textSet:逗号分隔的单词字符串,非法字符会屏蔽
 inputStr:被分割的字符串
 ignoreCase:是否区分大小写
 return:int 输入字符串是否可以被完全分隔为给定的单词
    0：成功
    1：失败
    2：参数不合法
 */
int splitStringToWord(const string &textSet,const string &inputStr)
{
    int ret = 0;
    if(textSet.length() == 0 || inputStr.length() == 0)
    {
        return 2;
    }
    CharNode *head = analyseStr(textSet);
    const char *inputStrPtr = inputStr.c_str();
    int curIndex = 0;
    char curChar = 0;
    char nextChar = 0;
    CharNode *curPtr = head;
    string tempStr;
    string existStr;
    string notExistStr;
    while(true)
    {
        curChar = changeChar(inputStrPtr[curIndex]);
        curIndex ++;
        curPtr = curPtr->childs[curChar-'a'];
        nextChar = changeChar(inputStrPtr[curIndex]);
        tempStr += curChar;
        if(nextChar == '\0')
        {
            if(curPtr && curPtr->charData->isEnd)
            {
                existStr = existStr + tempStr + " ";
            }
            else
            {
                notExistStr = notExistStr + tempStr + " ";
                ret = 1;
            }
            break;
        }
        else
        {
            if(curPtr != NULL)
            {
                if(curPtr->childs[nextChar-'a'] == NULL)
                {
                    if(curPtr->charData->isEnd)
                    {
                        existStr = existStr + tempStr + " ";
                    }
                    else
                    {
                        notExistStr = notExistStr + tempStr + " ";
                        ret = 1;
                    }
                    curPtr = head;
                    tempStr = "";
                }
            }
            else
            {
                notExistStr = notExistStr + tempStr + " ";
                ret = 1;
                curPtr = head;
                tempStr = "";
            }
        }
    }
    freeNode(head);
    printf("---- exist str = %s\n",existStr.c_str());
    printf("---- not exist str = %s\n",notExistStr.c_str());
    return ret;
}
int main()
{
    //第一题
    int array[] = {3,2,5,7,4,50,20,30};
    int ret1 = getFirstDoubleIndex(array, 8);
    printf("---- ret1 = %d\n",ret1);
    //第二题
    int array1[] = {10,40,5,200};
    int len1 = 4;
    int array2[] = {234,5,2,148,23};
    int len2 = 5;
    int target = 42;
    int ret2 = getArrayAddEqualTarget(array1,len1,array2,len2,target);
    printf("---- ret2 = %d\n",ret2);
    //第三题
    string textSet = "joy,castle,cat";
    string inputStr = "abc";
    int ret3 = splitStringToWord(textSet, inputStr);
    printf("---- ret3 = %d\n",ret3);
    return 0;
}
