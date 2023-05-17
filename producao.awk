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
    for (i = 0; i < n; ++i) {
        if (i < n - 1) printf "%d X%d + ", V[i], i
        else printf "%d X%d;\n", V[i], i
    }

    # generate constraints
    for (j = 0; j < m; ++j) {
        printf "\n"
        for (i = 0; i < n; ++i) {
            if (i < n - 1) printf "%f X%d + ", P[i][j], i
            else printf "%f X%d <= %d;\n", P[i][j], i, L[j]
        }
    }

    # variable bounds
    printf "\n"
    for (i = 0; i < n; ++i) {
        printf "X%d >= 0;\n", i
    }
}

