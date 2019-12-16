# A* pathfinder

## Features

Takes a maze availability grid ( B&W only ) and find the optimal path from chosen start cell to targetted cell.
Currently, the algorithm has two features and a upcoming third one :

### A* with cell-based motions 

The first A* will use cell-based motions, where the algorithm can only jump 1 cell from the
current one. This one is very trivial and a method everyone usually start with when implementing an A* algorithm.

### A* with line-based motions

Here the children should be generated so that a straight corridor is directly followed (ie children
can only be corners, intersections or dead-ends). The distance to the parent may not be 1 anymore. The children is in a 
defined direction at a calculated distance, and we go directly there instead of computing every cell on the way.

### Upcoming : A* with corridor-based motions

Here the children should be generated so that any corridor is directly followed (ie children
can only be intersections or dead-ends, but not simple corners).
For this one, since by construction the nodes can only be intersections or dead-end AND the starting and goal positions may be in the middle of a corridor.
It is necessary to add checks. ( and to reimplement the Point::show and Point::print methods )
