# CS170-grading-tools
Grading tools developed as a CS170 TA
The grading tools consist of a shell script which copies the contents from the "test" folder in to the other folders present.
After it is copied into the first folder, the batch file inside is then ran to check the test cases.
After the test cases are checked, it then compiles with a .cpp file that overloads the new and delete operators to check for memory leaks.
After the memory leak check, it then removes the compiled executable, exit that folder and repeats this process for the next folder.
This whole process ends when all the folders are checked.
