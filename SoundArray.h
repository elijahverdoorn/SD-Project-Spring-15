#ifndef _AUDIO_
#define _AUDIO_

#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
using namespace std;


class SoundArray{
public:
  sf::Sound *sounds;
  sf::SoundBuffer *buffers;
  int size;
  unsigned int DEFAULT_SIZE=30;
  SoundArray(unsigned int sz);
  SoundArray();
  SoundArray(SoundArray &t);
  ~SoundArray();
  int getSize();
  void playSound(int i, std::string s);
  sf::Sound &operator [](int i);
};

#endif // _AUDIO_