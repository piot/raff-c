/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include <raff/raff.h>
#include <raff/tag.h>

static uint8_t* read_whole_file(const char* filename)
{
    uint8_t* source = 0;
    FILE* fp = fopen(filename, "rb");
    if (fp == 0) {
        // SWAMP_LOG_INFO("errror:%s\n", filename);
        return 0;
    }
    if (fseek(fp, 0L, SEEK_END) != 0) {
        // SWAMP_LOG_INFO("seek err:\n");
        return 0;
    }

    long bufsize = ftell(fp);
    if (bufsize == -1) {
        // SWAMP_LOG_INFO("bufsize error\n");
        return 0;
    }

    source = malloc(sizeof(uint8_t) * (bufsize));

    if (fseek(fp, 0L, SEEK_SET) != 0) {
        // SWAMP_LOG_INFO("seek error\n");
        return 0;
    }

    size_t new_len = fread(source, sizeof(uint8_t), bufsize, fp);

    fclose(fp);

    return source;
}

int main(int argc, char* argv[])
{
    char buf[1024];

    uint8_t* data = read_whole_file("test.swamp-pack");

    RaffTag raffIcon, raffName;
    int count = raffReadHeader(data, 1024, raffIcon, raffName);
    if (count < 0) {
        return count;
    }
    data += count;
    printf("icon: %s\n", raffTagToString(buf, 1024, raffIcon));
    printf("name: %s\n", raffTagToString(buf, 1024, raffName));

    RaffTag icon, name;

    uint32_t chunkSize;
    count = raffReadChunkHeader(data, 1024, icon, name, &chunkSize);
    if (count < 0) {
        return count;
    }
    data += count;

    printf("icon: %s\n", raffTagToString(buf, 1024, icon));
    printf("name: %s\n", raffTagToString(buf, 1024, name));

    return 0;
}