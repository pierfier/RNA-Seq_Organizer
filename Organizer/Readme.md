- Program that analyzes raw and summary Tuxedo data.
- A threshold value can be set to filter out the protein expression level based on average 
and standard deviation

------- Additional features ------

- Adding experiment functionality:
    
    Store multiple experiment data that allows for overlap check between common genes

    Allow different data files to be parsed for a type of experiment, 
    which means different kinds of data can be stored and analyzed

    In order for this to happen, there needs to be a standard way of parsing data
    The method will go as follows for each type of data:
    
    -> All data:

    - Tabs are used as delimiters, so that output and input files can be opened in Excel
    - First line is the header that will contain what is in each column. This is never read

    -> Raw Tuxedo data
        
        - The first column are the gene_id's (the unique name for each gene)
        - The next set of columns, depending on the number of replicates, are the control expression values
        - The next set of columns, again depending on the number of replicates, are the target expression values

    -> Summary Tuxedo data

        - The first column are the gene_id's (the unique name for each gene)
        - The next column are the fold change values, taken in as a string so there is no comparison capability
        - The next column are the p values, again taken in as a string so no comparison capability
