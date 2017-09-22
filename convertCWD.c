#include "main.h"
#include "string.h"

void convertCWD(char cwd[]){
  int i, flag=0, len = strlen(cwd), j;
  for(i=0; HOME[i]!='\0'; i++) {
    if(cwd[i]!=HOME[i]){
      flag = 1;
      break;
    }
  }
  if(flag==1){
    return;
  } else {
    char newCWD[len-i+3];
    newCWD[0]='~';
    for(j=1; i<len; i++, j++){
      newCWD[j] = cwd[i];
    }
    strcpy(cwd, newCWD);
  }
}
