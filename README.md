# TerminalTuner
A lightweight CLI instrument tuner. Compatible with Linux, Mac and Windows. Great for quickly tunning your instrument.
It is precise and fast.

## How to build
Just run `make`.

## Dependencies needed to build
[PortAudio](http://www.portaudio.com) is a dependency and needs to be installed before build. 

## How to use
Run the command `./TerminalTuner` to execute the generated binary file. A list of available input devices will show up, if unsure just hit enter and it will automatically use the default input device.
When running it will show information about the current note, frequency and the targeted frequency for that note.

Example: `Note:E 4  330.15Hz / 329.63Hz`

## Compatibility
In theory it should be compatible with all operating systems considering that PortAudio is cross-platform, however only linux
has been tested.
