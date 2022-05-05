#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>


extern int nondet_int();

void make_nondet_len_string(char *buffer, _Bool taint);

int append(char *buffer, int position, char *stringToAppend);

int checkpart(char *buffer, int position, char *string, _Bool expected);

void check(char *buffer, char *username, char *password);


int main() {

    __CPROVER_field_decl_local("tainted", (_Bool) 0);
    __CPROVER_field_decl_global("tainted", (_Bool) 0);

    char username[8];
    char password[8];

    make_nondet_len_string(username, 0);
    make_nondet_len_string(password, 1);

    char encodedSensitiveData[20] = "";

    int position = 0;

    position = append(encodedSensitiveData, position, username);
    position = append(encodedSensitiveData, position, " ");
    position = append(encodedSensitiveData, position, password);

//    strcat(encodedSensitiveData, username);
//    strcat(encodedSensitiveData, " ");
//    strcat(encodedSensitiveData, password);

    check(encodedSensitiveData, username, password);

    int x = 3;
    int y;

    y = x;
}

void make_nondet_len_string(char *buffer, _Bool taint) {

    int lengthBuffer = nondet_int();
    __CPROVER_assume(0 <= lengthBuffer && lengthBuffer <= 7);
    buffer[lengthBuffer] = '\0';

    for (int i = 0; i < lengthBuffer; ++i) {
        __CPROVER_set_field(&buffer[i], "tainted", taint);
    }
}

int append(char *buffer, int position, char *stringToAppend) {

    for (int i = 0; i < strlen(stringToAppend); ++i) {
        buffer[position + i] = stringToAppend[i];
        __CPROVER_set_field(&buffer[position + i], "tainted", __CPROVER_get_field(&stringToAppend[i], "tainted"));
    }

    return position + strlen(stringToAppend);
}

int checkpart(char *buffer, int position, char *stringToCheck, _Bool expected) {

    for (int i = 0; i < strlen(stringToCheck); ++i) {
        _Bool actual = __CPROVER_get_field(&buffer[position + i], "tainted");
        assert(actual == expected);
    }

    return position + strlen(stringToCheck);
}

void check(char *buffer, char *username, char *password) {

    int position = 0;

    position = checkpart(buffer, position, username, 0);
    position = checkpart(buffer, position, " ", 0);
    position = checkpart(buffer, position, password, 1);

    checkpart(buffer, position, "\0", 0);
}