all: TP_GTK

TP_GTK: ./src/TP_GTK.cpp
	g++ -std=c++17 -o ./Debug/TP_GTK ./src/TP_GTK.cpp ./src/IconParser.cpp ./src/IconNames.cpp ./src/Product.cpp ./src/ProductParser.cpp ./src/ProductsList.cpp ./src/Recipe.cpp ./src/RecipesList.cpp ./src/Note.cpp ./src/NotesList.cpp `pkg-config --cflags --libs gtk+-3.0` -lgtk-3 -lglib-2.0 -lpango-1.0 -lepoxy -lGL -lglut -lGLEW
