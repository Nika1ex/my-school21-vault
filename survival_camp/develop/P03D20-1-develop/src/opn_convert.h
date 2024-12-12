#ifndef OPN_CONVERT_H
#define OPN_CONVERT_H

#define MAX 100

void get_function(char *s);
void infix_to_postfix(const char *infix, char result[][MAX], int *num_elements);
int is_operand(char c);
int is_operator(char c);
int precedence(char c);
int is_function(const char *s, int *func_len);
int is_alpha(char c);

#endif