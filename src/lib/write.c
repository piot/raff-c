/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <raff/write.h>

static int writeHeader(uint8_t* data, size_t maxCount, RaffTag icon, RaffTag name)
{
    if (maxCount < 8) {
        return -2;
    }

    *data++ = icon[0];
    *data++ = icon[1];
    *data++ = icon[2];
    *data++ = icon[3];

    *data++ = name[0];
    *data++ = name[1];
    *data++ = name[2];
    *data++ = name[3];

    return 8;
}

int raffWriteHeader(uint8_t* data, size_t maxCount)
{
    if (maxCount < 9) {
        return -2;
    }

    RaffTag expectedIcon = {0xF0, 0x9F, 0xA6, 0x8A};
    RaffTag expectedName = {"RAFF"};
    int headerCount = writeHeader(data, maxCount, expectedIcon, expectedName);

    data += headerCount;

    *data++ = 0x0a;

    return headerCount + 1;
}

static void writeUint32(uint8_t* data, uint32_t t)
{
    *data++ = (t >> 24) & 0xff;
    *data++ = (t >> 16) & 0xff;
    *data++ = (t >> 8) & 0xff;
    *data++ = t & 0xff;
}

int raffWriteChunkHeader(uint8_t* data, size_t maxCount, RaffTag icon, RaffTag tag, uint32_t chunkSize)
{
    if (maxCount < 8 + 4) {
        return -3;
    }

    int octetCount = writeHeader(data, maxCount, icon, tag);
    if (octetCount < 0) {
        return octetCount;
    }
    data += octetCount;

    writeUint32(data, chunkSize);

    return octetCount + 4;
}
