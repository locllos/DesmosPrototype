#include "hdr/service.h"

char* getStringFormatNumber(int number)
{
    char* string_number = (char*)calloc(32, sizeof(char));

    sprintf(string_number, "%d", number);

    return string_number;
}