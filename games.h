#pragma once
#ifndef GAMES_H
#define _GAMES_H

#include "teams.h"
typedef struct games
{
    TEAM team1;
    TEAM team2;
    int status;
    struct games *next;
} GAMES;

typedef struct GamesQueue
{
    GAMES *front;
    GAMES *rear;
} GAMESQUEUE;

void AddGame(GAMESQUEUE *q, TEAM *team1, TEAM *team2);
GAMESQUEUE *createGameList(TEAMLIST teamsList);
void deleteGamesQueue(GAMESQUEUE *q);
void RunGame(TEAMLIST teams);
int countElements(TEAMLIST stack);
GAMESQUEUE *createGameListFromStack(TEAMLIST teamsList);
void addToFinalist(TEAMSTREE **finalist, TEAMLIST top);

int RunBracket(GAMESQUEUE *games, TEAMLIST *winners, TEAMLIST *losers);
TEAMLIST RunGameUntiln(TEAMLIST matches, int n);
TEAMLIST RunGameUntilnStack(TEAMLIST matches, int n);
void printQueueToFile(GAMESQUEUE *root, FILE *file);
void printWinnersToFile(TEAMLIST winners, FILE *file);
void playOutLanPartyPrint(TEAMLIST party, TEAMSTREE **finalists, FILE *file);
void playOutLanParty(TEAMLIST party, TEAMSTREE **finalists);
    

#pragma warning(pop)
#endif