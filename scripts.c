#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scripts.h"
#include "constants.h"
#include "rules.h"

char *ROLE_NAMES[NUM_BOTCT_ROLES];
char *ROLE_TEAMS[NUM_BOTCT_ROLES];
char *ROLE_CLASSES[NUM_BOTCT_ROLES];

int ROLE_IN_SCRIPT[NUM_BOTCT_ROLES];

int TOTAL_MINIONS = 8;
int TOTAL_OUTSIDERS = 8;
int FIRST_MINION_INDEX = 1;
int FIRST_OUTSIDER_INDEX = 18;

void initRoleStrings(int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        ROLE_NAMES[i] = (char*) malloc(SIZE);
        ROLE_TEAMS[i] = (char*) malloc(SIZE);
        ROLE_CLASSES[i] = (char*) malloc(SIZE);
    }
}

void addRole(int *index, char* name, char* team, char* class, int roleInScript, int maxLen)
{
    int SIZE = maxLen*sizeof(char);
    snprintf(ROLE_NAMES[*index], SIZE, "%s", name);
    snprintf(ROLE_TEAMS[*index], SIZE, "%s", team);
    snprintf(ROLE_CLASSES[*index], SIZE, "%s", class);
    ROLE_IN_SCRIPT[*index] = roleInScript;
    
    *index = *index + 1;
}

