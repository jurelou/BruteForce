/**
    zipReader.hpp
    Purpose: parser for files based on zip format

    @author Louis JURCZYK
    @version 1.0 03/03/19
*/

#ifndef         _ZIPREADER_HPP_
#define         _ZIPREADER_HPP_

#include		<iostream>
#include        <fstream>

struct centralDirectory {
    uint32_t headerSignature;
    uint16_t versionMadeBy;
    uint16_t versionNeededToExtract;
    uint16_t bitFlag;
    uint16_t compressionMethod;
    uint16_t lastModFileTime;
    uint16_t lastModFileDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t fileNameLength;
    uint16_t extraFieldLength;
    uint16_t fileCommentLength;
    uint16_t diskNumberStart;
    uint16_t internalFileAttributes;
    uint32_t externalFileAttributes;
    uint32_t relativeOffset;
    char    *filename;
    char    *extraField;
    char    *fileComment;
    bool    isEncrypted;
    bool strongEncryption;
};

struct endOfCentralDirectory {

};

struct localFileHeader {

};

namespace   zipReader {
    void    readCentralDirectory(struct centralDirectory* dest, std::ifstream& file, const size_t offset);
}

#endif      /*_ZIPREADER_HPP_*/