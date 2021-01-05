/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#ifndef RAFF_TAG_H
#define RAFF_TAG_H

#include <raff/types.h>

int raffTagEqual(RaffTag icon, RaffTag expectedIcon);

const char* raffTagToString(char* target, size_t count, RaffTag self);
const char* raffTagToRawString(char* target, size_t count, RaffTag self);

#endif
