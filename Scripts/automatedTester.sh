#!/bin/bash
echo "starting automated tester"
echo "use is <programName.sh>, <directoryToCreateName>, <executableName>"

                echo "creating directory named $1"
                mkdir $1
                cd $1
echo "cmake_minimum_required(VERSION 3.14)
	project(homework)

    # Using -Wall is required:
    add_compile_options(-Wall)

    # These compile flags are highly recommended, but not required:
    add_compile_options(-Wextra -Wpedantic)

# Create the executable hw0 from the source file main.cc:
    add_executable(hw0 hw0.cc)

# Create a tar file every time:
    add_custom_target(hw0.tar ALL COMMAND tar cf hw0.tar hw0.cc CMakeLists.txt)" > CMakeLists.txt;



                echo "renaming executable to $2"
                grep -rl 'hw0' ./ | xargs sed -i 's/hw0/'$2'/g'
                touch $2.cc
                cmake .
                make
                echo "#include <iostream> " > $2.cc
                echo " " >> $2.cc
                echo "using namespace std;" >>$2.cc
                echo "int main(int argc, char *argv[]){" >> $2.cc
                echo "cout << "hello world" << endl "
                echo "return 0; " >> $2.cc
                echo "}" >> $2.cc
                make


echo "#!/bin/bash
echo "starting automated tester"

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
echo "4" > valuesCheck
echo "15" >> valuesCheck
echo "-13" >> valuesCheck
echo "-10" >> valuesCheck
echo "37" >> valuesCheck
echo "1" >> valuesCheck
echo "0" >> valuesCheck
echo "246" >> valuesCheck
echo "70" >> valuesCheck
echo "9" >> valuesCheck
echo "40" >> valuesCheck
echo "face" >> valuesCheck

cmp values valuesCheck

file1="values"
file2="valuesCheck"

if cmp -s $file1 $file2; then
    printf 'The file "%s" is the same as "%s"\n' $file1 $file2
else
    printf 'The file "%s" is different from "%s"\n' $file1 $file2
fi" > tester.sh
chmod u=rxw tester.sh
