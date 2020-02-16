Basic Linux SDAT Player 1.3


to build: run "sh build.sh" while in the directory. portaudio is needed.

to run: run the executable in CLI with the SDAT passed as an argument. If no SDAT is specified, it will look for "platinum.sdat" in the directory

if a file is passed as an argument, the second argument will be the song number (first song if not defined). Putting any 3rd argument will trigger infinite looping.

Not all SDAT commands and features are implemented yet.

Changes in 1.3:
-General fixes and improvements
-Switched over to floats for some calculations

Changes in 1.2:
-Pitch Bend
-PSG (minus the noise channels)

Changes in 1.1:
-Stability fixes and less crashes
-Playback controls
-More logging of un-implemented features
