#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "knowledge.h"
#include "constants.h"
#include "scripts.h"



void initStrings(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    for (int i = 0; i < NUM_SETS; i++)
    {
        for (int j = 0; j < FUNCTION_RESULT_SIZE*INT_LENGTH; j++)
        {
            funcName[i][j] = (char*) malloc(SIZE);
        }
    }
}

void initElementStrings(char *elementName[NUM_SETS][MAX_SET_ELEMENTS], int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    for (int i = 0; i < NUM_SETS; i++)
    {
        for (int j = 0; j < MAX_SET_ELEMENTS; j++)
        {
            elementName[i][j] = (char*) malloc(SIZE);
        }
    }
}
void writeRoleFunc(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int set, int index[], char *name, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(funcName[set][index[set]], SIZE, "is_%s", name);
    index[set] += 1;
    snprintf(funcName[set][index[set]], SIZE, "is_NOT_%s", name);
    index[set] += 1;
}

void writeRoleInGameFunc(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int set, int index[], char *name, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(funcName[set][index[set]], SIZE, "is_%s_in_PLAY", name);
    index[set] += 1;
    snprintf(funcName[set][index[set]], SIZE, "is_NOT_%s_in_PLAY", name);
    index[set] += 1;
}

void writeFunc(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int set, int index[], char *str, char *strNegation, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(funcName[set][index[set]], SIZE, "%s", str);
    index[set] += 1;
    snprintf(funcName[set][index[set]], SIZE, "%s", strNegation);
    index[set] += 1;
}

void writeDeathFunc(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int set, int index[], int night, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(funcName[set][index[set]], SIZE, "died_NIGHT%d", night);
    index[set] += 1;
    snprintf(funcName[set][index[set]], SIZE, "alive_NIGHT%d", night);
    index[set] += 1;
}

void writePoisonFunc(char *funcName[NUM_SETS][FUNCTION_RESULT_SIZE*INT_LENGTH], int set, int index[], int night, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(funcName[set][index[set]], SIZE, "is_poisoned_NIGHT%d", night);
    index[set] += 1;
    snprintf(funcName[set][index[set]], SIZE, "is_NOT_poisoned_NIGHT%d", night);
    index[set] += 1;
}



KnowledgeBase* initKB(int NUM_PLAYERS, int NUM_DAYS)
{
    //Allocate memory
    KnowledgeBase* kb = (KnowledgeBase*) malloc(sizeof(KnowledgeBase));

    

    resetKnowledgeBase(kb->KNOWLEDGE_BASE);

    //Sets
    kb->SET_NAMES[0] = "PLAYERS";
    kb->SET_NAMES[1] = "DAYS";
    kb->SET_NAMES[2] = "METADATA";

    kb->SET_SIZES[0] = NUM_PLAYERS; //NUM PLAYERS
    kb->SET_SIZES[1] = NUM_DAYS; //NUM DAYS
    kb->SET_SIZES[2] = 1; //Metadata

    int index[3] = {0, 0, 0};


    initStrings(kb->FUNCTION_NAME, 64);
    initElementStrings(kb->ELEMENT_NAMES, 255);
    // ===========================================
    //  PLAYER FUNCTIONS
    // ===========================================
    //Roles
    
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        writeRoleFunc(kb->FUNCTION_NAME, 0, index, ROLE_NAMES[i], 64);
    }
    //Teams
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_GOOD", "is_EVIL", 64);
    //Classes
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_TOWNSFOLK", "is_NOT_TOWNSFOLK", 64);
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_OUTSIDER", "is_NOT_OUTSIDER", 64);
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_MINION", "is_NOT_MINION", 64);
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_DEMON", "is_NOT_DEMON", 64);

    //Deaths  
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_DEAD", "is_ALIVE", 64);
    writeFunc(kb->FUNCTION_NAME, 0, index, "died_in_NIGHT", "died_NOT_in_NIGHT", 64);
    writeFunc(kb->FUNCTION_NAME, 0, index, "died_by_HANGING", "died_NOT_by_HANGING", 64);
    //Death on night
    for (int night = 0; night < NUM_DAYS; night++)
    {
        writeDeathFunc(kb->FUNCTION_NAME, 0, index, night, 64);
    }
    //Poison
    for (int night = 0; night < NUM_DAYS; night++)
    {
        writePoisonFunc(kb->FUNCTION_NAME, 0, index, night, 64);
    }

    //REDHERRING
    writeFunc(kb->FUNCTION_NAME, 0, index, "is_REDHERRING", "is_NOT_REDHERRING", 64);

    // ===========================================
    //  DAY FUNCTIONS
    // ===========================================
    //FUNCTION_NAME[1][0] = "idk";
    //writeFunc(kb->FUNCTION_NAME, 1, index, "idk", "idk", 64);

    // ===========================================
    //  METADATA FUNCTIONS
    // ===========================================
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        writeRoleInGameFunc(kb->FUNCTION_NAME, 2, index, ROLE_NAMES[i], 64);
    }

    return kb;
}

