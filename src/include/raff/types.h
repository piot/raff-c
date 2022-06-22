/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef RAFF_TYPES_H
#define RAFF_TYPES_H

#include <stdint.h>
#include <stdlib.h>

typedef uint8_t RaffTag[4];

int raffTagEqual(RaffTag icon, RaffTag expectedIcon);
const char* raffTagToString(char* target, size_t count, RaffTag self);

#endif
