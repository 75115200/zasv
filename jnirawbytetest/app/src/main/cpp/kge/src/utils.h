/**
* Author: taylorcyang@tencent.com
* Date:   2016-08-30
* Time:   17:06
* Life with Passion, Code with Creativity.
*/

#include <cstdint>
#include <sys/time.h>

namespace radio {

inline uint64_t currentTimeUs()
{
    struct timeval tv;
    ::gettimeofday(&tv, NULL);

    uint64_t usecondsSinceEpoch =
            static_cast<uint64_t>(tv.tv_sec) * 1000 * 1000 +
            static_cast<uint64_t>(tv.tv_usec);

    return usecondsSinceEpoch;
}

static constexpr int LEFT = 1;
static constexpr int RIGHT = 1 << 1;

/**
 * @param mono pcm buffer PCM16le
 * @param monoSize sizeOf mono buffer in bytes
 * @param stereo buffer to write data, it's length MUST >= 2 * monoSize
 * @param channelMask expand mono to left|right channel of the stereo data
 *
 * <pre>
 * mono
 * +---+---+---+---+
 * | 1 | 1 | 2 | 2 |
 * +---+---+---+---+
 *
 * stereo
 * +---+---+---+---+---+---+---+---+
 * |l1 |l1 |r1 |r1 |l2 |l2 |r2 |r2 |
 * +---+---+---+---+---+---+---+---+
 *
 * </pre>
 */
inline void mono2stereo(
        std::uint8_t *mono,
        std::size_t monoSize,
        std::uint8_t *stereo,
        int channelMask)
{
    for (std::size_t i = 0; i < monoSize; i += 2) {
        uint16_t *monoPcm16 = reinterpret_cast<uint16_t *>(mono + i);
        uint16_t *stereoPcm16 = reinterpret_cast<uint16_t *>(stereo + (i << 1));

        //left channel
        if (channelMask & LEFT) {
            *stereoPcm16 = *monoPcm16;
        }

        //right channel
        if (channelMask & RIGHT) {
            *(stereoPcm16 + 1) = *monoPcm16;
        }
    }
}

}
