all: swuser swuser_static

swuser: main.c
	gcc -Os -o $@ $<
	strip -s $@

swuser_static: main.c
	gcc -Os -fdata-sections -ffunction-sections -Wl,--gc-sections -static -o $@ $<
	strip -s $@

clean:
	rm -f swuser swuser_static

.PHONY: all clean