void copyTo(KnowledgeBase* dest, KnowledgeBase* src)
{
    //Deep copy knowlegde base (these might change)
    memcpy(dest->KNOWLEDGE_BASE, src->KNOWLEDGE_BASE, sizeof(long)*NUM_SETS*MAX_SET_ELEMENTS*FUNCTION_RESULT_SIZE);
    memcpy(dest->SET_SIZES, src->SET_SIZES, sizeof(int)*NUM_SETS);
    for (int i = 0; i < NUM_SETS; i++)
    {
        //Shallow copy names (these will not change)
        dest->SET_NAMES[i] = src->SET_NAMES[i];
        //strcpy(dest->SET_NAMES[i], src->SET_NAMES[i]); //Deep copy version

        for (int j = 0; j < MAX_SET_ELEMENTS; j++)
        {
            //Shallow copy names (these will not change)
            dest->ELEMENT_NAMES[i][j] = src->ELEMENT_NAMES[i][j];
        }

        for (int j = 0; j < FUNCTION_RESULT_SIZE*INT_LENGTH; j++)
        {
            //Shallow copy names (these will not change)
            dest->FUNCTION_NAME[i][j] = src->FUNCTION_NAME[i][j];
           //strcpy(dest->FUNCTION_NAME[i][j], src->FUNCTION_NAME[i][j]); //Deep copy version
        }
    }
}

int getSetIDWithName(KnowledgeBase* kb, char* set, int validate)
{
    for (int i = 0; i < NUM_SETS; i++)
    {
        if (strcmp(set,kb->SET_NAMES[i]) == 0)
        {
            return i;
        }
    }
    if (validate == 1)
    {
        printf("ERROR: WRONG SET NAME '%s'\n", set);
        exit(1);
    }
    return -1;
}

int getSetFunctionIDWithName(KnowledgeBase* kb, int setID, char* function, int validate)
{
    for (int i = 0; i < FUNCTION_RESULT_SIZE*INT_LENGTH; i++)
    {
        //printf("COMPARE: %s, %s\n",function,FUNCTION_NAME[setID][i]);
        if (strcmp(function,kb->FUNCTION_NAME[setID][i]) == 0)
        {
            return i;
        }
    }
    if (validate == 1)
    {
        printf("ERROR: WRONG FUNCTION (set='%d') NAME '%s' set contains=\n", setID, function);
        for (int i = 0; i < FUNCTION_RESULT_SIZE*INT_LENGTH; i++)
        {
            printf("%s,\n",kb->FUNCTION_NAME[setID][i]);
        }
        exit(1);
    }
    return -1;
}

int getSetElementIDWithName(KnowledgeBase* kb, int setID, char* element, int validate)
{
    for (int i = 0; i < MAX_SET_ELEMENTS; i++)
    {
        //printf("COMPARE: %s, %s\n",function,FUNCTION_NAME[setID][i]);
        if (strcmp(element,kb->ELEMENT_NAMES[setID][i]) == 0)
        {
            return i;
        }
    }
    if (validate == 1)
    {
        printf("ERROR: WRONG ELEMENT (set='%d') NAME '%s' set contains=\n", setID, element);
        for (int i = 0; i < MAX_SET_ELEMENTS; i++)
        {
            printf("%s,\n",kb->ELEMENT_NAMES[setID][i]);
        }
        exit(1);
    }
    return -1;
}

void getIndexAndBit(int* index, int* bit, int functionID)
{
    *index = functionID / INT_LENGTH;
    *bit = functionID - (*index * INT_LENGTH);
}



