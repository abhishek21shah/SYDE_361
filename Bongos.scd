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
Synth(\Bongo, [\sustain, 0.7])
Synth(\Bongo, [\freq, 98])  // Middle zone
Synth(\Bongo, [\freq, 96])  // Outer zone

///////////////////////////////////////////

(
var radius = 10; // To be retrieved from BiLinear function?
var frequency, notes, on, off;
notes = Array.newClear(128);

if ((radius >= 0) && (radius < 4), { frequency = 100; },
	if ((radius >= 4) && (radius < 7), { frequency = 98; },
		if (radius >= 7, { frequency = 96; },)));

// MIDIClient.init; // Posts list of available devices
MIDIIn.connectAll;

on = MIDIFunc.noteOn({ |velocity, num, channel|
	notes[num] = Synth(\Bongo, [\freq, frequency, \amp, velocity *  0.00315]);
	[\velocity,velocity, \num,num, \freq,frequency, \channel, channel].postln;
	// What effects do num and freq have?

});

off = MIDIFunc.noteOff({ |velocity, num, channel|
	notes[num].release;
});

q = { on.free; off.free; };
)

// when done:
q.value;
