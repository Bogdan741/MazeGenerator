set(ALGORITHMS
    # astar.cpp
    # BFSSolver.cpp
    breadthfirstsearch.cpp
    depthfirstsearch.cpp
    # DFSSolver.cpp
    kruscal.cpp
    # mazesolveralgo.cpp
    prim.cpp
    spanningtreealgo.cpp
)

add_library(Algorithms STATIC ${ALGORITHMS})