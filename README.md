# 2048_Solver
A 2048 AI Solver based on Expectimax Algorithm. Its success rate is over 90%.
The heuristics functions used will be explained below.

## 1. Weight heuristics

If you ask any 2048 expert for advice on this game, they may tell you to try to keep the maximum tile at the corner of the board so that it will not influence the merge of other small tiles. Actually, a better method is to keep all the large tiles at the edge of the board monotonically. In this way, not only they will not be obstacles to other small tiles, but also it is easier for themselves to merge into a larger one. 
In order to achieve this, a weight is set for each tile respectively:
 
<img width="134" alt="image" src="https://user-images.githubusercontent.com/57789409/133735456-4c6e25da-4d33-48e4-a5e6-1ebbdda96836.png">

_Figure 1: Weight for the grid_

This heuristic function returns the sum of each value in the tile multiplied by its weight accordingly.


## 2. Cluster heuristics
In order to make tiles easier to merge, we want more tiles with same value to cluster. The weight heuristics alone cannot guarantee that and sometimes the distance of two tiles with same value may be very long. That’s why a penalty mechanism is introduced so that one state may be prioritized if its smoothness is high. 
 
<img width="132" alt="image" src="https://user-images.githubusercontent.com/57789409/133735479-7976e15b-20fe-4a3b-993d-1f4f7d711478.png">

_Figure 2: One good example of cluster heuristics_

The penalty mechanism works simply by adding the difference between all the tiles and their neighbours. It will try to make large tiles to cluster and meanwhile have minor effect on small tiles so they can move and merge according to other effective heuristics.

## 3. Free tile heuristics
The number of empty tiles is also counted and returned as part of evaluation.

<img width="130" alt="image" src="https://user-images.githubusercontent.com/57789409/133737411-30ba8181-897c-4687-ad05-6a9bcc08f496.png">

_Figure 3: One good example of free tile heuristics_


## 4. Monotony heuristics
Monotony heuristics is a complement to the weight heuristics so that the arrangement of the edges will be more monotonic. If the last row and column is a geometric sequence, it is considered a better state.

<img width="126" alt="image" src="https://user-images.githubusercontent.com/57789409/133737883-08bf80b1-86c9-4cb1-aba4-d54887120ac3.png">

_Figure 4: One good example of monotony heuristics_


## Final evaluation heuristics

For now, after performing many tests, monotony heuristics has been temporaily abandoned, although it does help sometimes. The final evaluation heuristics is shown as follows:

<img width="1065" alt="image" src="https://user-images.githubusercontent.com/57789409/133735686-53ad0827-0cdd-40f9-8ad9-530983ace749.png">

