rm -rf *.so *.o fe
gcc -c -fPIC src/fe_math.c src/fe.c
gcc -o fe_math.so -shared -fPIC fe_math.o fe.o -lm
gcc -o fe src/fe.c -ldl -Wall -Wextra -pedantic -std=c89 -march=native -g
