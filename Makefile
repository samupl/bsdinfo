target all:
	gcc -lkvm -lc bsdinfo.c -o bsdinfo

xterm-256:
	gcc -lkvm -lc bsdinfo-xterm-256.c -o bsdinfo

install:
	cp bsdinfo /usr/local/bin/bsdinfo

deinstall:
	rm /usr/local/bin/bsdinfo

clean:
	rm -rf bsdinfo



