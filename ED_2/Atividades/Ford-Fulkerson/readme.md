washington.c : A C language program to generate ten types of
networks/graphs. Contributed by seminar students working with
Richard Anderson. Compatible with the DIMACS format.

             To use:  cc washington.c -o gengraph
                      gengraph function arg1 arg2 arg3

             Command line arguments have the following meanings:

                      function:           index of desired graph type
                      arg1, arg2, arg3:   meanings depend on graph type
                                          (briefly listed below: see code
                                           comments for more info)

    	 Mesh Graph:          1 rows  cols  maxcapacity
     	 Random Level Graph:  2 rows  cols  maxcapacity
    	 Random 2-Level Graph:3 rows  cols  maxcapacity
    	 Matching Graph:      4 vertices  degree
    	 Square Mesh:         5 side  degree  maxcapacity
    	 Basic Line:          6 rows  cols  degree
                 Exponential Line:    7 rows  cols  degree
                 Double Exponential   8 rows  cols  degree

DinicBadCase: 9 vertices
(causes n augmentation phases)  
 GoldBadCase 10 vertices
Cheryian 11 dim1 dim2 range
(last 2 are bad for goldberg's algorithm)
