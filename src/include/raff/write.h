/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef RAFF_WRITE_H
#define RAFF_WRITE_H

#include <raff/types.h>

int raffWriteHeader(uint8_t* data, size_t maxCount);
int raffWriteChunkHeader(uint8_t* data, size_t maxCount, RaffTag icon, RaffTag tag, uint32_t chunkSize);

#endif
