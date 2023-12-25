# CS170-grading-tools
Grading tools developed as a CS170 TA
The grading tool is using the depth first search approach in assessing child directories and executing the test cases.
This tool consist of a shell script which copies the contents from the "test" folder in to the other directories present in the same parent directory.
After it is copied into the first directory, the batch file inside is then ran to check the test cases.
After the test cases are checked, it then compiles with a .cpp file that overloads the new and delete operators to check for memory leaks.
After the memory leak check, it then removes the compiled executable, exit the child directory and repeats this process for the next directory in the parent directory.
This whole process ends when all the folders are checked.
