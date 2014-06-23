Problem:    minla
Rows:       43
Columns:    41 (25 integer, 25 binary)
Non-zeros:  354
Status:     INTEGER OPTIMAL
Objective:  totalDistance = 28 (MINimum)

   No.   Row name        Activity     Lower bound   Upper bound
------ ------------    ------------- ------------- -------------
     1 totalDistance
                                  28
     2 map[0]                      1             1             =
     3 map[1]                      1             1             =
     4 map[2]                      1             1             =
     5 map[3]                      1             1             =
     6 map[4]                      1             1             =
     7 injective[0]                1             1             =
     8 injective[1]                1             1             =
     9 injective[2]                1             1             =
    10 injective[3]                1             1             =
    11 injective[4]                1             1             =
    12 distance1[0,1]
                                   2            -0
    13 distance1[0,3]
                                   8            -0
    14 distance1[0,4]
                                   4            -0
    15 distance1[1,0]
                                   0            -0
    16 distance1[1,2]
                                   4            -0
    17 distance1[1,4]
                                   2            -0
    18 distance1[2,1]
                                   0            -0
    19 distance1[2,3]
                                   2            -0
    20 distance1[2,4]
                                   0            -0
    21 distance1[3,0]
                                   0            -0
    22 distance1[3,2]
                                   0            -0
    23 distance1[3,4]
                                   0            -0
    24 distance1[4,0]
                                   0            -0
    25 distance1[4,1]
                                   0            -0
    26 distance1[4,2]
                                   2            -0
    27 distance1[4,3]
                                   4            -0
    28 distance2[0,1]
                                   0            -0
    29 distance2[0,3]
                                   0            -0
    30 distance2[0,4]
                                   0            -0
    31 distance2[1,0]
                                   2            -0
    32 distance2[1,2]
                                   0            -0
    33 distance2[1,4]
                                   0            -0
    34 distance2[2,1]
                                   4            -0
    35 distance2[2,3]
                                   0            -0
    36 distance2[2,4]
                                   2            -0
    37 distance2[3,0]
                                   8            -0
    38 distance2[3,2]
                                   2            -0
    39 distance2[3,4]
                                   4            -0
    40 distance2[4,0]
                                   4            -0
    41 distance2[4,1]
                                   2            -0
    42 distance2[4,2]
                                   0            -0
    43 distance2[4,3]
                                   0            -0

   No. Column name       Activity     Lower bound   Upper bound
------ ------------    ------------- ------------- -------------
     1 x[0,0]       *              1             0             1
     2 x[0,1]       *              0             0             1
     3 x[0,2]       *              0             0             1
     4 x[0,3]       *              0             0             1
     5 x[0,4]       *              0             0             1
     6 x[1,0]       *              0             0             1
     7 x[1,1]       *              1             0             1
     8 x[1,2]       *              0             0             1
     9 x[1,3]       *              0             0             1
    10 x[1,4]       *              0             0             1
    11 x[2,0]       *              0             0             1
    12 x[2,1]       *              0             0             1
    13 x[2,2]       *              0             0             1
    14 x[2,3]       *              1             0             1
    15 x[2,4]       *              0             0             1
    16 x[3,0]       *              0             0             1
    17 x[3,1]       *              0             0             1
    18 x[3,2]       *              0             0             1
    19 x[3,3]       *              0             0             1
    20 x[3,4]       *              1             0             1
    21 x[4,0]       *              0             0             1
    22 x[4,1]       *              0             0             1
    23 x[4,2]       *              1             0             1
    24 x[4,3]       *              0             0             1
    25 x[4,4]       *              0             0             1
    26 d[0,1]                      1
    27 d[0,3]                      4
    28 d[0,4]                      2
    29 d[1,0]                      1
    30 d[1,2]                      2
    31 d[1,4]                      1
    32 d[2,1]                      2
    33 d[2,3]                      1
    34 d[2,4]                      1
    35 d[3,0]                      4
    36 d[3,2]                      1
    37 d[3,4]                      2
    38 d[4,0]                      2
    39 d[4,1]                      1
    40 d[4,2]                      1
    41 d[4,3]                      2

Integer feasibility conditions:

INT.PE: max.abs.err. = 0.00e+000 on row 0
        max.rel.err. = 0.00e+000 on row 0
        High quality

INT.PB: max.abs.err. = 0.00e+000 on row 0
        max.rel.err. = 0.00e+000 on row 0
        High quality

End of output
