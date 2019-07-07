# SYDE_361

## Bongos.ino
- `getCurrentState()` reads and updates the state of each of the five sensors and calls `BiLinear()`
- `BiLinear(int a, int b, int c, int d, int e)` calculates the location of hit and determines whether it's Zone 1, Zone 2, or Zone 3, then sets `note` equal to the corresponding sound for that zone
- `check_drums()` is called after every 180 ms and sends MIDI messages when the state of a sensor has changed

#### Global Variables
- `const int threshold = 30`: Minimum force reading from sensors to produce a sound
- `int channel = 9`: MIDI channel to send messages on
- `ellapsedMillis timer = 0`:
- `int notes[] = {60,90,120}`: MIDI note numbers corresponding to Zones 1, 2 and 3, respectively
- `int note`:
- `int prev_state[] = {0,0,0,0,0}`:
- `int new_state[] = {0,0,0,0,0}`:
- `const double r = 11.0`: Radius from middle of senor 3 to outer sensors
- `const double arc = 17.2787`: One fourth arc distance between the outer sensors

## Bongos.scd
- Defines our bongo synth sound
- Contains a callback function that receives MIDI noteOn messages and plays the note

## elapsedMillis.h
