## Problem Formulation
We are given n superheroes numbered from 1 to n. We need to divide them into two groups such that all pairs with high affinity are in the same group and the number of pairs with conflicts in the same group is minimized.

## Data Structure
We need to keep track of conflict pairs and affinity pairs. A good data structure for this purpose would be a set or a list.

## Branching
For each superhero, we have two options: to put it in group 1 or group 2. We need to explore both options.

## Bounding
To evaluate each partial solution, we need to have bounding functions. One bounding function could be to calculate the number of conflicts within each group, while another (potentially better) bounding function can be devised by the students. A simple heuristic could be to prefer groupings with the least number of conflicts.