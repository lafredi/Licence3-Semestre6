#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void assert_message(int cond, char* message){
    if(cond == 0 ){
      #ifdef WIN32
        printf("%s\n", message);
      #endif
      #ifdef UNIX
        perror(message);
      #endif
      exit(EXIT_FAILURE);
    }
}

void int_to_byte(unsigned int value, unsigned char buffer_byte[8]) {
  int i;

  for (i = 7; i >= 0; i--) {
    buffer_byte[i] = value & 1;
    value >>= 1;
  }
}

unsigned char toByte(unsigned char bits[]) {
  unsigned char b = 0;
  int i =0;
  for (i=0; i<8; i++) {
    b = (unsigned char) ((b << 1) + ((bits[i]) ? 1 : 0));
  }
  return b;
}
char* strndup(const char*  s)
{
    size_t slen = (size_t)strlen(s);
    char* copy;
    int n;
        n = slen;

    copy = malloc(n+1);

    if (copy)
    {
        memcpy(copy, s, n);
        copy[n] = 0;
    }

    return copy;
}
int convert_donmaine_name_to_label(char domaine_name[], char byts[]){
    char * label;
    int len;
    int index = 0;
    int i = 0;
    char* domaine_name_cp = strdup(domaine_name);

    assert_message( domaine_name != NULL, "Conot convert the domaine name, because its null.");
    label = strtok (domaine_name_cp, ".");
    while (label != NULL) {
        len = strlen(label);
        assert_message( len != 0 , "The label of domaine name is empty.");
        assert_message( len < 63, "The label of domaine name is bigger than 63 octets.");
        byts[index++] = len & 0x3f;
        for(i =0; i< len; i++){
            byts[index++] = label[i];
        }
        label = strtok (NULL, ".");
    }
    byts[index++] = 0;
    return index;
}
