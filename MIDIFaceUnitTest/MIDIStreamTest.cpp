#include "pch.h"
#include "CppUnitTest.h"

#include <MIDIFace.h>

#include <fstream>
#include <iostream>

char header_only_data[MIDIHEADER_LENGTH] = { 'M', 'T', 'h', 'd', // 1: MIDI file header
                                            0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                                            0x00, 0x01, // 6: Multi-track file
                                            0x00, 0x02, // 8: 2 tracks
                                            0x00, 96 };  // 10: division 96

char two_tracks_data[46] = { 'M', 'T', 'h', 'd', // 1: MIDI file header
                            0x00, 0x00, 0x00, 0x06, // 4: Length = 6
                            0x00, 0x01, // 8: Multi-track file
                            0x00, 0x02, // 12: 2 tracks
                            0x00, 96, // 16: 96 time per quarter note
                            'M', 'T', 'r', 'k', // 20: First track
                            0x00, 0x00, 0x00, 0x08, // 24: 8 bytes long
                            0x00, 0x00, 0x00, 0x00, // 28: Delta-time to 0
                            0x00, 0x00, 0x00, 0x00, // 32: Playing C0
                            'M', 'T', 'r', 'k', // 36: Second track
                            0x00, 0x00, 0x00, 0x08, // 40: 8 bytes long
                            0x00, 0x00, 0x00, 0x00, // 44: Delta-time to 0
                            0x00, 0x00, 0x00, 0x00 }; // 48: Playing C0

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace MIDIFaceUnitTest
{
	TEST_CLASS(MIDIStreamTest)
	{
	public:

        TEST_METHOD(ImmutableStreamHeaderOk)
        {
            std::stringstream string;
            string << header_only_data;
            std::stringbuf* buffer = string.rdbuf();

            MIDI::Stream *stream = MIDI::Stream::Create(buffer);

            Assert::AreEqual(MIDIHEADER_LENGTH, (signed int)stream->get_size());
            Assert::AreEqual(stream->get_length(), (unsigned int)6);
            Assert::AreEqual(stream->get_format(), MIDI::StreamFormat::MultiTracks);
            Assert::AreEqual(stream->get_division(), (unsigned int)96);
        }

        TEST_METHOD(ImmutableStreamTracksNumber)
        {
            std::stringstream string;
            string << two_tracks_data;
            std::stringbuf* buffer = string.rdbuf();

            MIDI::Stream* stream = MIDI::Stream::Create(buffer);

            std::vector<MIDI::Track> tracks = stream->get_tracks();

            Assert::AreEqual(tracks[0].get_length(), (unsigned int)8);
            Assert::AreEqual(tracks[1].get_length(), (unsigned int)8);
        }
	};
}
