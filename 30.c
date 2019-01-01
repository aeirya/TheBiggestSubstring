#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//زیررشته مشترک 

typedef struct strings 
{
    char* str;
    int len;
} string;

string bite(string s, int a, int len)
{
    string r;
    r.str = (char*)malloc((len)*sizeof(char));
    r.len = len;
    for(int i=0; i<len; i++) r.str[i] = s.str[i+a];
    return r;
}

string reverse(string s)
{
    string r;
    r.str = (char*) malloc(s.len * sizeof(char));
    for(int i=0; i<s.len; i++)
        r.str[i] = s.str[s.len-1-i];
    r.len = s.len;
    return r;
}

bool find(string s, string source)
{
     for(int i=0; i + s.len < source.len; i++)
        if( strcmp( bite(source, i, s.len).str , s.str )==0 )
            return true;
        else if ( strcmp( bite(source, i, s.len).str , reverse(s).str)==0 )
            return true;
     return false;
}

bool findInAll(string s, string* all, int n)
{
    for(int i=0; i<n; i++)
        if(!find(s, all[i])) 
            return false;
    return true;
}

char *analyze(string s, string* all, int n)
{
    string sub = s;
    for(int i=s.len-1; i>=0; i--)
    {
        for(int j=0; (j< i) && ((i-j)>sub.len); j++)
        {
            string ss = bite( s , j, i-j+1 );
            if(findInAll(ss, all, n)) sub = ss;
        }
    }
    return sub.str;
}

int main()
{
    int n;
    scanf("%d", &n);
    string *input;
    input = (string*) malloc(n*sizeof(string));
    string smin;
    for(int i=0; i<n; i++)
    { 
        input[i].str = (char*) malloc(50*sizeof(char));
        scanf("%s%n", input[i].str, &input[i].len);
        if(i==0 || smin.len > input[i].len) smin = input[i];
    }
    char *result = analyze(smin, input, n);
    printf("%s", result);
    return 0;
}