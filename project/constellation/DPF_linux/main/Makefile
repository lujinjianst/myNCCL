#CC = arm-linux-gcc
CC := gcc 
CFLAG := -g -Wall -I../../lib/libmad-0.15.0b -I../../lib/jpeg-8/ -I../../lib/freetype-2.3.11/include/
LDFLAG := -L../../lib/freetype-2.3.11/objs/.libs -L../../lib/jpeg-8/.libs -L../../lib/libmad-0.15.0b/.libs -ljpeg -lmad -lfreetype -lm

target := dpf

all:$(target)

$(target):main.o ../common/common.o ../mouse/mouse.o ../jpeg/jpeg.o ../jpeg/disp_jpeg.o ../mp3/play.o ../mp3/decode.o ../font/font.o ../jpeg/effects.o ../jpeg/welcome.o
	$(CC) main.o ../common/common.o ../mouse/mouse.o ../jpeg/jpeg.o ../jpeg/disp_jpeg.o ../jpeg/welcome.o ../mp3/play.o ../mp3/decode.o ../font/font.o ../jpeg/effects.o $(LDFLAG) -o $(target) 

main.o:main.c
	$(CC) -c main.c $(CFLAG) -o main.o

../common/common.o:../common/common.c
	$(CC) -c ../common/common.c $(CFLAG) -o ../common/common.o

../jpeg/jpeg.o:../jpeg/jpeg.c
	$(CC) -c ../jpeg/jpeg.c $(CFLAG) -o ../jpeg/jpeg.o

../jpeg/effects.o:../jpeg/effects.c
	$(CC) -c ../jpeg/effects.c $(CFLAG) -o ../jpeg/effects.o

../jpeg/disp_jpeg.o:../jpeg/disp_jpeg.c
	$(CC) -c ../jpeg/disp_jpeg.c $(CFLAG) -o ../jpeg/disp_jpeg.o

../jpeg/welcome.o:../jpeg/welcome.c
	$(CC) -c ../jpeg/welcome.c $(CFLAG) -o ../jpeg/welcome.o

../mouse/mouse.o:../mouse/mouse.c
	$(CC) -c ../mouse/mouse.c $(CFLAG) -o ../mouse/mouse.o

../mp3/play.o:../mp3/play.c
	$(CC) -c ../mp3/play.c $(CFLAG) -o ../mp3/play.o

../mp3/decode.o:../mp3/decode.c
	$(CC) -c ../mp3/decode.c $(CFLAG) -o ../mp3/decode.o

../font/font.o:../font/font.c
	$(CC) -c ../font/font.c $(CFLAG) -o ../font/font.o
clean:
	-rm -rf ../common/*.o ../common/*~
	-rm -rf ../jpeg/*.o ../jpeg/*~
	-rm -rf ../mouse/*.o ../mouse/*~
	-rm -rf ../mp3/*.o ../mp3/*~
	-rm -rf ../font/*.o ../font/*~
	-rm -rf *.o *~
	-rm -rf $(target)

.PHONY:clean
