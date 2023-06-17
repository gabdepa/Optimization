#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int n, k, m;
int conflicts[100][2];
int affinity[100][2];
int groups[100];
int min_conflicts = 1e9;

bool areInSameGroup(int a, int b)
{
    return (groups[a] != 0 && groups[b] != 0 && groups[a] == groups[b]);
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

int bdada(int hero_index)
{
    int conflicts_in_same_group = 0;
    int triangle_count = 0;

    for (int i = 0; i < k; i++)
    {
        if (areInSameGroup(conflicts[i][0], conflicts[i][1]))
        {
            conflicts_in_same_group++;
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            for (int l = j + 1; l < k; l++)
            {
                if (groups[conflicts[i][0]] == 0 || groups[conflicts[i][1]] == 0 || groups[conflicts[j][0]] == 0 || groups[conflicts[j][1]] == 0 || groups[conflicts[l][0]] == 0 || groups[conflicts[l][1]] == 0)
                {
                    if ((conflicts[i][0] == conflicts[j][0] || conflicts[i][0] == conflicts[j][1] || conflicts[i][1] == conflicts[j][0] || conflicts[i][1] == conflicts[j][1]) && (conflicts[i][0] == conflicts[l][0] || conflicts[i][0] == conflicts[l][1] || conflicts[i][1] == conflicts[l][0] || conflicts[i][1] == conflicts[l][1]))
                    {
                        triangle_count++;
                    }
                }
            }
        }
    }

    return conflicts_in_same_group + triangle_count;
}

int alternative_bounding_function(int hero_index)
{
    // Implement the logic for the alternative bounding function
    return 0; // placeholder
}

void branch_and_bound(int i, int (*bounding_function)(int))
{
    if (i > n)
    {
        if (satisfiesAffinity())
        {
            int total_conflicts = calculateConflicts();
            if (total_conflicts < min_conflicts)
            {
                min_conflicts = total_conflicts;
            }
        }
        return;
    }

    if (bounding_function(i) >= min_conflicts)
    {
        return; // Bound the search space if the bounding function is higher than the minimum found
    }

    // Recursive call - place in group 1
    groups[i] = 1;
    branch_and_bound(i + 1, bounding_function);

    // Recursive call - place in group 2
    groups[i] = 2;
    branch_and_bound(i + 1, bounding_function);
}

int main(int argc, char *argv[])
{
    int (*bounding_function)(int) = bdada; // Default bounding function
    // Parse command-line arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            bounding_function = alternative_bounding_function;
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
    branch_and_bound(1, bounding_function);
    printf("%d\n", min_conflicts);
    return 0;
}
