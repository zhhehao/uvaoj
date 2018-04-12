#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10000

int n;

struct dict
{
    char *key;
    char *content;
};

int get_dict(struct dict **tmp) 
{   
    FILE *fp = fopen("dict.txt", "rb");
    if (fp == NULL) {
        perror("Not found dict.txt");
        exit(0);
    }
    // 分配堆区空间
    *tmp = (struct dict *)malloc(10000 * sizeof(struct dict));
    if (*tmp == NULL) {
        perror("malloc failure!");
        exit(0);
    }

    // 把单词存储到内存
    char word[100], meaning[100];
    int i = 0;
    while (1) {
        fgets(word, sizeof(word), fp);
        fgets(meaning, sizeof(meaning), fp);
        if ( feof(fp) ) break;
        (*(*tmp+i)).key = (char *)malloc(strlen(word)+1);
        strcpy((*(*tmp+i)).key, word+1);
        (*(*tmp+i)).content = (char *)malloc(strlen(meaning)+1);
        strcpy((*(*tmp+i)).content, meaning+6);
        i++;
    }

    fclose(fp);
    fp = NULL;
    return i;
}

void search_word(char *w, struct dict *p) {
    int lo = 0, hi = n-1;
    while (lo <= hi) {
        int mid = lo + (hi-lo) / 2;
        int flag = strncmp(w, (*(p+mid)).key, strlen((*(p+mid)).key)-1);
        if (flag < 0) hi = mid - 1;
        else if (flag > 0) lo = mid + 1;
        else {printf("%s", (*(p+mid)).content); return;}
    }
    printf("没有查询到这个单词!\n");
}

void free_dict(struct dict *p) {
    for (int i = 0; i < n; i++) {
        free((*(p+i)).key);
        free((*(p+i)).content);
    }
    free(p);
}

int main(int argc, char *argv[])
{
    struct dict *p = NULL;

    //1，给p分配空间，分配空间后，需要设置内容
    n = get_dict(&p);

    //2, 用二分法查询单词
    char buf[100];
    while (1) {
        printf("请输入一个单词，输入0退出程序:\n");
        printf("----------------------------\n");
        scanf("%s", buf);
        if (buf[0] == '0') break;
        search_word(buf, p);
        printf("----------------------------\n");
    }
    
    //3, 释放空间
    free_dict(p);

    return 0;
}