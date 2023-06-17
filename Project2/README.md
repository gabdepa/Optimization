## Problem Formulation
We are given n superheroes numbered from 1 to n. We need to divide them into two groups such that all pairs with high affinity are in the same group and the number of pairs with conflicts in the same group is minimized.

## Data Structure
We need to keep track of conflict pairs and affinity pairs. A good data structure for this purpose would be a set or a list.

## Branching
For each superhero, we have two options: to put it in group 1 or group 2. We need to explore both options.

## Bounding
To evaluate each partial solution, we need to have bounding functions. One bounding function could be to calculate the number of conflicts within each group, while another (potentially better) bounding function can be devised by the students. A simple heuristic could be to prefer groupings with the least number of conflicts.

## Alternative Bounding Function
sing non-arbitrary weights requires a more strategic approach to bounding. One approach is to base the weights on the relative importance of minimizing conflicts versus preserving affinities. The goal is to make the estimate more accurate and reflective of the problem's constraints.

One way to determine weights is to consider the proportion of conflicts and affinities. If there are more conflicts than affinities, then we can increase the weight of the conflicts penalty. If there are more affinities, we can increase the weight of the affinity rewards.

Here we have normalized the weights of conflicts and affinities based on their relative proportions. This should offer a more balanced approach compared to using arbitrary weights. Please note that tweaking and experimenting with the bounding function is essential, and this example may not necessarily be the best bounding function for all instances of the problem. Developing a good bounding function often requires a deep understanding of the problem domain.
