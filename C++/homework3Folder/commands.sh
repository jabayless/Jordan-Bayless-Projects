echo "running command: echo ToDay | ./hw3"
echo ToDay | ./hw3
echo "
"
echo "running command: echo YESterDaY | ./hw3 -f 'Day %d of the month of %B of the year %Y'"
echo YESterDaY | ./hw3 -f 'Day %d of the month of %B of the year %Y'
echo "
"
echo "running command: echo 2021.1 | ./hw3 -f 'Week-based year: %G%nConventional year: %Y'"
echo 2021.1 | ./hw3 -f 'Week-based year: %G%nConventional year: %Y'
echo "
"
echo "running command: ./hw3 -f"A day that will live in infamy: %A %B %e %Y" -v pearl"
./hw3 -f"A day that will live in infamy: %A %B %e %Y" -v pearl
echo "
"

echo "running command: ./hw3 -f"A day that will live in infamy: %A %B %e %Y" -v <pearl"
./hw3 -f"A day that will live in infamy: %A %B %e %Y" -v <pearl
echo "
"

echo "running command: ./hw3 -vi limits pearl"
./hw3 -vi limits pearl
echo "
"
echo "running command: cat pearl | ./hw3 -f '%04Y %b %d %a' -v limits"
cat pearl | ./hw3 -f '%04Y %b %d %a' -v limits
echo "
"