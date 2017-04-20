#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../types/token.h"
#include "../types/structs.h"
#include "../utils/utils.h"
#include "./symbol_table.h"

void
populateSymbolTable(parseTree pT, symbolTableTree sT, hashTable * fT)
{
    parseTreeNode * listPointer, * inputListPointer, * outputListPointer;
    int i, scopeId;
    tableEntry * data;

    // Empty node
    if (*pT == NULL) {
        return;
    }

    // Assign parents scopeId to child
    if ((**pT).left != NULL) {
        (**pT).scopeId = (**pT).left->scopeId;
    } else if ((**pT).parent != NULL) {
        (**pT).scopeId = (**pT).parent->scopeId;
    }


    switch ((**pT).data.name) {
        // When a new scope is opened
        case program:
            scopeId        = insertInSTT(token_to_string((**pT).data.name), -1, sT);
            (**pT).scopeId = scopeId;
            break;

        case module:
        case driverModule:
        case conditionalStmt:
        case iterativeStmt:
            scopeId        = (**pT).parent->scopeId;
            (**pT).scopeId = insertInSTT(token_to_string((**pT).data.name), scopeId, sT);
            break;
    }

    switch ((**pT).data.name) {
        // When we insert into table
        case N1:
        case N2:
        case declareStmt:
            // In AST
            // declareStmt -> idList dataType
            // idList is a doubly linked list
            //
            listPointer = (**pT).children[0];

            scopeId = (**pT).scopeId;
            // Assign scope of type child (doesn't matter but just my ocd :p)
            (**pT).children[0]->scopeId = scopeId;
            while (listPointer != NULL) {
                // Assign scope
                listPointer->scopeId = scopeId;
                // Make the table entry
                data = (tableEntry *) malloc(sizeof(tableEntry));
                if ((**pT).data.name == N2) {
                    data->type = (**pT).children[1]->data.name;
                } else {
                    data->type = (**pT).children[1]->children[0]->data.name;
                }

                data->location = -1;
                // Insert
                insertEntryInSTT(listPointer->data.string, *data, scopeId, sT);
                // Move pointer forward
                listPointer = listPointer->right;
            }
            // Try going rightwards
            populateSymbolTable(&((**pT).right), sT, fT);
            // We don't want to recurese again
            return;

        case moduleDeclarations:
            // In AST
            // moduleDeclaration is a doubly linked list
            listPointer = (**pT).children[0];
            scopeId     = (**pT).scopeId;

            while (listPointer != NULL) {
                // Assign scope
                listPointer->scopeId = scopeId;
                // Make the table entry
                data = (tableEntry *) malloc(sizeof(tableEntry));
                data->isDefined = -1;
                data->location  = -1;
                for (i = 0; i < 20; i++) {
                    data->inputTypes[20]  = -1;
                    data->outputTypes[20] = -1;
                }
                // Insert
                insertEntryInFT(listPointer->data.string, *data, fT);
                // Move pointer forward
                listPointer = listPointer->right;
            }
            // We don't want to recurese again
            return;

        case module:
            // In AST
            // module.addr -> ID, input_plist, output_plist, moduleDef
            // input_plist -> list of N1
            // N1 -> ID dataType
            // output_plist -> list of N2
            // N2 -> ID (INTEGER | REAL | BOOLEAN)
            inputListPointer  = NULL;
            outputListPointer = NULL;
            for (i = 0; i < 20; i++) {
                if ((**pT).children[i] != NULL) {
                    if ((**pT).children[i]->data.name == input_plist) {
                        inputListPointer = (**pT).children[i]->children[0];
                    } else if ((**pT).children[i]->data.name == output_plist) {
                        outputListPointer = (**pT).children[i]->children[0];
                    }
                }
            }

            scopeId = (**pT).scopeId;

            data = (tableEntry *) malloc(sizeof(tableEntry));
            data->isDefined = 1;
            data->location  = -1;
            for (i = 0; i < 20; i++) {
                data->inputTypes[20]  = -1;
                data->outputTypes[20] = -1;
            }

            i = 0;
            while (inputListPointer != NULL) {
                data->inputTypes[i] = inputListPointer->children[1]->children[0]->data.name;
                // Move pointer forward
                inputListPointer = inputListPointer->right;
                i++;
            }
            i = 0;
            while (outputListPointer != NULL) {
                data->outputTypes[i] = outputListPointer->children[1]->data.name;
                // Move pointer forward
                outputListPointer = outputListPointer->right;
                i++;
            }

            insertEntryInFT((**pT).children[0]->data.string, *data, fT);
        default:
            // Recurse
            for (i = 0; i < 20; i++) {
                populateSymbolTable(&((**pT).children[i]), sT, fT);
            }
            populateSymbolTable(&((**pT).right), sT, fT);
            break;
    }
} /* populateSymbolTable */
