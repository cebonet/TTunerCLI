# ttuner
A simple and lightweight CLI application. ttuner is an instrument tuner compatible with Linux, Mac and Windows. It is fast and precise. Great for quickly tunning your instrument !

## How to build
Just run `make`.

## Dependencies needed to build
[PortAudio](http://www.portaudio.com) is the only dependency needed and is provided in the lib folder. You may need to generate your own shared library if using another platform than Linux(64-bit). 

## How to use
Run the command `./ttuner` to execute the generated binary file. A list of available input devices will show up, if unsure just hit enter and it will automatically use the default input device.
When running it will show information about the current note, frequency and the targeted frequency for that note.

Example: `Note:E 4  330.15Hz / 329.63Hz`

## Compatibility
In theory it should be compatible with all operating systems considering that PortAudio is cross-platform, however only linux
has been tested.
