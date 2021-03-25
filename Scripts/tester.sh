#!/bin/bash
echo starting automated tester

#values is the output of your program
touch values;
#valuesCheck is what you want your program to produce
touch valuesCheck;

#this section is the command arguments you would type to 
#run your program with whatever values
./hw2 + 2 2 > values
./hw2 -d + 1 2 3 4 5 >> values
./hw2 -d - 1 2 3 4 5 >> values
./hw2 -h - 1 17 >> values
./hw2 -h - 100 0b101 0x19 017 >> values
./hw2 -o / 13 007 >> values
./hw2 -o / 7 13 >> values
./hw2 '*' 2 123 1 >> values
./hw2 @ 30 70 29 >> values
./hw2 - 0b1001 >> values
./hw2 -h + 64 >> values
./hw2 -h / 64206 >> values

#the values 4, 15 etc. are the values that will be placed into a file
#that are the correct outputs that you want your program to compare against
#the values below are compared to the command arguments you typed above
echo 4 > valuesCheck
echo 15 >> valuesCheck
echo -13 >> valuesCheck
echo -10 >> valuesCheck
echo 37 >> valuesCheck
echo 1 >> valuesCheck
echo 0 >> valuesCheck
echo 246 >> valuesCheck
echo 70 >> valuesCheck
echo 9 >> valuesCheck
echo 40 >> valuesCheck
echo face >> valuesCheck

cmp values valuesCheck

file1=values
file2=valuesCheck

if cmp -s  ; then
    printf 'The file %s is the same as %s\n'  
else
    printf 'The file %s is different from %s\n'  
fi
