#include "games.h"

void AddGame(GAMESQUEUE *q, TEAM *team1, TEAM *team2)
{

    GAMES *newNode = malloc(sizeof(GAMES));

    newNode->team1 = *team1;
    newNode->team2 = *team2;
    newNode->next = NULL;

    if (q->rear == NULL)
    {

        q->rear = newNode;
    }
    else
    {
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }

    if (q->front == NULL)
    {

        q->front = q->rear;
    }
}

void deleteGamesQueue(GAMESQUEUE *q)
{
    GAMES *temp;
    while (q->front != NULL)
    {
        temp = q->front;
        q->front = q->front->next;
        free(temp);
    }
    free(q);
}

GAMESQUEUE *createGameList(TEAMLIST teamsList)
{
    TEAMLIST temp = teamsList;
    GAMESQUEUE *q;

    q = malloc(sizeof(GAMESQUEUE));

    if (q == NULL)
    {
        printf("fail");
        return NULL;
    }

    q->front = q->rear = NULL;
    q->front = NULL;

    while (temp.teams->next != NULL)
    {

        AddGame(q, temp.teams, temp.teams->next);
        temp.teams = temp.teams->next;
   
        temp.teams = temp.teams->next;
   
    }

    return q;
}
GAMESQUEUE *createGameListFromStack(TEAMLIST teamsList)
{
    TEAMLIST temp = teamsList;
    GAMESQUEUE *q;
    q = malloc(sizeof(GAMESQUEUE));
    if (q == NULL)
    {
        printf("Failed");
        return NULL;
    }
    q->front = q->rear = NULL;
    while (temp.teams != NULL && temp.teams->next != NULL)
    {
        AddGame(q, temp.teams, temp.teams->next);
        temp.teams = temp.teams->next->next;
    }

    return q;
}
int RunBracket(GAMESQUEUE *games, TEAMLIST *winners, TEAMLIST *losers)
{
    GAMES *current = games->front;
    int i = 0; // reamaining teams
    int score1, score2;
    deleteTeamStack(&losers->teams);
    while (games->front != NULL)
    {
        i++;
        score1 = getAVGScore(games->front->team1);
        score2 = getAVGScore(games->front->team2);
        if (score1 < score2)
        {
            games->front->team2.players->points += games->front->team2.nrPlayers;
            addTeamTop(&winners->teams, games->front->team2);
            addTeamTop(&losers->teams, games->front->team1);
        }
        else
        {
            games->front->team1.players->points += games->front->team1.nrPlayers;
            addTeamTop(&(*winners).teams, games->front->team1);
            addTeamTop(&(*losers).teams, games->front->team2);
        }
        games->front = games->front->next;
    }
    i = i + 1;
    (*winners).nrTeams = i;
    (*losers).nrTeams = i;
    return i;
}


TEAMLIST RunGameUntiln(TEAMLIST matches, int n)
{
    GAMESQUEUE *games;
    games = createGameList(matches);
    TEAMLIST winners, losers;
    winners.teams = malloc(sizeof(TEAM));
    losers.teams = malloc(sizeof(TEAM));
    winners.teams->next = NULL;
    losers.teams->next = NULL;

    int teamsRemaining = matches.nrTeams;
    while (teamsRemaining > n)
    {
        teamsRemaining = RunBracket(games, &winners, &losers);

       
        deleteTeamStack(&losers.teams);
        deleteGamesQueue(games);
        games = createGameListFromStack(winners);
        if (teamsRemaining > n)
            deleteTeamStack(&winners.teams);
    }
    return winners;
}
TEAMLIST RunGameUntilnStack(TEAMLIST matches, int n)
{
    GAMESQUEUE *games;
    games = createGameListFromStack(matches);
    TEAMLIST winners, losers;

    winners.teams = malloc(sizeof(TEAM));
    losers.teams = malloc(sizeof(TEAM));
    winners.teams->next = NULL;
    losers.teams->next = NULL;

    int teamsRemaining = matches.nrTeams;
    while (teamsRemaining >= n)
    {
        teamsRemaining = RunBracket(games, &winners, &losers);

        deleteTeamStack(&losers.teams);
        deleteGamesQueue(games);
        games = createGameListFromStack(winners);
        deleteTeamStack(&winners.teams);
    }
    free(losers.teams);

    return winners;
}

