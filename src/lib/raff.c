/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <memory.h>
#include <raff/raff.h>
#include <stdio.h>

int raffReadMarker(const uint8_t* data, size_t count, RaffTag tag)
{
    if (count < 4) {
        return -2;
    }

    tag[0] = *data++;
    tag[1] = *data++;
    tag[2] = *data++;
    tag[3] = *data++;

    return 4;
}

int raffReadHeader(const uint8_t* data, size_t count, RaffTag icon, RaffTag name)
{
    if (count < 9) {
        return -2;
    }

    icon[0] = *data++;
    icon[1] = *data++;
    icon[2] = *data++;
    icon[3] = *data++;

    name[0] = *data++;
    name[1] = *data++;
    name[2] = *data++;
    name[3] = *data++;

    uint8_t suffix = *data++;

    if (suffix != 0x0a) {
        return -3;
    }

    return 9;
}

int raffReadChunkHeader(const uint8_t* data, size_t count, RaffTag icon, RaffTag name, uint32_t* chunkSize)
{
    if (count < 12) {
        return -2;
    }

    icon[0] = *data++;
    icon[1] = *data++;
    icon[2] = *data++;
    icon[3] = *data++;

    name[0] = *data++;
    name[1] = *data++;
    name[2] = *data++;
    name[3] = *data++;

    uint32_t t = 0;

    t |= *data++ << 24;
    t |= *data++ << 16;
    t |= *data++ << 8;
    t |= *data++;

    *chunkSize = t;

    return 12;
}

int raffTagEqual(RaffTag icon, RaffTag expectedIcon)
{
    return memcmp(icon, expectedIcon, sizeof(RaffTag)) == 0;
}

int raffReadAndVerifyHeader(const uint8_t* data, size_t count)
{
    RaffTag icon;
    RaffTag name;

    int encounteredCount = raffReadHeader(data, count, icon, name);
    if (encounteredCount < 9) {
        return -1;
    }

    RaffTag expectedIcon = {0xF0, 0x9F, 0xA6, 0x8A};
    int iconEqual = raffTagEqual(icon, expectedIcon);
    if (!iconEqual) {
        return -2;
    }

    RaffTag expectedName = {"RAFF"};
    int nameEqual = raffTagEqual(name, expectedName);
    if (!nameEqual) {
        return -3;
    }

    return 9;
}

const char* raffTagToString(char* target, size_t count, RaffTag self)
{
    snprintf(target, count, "'%c%c%c%c' (0x%02X,0x%02X,0x%02X,0x%02X)", self[0], self[1], self[2], self[3], self[0],
             self[1], self[2], self[3]);
    return target;
}

const char* raffTagToRawString(char* target, size_t count, RaffTag self)
{
    snprintf(target, count, "%c%c%c%c", self[0], self[1], self[2], self[3]);

    return target;
}
