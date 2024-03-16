#include <stdio.h>
#include <string.h>
#define MAX_RULES 128
#define MAX_WAYS 32
#define MAX_BYTES 16

/*
 * This is a data structure that stores the contents of the read file.
 * The first index stores the ASCII values for uppercase letters
 * The second index is what I think is the maximum possible number of ways it can be translated
 * The third index is the maximum number of bytes of the object I think he was translated
 */

char table[MAX_RULES][MAX_WAYS][MAX_BYTES];

char exist[MAX_RULES];
char parent[MAX_RULES][MAX_WAYS];
char child[MAX_RULES][MAX_WAYS];
int cnt;
char start;
int ok[MAX_RULES];
int notok[MAX_RULES];
// debug
static inline void print_table()
{
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        printf("%c->", c);
        for (int j = 0; strlen(table[c][j]); j++) {
            if(strlen(table[c][j + 1]))
                printf("%s|", table[c][j]);
            else 
                printf("%s", table[c][j]);
        }
        printf("\n");
    }

}
void find_ancestors(char c, int *flag)
{
    if(c == start) {
        *flag = 1;
        return ;
    }
    if(c == 0)
        return ;
    for (int i = 0; parent[c][i]; i++) {
        find_ancestors(parent[c][i], flag);
    }
}
void find_children(char c, int *flag)
{
    if(ok[c] == 1) {
        *flag = 1;
        return ;
    }
    if (c == 0)
        return ;
    for (int i = 0; child[c][i]; i++) {
        find_children(child[c][i], flag);
    }
}
void read_grammar_from_file(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_BYTES];
    int rule_index = -1;
    int way_index = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {

        char *token;
        char delimiters[] = "->|\n";
        token = strtok(line, delimiters);

        // Ensure we have both left and right parts of the production
        if (token == NULL) {
            continue;
        }

        // Left part of the production
        rule_index = token[0];
        exist[cnt++] = token[0];
        char pos = token[0];
        // Right part of the production
        token = strtok(NULL, delimiters);
        while (token != NULL) {
            strcpy(table[rule_index][way_index], token);
            printf("token = %s\n", token);
            way_index++;
            token = strtok(NULL, delimiters);
        }

        // Reset way index for the next production
                way_index = 0;
    }

    fclose(fp);
}
void build_tree()
{
    start = exist[0];
    parent[start][0] = start;

    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        for (int j = 0; strlen(table[c][j]); j++) {
            char *p = table[c][j];
            while(*p) {
                if(*p >= 'A' && *p <= 'Z' && *p != c) { 
                    int cnt = 0;
                    while(parent[*p][cnt]) cnt++;
                    parent[*p][cnt] = c; 
                    //printf("%c 's %d parent is %c\n", *p, cnt, c);
                }
                p++;
            }
        }
    }

}
/*This tree serves reverse tagging*/

void build_child()
{
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        int count = 0;
        for (int j = 0; strlen(table[c][j]); j++) {
            char *p = table[c][j];
            while (*p) {
                if (*p >= 'A' && *p <= 'Z' && *p != c) {
                    child[c][count++] = *p;
                    //printf("%c 's child is %c\n", c, *p);
                }
                p++;
            }
        }
        
    }
}
void compact_grammar() {
    /* forward mark */
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        int flag = 0;
        find_ancestors(c, &flag);
        if (!flag) {
            //delete illegal nodes
            exist[i] = 0;
            for (int j = i + 1; j < cnt; j++) {
                exist[j - 1] = exist[j];
            }
            cnt -= 1;
            i -= 1;
        }
    }
    printf("forward:\n");
    print_table();

    build_child();
    /* reverse mark */

    /* For those who can go directly to the terminator, we put a special mark */
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        int flag = 0;
        for (int j = 0; strlen(table[c][j]); j++) { 
            int label = 0;
            char *p = table[c][j];
            while(*p){ 
                if(*p >= 'A' && *p <= 'Z')
                    label = 1;
                p++;
            }
            if (label == 0) 
                flag = 1;
        }
        if (flag == 1) {
            ok[c] = 1;
        }

    }
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        int flag = 0;
        find_children(c, &flag);    
        if(!flag) {
            exist[i] = 0;
            for (int j = i + 1; j < cnt; j++) {
                exist[j - 1] = exist[j];
            }
            cnt -= 1;
            i -= 1;
            notok[c] = 1;
            //printf("%c is not ok\n", c);
        }
    }
    for (int i = 0; i < cnt; i++) {
        char c = exist[i];
        int nchild = 0;
        for (int j = 0; strlen(table[c][j]); j++) {
            nchild += 1;
        }
        for (int j = 0; j < nchild; j++) {
            char *p = table[c][j];
            while(*p) {
                if (*p >= 'A' && *p <= 'Z' && notok[*p] == 1) {
                    memset(table[c][j], 0, 16);
                    for (int k = j + 1; k < nchild; k++) {
                        strcpy(table[c][k - 1], table[c][k]);
                        memset(table[c][k], 0, 16);
                    }
                    nchild -= 1;
                    j -= 1;
                    break;
                }
                p++;
            }
        }
        
    }
    printf("reverse:\n");
    print_table();

}

int main() {
    read_grammar_from_file("input.txt");
    printf("input:\n");
    print_table();
    build_tree();
    compact_grammar();
    // Print table content for verification
       return 0;
}

