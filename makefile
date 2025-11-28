all : complile link

complile :
	g++ -c main.cpp -I"C:\Program Files\SFML-2.5.1\include" -DSFML_STATIC

link :
	g++ main.o -o main -L"C:\Program Files\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean :
	rm -rf \*.o