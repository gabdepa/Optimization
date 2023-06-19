# Superhero Grouping Problem Solver

This program solves the Superhero Grouping Problem using the Branch and Bound algorithm. The goal of the problem is to assign superheroes to different groups in such a way that conflicts between superheroes and affinities between superheroes are minimized.

## Problem Description

Given a set of superheroes and a set of conflicts and affinities between them, the program assigns each superhero to one of two groups to minimize the number of conflicts and maximize the number of satisfied affinities.

 - Conflicts: A conflict is a pair of superheroes that cannot be assigned to the same group.
 - Affinities: An affinity is a pair of superheroes that should be assigned to the same group.

## Program Structure

The program consists of the following functions:

- **`areInSameGroup(int a, int b)`**: Checks if superheroes 'a' and 'b' are in the same group.
- **`satisfiesAffinity()`**: Checks if all affinities are satisfied for the current group assignment.
- **`calculateConflicts()`**: Calculates the total number of conflicts for the current group assignment.
- **`bdada()`**: Custom bounding function using conflicts and triangles to evaluate the optimality of a group assignment.
- **`alternative_bounding_function()`**: Alternative bounding function that considers conflicts and affinities to evaluate the optimality of a group assignment.
- **`branch_and_bound(int i)`**: Recursive function implementing the Branch and Bound algorithm to search for the optimal group assignment.
- **`main()`**: Entry point of the program that reads the input, calls the Branch and Bound algorithm, and outputs the results.

## Usage

To compile and run the program, use the following command:

```
$ make

$ ./separa <OPTIONS> < example/<EXAMPLES>
```

Available options:

- **`f`**: Disable viability check. The program will not check if all affinities are satisfied.
- **`o`**: Disable optimality check. The program will not use the bounding function to prune the search tree.
- **`a`**: Use the alternative bounding function instead of the default bdada() function.

## Input Format

The program expects the input in the following format:

```
n k m
conflicts[0][0] conflicts[0][1]
conflicts[1][0] conflicts[1][1]
...
affinity[0][0] affinity[0][1]
affinity[1][0] affinity[1][1]
...
```

- **`n`**: The number of superheroes.
- **`k`**: The number of conflicts.
- **`m`**: The number of affinities.
- **`conflicts[i][0] conflicts[i][1]`**: The superheroes involved in the i-th conflict.
- **`affinity[i][0] affinity[i][1]`**: The superheroes involved in the i-th affinity.

## Output Format

The program outputs the following:

```
min_conflicts
best_group_assignment
```
- **`min_conflicts`**: The minimum number of conflicts achieved by the optimal group assignment.
- **`best_group_assignment`**: The superhero IDs assigned to the first group in the optimal group assignment.

## Example

Input:
```
4 2 2
1 3
2 4
1 2
3 4
```
Output:
```
0
1 2
```
The program assigns superhero 1 and superhero 2 to the first group, resulting in zero conflicts and satisfying all affinities.

## Performance

The program uses the Branch and Bound algorithm to solve the Superhero Grouping Problem. The performance of the program depends on the complexity of the input and the selected bounding function. The bdada() function and the alternative_bounding_function() function have different trade-offs in terms of conflicts and runtime. Experiment with different bounding functions and program options to find the best configuration for your specific problem instance.
