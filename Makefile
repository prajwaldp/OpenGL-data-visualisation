all:
	g++ -lGL -lGLU -lglut src/main.cpp -o bin/runner
	g++ -lGL -lGLU -lglut src/menu.cpp -o bin/menu
	g++ -lGL -lGLU -lglut src/text.cpp -o bin/text
