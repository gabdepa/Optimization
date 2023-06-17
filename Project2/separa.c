#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

int n, k, m;
int conflicts[100][2];
int affinity[100][2];
int groups[100];
int min_conflicts = 1e9;
int best_groups[100];
bool disable_viability = false;
bool disable_optimality = false;
int nodes = 0;

bool areInSameGroup(int a, int b)
{
    return (groups[a] == groups[b]);
}

bool satisfiesAffinity()
{
    for (int i = 0; i < m; i++)
    {
        if (!areInSameGroup(affinity[i][0], affinity[i][1]))
        {
            return false;
        }
    }
    return true;
}

int calculateConflicts()
{
    int total_conflicts = 0;
    for (int i = 0; i < k; i++)
    {
        if (areInSameGroup(conflicts[i][0], conflicts[i][1]))
        {
            total_conflicts++;
        }
    }
    return total_conflicts;
}

int bdada()
{
    int ce = 0;
    int te = 0;
    for (int i = 0; i < k; i++)
    {
        int a = conflicts[i][0];
        int b = conflicts[i][1];
        if (groups[a] && groups[b] && groups[a] == groups[b])
        {
            ce++;
        }
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            for (int l = j + 1; l < k; l++)
            {
                int a1 = conflicts[i][0], b1 = conflicts[i][1];
                int a2 = conflicts[j][0], b2 = conflicts[j][1];
                int a3 = conflicts[l][0], b3 = conflicts[l][1];
                if (!groups[a1] && !groups[b1] && !groups[a2] && !groups[b2] && !groups[a3] && !groups[b3])
                {
                    te++;
                }
            }
        }
    }
    return ce + te;
}

void branch_and_bound(int i)
{
    nodes++;
    if (i == n + 1)
    {
        if ((!disable_viability && satisfiesAffinity()) || disable_viability)
        {
            int total_conflicts = calculateConflicts();
            if (total_conflicts < min_conflicts)
            {
                min_conflicts = total_conflicts;
                memcpy(best_groups, groups, sizeof(groups));
            }
        }
        return;
    }
    if (!disable_optimality && bdada() >= min_conflicts)
    {
        return;
    }
    groups[i] = 1;
    branch_and_bound(i + 1);
    groups[i] = 2;
    branch_and_bound(i + 1);
}

int main(int argc, char *argv[])
{
    clock_t start_time = clock();
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-f") == 0)
        {
            disable_viability = true;
        }
        if (strcmp(argv[i], "-o") == 0)
        {
            disable_optimality = true;
        }
    }
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < k; i++)
    {
        scanf("%d%d", &conflicts[i][0], &conflicts[i][1]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &affinity[i][0], &affinity[i][1]);
    }
    branch_and_bound(1);
    printf("%d\n", min_conflicts);
    for (int i = 1; i <= n; i++)
    {
        if (best_groups[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    fprintf(stderr, "Number of nodes in the tree: %d\n", nodes);
    fprintf(stderr, "Time taken: %f seconds\n", time_taken);
    return 0;
}
