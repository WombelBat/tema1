#include "teams.h"

int getAVGScore(TEAM team)
{
    int score = 0;
    for (int i = 0; i < team.nrPlayers; i++)
    {
        score += team.players[i].points;
    }
    score = score / team.nrPlayers;

    return score;
}

void addTeam(TEAM **head, FILE *file)
{
    TEAM *newNode = (TEAM *)malloc(sizeof(TEAM));

    fscanf(file, "%d", &newNode->nrPlayers);

    readStringFile(&newNode->TeamName, file, '\n');

    newNode->players = malloc(sizeof(PLAYER) * newNode->nrPlayers);
    for (int i = 0; i < newNode->nrPlayers; i++)
    {
        readStringFile(&newNode->players[i].firstName, file, ' ');
        readStringFile(&newNode->players[i].secondName, file, ' ');

        fscanf(file, "%d", &newNode->players[i].points);
    }

    newNode->next = *head;
    *head = newNode;
}

void addTeamTop(TEAM **top, TEAM data)
{
    TEAM *newTeam = (TEAM *)malloc(sizeof(TEAM));
    newTeam->players = (PLAYER *)malloc(sizeof(PLAYER) * data.nrPlayers);
    newTeam->nrPlayers = data.nrPlayers;
    newTeam->TeamName = (char *)malloc(sizeof(char) * (strlen(data.TeamName) + 1));
    strcpy(newTeam->TeamName, data.TeamName);

    for (int i = 0; i < data.nrPlayers; i++)
    {
        newTeam->players[i] = data.players[i];
    }
    if (top == NULL)
        newTeam->next = NULL;
    else
        newTeam->next = *top;
    *top = newTeam;
}

void deleteTeam(TEAM **head, char *teamName)
{
    if (*head == NULL)
    {
        return;
    }
    TEAM *current = *head, *previos = *head;
    if (!strcmp(current->TeamName, teamName))
    {
        *head = (*head)->next;
        free(current->players);
        free(current);
        return;
    }
    while (current != NULL)
    {
        if (!strcmp(current->TeamName, teamName))
        {
            previos->next = current->next;
            free(current->players);
            free(current);
            return;
        }
        previos = current;
        current = current->next;
    }
}

void deleteTeamStack(TEAM **top)
{
    TEAM *temp;
    while ((*top) != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

TEAMLIST createLanParty()
{
  
    FILE *file = fopen("d.in", "rt");
    TEAMLIST party;

    fscanf(file, "%d", &party.nrTeams);

    party.teams = malloc(sizeof(TEAM));
    party.teams->next = NULL;

    for (int k = 0; k < party.nrTeams; k++)
    {
        addTeam(&party.teams, file);
    }

    fclose(file);

    return party;
}


TEAMLIST InitialCulling(TEAMLIST teams)
{
    TEAMLIST current = teams;
    int power = (int)log2(teams.nrTeams);
    int nrOfTeams = pow(2, power);
    int minScor = 50000000;
    TEAM *minTeam;

    for (; teams.nrTeams > nrOfTeams; teams.nrTeams--)
    {
        do
        {
            int teamScore = 0;
            for (int i = 0; i < current.teams->nrPlayers; i++)
            {
                teamScore += current.teams->players[i].points;
            }
            teamScore = (int)teamScore / current.teams->nrPlayers;

            if (teamScore < minScor)
            {
                minScor = teamScore;
                minTeam = current.teams;
            }

            teamScore = 0;

            current.teams = current.teams->next;
        } while (current.teams->next != NULL);
        deleteTeam(&teams.teams, minTeam->TeamName);
        minScor = 50000000;
        current.teams = teams.teams;
    }

    return teams;
}

void readStringFile(char **string, FILE *file, char endInFile)
{
    int i = 0;
    *string = (char *)malloc(sizeof(char));

    while ((*string)[i - 1] != '\0')
    {
        (*string) = (char *)realloc((*string), sizeof(char) * (i + 1));
        fscanf(file, "%c", &((*string)[i]));
        if ((*string)[i] == endInFile)
            (*string)[i] = '\0';
        i++;
    }
}
void getObjectives(int **v)
{
    FILE *file = fopen("c.in", "rt");
    for (int i = 0; i < 5; i++)
    {
        fscanf(file, "%d", &(*v)[i]);
    }
    TEAMLIST party;
    for (int i = 0; i < 5; i++)
        printf("%d ", (*v)[i]);

    fclose(file);
}

void printToFile(TEAMLIST root,FILE *file)
{
    
    while (root.teams->next != NULL)
    {
        fprintf(file, "%s\n", root.teams->TeamName);

        root.teams = root.teams->next;
    }
 
   
}



TEAMSTREE *addTeamBST(TEAMSTREE *node, TEAM data)
{
    if (node == NULL)
    {
        node = malloc(sizeof(TEAMSTREE));
        node->team.nrPlayers = data.nrPlayers;
        node->team.TeamName = malloc(sizeof(char) * (strlen(data.TeamName) + 1));
        strcpy(node->team.TeamName, data.TeamName);
        node->team.players = malloc(sizeof(PLAYER) * data.nrPlayers);
        for(int i=0;i<data.nrPlayers;i++)
            node->team.players[i]=data.players[i];
     
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    int key = getAVGScore(data);
    int testVal = getAVGScore(node->team);

    if (key < testVal)
        node->left = addTeamBST(node->left, data);
    else if (key > testVal)
        node->right = addTeamBST(node->right, data);
    else if (strcmp(node->team.TeamName, data.TeamName) > 0)
        node->left = addTeamBST(node->left, data);
    else if (strcmp(node->team.TeamName, data.TeamName) < 0)
        node->right = addTeamBST(node->right, data);

    node = balanceTree(node);

    return node;
}
void printfBST(TEAMSTREE *root, FILE *file)
{
    if (root == NULL)
    {
        return;
    }
    printfBST(root->right, file);
    fprintf(file, " %s \t\t %d\n", root->team.TeamName, getAVGScore(root->team));
    printfBST(root->left, file);
}

int getBalance(TEAMSTREE *node)
{
    if (node == NULL)
        return 0;
    int heightL = getHeight(node->left);
    int heightR = getHeight(node->right);
    return heightL - heightR;
}

TEAMSTREE *rotateLeft(TEAMSTREE *node)
{
    TEAMSTREE *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}

TEAMSTREE *rotateRight(TEAMSTREE *node)
{
    TEAMSTREE *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

TEAMSTREE *balanceTree(TEAMSTREE *node)
{
    int balanceFactor = getBalance(node);

    if (balanceFactor > 1) 
    {
        if (getBalance(node->left) < 0) 
            node->left = rotateLeft(node->left);
        node = rotateRight(node);
    }
    else if (balanceFactor < -1) 
    {
        if (getBalance(node->right) > 0) 
            node->right = rotateRight(node->right);
        node = rotateLeft(node); 
    }

    return node;
}

int getHeight(TEAMSTREE *node)
{
    if (node == NULL)
        return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void traverseTreeAtHeight(TEAMSTREE *node, int currentHeight, int targetHeight, FILE *file)
{
    if (node == NULL)
        return;

    traverseTreeAtHeight(node->left, currentHeight + 1, targetHeight, file);

    if (currentHeight == targetHeight)
        fprintf(file,"%s\n",node->team.TeamName);

    traverseTreeAtHeight(node->right, currentHeight + 1, targetHeight, file);
}

void printTreeAtHeight(TEAMSTREE *root, int targetHeight, FILE *file)
{
    traverseTreeAtHeight(root, 1, targetHeight, file);
}