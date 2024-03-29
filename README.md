# RAFF

[![Actions Status](https://github.com/piot/raff-c/workflows/build%20linux/badge.svg)](https://github.com/piot/raff-c/actions)
[![Actions Status](https://github.com/piot/raff-c/workflows/build%20mac%20os/badge.svg)](https://github.com/piot/raff-c/actions)
[![Actions Status](https://github.com/piot/raff-c/workflows/build%20Windows/badge.svg)](https://github.com/piot/raff-c/actions)

Chunk file format inspired by [FourCC](https://en.wikipedia.org/wiki/FourCC), and its respective file formats such as [IFF](https://en.wikipedia.org/wiki/Interchange_File_Format).


## File Header

| type          | octets | name                                                                      |
| :------------ | -----: | :------------------------------------------------------------------------ |
| [Icon](#icon) |      4 | 0xF0, 0x9F, 0xA6, 0x8A [[1]](https://www.compart.com/en/unicode/U+1F98A). |
| FourCC        |      4 | 0x52, 0x41, 0x46, 0x46 (the string "`RAFF`")                              |
| LF            |      1 | 0x0a (LF)                                                                 |


## Chunk Header

| type                 |      octets | name                                                |
| :------------------- | ----------: | :-------------------------------------------------- |
| [Icon](#icon)        |           4 | Any UTF-8 Unicode compatible character (big endian) |
| FourCC               |           4 | Any alpha numerical characters [A-Z, a-z, 0-9]      |
| uint32  (big endian) |           4 | `ChunkSize`. Number of octets following.            |
| chunk                | `ChunkSize` | Implementation specific chunk.                      |


## Intra Chunk Divider

An intra chunk divider is an optional divider inside a chunk.

| type          | octets | name                                                |
| :------------ | -----: | :-------------------------------------------------- |
| [Icon](#icon) |      4 | Any UTF-8 Unicode compatible character (big endian) |

#### Icon
Recommended to be a UTF-8 encoded Unicode character, that is supported by [NerdFonts](https://www.nerdfonts.com/).
