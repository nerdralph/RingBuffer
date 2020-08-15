# maximum buffer size is 128
ringtest: ringtest.c
	$(CC) -DRINGBUFSIZE=128 -O $^ -o $@

test:
	./ringtest
