# SYDE_361

## Bongos.ino

- Sensor(s) Triggered
`Read and store sensor values from the five pins`
- Threshold Validation
`Filter out all sensors below the threshold value`
- Store the filtered sensor readings

#### Global Variables
- `const int threshold = 30`: Minimum force reading from sensors to produce a sound
- `int channel = 9`: MIDI channel to send messages on
- `ellapsedMillis timer = 0`:
- `int notes[] = {63,63,60,63,63}`:
- `int note`:
- `int prev_state[] = {0,0,0,0,0}`:
- `int new_state[] = {0,0,0,0,0}`:

## Bongos.scd

## elapsedMillis.h
