#include <SD.h>
#include <TMRpcm.h>

#define SD_CS_PIN 10
#define SPEAKER_PIN 9

TMRpcm audio;

void setup() {
  Serial.begin(115200);
  audio.speakerPin = SPEAKER_PIN;
  if (!SD.begin(10)) {
    Serial.println("SD card initialization failed");
    return;
  }
  audio.quality(1);
  //audio.volume(1);
  //audio.volume(1);
  //audio.volume(1);
}


bool firstPlay = true;

void loop() {
  if (firstPlay){
    audio.play("song.wav");
    firstPlay = false;
  }
  
  if (not (audio.isPlaying())){
    audio.play("song.wav",4);
  }
  
}