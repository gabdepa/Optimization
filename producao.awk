#!/usr/bin/awk -f

BEGIN { 
    FS = " " # Defines field separator as a space
}

# Data extraction section
{
    if (FNR == 1) {
        n = $1  # Get the number of products
        m = $2  # Get the number of compounds
    } else if (FNR == 2) {
        for (i = 1; i <= n; ++i) V[i-1] = $i  # Get values of products
    } else if (FNR > 2 && FNR <= 2 + m) {
        C[FNR - 3] = $1  # Get cost of compounds
        L[FNR - 3] = $2  # Get limits of compounds
    } else {
        for (j = 1; j <= m; ++j) P[FNR - m - 3][j-1] = $j  # Get proportions of compounds in products
    }
}

# convert output to lp_solve format
END {
    # Print objective function to be maximized
    printf "max: "
    for (i = 0; i < n - 1; ++i) {
        printf "%dx%d + ", V[i], i  # Print variable coefficient and index for all but last variable
    }
    printf "%dx%d;\n", V[i], i  # Print variable coefficient and index for the last variable

    printf "\n"  # Print a newline for readability

    # Generate constraints
    for (j = 0; j < m; ++j) {
        for (i = 0; i < n - 1; ++i) {
            printf "%.1fx%d + ", P[i][j], i  # Print variable coefficient and index for all but last variable in the constraint
        }
        printf "%.1fx%d <= %d;\n", P[i][j], i, L[j]  # Print variable coefficient, index and constraint limit for the last variable
    }

    # Print variable bounds
    printf "\n"  # Print a newline for readability
    for (i = 0; i < n; ++i) {
        printf "x%d >= 0;\n", i  # Print variable index and lower bound
    }
}
