all:
	gcc -g -o tgt src/tgt.c src/base/set.c src/base/mains.c src/file_edit/esfile.c src/logic/struct.c src/logic/draw.c src/visual/del_s.c
clean:
	rm tgt