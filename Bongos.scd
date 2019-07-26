(
Server.default=s=Server.internal;
s.boot;
)

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

Synth(\Bongo) // Centre zone
Synth(\Bongo, [\amp, 5.4])
Synth(\Bongo, [\sustain, 0.7])

Synth(\Bongo, [\freq, 73.4, \amp, 1.0])  // Middle zone (38)
Synth(\Bongo, [\freq, 82.4, \amp, 1.0])  // Off center zone (40)
Synth(\Bongo, [\freq, 92.5, \amp, 1.0])  // Outer zone (42)

///////////////////////////////////////////

(
var notes, on, off;
notes = Array.newClear(128);

// MIDIClient.init; // Posts list of available devices
MIDIIn.connectAll;

on = MIDIFunc.noteOn({ |velocity, midinote, channel|
	notes[midinote] = Synth(\Bongo, [\freq, midinote.midicps, \amp, velocity * 0.2]);
	[\velocity,velocity, \midinote,midinote, \freq,midinote.midicps, \channel, channel].postln;
});

off = MIDIFunc.noteOff({ |velocity, midinote, channel|
	notes[midinote].release;
});

q = { on.free; off.free; };
)

// when done:
q.value;
