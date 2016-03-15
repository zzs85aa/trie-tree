/*
 *function: trie tree

 *author:blueShell

  mail:zzs85aa@163.com
 * */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <stdint.h>

#define   MAX_TRIE_NODE      10240
#define   MAX_NODE           26
#define   MAX_SPLIT_NUM      97
#define   MAX_LINE_SIZE      65536

typedef struct TRIE_NODE
{
    struct TRIE_NODE *node[MAX_NODE];
    int v;
}trie;

int check(trie *root, trie *ns, uint32_t *cur, char *str, int sl)
{
    int flag = -1;
    int i, j;
    uint32_t c = *cur;
    trie *tnode, *node;
    
    char ch = str[0];
    printf("go0\n");
    for (i=0; i<MAX_NODE; i++)
    {
        tnode = root->node[i];
        if (NULL == tnode)
        {
            printf("no.\n");
            tnode = &(ns[c++]);
            root->node[i] = tnode;
            tnode->v = ch;
            break;
        }
        if (ch == tnode->v)
        {
            printf("find.node=%d\n",tnode->v);
            flag = 0;
            break;
        }
    }

    for (i=1; i<sl; i++)
    {
        ch = str[i];
        j = 0;
        for (;;)
        {
            if (j > MAX_NODE-1)
            {
                printf("overflow,ch=%d\n",ch);
                break;
            }
            node = tnode->node[j];
            if (node == NULL)
            {
                node = &(ns[c++]);
                tnode->node[j] = node;
                node->v = ch;
                tnode = node;
                
                break;
            }
            if (ch == node->v)
            {
                printf("find, node=%d\n", node->v);
                tnode = node;
                break;
            }
            j++;
        }
    }
    *cur = c;

    return 0;
}


int main(int argc, char **argv)
{
    char lb[MAX_LINE_SIZE];
    char str[128];
    trie *root;
    FILE *fp;
    char *file;
    int ret;
    uint32_t c = 0;
    uint32_t trie_size;
    if (argc < 2)
    {
        printf("input format err.\n");
        return -1;
    }
    file = argv[1];
    fp = fopen(file,"rb");
    if (NULL == fp)
    {
        printf("fopen file err.\n");
        return -1;        
    }
    trie_size = MAX_TRIE_NODE * sizeof(trie);
    trie *trieNodes = (struct TRIE_NODE *)malloc(trie_size);
    if (NULL == trieNodes)
    {
        printf("malloc err.\n");
        return -1;
    }
    printf("malloc size=%dKb\n", trie_size/1024);
    memset(trieNodes, 0, trie_size);
    root = trieNodes;
    uint32_t tc;
    char *s ,*t;
    char *tp[128];
    for(;;)
    {
        if (NULL == fgets(lb, MAX_LINE_SIZE, fp))
        {
            goto end_process;
        }
        tc = 0;
        s = lb;
        tp[tc++] = lb;
        for(;;)
        {
            t = strchr(s, '\t');
            if (NULL == t)
            {
                if (MAX_SPLIT_NUM != tc)
                {
                    printf("tc=%d\n", tc);
                }
                break;
            }
            tp[tc++] = t+1;
            s = t+1;
        }
        printf("pkg=%.*s\n",tp[8]-tp[7]-1, tp[7]);
        //ret = check(root, trieNodes+1, &c, str, strlen(str));
    }

    end_process:
    if (fp != NULL)
    {
        fclose(fp);
    }
    if (trieNodes != NULL)
    {
        free(trieNodes);
        trieNodes = NULL;
    }

    return 0;
}

