#include "engine.h"

bool SaveStorageValue(const char* fileName, unsigned int position, int value){
  bool success = false;
  int dataSize = 0;
  unsigned int newDataSize = 0;
  unsigned char *fileData = LoadFileData(fileName, &dataSize);
  unsigned char *newFileData = NULL;

  if (fileData != NULL)
  {
    if (dataSize <= (position*sizeof(int)))
    {
      newDataSize = (position + 1)*sizeof(int);
      newFileData = (unsigned char *)RL_REALLOC(fileData, newDataSize);
      if (newFileData != NULL)
      {
        int *dataPtr = (int *)newFileData;
        dataPtr[position]=value;
      }
      else
      {
        TraceLog(LOG_WARNING, "FLIEIO: [%s] Failed to realloc data (%u), position in bytes (%u) bigger than actual file size", fileName, dataSize, position*sizeof(int));
        newFileData = fileData;
        newDataSize = dataSize;
      }
    }
    else
    {
      newFileData = fileData;
      newDataSize = dataSize;
      int *dataPtr = (int *)newFileData;
      dataPtr[position] = value;
    }

    success = SaveFileData(fileName, newFileData, newDataSize);
    RL_FREE(newFileData);
    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", fileName, value);
  }
  else
  {
    TraceLog(LOG_INFO, "FILEIO: [%s] File created successfully", fileName);
    dataSize = (position + 1)*sizeof(int);
    fileData = (unsigned char *)RL_MALLOC(dataSize);
    int *dataPtr = (int *)fileData;
    dataPtr[position] = value;
    success = SaveFileData(fileName, fileData, dataSize);
    UnloadFileData(fileData);
    TraceLog(LOG_INFO, "FILEIO: [%s] Saved storage value: %i", fileName, value);
  }
  return success;
}

int LoadStorageValue(const char * fileName, unsigned int position)
{
  int value = 0;
  int dataSize = 0;
  unsigned char *fileData = LoadFileData(fileName, &dataSize);
  if (fileData != NULL)
  {
    if (dataSize < ((int)(position*4))) TraceLog(LOG_WARNING, "FILEIO: [%s] Failed to find storage position: %i", fileName, position);
    else
    {
      int *dataPtr = (int *)fileData;
      value = dataPtr[position];
    }
    UnloadFileData(fileData);
    TraceLog(LOG_INFO, "FILEIO: [%s] Loaded storage value: %i", fileName, value);
  }
  return value;
}
