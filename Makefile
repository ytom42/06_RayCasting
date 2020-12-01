all:
	gcc -L minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit main.c
	./a.out

# magick convert [-depth 8 -colors 16 -background while] -resize 64x64 test.png test.xpm