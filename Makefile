all: xlsreader.so

xlsreader.so: xlsreader.c
	gcc -o libxlsreader.so -fpic -shared xlsreader.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader

install: lrtest.so lrtest.lua
	cp xlsreader.so /usr/lib64
	cp xlsx_help.lua $(INST_LUADIR)

