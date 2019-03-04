all: xlslib libxlsreader.so

xlslib:lib_src/configure
	cd ./lib_src && pwd && make -i clean && chmod +x ./configure && ./configure && make && make install && cd ..

libxlsreader.so: src/xlsreader.c
	gcc -o libxlsreader.so -fpic -shared src/xlsreader.c -I/usr/local/libxls/include -L/usr/local/libxls/lib -lxlsreader

install: libxlsreader.so xlsx_help.lua
	cp libxlsreader.so /usr/lib64
	cp xlsx_help.lua $(INST_LUADIR)