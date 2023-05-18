#!/usr/bin/awk -f

BEGIN { 
    FS = " " # Defines field separator as a space
}

# Data extraction section
{
     if (FNR == 1) {  # For the first record in the file
        n = $1  # Assign the first field to 'n' (which represents the number of products)
        m = $2  # Assign the second field to 'm' (which represents the number of compounds)
    } else if (FNR == 2) {  # For the second record in the file
        for (i = 1; i <= n; ++i) V[i-1] = $i  # Assign the fields to the array 'V' (which represents the values of the products)
    } else if (FNR > 2 && FNR <= 2 + m) {  # For the records from the third to 'm+2' in the file
        C[FNR - 3] = $1  # Assign the first field to the array 'C' (which represents the cost of each compound)
        L[FNR - 3] = $2  # Assign the second field to the array 'L' (which represents the limit of each compound)
    } else {  # For the rest of the records in the file
        for (j = 1; j <= m; ++j) P[FNR - m - 3][j-1] = $j  # Assign the fields to the 2D array 'P' (which represents the proportions of compounds in each product)
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
