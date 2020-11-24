#!/bin/bash

set -e

cd $(dirname $0)
gcc -Wall -Werror -Wextra main1.c get_next_line.c -o a.out || (echo COMPILATION FAILED && exit 1)

echo ">>>>>>>>>>> Sequential Read"
gcc -Wall -Werror -Wextra main2.c get_next_line.c -o a.out
gcc -Wall -Werror -Wextra main2_generator.c -o gen.out
./gen.out > ours
echo "our -end"
./a.out > yours || (echo EXECUTION FAILED && exit 1)
echo "your -end"
diff yours ours  || (echo FAILED && exit 1)
rm -f yours ours
rm -f a.out gen.out