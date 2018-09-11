# SourceCopyHelp

This utility helps you to put comments in your source code. The utility works with a file list which you must place in the comments.txt file. If the executable file for this utility is in the same directory as the source files, you can list the source files relative to the utility's directory, otherwise list the files as full path names.
Do not bother yourself manually typing a large list of files into the comments.txt, rather use command-line options to list the files for you. For windows, under CMD console, type

dir /s /b

to produce a (full-path) list of all files in the current directory and sub-directories.

under linux use the command

find [dirname] -type f

substituting dirname with your directory or . for current directory

append the 
    > comments.txt
to direct the output to the comments.txt file.

Feel free to change the string to be patched to whatever you like but dont remove the copyright notice in the source code.

