#!/usr/bin/awk -f

BEGIN { 
    FS = " "  # Field separator is a space
}

# Data extraction section
{
    if (FNR == 1) {  # First line defines number of products and compounds
        n = $1  # Number of products
        m = $2  # Number of compounds
    } else if (FNR == 2) {  # Second line gives values of each product
        for (i = 1; i <= n; ++i) V[i-1] = $i
    } else if (FNR > 2 && FNR <= 2 + m) {  # Next 'm' lines give cost and limit of each compound
        C[FNR - 3] = $1
        L[FNR - 3] = $2
    } else {  # Remaining lines give proportions of compounds in each product
        for (j = 1; j <= m; ++j) P[FNR - m - 3][j-1] = $j
    }
}

# Convert output to lp_solve format
END {
    # Objective function to be maximized
    printf "max: "
    for (i = 0; i < n; ++i) {
        cost = 0
        for (j = 0; j < m; ++j) {
            cost += P[i][j] * C[j]
        }
        profit = V[i] - cost
        printf "%.1fx%d", profit, i + 1  # Print variable coefficient and index
        if (i < n - 1) {
            printf " + "
        }
    }
    printf ";\n"

    printf "\n"  # Print a newline for readability

    # Generate constraints
    for (j = 0; j < m; ++j) {
        for (i = 0; i < n; ++i) {
            printf "%.1fx%d", P[i][j], i + 1  # Print variable coefficient and index
            if (i < n - 1) {
                printf " + "
            } else {
                printf " <= %d;\n", L[j]  # Print constraint limit
            }
        }
    }

    # Print variable bounds
    printf "\n"  # Print a newline for readability
    for (i = 0; i < n; ++i) {
        printf "x%d >= 0;\n", i + 1  # Print variable index and lower bound
    }
}