void RunGame(TEAMLIST teams)
{
    int n = 8;
    GAMESQUEUE *party=createGameList(teams);
    TEAMLIST winners, losers;
    int l = 0;
    winners = RunGameUntiln(teams, n);
    GAMESQUEUE *queu = createGameListFromStack(winners);
    TEAMSTREE *finalist = malloc(sizeof(TEAMSTREE));
    finalist = malloc(sizeof(TEAMSTREE));
    addToFinalist(&finalist, losers);
}
void addToFinalist(TEAMSTREE **finalist, TEAMLIST top)
{
    TEAM *current = top.teams;
   
    while (current != NULL)
    {
        *finalist = addTeamBST(*finalist, *current);
        current = current->next;
    }
}

int countElements(TEAMLIST stack)
{
    int count = 0;
    TEAM *current = stack.teams;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void playOutLanPartyPrint(TEAMLIST party, TEAMSTREE **finalists, FILE *file)
{
    
    TEAMLIST losers, winnners;
    GAMESQUEUE *queue = createGameList(party);
    int nrRemainingTeams = party.nrTeams;
    int nrOfFinalists = 8;

    while(nrRemainingTeams > nrOfFinalists)
    {
        printQueueToFile(queue,file);
        RunBracket(queue,&winnners,&losers);
        printWinnersToFile(winnners,file);

        nrRemainingTeams=countElements(winnners);
        deleteGamesQueue(queue);
        queue=createGameListFromStack(winnners);

        if(nrRemainingTeams > nrOfFinalists)
        {
            deleteTeamStack(&winnners.teams);
        }
        deleteTeamStack(&losers.teams);
    }

    addToFinalist(&(*finalists),winnners);
    while (nrRemainingTeams > 1)
    {
        printQueueToFile(queue, file);
        RunBracket(queue, &winnners, &losers);
        printWinnersToFile(winnners, file);

        nrRemainingTeams = countElements(winnners);
        deleteGamesQueue(queue);
        queue = createGameListFromStack(winnners);

        addToFinalist(&(*finalists), losers);
        deleteTeamStack(&losers.teams);
        if(nrRemainingTeams <=1)
        {
            addToFinalist(&(*finalists),winnners);
        }
        deleteTeamStack(&winnners.teams);
    }


}

void playOutLanParty(TEAMLIST party, TEAMSTREE **finalists)
{

    TEAMLIST losers, winnners;
    GAMESQUEUE *queue = createGameList(party);
    int nrRemainingTeams = party.nrTeams;
    int nrOfFinalists = 8;

    while (nrRemainingTeams > nrOfFinalists)
    {
        
        RunBracket(queue, &winnners, &losers);
        

        nrRemainingTeams = countElements(winnners);
        deleteGamesQueue(queue);
        queue = createGameListFromStack(winnners);

        if (nrRemainingTeams > nrOfFinalists)
        {
            deleteTeamStack(&winnners.teams);
        }
        deleteTeamStack(&losers.teams);
    }

    addToFinalist(&(*finalists), winnners);
    while (nrRemainingTeams > 1)
    {
        
        RunBracket(queue, &winnners, &losers);
      

        nrRemainingTeams = countElements(winnners);
        deleteGamesQueue(queue);
        queue = createGameListFromStack(winnners);

        addToFinalist(&(*finalists), losers);
        deleteTeamStack(&losers.teams);
        if (nrRemainingTeams <= 1)
        {
            addToFinalist(&(*finalists), winnners);
        }
        deleteTeamStack(&winnners.teams);
    }
}

void printWinnersToFile(TEAMLIST winners, FILE *file)
{
    fprintf(file,"\n Winners of the round \n");
    while(winners.teams->next !=NULL)
    {
        fprintf(file, "%s \t %d\n", winners.teams->TeamName, getAVGScore(*winners.teams));
        winners.teams=winners.teams->next;
    }

}

void printQueueToFile(GAMESQUEUE *root,FILE *file)
{
    GAMESQUEUE *queue=root;
    fprintf(file,"\n CURRENT ROUND \n");
    while(queue->front!=NULL)
    {
        fprintf(file,"%s\t\t\t%s\n",queue->front->team1.TeamName,queue->front->team2.TeamName);

        queue->front=queue->front->next;
    }

}