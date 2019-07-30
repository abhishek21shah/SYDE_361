// Boots the server - must run first
(
Server.default=s=Server.internal;
s.boot;
)

// Modified from DrumSynths SC Example - SOS Drums by Renick Bell
// Defines our custom bongo synth
(
SynthDef(\Bongo,
	{arg out = 0, sustain = 0.4, drum_mode_level = 0.25,
	freq = 100, drum_timbre = 8.0, amp = 0.8;
	var drum_mode_sin_1, drum_mode_sin_2, drum_mode_pmosc, drum_mode_mix, drum_mode_env;
		var drum_reson;
		var output;

	drum_mode_env = EnvGen.ar(Env.perc(0.005, sustain), 1.0, doneAction: 2);
	drum_mode_sin_1 = SinOsc.ar(freq*0.8, 0, drum_mode_env * 0.5);
	drum_mode_sin_2 = SinOsc.ar(freq, 0, drum_mode_env * 0.5);
	drum_mode_pmosc = PMOsc.ar(	Saw.ar(freq*0.9),
								freq*0.85,
								drum_timbre/1.3,
								mul: drum_mode_env*5,
								add: 0);
	drum_mode_mix = Mix.new([drum_mode_sin_1, drum_mode_sin_2, drum_mode_pmosc]) * drum_mode_level;
		output = drum_mode_mix * 2 * amp;
		Out.ar(out, [output, output])
	}
).add
);

// To test the default synth sound
Synth(\Bongo)

// For playback exercise during user testing, run these lines of code
Synth(\Bongo, [\freq, 73.4, \amp, 1.0])  // Middle zone (MIDI note 38)
Synth(\Bongo, [\freq, 82.4, \amp, 1.0])  // Off center zone (MIDI note 40)
Synth(\Bongo, [\freq, 92.5, \amp, 1.0])  // Outer zone (MIDI note 42)

// Receives MIDI messages from the Teensy and turns notes on or off
// Frequency depends on frequency of the MIDI note received
// Amplitude depends on MIDI velocity received (multiplied by a scaling factor of 0.02)
// http://doc.sccode.org/Guides/UsingMIDI.html
(
var notes, on, off;
notes = Array.newClear(128); // To store the states of all notes

MIDIIn.connectAll; // Connects to all possible MIDI inputs

// Play note when noteOn message is received
on = MIDIFunc.noteOn({ |velocity, midinote, channel|
	notes[midinote] = Synth(\Bongo, [\freq, midinote.midicps, \amp, velocity * 0.02]);

	// Print the values for debugging
	[\velocity,velocity, \midinote,midinote, \freq,midinote.midicps, \channel, channel].postln;
});

// Stop playing note when noteOff message is received
off = MIDIFunc.noteOff({ |velocity, midinote, channel|
	notes[midinote].release;
});

// Function that frees the nodes so they can be used again
q = { on.free; off.free; };
)

// When done, run q
q.value;
