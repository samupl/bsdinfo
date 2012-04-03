target all:
	gcc -lkvm -lc bsdinfo.c -o bsdinfo

install:
	cp bsdinfo /usr/local/bin/bsdinfo

deinstall:
	rm /usr/local/bin/bsdinfo

clean:
	rm -rf bsdinfo