void resetKnowledgeBase(long knowledgeBase[NUM_SETS][MAX_SET_ELEMENTS][FUNCTION_RESULT_SIZE])
{
    for (int set = 0; set < NUM_SETS; set++)
    {
        for (int element = 0; element < MAX_SET_ELEMENTS; element++)
        {
            for (int i = 0; i < FUNCTION_RESULT_SIZE; i++)
            {
                knowledgeBase[set][element][i] = 0;
            }
        }
    }
}

void resetElement(KnowledgeBase* kb, int set, int element)
{
    for (int i = 0; i < FUNCTION_RESULT_SIZE; i++)
    {
        kb->KNOWLEDGE_BASE[set][element][i] = 0;
    }
}

void addKnowledge(KnowledgeBase* kb, int set, int element, int function)
{
    int index, bit;
    getIndexAndBit(&index, &bit, function);

    long mask = 1L << bit;

    kb->KNOWLEDGE_BASE[set][element][index] |= mask;
}

int isKnown(KnowledgeBase* kb, int set, int element, int function)
{
    int index, bit;
    getIndexAndBit(&index, &bit, function);

    return (kb->KNOWLEDGE_BASE[set][element][index] >> bit) & 1;
}

int isKnownName(KnowledgeBase* kb, char* set, int element, char* function)
{
    int setID = getSetIDWithName(kb, set, 1);
    int functionID = getSetFunctionIDWithName(kb, setID, function, 1);

    return isKnown(kb, setID, element, functionID);
}

void addKnowledgeName(KnowledgeBase* kb, char* set, int element, char* function)
{
    int setID = getSetIDWithName(kb, set, 1);
    int functionID = getSetFunctionIDWithName(kb, setID, function, 1);

    addKnowledge(kb, setID, element, functionID);
}


int hasExplicitContradiction(KnowledgeBase* kb)
{
    //[NUM_SETS][MAX_SET_ELEMENTS][FUNCTION_RESULT_SIZE];
    for (int set = 0; set < NUM_SETS; set++)
    {
        for (int element = 0; element < MAX_SET_ELEMENTS; element++)
        {
            for (int function = 0; function < FUNCTION_RESULT_SIZE*INT_LENGTH; function += 2)
            {
                //Using the fact that for any statement A stored at an even index i NOT(A) is stored at the odd index i+1 
                if ((isKnown(kb, set, element, function) == 1) && (isKnown(kb, set, element, function+1) == 1))
                { //If A AND NOT(A) -> we have a contradiction
                    return 1; 
                }
            }
        }
    }
    return 0;
}



void printKnowledgeBase(KnowledgeBase* kb)
{

    for (int set = 0; set < NUM_SETS; set++)
    {
        for (int element = 0; element < MAX_SET_ELEMENTS; element++)
        {
            for(int function = 0; function < FUNCTION_RESULT_SIZE*INT_LENGTH; function++)
            {
                int index = function / INT_LENGTH;
                int bit = function - (index * INT_LENGTH);
                
                if (((kb->KNOWLEDGE_BASE[set][element][index] >> bit) & 1) == 1)
                {
                    printf("%s(%d:%s), ", kb->FUNCTION_NAME[set][function], element, kb->SET_NAMES[set]);
                }
            }
            printf("\n");
        }
    }
    printf("\n");
}


void printPlayerName(char* name, int maxLen)
{
    for (int c = 0; c < maxLen; c++)
    {
        if (c < strlen(name))
        {
            printf("%c", name[c]);
        }
        else
        {
            printf(" ");
        }
    }
}

