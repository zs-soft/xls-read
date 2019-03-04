all: xlsreader.so

xlsreader.so: src/xlsreader.c
	gcc -o libxlsreader.so -fpic -shared src/xlsreader.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader

install: xlsreader.so xlsx_help.lua
	cp xlsreader.so /usr/lib64
	cp xlsx_help.lua $(INST_LUADIR)

