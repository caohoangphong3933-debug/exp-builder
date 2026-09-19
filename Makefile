all: exp.so

exp.so: minimal.c
	gcc -shared -fPIC -o exp.so minimal.c -I RedisModulesSDK -std=gnu99 -Wl,-E

clean:
	rm -f exp.so
