current: main

main.o: main.cpp Engine.o Tile.o Engine.cpp Tile.cpp
	g++ -c -std=c++11 main.cpp

main: main.o main.cpp Engine.o HUD.o Map.o Character.o Cursor.o CharacterArray.o SoundArray.o Team.o Object.o
	g++ -o main main.o Engine.o HUD.o Tile.o Map.o SoundArray.o Character.o Cursor.o CharacterArray.o Team.o Object.o -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window -lsfml-network

Engine.o: Engine.cpp Engine.h Tile.h Tile.cpp SoundArray.h SoundArray.cpp HUD.h HUD.cpp
	g++ -c -std=c++11 Engine.cpp

Tile.o: Tile.cpp Tile.h
	g++ -c -std=c++11 Tile.cpp

Map.o: Map.cpp Map.h Tile.cpp Tile.h Object.h Object.cpp
	g++ -c -std=c++11 Map.cpp

Character.o: Character.h Character.cpp
	g++ -c -std=c++11 Character.cpp

Cursor.o: Cursor.h Cursor.cpp
	g++ -c -std=c++11 Cursor.cpp

Editor: Editor.o Editor.cpp Button.o Character.o Object.o Tile.o
	g++ -o Editor Editor.o Button.o Tile.o Object.o Character.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Editor.o: Editor.cpp
	g++ -c -std=c++11 Editor.cpp

Button.o: Button.cpp Button.h
	g++ -c -std=c++11 Button.cpp

CharacterArray.o: CharacterArray.h CharacterArray.cpp
	g++ -c -std=c++11 CharacterArray.cpp

SoundArray.o: SoundArray.h SoundArray.cpp
	g++ -c -std=c++11 SoundArray.cpp

Team.o: Team.cpp Team.h
	g++ -c -std=c++11 Team.cpp

TileGameUI.o: TileGameUI.cpp
	g++ TileGameUI.cpp -o TileGameUI -lsfml-graphics -lsfml-window -lsfml-system

Object.o: Object.cpp Object.h Tile.h Tile.cpp
	g++ -c -std=c++11 Object.cpp

HUD.o: HUD.cpp HUD.h
	g++ -c -std=c++11 HUD.cpp
