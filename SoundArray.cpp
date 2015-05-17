#include "SoundArray.h"


SoundArray::SoundArray(unsigned int sz){
  size=sz;
  sounds=new sf::Sound[sz];
}

SoundArray::SoundArray(){
  //build array of sounds
  sounds=new sf::Sound[DEFAULT_SIZE];
  //build each sound
  sf::Sound sound00, sound01, sound02, sound03, sound04, sound05, sound06, sound07;
  sf::Sound sound08, sound09, sound10, sound11, sound12;
  //put sounds into the sound array
  sounds[0]=sound00;
  sounds[1]=sound01;
  sounds[2]=sound02;
  sounds[3]=sound03;
  sounds[4]=sound04;
  sounds[5]=sound05;
  sounds[6]=sound06;
  sounds[7]=sound07;
  sounds[8]=sound08;
  sounds[9]=sound09;
  sounds[10]=sound10;
  sounds[11]=sound11;
  sounds[12]=sound12;
  //build array of buffers
  buffers=new sf::SoundBuffer[DEFAULT_SIZE];
  //build corresponding buffers
  sf::SoundBuffer b00_horn, b01_yahoo, b02_break, b03_bird, b04_eat, b05_gate, b06_hit;
  sf::SoundBuffer b07_fly, b08_attacked, b09_coin, b10_diveWater, b11_jump, b12_swim;

  //put buffers into the buffer array
  buffers[0]=b00_horn;
  buffers[1]=b01_yahoo;
  buffers[2]=b02_break;
  buffers[3]=b03_bird;
  buffers[4]=b04_eat;
  buffers[5]=b05_gate;
  buffers[6]=b06_hit;
  buffers[7]=b07_fly;
  buffers[8]=b08_attacked;
  buffers[9]=b09_coin;
  buffers[10]=b10_diveWater;
  buffers[11]=b11_jump;
  buffers[12]=b12_swim;

}


void SoundArray::playSound(int i, std::string s){

  if (!buffers[i].loadFromFile(s + ".wav"))
        std::cout<<"error loading file"<<std::endl;
    sounds[i].setBuffer(buffers[i]);
    sounds[i].play();

    }


SoundArray::SoundArray(SoundArray &t){
  if (t.size){size=t.size;}
  else{size=t.DEFAULT_SIZE;}
  sounds= new sf::Sound[size];
  for(int i=0;i<size;i++){
    sounds[i]= t.sounds[i];
  }
}

SoundArray::~SoundArray(){

  delete sounds;
}

int SoundArray::getSize(){
  if (size) {return size;}
  else{return DEFAULT_SIZE;}
}


sf::Sound &SoundArray:: operator[] (int i){
  if (i>=0 and i<=(size-1)){
    return sounds[i];
  }
  else if(i<0){
    cout<<"----warning"<<endl;
    return sounds[0];
  }
  else{
    cout<<"warning"<<endl;
    return sounds[size-1];
  }
}