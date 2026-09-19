all: exp.so

exp.so: test.c
gcc -shared -fPIC -o exp.so test.c -I RedisModulesSDK -std=gnu99 -Wl,-E

clean:
rm -f exp.so
