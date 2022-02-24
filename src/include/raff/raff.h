/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef RAFF_RAFF_H
#define RAFF_RAFF_H

#include <stdint.h>
#include <stdlib.h>

#include <raff/types.h>

int raffReadHeader(const uint8_t* data, size_t count, RaffTag icon, RaffTag tag);
int raffReadChunkHeader(const uint8_t* data, size_t count, RaffTag icon, RaffTag tag, uint32_t* chunkSize);

int raffReadAndVerifyHeader(const uint8_t* data, size_t count);
int raffReadMarker(const uint8_t* data, size_t count, RaffTag tag);



#endif