void initTB(RuleSet** rs, KnowledgeBase** kb, int NUM_PLAYERS, int NUM_MINIONS, int NUM_DEMONS, int BASE_OUTSIDERS, int NUM_DAYS)
{
    //Temporary string buffer for writing names into
    char buff[STRING_BUFF_SIZE];

    printf("NAME THINGS...\n");
    int count = 0;
    initRoleStrings(64);

    int TB = 0;
    int SV = 1;
    int BMR = 2;

    int SCRIPT = TB;
    
    //Roles
    //Demons
    //TB
    addRole(&count, "IMP", "EVIL", "DEMON", SCRIPT==TB, 64);
    //S&V
    addRole(&count, "FANG_GU", "EVIL", "DEMON", SCRIPT==SV, 64);
    addRole(&count, "VIGORMORTIS", "EVIL", "DEMON", SCRIPT==SV, 64);
    addRole(&count, "NO_DASHII", "EVIL", "DEMON", SCRIPT==SV, 64);
    addRole(&count, "VORTOX", "EVIL", "DEMON", SCRIPT==SV, 64);
    //BMR
    addRole(&count, "ZOMBUUL", "EVIL", "DEMON", SCRIPT==BMR, 64);
    addRole(&count, "PUKKA", "EVIL", "DEMON", SCRIPT==BMR, 64);
    addRole(&count, "SHABALOTH", "EVIL", "DEMON", SCRIPT==BMR, 64);
    addRole(&count, "PO", "EVIL", "DEMON", SCRIPT==BMR, 64);

    //Minions
    FIRST_MINION_INDEX = count;
    //TB
    addRole(&count, "BARON", "EVIL", "MINION", SCRIPT==TB, 64);
    addRole(&count, "SCARLET_WOMAN", "EVIL", "MINION", SCRIPT==TB, 64);
    addRole(&count, "SPY", "EVIL", "MINION", SCRIPT==TB, 64);
    addRole(&count, "POISONER", "EVIL", "MINION", SCRIPT==TB, 64);
    //S&V
    addRole(&count, "EVIL_TWIN", "EVIL", "MINION", SCRIPT==SV, 64);
    addRole(&count, "WITCH", "EVIL", "MINION", SCRIPT==SV, 64);
    addRole(&count, "CERENOVUS", "EVIL", "MINION", SCRIPT==SV, 64);
    addRole(&count, "PIT_HAG", "EVIL", "MINION", SCRIPT==SV, 64);
    //BMR
    addRole(&count, "GODFATHER", "EVIL", "MINION", SCRIPT==BMR, 64);
    addRole(&count, "DEVILS_ADVOCATE", "EVIL", "MINION", SCRIPT==BMR, 64);
    addRole(&count, "ASSASSIN", "EVIL", "MINION", SCRIPT==BMR, 64);
    addRole(&count, "MASTERMIND", "EVIL", "MINION", SCRIPT==BMR, 64);

    //Townsfolk
    //TB
    addRole(&count, "WASHERWOMAN", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "LIBRARIAN", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "INVESTIGATOR", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "CHEF", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "EMPATH", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "FORTUNE_TELLER", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "UNDERTAKER", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "MONK", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "RAVENKEEPER", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "VIRGIN", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "SLAYER", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "SOLDIER", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    addRole(&count, "MAYOR", "GOOD", "TOWNSFOLK", SCRIPT==TB, 64);
    //S&V
    addRole(&count, "CLOCKMAKER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "DREAMER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "SNAKE_CHARMER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "MATHEMATITICIAN", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "FLOWERGIRL", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "TOWN_CRIER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "ORACLE", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "SAVANT", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "SEAMSTRESS", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "PHILOSOPHER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "ARTIST", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "JUGGLER", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    addRole(&count, "SAGE", "GOOD", "TOWNSFOLK", SCRIPT==SV, 64);
    //BMR
    addRole(&count, "GRANDMOTHER", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "SAILOR", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "CHAMBERMAID", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "EXORCIST", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "INNKEEPER", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "GAMBLER", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "GOSSIP", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "COURTIER", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "PROFESSOR", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "MINSTREL", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "TEA_LADY", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "PACIFIST", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);
    addRole(&count, "FOOL", "GOOD", "TOWNSFOLK", SCRIPT==BMR, 64);

    //Outsiders
    FIRST_OUTSIDER_INDEX = count;
    //TB
    addRole(&count, "BUTLER", "GOOD", "OUTSIDER", SCRIPT==TB, 64);
    addRole(&count, "DRUNK", "GOOD", "OUTSIDER", SCRIPT==TB, 64);
    addRole(&count, "RECLUSE", "GOOD", "OUTSIDER", SCRIPT==TB, 64);
    addRole(&count, "SAINT", "GOOD", "OUTSIDER", SCRIPT==TB, 64);
    //S&V
    addRole(&count, "MUTANT", "GOOD", "OUTSIDER", SCRIPT==SV, 64);
    addRole(&count, "SWEETHEART", "GOOD", "OUTSIDER", SCRIPT==SV, 64);
    addRole(&count, "BARBER", "GOOD", "OUTSIDER", SCRIPT==SV, 64);
    addRole(&count, "KLUTZ", "GOOD", "OUTSIDER", SCRIPT==SV, 64);
    //BMR
    addRole(&count, "TINKER", "GOOD", "OUTSIDER", SCRIPT==BMR, 64);
    addRole(&count, "MOONCHILD", "GOOD", "OUTSIDER", SCRIPT==BMR, 64);
    addRole(&count, "GOON", "GOOD", "OUTSIDER", SCRIPT==BMR, 64);
    addRole(&count, "LUNATIC", "GOOD", "OUTSIDER", SCRIPT==BMR, 64);

    printf("INIT DATA STRUCTURES...\n");
    //Init data structures
    printf("-RULE SET...\n");
    *rs = initRS();
    printf("-DONE!..\n");
    printf("-KNOWLEDGE BASE...\n");
    *kb = initKB(NUM_PLAYERS, NUM_DAYS);
    printf("-DONE!..\n");

    printf("BUILD RULES...\n");

    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        if (ROLE_IN_SCRIPT[i] == 0)
        {
            snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[i]);
            addKnowledgeName(*kb, "METADATA", 0, buff);
        }
    }

    buildRules(*rs, *kb, NUM_PLAYERS, NUM_MINIONS, NUM_DEMONS, BASE_OUTSIDERS);
}

