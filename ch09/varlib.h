/*

file: varlib.h
author: 2018117610_moonjunyong
이 파일은 varlib.c 의 함수들을 다른 c 파일에서 사용하기 위해 함수 선언부가 포함된 헤더 파일입니다.
*/


// varlib.c -> functions

int     VLstore(char *name, char *val);
static char *new_string(char *name, char *val);
char    *VLlookup(char *name);
int     VLexport(char *name);
static struct var *find_item(char *name, int first_blank);
void    VLlist();
int     VLenviron2table(char *env[]);
char    **VLtable2environ();

