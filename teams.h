#pragma once
#ifndef TEAMS_H
#define _TEAMS_H

#include "player.h"
#include "math.h"


typedef struct TEAM
{
    int nrPlayers;
    char *TeamName;
    PLAYER *players;
    struct TEAM *next;
   
} TEAM;

typedef struct TEAMLIST
{
    int nrTeams;
    TEAM *teams;

} TEAMLIST;
typedef struct TeamsTree
{
    TEAM team;
    struct TeamsTree *left, *right;

} TEAMSTREE;

TEAMLIST createLanParty();
void deleteTeam(TEAM **head, char *teamName);
void addTeam(TEAM **head, FILE *file);
void addTeamTop(TEAM **top, TEAM data);
void deleteTeamStack(TEAM **top);
int getAVGScore(TEAM team);
TEAMLIST InitialCulling(TEAMLIST teams);


TEAMSTREE *addTeamBST(TEAMSTREE *node, TEAM data);
void printfBST(TEAMSTREE *root, FILE *file);
int getBalance(TEAMSTREE *node);
TEAMSTREE *rotateLeft(TEAMSTREE *node);
TEAMSTREE *rotateRight(TEAMSTREE *node);
TEAMSTREE *balanceTree(TEAMSTREE *node);
int getHeight(TEAMSTREE *node);
void traverseTreeAtHeight(TEAMSTREE *node, int currentHeight, int targetHeight, FILE *file);
void printTreeAtHeight(TEAMSTREE *root, int targetHeight, FILE *file);

void readStringFile(char **string, FILE *file, char endInFile);
void getObjectives(int **v);
void printToFile(TEAMLIST root, FILE *file);

#pragma warning(pop)
#endif