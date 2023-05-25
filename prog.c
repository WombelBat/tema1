#include "player.h"
#include "teams.h"
#include "games.h"

#include "math.h"

void printObjectivesToFile()
{
    FILE *file = fopen("r.out", "wt");
    int *objectivess=malloc(sizeof(int)*5);
    getObjectives(&objectivess);
    TEAMLIST party;
    party = createLanParty();
    if (objectivess[0] == 1)
    {
        printToFile(party, file);
    }


    party = InitialCulling(party);
    if (objectivess[1] == 1)
    {
        fprintf(file,"\n\n\n\n");
        printToFile(party, file);
    }
    printf("\n%s \t%s\n",party.teams->next->TeamName,party.teams->next->next->TeamName);
    TEAMSTREE *finalist ;
    if (objectivess[2] == 1)
        playOutLanPartyPrint(party, &finalist, file);
    else
        playOutLanParty(party, &finalist);

    if (objectivess[3] == 1)
    {
        fprintf(file,"\n Clasament");
        printfBST(finalist,file);
    }
    if (objectivess[4] == 1)
    {
        fprintf(file,"\ncalsament la height=2\n");
        finalist=balanceTree(finalist);
        printTreeAtHeight(finalist,2,file);

    }

            fclose(file);
}

int main()
{
    printObjectivesToFile();

    return 0;
}