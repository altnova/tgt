all:
	export TGT_HOME=/home/kid/arina/projects/tgt
	gcc -lpng -g -o tgt src/tgt.c src/base/set.c src/base/mains.c src/file_edit/esfile.c src/logic/struct.c src/logic/draw.c src/visual/del_s.c src/png/canvas.c src/gui/win.c

pngtk_t:
	gcc -lpng -g -o pngtk $(pkg-config --cflags --libs gtk+-3.0) src/gui/gui_main.c src/gui/win.c src/png/canvas.c

png_tk:
	./pngtk
	
clean:
	rm tgt