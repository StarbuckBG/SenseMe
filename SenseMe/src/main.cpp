//#include <Arduino.h>
#include "ardumidi.h"

bool state = false;
const int limit = 970;
const int threshold = 5;
const int velocity = 127;
bool states[] = {false,false,false,false,false,false};
int pins[] = {A0, A1, A2, A3, A4, A5};
char notes[] = {MIDI_D, MIDI_A, MIDI_E, MIDI_C, MIDI_F, MIDI_B+MIDI_FLAT};

void setup(){
Serial.begin(115200);
}

void setNoteState(bool state, char note){
  if(state == true){
    midi_note_on(0, note, velocity);
    midi_note_on(0, note + 7, velocity);
    midi_note_on(0, note + MIDI_OCTAVE, velocity);
  }
  else{
    midi_note_off(0, note, velocity);
    midi_note_off(0, note + 7, velocity);
    midi_note_off(0, note + MIDI_OCTAVE, velocity);
  }
}

  void evaluateSignal(int pinIndex,int value){
    if (value <= limit && states[pinIndex] == false){
      states[pinIndex] = true;
      setNoteState(states[pinIndex], notes[pinIndex]);
    }
    else if (value > limit + threshold && states[pinIndex] == true){
      states[pinIndex] = false;
      setNoteState(states[pinIndex], notes[pinIndex]);
    }
  }



  void loop(){
    delay(10);
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++)
    {
      int signalValue = analogRead(pins[i]);
        evaluateSignal(i, signalValue);
      //  Serial.println(signalValue);
    }
  }
