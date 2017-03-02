#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../custom_types/token.h"
#include "../../custom_types/structs.h"
#include "../../headers/utils.h"
#include "../../headers/parser.h"

void readFirstAndFollow(const char *first_file, const char *follow_file, non_terminals nt){

    int i, j;

    FILE *first_fp = fopen(first_file, "rt");
    if (first_fp == NULL)
        printf("First file does not exist.\n");

    FILE *follow_fp = fopen(follow_file, "rt");
        if (follow_fp == NULL)
            printf("Follow file does not exist.\n");

    // Tokens are no longer
    char buffer[50];
    char ch;

    int row_num = 0;
    int word_num = 0;

    token name;

    // Initialize everything with zeros
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 20; j++) {
            nt[i].first[j] = 0;
            nt[i].follow[j] = 0;
        }
    }

    while (fscanf(first_fp, "%s%c", buffer, &ch) == 2){

        if (word_num == 0){
            // Index of non-terminals starts from 500
            name = string_to_token(buffer) - 500;
        } else {
            nt[name].first[word_num-1] = string_to_token(buffer);
        }

        // Essential for lhs and rhs
        word_num++;

        // Take care of line number
        if (ch == '\n'){
            row_num++;
            word_num = 0;
        }
    }

    // Reset variables
    row_num = 0;
    word_num = 0;

    while (fscanf(follow_fp, "%s%c", buffer, &ch) == 2){

        if (word_num == 0){
            // Index of non-terminals starts from 500
            name = string_to_token(buffer) - 500;
        } else {
            nt[name].follow[word_num-1] = string_to_token(buffer);
        }

        // Essential for lhs and rhs
        word_num++;

        // Take care of line number
        if (ch == '\n'){
            row_num++;
            word_num = 0;
        }
    }

    fclose(first_fp);
    fclose(follow_fp);
}