void printPlayerTable(KnowledgeBase* kb)
{
    printf("         |");
    for (int role = 0; role < NUM_BOTCT_ROLES; role++)
    {
        //Only print roles in the script
        if (ROLE_IN_SCRIPT[role] == 1)
        {
            for (int c = 0; c < 3; c++)
            {
                printf("%c", ROLE_NAMES[role][c]);
            }
            printf("|");
        }
    }
    printf("\n");
    printf("---------|");
    for (int role = 0; role < NUM_BOTCT_ROLES; role++)
    {
        //Only print roles in the script
        if (ROLE_IN_SCRIPT[role] == 1)
        {
            printf("---|");
        }
    }
    printf("-----------|------|");
    printf("\n");
    int set = 0;
    for (int element = 0; element < kb->SET_SIZES[set]; element++)
    {
        int isTownsfolk = isKnownName(kb, "PLAYERS", element, "is_TOWNSFOLK"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 56) & 1);
        int isOutsider = isKnownName(kb, "PLAYERS", element, "is_OUTSIDER"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 58) & 1);
        int isMinion = isKnownName(kb, "PLAYERS", element, "is_MINION"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 60) & 1);
        int isDemon = isKnownName(kb, "PLAYERS", element, "is_DEMON"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 62) & 1);

        int isGood = isKnownName(kb, "PLAYERS", element, "is_GOOD"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 54) & 1);
        int isEvil = isKnownName(kb, "PLAYERS", element, "is_EVIL"); //((kb->KNOWLEDGE_BASE[set][element][0] >> 55) & 1);

        //printf("PLAYER %d |", element);
        //printf("%s |", kb->ELEMENT_NAMES[0][element]);
        printPlayerName(kb->ELEMENT_NAMES[0][element], 9);
        printf("|");
        for (int role = 0; role < NUM_BOTCT_ROLES; role++)
        {
            //Only print roles in the script
            if (ROLE_IN_SCRIPT[role] == 1)
            {
                int function1 = role*2;
                int index1 = function1 / INT_LENGTH;
                int bit1 = function1 - (index1 * INT_LENGTH);

                int function2 = role*2+1;
                int index2 = function2 / INT_LENGTH;
                int bit2 = function2 - (index2 * INT_LENGTH);
                if (((kb->KNOWLEDGE_BASE[set][element][index1] >> bit1) & 1) == 1)
                {
                    printf(" * ");
                }
                else if (((kb->KNOWLEDGE_BASE[set][element][index2] >> bit2) & 1) == 1)
                {
                    printf("   ");
                }
                else
                {
                    printf(" ? ");
                }
                printf("|");
            }
        }
        if (isTownsfolk == 1)
        {
            printf(" TOWNSFOLK ");
        }
        else if (isOutsider == 1)
        {
            printf("  OUTSIDER ");
        }
        else if (isMinion == 1)
        {
            printf("   MINION  ");
        }
        else if (isDemon == 1)
        {
            printf("   DEMON   ");
        }
        else
        {
            printf("     ?     ");
        }
        printf("|");
        if (isGood == 1)
        {
            printf(" GOOD ");
        }
        else if (isEvil == 1)
        {
            printf(" EVIL ");
        }
        else
        {
            printf("  ?   ");
        }
        printf("|\n");
    }
}

void printRoleTable(KnowledgeBase* kb)
{
    printf("         |");
    for (int role = 0; role < NUM_BOTCT_ROLES; role++)
    {
        //Only print roles in the script
        if (ROLE_IN_SCRIPT[role] == 1)
        {
            for (int c = 0; c < 3; c++)
            {
                printf("%c", ROLE_NAMES[role][c]);
            }
            printf("|");
        }
    }
    printf("\n");
    printf("---------|");
    for (int role = 0; role < NUM_BOTCT_ROLES; role++)
    {
        //Only print roles in the script
        if (ROLE_IN_SCRIPT[role] == 1)
        {
            printf("---|");
        }
    }
    //printf("-----------|------|");
    printf("\n");
    int set = 2;
    int element = 0;
    printf("IN GAME  |");
    for (int role = 0; role < NUM_BOTCT_ROLES; role++)
    {
        //Only print roles in the script
        if (ROLE_IN_SCRIPT[role] == 1)
        {
            int function1 = role*2;
            int index1 = function1 / INT_LENGTH;
            int bit1 = function1 - (index1 * INT_LENGTH);

            int function2 = role*2+1;
            int index2 = function2 / INT_LENGTH;
            int bit2 = function2 - (index2 * INT_LENGTH);
            if (((kb->KNOWLEDGE_BASE[set][element][index1] >> bit1) & 1) == 1)
            {
                printf(" * ");
            }
            else if (((kb->KNOWLEDGE_BASE[set][element][index2] >> bit2) & 1) == 1)
            {
                printf("   ");
            }
            else
            {
                printf(" ? ");
            }
            printf("|");
        }
    }
    printf("\n");
    
}