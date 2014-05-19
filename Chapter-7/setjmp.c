#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#define TOK_ADD 5
#define TOK_ERR 1
#define MAXLINE 1024

void do_line(char *);
void cmd_add(void);
int get_token(void);

jmp_buf jmpbuffer;

int main(void)
{
    char line[MAXLINE];

    if (setjmp(jmpbuffer) != 0) {
        fprintf(stderr, "error\n");
    }
    while (fgets(line, MAXLINE, stdin) != NULL) {
        do_line(line);
    }
    return 0;
}

char *tok_ptr; /* global pointer for get_token() */

void do_line(char *ptr)
{
    int cmd;
    /* process one line of input */
    tok_ptr = ptr;
    while ((cmd = get_token()) > 0) {
        switch (cmd) {  /* one case for each command */
        case TOK_ADD:
            cmd_add();
            break;
        case TOK_ERR:
            cmd_add();
            break;
        }
    }
}

void cmd_add(void)
{
    int token;
    token = get_token();
    /* rest of processing for this command */
    if (token < 0 || token == TOK_ERR) {
        longjmp(jmpbuffer, 1);
    }
}

int get_token(void)
{
    /* fetch next token from line pointed to by tok_ptr */
    return TOK_ERR;
}