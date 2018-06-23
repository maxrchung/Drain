#include "Wav.hpp"
#include <sstream>

std::ostream& operator<<(std::ostream& os, const Wav& wav) {
	os << "chunkId: " << wav.chunkId << '\n';
	os << "chunkSize: " << wav.chunkSize << '\n';
	os << "format: " << wav.format << '\n';
	os << "subchunk1Id: " << wav.subchunk1Id << '\n';
	os << "subchunk1Size: " << wav.subchunk1Size << '\n';
	os << "audioFormat: " << wav.audioFormat << '\n';
	os << "numChannels: " << wav.numChannels << '\n';
	os << "sampleRate: " << wav.sampleRate << '\n';
	os << "byteRate: " << wav.byteRate << '\n';
	os << "blockAlign: " << wav.blockAlign << '\n';
	os << "bitsPerSample: " << wav.bitsPerSample << '\n';
	os << "subchunk2Id: " << wav.subchunk2Id << '\n';
	os << "subchunk2Size: " << wav.subchunk2Size << '\n';
	os << "size: " << wav.size << '\n';

	return os;
}