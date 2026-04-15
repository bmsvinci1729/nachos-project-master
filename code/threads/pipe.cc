#include "pipe.h"

#include <cstring>

#include "debug.h"

Descriptor::Descriptor(char *desType, char *permission, char *buffer,
                       bool ownsBuffer) {
    this->buf = buffer;
    this->desType = desType;
    this->permission = permission;
    this->currSeekPos = 0;
    this->ownsBuffer = ownsBuffer;
}

Descriptor::~Descriptor() {
    if (ownsBuffer && buf != NULL) {
        delete[] buf;
        buf = NULL;
    }
}

PipeDescriptors::PipeDescriptors() {
    for (int i = 0; i < MAX_NUM_DESCRIPTORS; i++) {
        descriptors[i] = NULL;
    }
}

int PipeDescriptors::createDes(int *x, int *y, char *desType) {
    if (x == NULL || y == NULL) return -1;

    int parentPd = -1;
    int childPd = -1;

    for (int i = 0; i < MAX_NUM_DESCRIPTORS; i++) {
        if (descriptors[i] == NULL) {
            if (parentPd < 0) {
                parentPd = i;
            } else {
                childPd = i;
                break;
            }
        }
    }

    if (parentPd < 0 || childPd < 0) return -1;

    char *pipeBuffer = new char[PIPE_BUFFER_SIZE];
    bzero(pipeBuffer, PIPE_BUFFER_SIZE);

    descriptors[parentPd] = new Descriptor(desType, (char *)"w", pipeBuffer, true);
    descriptors[childPd] = new Descriptor(desType, (char *)"r", pipeBuffer, false);

    *x = parentPd;
    *y = childPd;
    return 1;
}

int PipeDescriptors::readDes(int des, char *buf, int numBytes) {
    if (des < 0 || des >= MAX_NUM_DESCRIPTORS || buf == NULL || numBytes < 0) {
        return -1;
    }

    Descriptor *pDes = descriptors[des];
    if (pDes == NULL || strcmp(pDes->permission, "r") != 0) {
        return -1;
    }

    for (int i = 0; i < numBytes; i++) {
        buf[i] = pDes->buf[i];
    }
    return numBytes;
}

int PipeDescriptors::writeDes(int des, char *buf, int numBytes) {
    if (des < 0 || des >= MAX_NUM_DESCRIPTORS || buf == NULL || numBytes < 0) {
        return -1;
    }

    Descriptor *pDes = descriptors[des];
    if (pDes == NULL || strcmp(pDes->permission, "w") != 0) {
        return -1;
    }

    if (pDes->currSeekPos + numBytes > PIPE_BUFFER_SIZE) return -1;

    for (int i = 0; i < numBytes; i++) {
        pDes->buf[pDes->currSeekPos + i] = buf[i];
    }
    pDes->currSeekPos += numBytes;
    return numBytes;
}
