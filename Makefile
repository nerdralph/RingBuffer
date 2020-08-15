# maximum buffer size is 128
ringtest: ringtest.c ringbuffer.c
	$(CC) -DRINGBUFSIZE=128 -O $^ -o $@

test:
	./ringtest
