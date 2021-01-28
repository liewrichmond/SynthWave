#include "SynthSound.h"

bool SynthSound::appliesToNote(int midiNoteNumber)
{
	return true;
}

bool SynthSound::appliesToChannel(int midiChannel)
{
	return true;
}