void buildRules(RuleSet* rs, KnowledgeBase* kb, int numPlayers, int numMinions, int numDemons, int baseOutsiders)
{
    int numEvil = numMinions+numDemons;
    int numGood = numPlayers-numEvil;

    int maxOutsiders = baseOutsiders + 2; //For Baron
     
    // ===========================================
    //  Setup memory
    // ===========================================
    printf("-SETUP MEMORY...\n");
    //Temporary string buffer for writing names into
    char buff[STRING_BUFF_SIZE];
    
    

    
    // ===========================================
    //  Make role based rules
    // ===========================================
    printf("-ROLE RULES...\n");
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        //A role implies a team
        //<PLAYER>is_<ROLE> => <PLAYER>is_<ROLE_TEAM>
        setTempRuleParams(rs, 1,0);
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_TEAMS[i]);
        setTempRuleResultName(rs, kb, 0, "PLAYERS", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        //A role implies a class
        //<PLAYER>is_<ROLE> => <PLAYER>is_<ROLE_CLASS>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_CLASSES[i]);
        setTempRuleResultName(rs, kb, 0, "PLAYERS", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        //Only one player can have a role
        //<PLAYER_A>is_<ROLE> => <PLAYER_B>is_NOT<ROLE>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s", ROLE_NAMES[i]);
        setTempRuleResultName(rs, kb, -1, "PLAYERS", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        
        //A player must have one role
        //<PLAYER>is_NOT_{<ROLE_A>, <ROLE_B>...} => <PLAYER>is_<ROLE_Z>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        setTempRuleResultName(rs, kb, 0, "PLAYERS", buff); //A player is role ROLE_NAME[i] if
        for (int j = 0; j < NUM_BOTCT_ROLES; j++)
        {
            if (j!=i)
            { //A player is NOT role ROLE_NAME[j] for all i!=j
                snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s", ROLE_NAMES[j]);
                addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
            }
        }
        pushTempRule(rs);
        
    }

    
    // ===========================================
    //  More role rules
    // ===========================================
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        //Each player only has one role
        //<PLAYER>is_<ROLE_A> => <PLAYER>is_NOT<ROLE_B>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        for (int j = 0; j < NUM_BOTCT_ROLES; j++)
        {
            if (i!=j)
            { //I and j are mutually exclusive
                snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s", ROLE_NAMES[j]);
                setTempRuleResultName(rs, kb, 0, "PLAYERS", buff);
            }
        }
        pushTempRule(rs);
    }
    //works up to here
    // ===========================================
    //  Role Metadata implications
    // ===========================================
    
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        //<PLAYER_i>is_NOT_<ROLE> => <METADATA>is_NOT_ROLE_in_PLAY
        setTempRuleParams(rs, numPlayers,1);
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[i]);
        setTempRuleResultName(rs, kb, -1, "METADATA", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s", ROLE_NAMES[i]);
        for (int j = 0; j < numPlayers; j++)
        {
            addConditionToTempRuleName(rs,kb, j, "PLAYERS", buff);
        }
        pushTempRule(rs);
    }
    
    

    printf("-METADATA RULES...\n");
    for (int i = 0; i < NUM_BOTCT_ROLES; i++)
    {
        //<PLAYER>is_<ROLE> => <METADATA>is_<ROLE>_in_PLAY
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[i]);
        setTempRuleResultName(rs, kb, -1, "METADATA", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_%s", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        //take the contrapositive
        //<PLAYER>is_NOT_<ROLE>_in_PLAY => <PLAYER>is_NOT_<ROLE>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s", ROLE_NAMES[i]);
        setTempRuleResultName(rs, kb, -1, "PLAYERS", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[i]);
        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
        pushTempRule(rs);
    }
    
    //Counting arguments for role metadata 
    //If found all minions in play set all unused minions to is_NOT_<MINION>_in_PLAY
    int numUnusedMinions = TOTAL_MINIONS-numMinions;
    if (0 < numMinions && numMinions < TOTAL_MINIONS)
    {
        for (int i = 0; i < 16; i++)
        {
            //Permute all subsets of size 4
            int count = 0;
            for (int j = 0; j < TOTAL_MINIONS; j++)
            {
                if (((i >> j) & 1) == 1)
                {
                    count++;
                }
            }
            if (count == numMinions)
            {
                //<METADATA>is_NOT_<MINION>_in_PLAY => <METADATA>is_<MINION>_in_PLAY
                setTempRuleParams(rs, 1,0);
                

                for (int j = 0; j < TOTAL_MINIONS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_MINION_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_MINION_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
            if (count == numUnusedMinions)
            {
                //<PLAYER>is_<MINION>_in_PLAY => <METADATA>is_NOT_<MINION>_in_PLAY
                setTempRuleParams(rs, 1,0);
                

                for (int j = 0; j < TOTAL_MINIONS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_MINION_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_MINION_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
        }
    }
    
 
    

    int numUnusedOutsiders = TOTAL_OUTSIDERS-numMinions;

    //If found all outsiders (either with or without baron) in play set all unused outsiders to is_NOT_<OUTSIDER>_in_PLAY

    //Base outsiders (requires knowing there is not a baron)
    if (baseOutsiders == 0)
    {
        //<METADATA>is_NOT_BARON_in_PLAY => <METADATA>is_NOT_<OUTSIDER>_in_PLAY (x4)
        setTempRuleParams(rs, 1,0);
        

        //The baron can't be in play for this
        addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_NOT_BARON_in_PLAY");
        for (int j = 0; j < TOTAL_OUTSIDERS; j++)
        {
            snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
            setTempRuleResultName(rs, kb, 0, "METADATA", buff);
        }
        pushTempRule(rs);
    }
    else if (0 < baseOutsiders && baseOutsiders < TOTAL_OUTSIDERS)
    {
        for (int i = 0; i < 16; i++)
        {
            //Permute all subsets of size 4
            int count = 0;
            for (int j = 0; j < TOTAL_OUTSIDERS; j++)
            {
                if (((i >> j) & 1) == 1)
                {
                    count++;
                }
            }
            if (count == baseOutsiders)
            {
                //<METADATA>is_<OUTSIDER>_in_PLAY (xA) AND <METADATA>is_NOT_BARON_in_PLAY => <METADATA>is_NOT_<OUTSIDER>_in_PLAY (x4-A)
                setTempRuleParams(rs, 1,0);
                

                //The baron can't be in play for this
                addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_NOT_BARON_in_PLAY");

                for (int j = 0; j < TOTAL_OUTSIDERS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
            if (count == numUnusedOutsiders)
            {
                //<METADATA>is_NOT_<OUTSIDER>_in_PLAY (xA) AND <METADATA>is_NOT_BARON_in_PLAY => <METADATA>is_<OUTSIDER>_in_PLAY (x4-A)
                setTempRuleParams(rs, 1,0);
                

                //The baron can't be in play for this
                addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_NOT_BARON_in_PLAY");

                for (int j = 0; j < TOTAL_OUTSIDERS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
        }
    }

    //Extended outsiders outsiders (requires knowing there is a baron)
    int numOutsidersWithBaron = baseOutsiders+2;
    int numUnusedOutsidersWithBaron = TOTAL_OUTSIDERS-numMinions;

    if (numOutsidersWithBaron == TOTAL_OUTSIDERS)
    {
        //<METADATA>is_BARON_in_PLAY => <METADATA>is_<OUTSIDER>_in_PLAY (x4)
        setTempRuleParams(rs, 1,0);
        

        //The baron can't be in play for this
        addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_BARON_in_PLAY");
        for (int j = 0; j < 4; j++)
        {
            snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
            setTempRuleResultName(rs, kb, 0, "METADATA", buff);
        }
        pushTempRule(rs);
    }
    else if (0 < numOutsidersWithBaron && numOutsidersWithBaron < 4)
    {
        for (int i = 0; i < 16; i++)
        {
            //Permute all subsets of size 4
            int count = 0;
            for (int j = 0; j < TOTAL_OUTSIDERS; j++)
            {
                if (((i >> j) & 1) == 1)
                {
                    count++;
                }
            }
            if (count == numOutsidersWithBaron)
            {
                //<METADATA>is_<OUTSIDER>_in_PLAY (xA) AND <METADATA>is_BARON_in_PLAY => <METADATA>is_NOT_<OUTSIDER>_in_PLAY (x4-A)
                setTempRuleParams(rs, 1,0);
                

                //The baron can't be in play for this
                addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_BARON_in_PLAY");

                for (int j = 0; j < TOTAL_OUTSIDERS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
            if (count == numUnusedOutsidersWithBaron)
            {
                //<METADATA>is_NOT_<OUTSIDER>_in_PLAY (xA) AND <METADATA>is_BARON_in_PLAY => <METADATA>is_<OUTSIDER>_in_PLAY (x4-A)
                setTempRuleParams(rs, 1,0);
                

                //The baron can't be in play for this
                addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_BARON_in_PLAY");

                for (int j = 0; j < TOTAL_OUTSIDERS; j++)
                {
                    if (((i >> j) & 1) == 1)
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        addConditionToTempRuleName(rs,kb, 0, "METADATA", buff);
                    }
                    else
                    {
                        snprintf(buff, STRING_BUFF_SIZE, "is_%s_in_PLAY", ROLE_NAMES[j+FIRST_OUTSIDER_INDEX]);
                        setTempRuleResultName(rs, kb, 0, "METADATA", buff);
                    }
                }
                pushTempRule(rs);
            }
        }
    }


    // ===========================================
    //  Team Deduction argument rules
    // ===========================================
    //A player can only have one class
    //<PLAYER>is_TOWNSFOLK => <PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION AND <PLAYER>is_NOT_OUTSIDER
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MINION");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_TOWNSFOLK");
    pushTempRule(rs);

    //<PLAYER>is_OUTSIDER => <PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION AND <PLAYER>is_NOT_TOWNSFOLK
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MINION");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_OUTSIDER");
    pushTempRule(rs);

    //<PLAYER>is_MINION => <PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_OUTSIDER AND <PLAYER>is_NOT_TOWNSFOLK
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_MINION");
    pushTempRule(rs);


    //<PLAYER>is_DEMON => <PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_OUTSIDER AND <PLAYER>is_NOT_TOWNSFOLK
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MINION");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_DEMON");
    pushTempRule(rs);

    //If a player is none of the roles within a class that player can't be that class (deduction)
    //<PLAYER>is_NOT_IMP => <PLAYER>is_NOT_DEMON
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_IMP");
    pushTempRule(rs);

    //The converse is also true
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_IMP");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DEMON");
    pushTempRule(rs);

    //<PLAYER>is_NOT_BARON AND <PLAYER>is_NOT_SCARLET_WOMAN AND <PLAYER>is_NOT_SPY AND <PLAYER>is_NOT_POISONER=> <PLAYER>is_NOT_MINION
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MINION");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_BARON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_SCARLET_WOMAN");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_SPY");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_POISONER");
    pushTempRule(rs);

    //The converse is also true
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_BARON");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_SCARLET_WOMAN");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_SPY");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_POISONER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MINION");
    pushTempRule(rs);

    //<PLAYER>is_NOT_BUTLER AND <PLAYER>is_NOT_DRUNK AND <PLAYER>is_NOT_RECLUSE AND <PLAYER>is_NOT_SAINT=> <PLAYER>is_NOT_OUTSIDER
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_BUTLER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DRUNK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_RECLUSE");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_SAINT");
    pushTempRule(rs);

    //The converse is also true
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_BUTLER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DRUNK");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_RECLUSE");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_SAINT");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    pushTempRule(rs);


    //<PLAYER>is_NOT_WASHERWOMAN AND <PLAYER>is_NOT_LIBRARIAN AND <PLAYER>is_NOT_INVESTIGATOR AND <PLAYER>is_NOT_CHEF
    //AND <PLAYER>is_NOT_EMPATH AND <PLAYER>is_NOT_FORTUNE_TELLER AND <PLAYER>is_NOT_UNDERTAKER AND <PLAYER>is_NOT_MONK
    //AND <PLAYER>is_NOT_RAVENKEEPER AND <PLAYER>is_NOT_VIRGIN AND <PLAYER>is_NOT_SLAYER AND <PLAYER>is_NOT_SOLDIER
    //AND <PLAYER>is_NOT_MAYOR => <PLAYER>is_NOT_TOWNSFOLK
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_WASHERWOMAN");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_LIBRARIAN");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_INVESTIGATOR");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_CHEF");

    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_EMPATH");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_FORTUNE_TELLER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_UNDERTAKER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MONK");

    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_RAVENKEEPER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_VIRGIN");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_SLAYER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_SOLDIER");

    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MAYOR");
    pushTempRule(rs);

    //The converse is also true
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_WASHERWOMAN");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_LIBRARIAN");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_INVESTIGATOR");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_CHEF");

    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_EMPATH");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_FORTUNE_TELLER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_UNDERTAKER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MONK");

    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_RAVENKEEPER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_VIRGIN");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_SLAYER");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_SOLDIER");

    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MAYOR");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    pushTempRule(rs);


    //A player must have a class
    //<PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION AND <PLAYER>is_NOT_OUTSIDER => <PLAYER>is_TOWNSFOLK
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MINION");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    pushTempRule(rs);

    //<PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION AND <PLAYER>is_NOT_TOWNSFOLK => <PLAYER>is_OUTSIDER
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MINION");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    pushTempRule(rs);

    //<PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_OUTSIDER AND <PLAYER>is_NOT_TOWNSFOLK => <PLAYER>is_MINION
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_MINION");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    pushTempRule(rs);

    //<PLAYER>is_NOT_MINION AND <PLAYER>is_NOT_OUTSIDER AND <PLAYER>is_NOT_TOWNSFOLK => <PLAYER>is_DEMON
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MINION");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    pushTempRule(rs);


    //Deduction by clases
    //<PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION => <PLAYER>is_GOOD
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_GOOD");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_MINION");
    pushTempRule(rs);

    //<PLAYER>is_NOT_TOWNSFOLK AND <PLAYER>is_NOT_OUTSIDER => <PLAYER>is_EVIL
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_EVIL");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    pushTempRule(rs);

    //Other way of the iff (if and only if)
    //<PLAYER>is_GOOD => <PLAYER>is_NOT_DEMON AND <PLAYER>is_NOT_MINION
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_MINION");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_GOOD");
    pushTempRule(rs);

    //<PLAYER>is_EVIL => <PLAYER>is_NOT_TOWNSFOLK AND <PLAYER>is_NOT_OUTSIDER
    setTempRuleParams(rs, 1,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_TOWNSFOLK");
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_OUTSIDER");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_EVIL");
    pushTempRule(rs);

    // ===========================================
    //  Team Counting argument rules
    // ===========================================
    //RULE DISABLED DUE TO BAD PERFORMANCE
    //EDIT: new optimisation reduces this from O(n!) down to O(n) ish ish runing so re enabled

    //If all good players have been found the rest are evil
    //<PLAYER_1>is_GOOD AND ... <PLAYER_[num good players]>is_GOOD => <PLAYER_A>is_EVIL
    setTempRuleParams(rs, numGood,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_EVIL"); 
    for (int j = 0; j < numGood; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_GOOD");
    }
    pushTempRule(rs);
    


    //If all evil players have been found the rest are good
    //<PLAYER_1>is_EVIL AND ... <PLAYER_[num evil players]>is_EVIL => <PLAYER_A>is_GOOD
    setTempRuleParams(rs, numEvil,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_GOOD"); 
    for (int j = 0; j < numEvil; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_EVIL");
    }
    pushTempRule(rs);

    //If all minion players have been found the rest are not minions
    //<PLAYER_1>is_MINION AND ... <PLAYER_[num minion players]>is_MINION => <PLAYER_A>is_NOT_MINION
    setTempRuleParams(rs, numMinions,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_NOT_MINION"); 
    for (int j = 0; j < numMinions; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_MINION");
    }
    pushTempRule(rs);

    //If all demon players have been found the rest are not demons
    //<PLAYER_1>is_DEMON AND ... <PLAYER_[num minion players]>is_DEMON => <PLAYER_A>is_NOT_DEMON
    setTempRuleParams(rs, numDemons,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_NOT_DEMON"); 
    for (int j = 0; j < numDemons; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_DEMON");
    }
    pushTempRule(rs);


    //Outsider counting
    //If all outsider players have been found the rest are not outsider
    //<PLAYER_1>is_OUTSIDER AND ... <PLAYER_[num outsider players]>is_OUTSIDER => <PLAYER_A>is_NOT_OUTSIDER
    setTempRuleParams(rs, maxOutsiders,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_NOT_OUTSIDER"); 
    for (int j = 0; j < maxOutsiders; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_OUTSIDER");
    }
    pushTempRule(rs);

    //If all outsider players have been found the rest are not outsider
    //<PLAYER_1>is_OUTSIDER AND ... <PLAYER_[num outsider players]>is_OUTSIDER => <PLAYER_A>is_NOT_OUTSIDER
    setTempRuleParams(rs, baseOutsiders+1,1);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_NOT_OUTSIDER"); 
    for (int j = 0; j < baseOutsiders; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_OUTSIDER");
    }
    addConditionToTempRuleName(rs,kb, baseOutsiders, "METADATA", "is_NOT_BARON_in_PLAY");
    pushTempRule(rs);

    //Counting too many outsiders implies the existence of a baron
    //<PLAYER_1>is_OUTSIDER AND ... <PLAYER_[num outsider players]>is_OUTSIDER => <METADATA>is_BARON_in_PLAY
    setTempRuleParams(rs, baseOutsiders+1,1);
    
    setTempRuleResultName(rs, kb, -1, "METADATA", "is_BARON_in_PLAY"); 
    for (int j = 0; j < baseOutsiders+1; j++)
    {
        addConditionToTempRuleName(rs,kb, j, "PLAYERS", "is_OUTSIDER");
    }
    pushTempRule(rs);


    

    // ===========================================
    //  Dead rules
    // ===========================================
    //<PLAYER>died_by_HANGING AND <METADATA>is_NOT_SCARLET_WOMAN_in_PLAY=> <PLAYER>is_NOT_DEMON
    setTempRuleParams(rs, 2,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_DEMON");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "died_by_HANGING");
    addConditionToTempRuleName(rs,kb, 1, "METADATA", "is_NOT_SCARLET_WOMAN_in_PLAY");
    pushTempRule(rs);

    //If a player died: the player is dead
    for (int i = 0; i < 10; i++)
    {
        //<METADATA>died_NIGHT<i> => <PLAYER>is_DEAD
        setTempRuleParams(rs, 1,0);
        
        setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_DEAD");
        snprintf(buff, STRING_BUFF_SIZE, "died_NIGHT%d", i);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

    }
    
    // ===========================================
    //  Poison rules
    // ===========================================
    for (int i = 0; i < 10; i++)
    {
        //<METADATA>is_NOT_POISONER_in_PLAY => <PLAYER>is_NOT_poisoned_NIGHT<i>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_poisoned_NIGHT%d", i);
        setTempRuleResultName(rs, kb, -1, "PLAYERS", buff);
        addConditionToTempRuleName(rs,kb, 0, "METADATA", "is_NOT_POISONER_in_PLAY");
        pushTempRule(rs);

        //Contrapositive logic
        // <PLAYER>is_poisoned_NIGHT<i> => <METADATA>is_POISONER_in_PLAY
        setTempRuleParams(rs, 1,0);
        
        setTempRuleResultName(rs, kb, -1, "METADATA", "is_POISONER_in_PLAY");
        snprintf(buff, STRING_BUFF_SIZE, "is_poisoned_NIGHT%d", i);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        //<PLAYER>is_EVIL => <PLAYER>is_NOT_poisoned_NIGHT<i>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_poisoned_NIGHT%d", i);
        setTempRuleResultName(rs, kb, 0, "PLAYERS", buff);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_EVIL");
        pushTempRule(rs);

        //Contrapositive logic
        //<PLAYER>is_poisoned_NIGHT<i> => <PLAYER>is_GOOD
        setTempRuleParams(rs, 1,0);
        
        setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_GOOD");
        snprintf(buff, STRING_BUFF_SIZE, "is_poisoned_NIGHT%d", i);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

        //Only one player can be poisoned at once
        //<PLAYER_A>is_poisoned_NIGHT<i> => <PLAYER_B>is_NOT_poisoned_NIGHT<i>
        setTempRuleParams(rs, 1,0);
        
        snprintf(buff, STRING_BUFF_SIZE, "is_NOT_poisoned_NIGHT%d", i);
        setTempRuleResultName(rs, kb, -1, "PLAYERS", buff);
        snprintf(buff, STRING_BUFF_SIZE, "is_poisoned_NIGHT%d", i);
        addConditionToTempRuleName(rs,kb, 0, "PLAYERS", buff);
        pushTempRule(rs);

    }
    // ===========================================
    //  Red Herring rules
    // ===========================================
    //<PLAYER>is_REDHERRING => <PLAYER_Y>is_NOT_REDHERRING
    setTempRuleParams(rs, 2,0);
    
    setTempRuleResultName(rs, kb, -1, "PLAYERS", "is_NOT_REDHERRING");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_REDHERRING");
    pushTempRule(rs);

    //<PLAYER>is_REDHERRING => <PLAYER>is_GOOD
    setTempRuleParams(rs, 2,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_GOOD");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_REDHERRING");
    pushTempRule(rs);

    //Contrapositive logic
    //<PLAYER>is_EVIL => <PLAYER>is_NOT_REDHERRING
    setTempRuleParams(rs, 2,0);
    
    setTempRuleResultName(rs, kb, 0, "PLAYERS", "is_NOT_REDHERRING");
    addConditionToTempRuleName(rs,kb, 0, "PLAYERS", "is_EVIL");
    pushTempRule(rs);
}