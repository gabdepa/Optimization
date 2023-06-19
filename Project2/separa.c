#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Global variables declaration
int n, k, m;
int conflicts[100][2];   // Array to store conflict pairs
int affinity[100][2];    // Array to store affinity pairs
int groups[100];         // Array to store group assignment for each superhero
int min_conflicts = 1e9; // Store minimum number of conflicts
int best_groups[100];    // Store best group configuration
bool disable_viability = false;
bool disable_optimality = false;
bool use_professors_bounding_function = false;
int nodes = 0; // Store number of nodes explored in the tree

// Function to check if superheroes 'a' and 'b' are in the same group
bool areInSameGroup(int a, int b)
{
    return (groups[a] == groups[b]);
}

// Function to check if all affinities are satisfied
bool satisfiesAffinity()
{
    for (int i = 0; i < m; i++)
    {
        if (!areInSameGroup(affinity[i][0], affinity[i][1]))
        {
            return false; // If any affinity is not satisfied, return false
        }
    }
    return true; // All affinities are satisfied
}

// Function to calculate total conflicts for the current group assignment
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

// Custom bounding function using conflicts and triangles
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
    // Check for triangles
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int l = 0; l < k; l++)
            {
                if (i == j || i == l || j == l)
                    continue; // Not a valid triangle
                int a1 = conflicts[i][0], b1 = conflicts[i][1];
                int a2 = conflicts[j][0], b2 = conflicts[j][1];
                int a3 = conflicts[l][0], b3 = conflicts[l][1];
                // Check if (a1, b1), (a2, b2), (a3, b3) form a triangle
                bool isTriangle = ((a1 == a2 && b1 == b3) || (a1 == b3 && b1 == a2) ||
                                   (a2 == a3 && b2 == b1) || (a2 == b1 && b2 == a3) ||
                                   (a3 == a1 && b3 == b2) || (a3 == b2 && b3 == a1));
                // Check if none of the superheroes in the conflicts have their groups chosen
                bool notInCe = (!groups[a1] && !groups[b1]) && (!groups[a2] && !groups[b2]) && (!groups[a3] && !groups[b3]);

                if (isTriangle && notInCe)
                {
                    te++;
                }
            }
        }
    }
    return ce + te;
}

int alternative_bounding_function()
{
    int conflicts_penalty = 0;
    int affinity_reward = 0;

    double conflict_weight = (double)m / (k + m); // normalize by total pairs
    double affinity_weight = (double)k / (k + m); // normalize by total pairs

    // Adding penalty for each conflict within the group
    for (int i = 0; i < k; i++)
    {
        int a = conflicts[i][0];
        int b = conflicts[i][1];
        if (groups[a] && groups[b] && groups[a] == groups[b])
        {
            conflicts_penalty += conflict_weight; // Use the normalized weight
        }
    }

    // Adding rewards for each affinity within the group
    for (int i = 0; i < m; i++)
    {
        int a = affinity[i][0];
        int b = affinity[i][1];
        if (groups[a] && groups[b] && groups[a] == groups[b])
        {
            affinity_reward += affinity_weight; // Use the normalized weight
        }
    }

    // The function tries to minimize the result, thus conflicts increase the value
    // while affinities decrease it.
    return conflicts_penalty - affinity_reward;
}

void branch_and_bound(int i)
{
    // Increment the number of nodes in the search tree
    nodes++;
    // If all superheroes are assigned to a group
    if (i == n + 1)
    {
        // Check if the current assignment satisfies all affinities, or viability check is disabled
        if ((!disable_viability && satisfiesAffinity()) || disable_viability)
        {
            // Calculate the number of conflicts for the current assignment
            int total_conflicts = calculateConflicts();

            // If the number of conflicts for the current assignment is less than
            // the minimum number of conflicts found so far, update the best groups
            if (total_conflicts < min_conflicts)
            {
                min_conflicts = total_conflicts;
                memcpy(best_groups, groups, sizeof(groups));
            }
        }
        return;
    }
    // Evaluate bounding function if optimality check is not disabled
    int bounding_function_result = 0;
    if (!disable_optimality)
    {
        bounding_function_result = use_professors_bounding_function ? bdada() : alternative_bounding_function();
    }
    // Prune if the bounding function result is not promising
    if (!disable_optimality && bounding_function_result >= min_conflicts)
    {
        return;
    }
    // Try putting superhero 'i' in group 1
    groups[i] = 1;
    branch_and_bound(i + 1);
    // Try putting superhero 'i' in group 2
    groups[i] = 2;
    branch_and_bound(i + 1);
    // Backtrack by resetting the group assignment for superhero 'i'
    groups[i] = 0;
}

int main(int argc, char *argv[])
{
    clock_t start_time = clock(); // Record start time

    // Parse command line arguments
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
        if (strcmp(argv[i], "-a") == 0)
        {
            use_professors_bounding_function = true;
        }
    }
    // Input reading
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 0; i < k; i++)
    {
        scanf("%d%d", &conflicts[i][0], &conflicts[i][1]);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &affinity[i][0], &affinity[i][1]);
    }

    // Start branch and bound
    branch_and_bound(1);

    // Output the minimum number of conflicts
    printf("%d\n", min_conflicts);
    // Output the best group assignment
    for (int i = 1; i <= n; i++)
    {
        if (best_groups[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    // Record end time and calculate time taken
    clock_t end_time = clock();
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Output diagnostic information
    fprintf(stderr, "Number of nodes in the tree: %d\n", nodes);
    fprintf(stderr, "Time taken: %f seconds\n", time_taken);

    return 0; // End program
}
