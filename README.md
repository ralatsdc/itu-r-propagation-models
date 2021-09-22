ln -s propa64.so libpropa64.so
gcc -Wall -g call_fun.c -L/(path) -lpropa64 -lm -o propa

example:
./propa tmr 10 10
