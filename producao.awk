#!/usr/bin/awk -f

BEGIN { 
    FS = " " # field separator is a space
}

# variable extraction data
{
    if (FNR == 1) {
        n = $1
        m = $2
    } else if (FNR == 2) {
        for (i = 1; i <= n; ++i) V[i-1] = $i
    } else if (FNR > 2 && FNR <= 2 + m) {
        C[FNR - 3] = $1
        L[FNR - 3] = $2
    } else {
        for (j = 1; j <= m; ++j) P[FNR - m - 3][j-1] = $j
    }
}

# convert output to lp_solve format
END {
    # objective function to be maximized
    printf "max: "
    for (i = 0; i < n - 1; ++i) {
        printf "%dx%d + ", V[i], i
    }
    printf "%dx%d;\n", V[i], i

    printf "\n"

    # generate constraints
    for (j = 0; j < m; ++j) {
        for (i = 0; i < n - 1; ++i) {
            printf "%.1fx%d + ", P[i][j], i
        }
        printf "%.1fx%d <= %d;\n", P[i][j], i, L[j]
    }

    # variable bounds
    printf "\n"
    for (i = 0; i < n; ++i) {
        printf "x%d >= 0;\n", i
    }
}