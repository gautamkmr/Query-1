 
Problem 1
 
You are given a list of queries (short whitespace-delimited multi-word text fragments, you can use an attached file problem1-input.txt). Please create a program that reads this list from a text file, the path to which will be given as the first command-line argument. The program should parse the input to create an appropriate data structure and then iterate over the following:
·         Read a line of input from STDIN. If EOF is read from STDIN, exit.
·         Referencing the data structure, print to STDOUT the queries from the text file containing all of the words in the input line regardless of order. Note that the order in which the queries are printed is unimportant; it does not have to reflect the order in which the queries occurred in the input list. Also note that case should be ignored.
 
For example, if the capital letters stand for words, and the input list is:
 
A B
B C
C D E
E D F
E F G H
 
then the following inputs (in bold below) on STDIN should produce the following outputs on STDOUT (where, again, the order in which the output queries are printed is unimportant).
 
A
A B
 
E
C D E
E D F
E F G H
 
D E
C D E
E D F
 
Please note that efficiency is important, as the input set might be quite large and there may be a user waiting for the output of the program.

Instruction: 
Compile:  g++ query1.cpp

Run:   ./a.out file_name

<Enter your Query>  
