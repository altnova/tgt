all:
	gcc -lpng -g -o bin/tgt src/cfg/tgt.c src/bsc/set.c src/fld/wfile.c src/bsc/mains.c src/fld/esfile.c src/lgc/struct.c src/lgc/draw.c src/vis/del_s.c src/gui/win.c src/png/canvas.c 

pngtk_t:
	gcc -lpng -g -o bin/pngtk $(pkg-config --cflags --libs gtk+-3.0) src/gui/gui_main.c src/gui/win.c src/png/canvas.c

png_tk:
	./pngtk
	
clean:
	rm bin/tgt