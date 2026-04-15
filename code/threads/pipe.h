#ifndef PIPE_H
#define PIPE_H

#include "copyright.h"

#define PIPE_BUFFER_SIZE 2048
#define MAX_NUM_DESCRIPTORS 64

class Descriptor {
   public:
    Descriptor(char *desType, char *permission, char *buffer, bool ownsBuffer);
    ~Descriptor();

    char *buf;
    char *desType;
    char *permission;
    int currSeekPos;

   private:
    bool ownsBuffer;
};

class PipeDescriptors {
   public:
    PipeDescriptors();

    int createDes(int *x, int *y, char *desType);
    int readDes(int des, char *buf, int numBytes);
    int writeDes(int des, char *buf, int numBytes);

   private:
    Descriptor *descriptors[MAX_NUM_DESCRIPTORS];
};

#endif
