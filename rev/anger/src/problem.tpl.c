#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tiny-AES-c/aes.h"
const char ENC_FLAG[]="${enc_flag}";
const size_t FLAG_SIZE=${flag_len}-1;
struct AES_ctx ctx;
const char key[]="This is the key";
const char iv[]="This is the iv.";
char buf[512];
void win(){
  printf("you win!\n");
  exit(0);
}
void print_hex(char *buf,size_t len){
  for(int i=0;i<len;++i){
    printf("%2.2x",(unsigned int)(buf[i])&0xff);
  }
  printf("\n");
}
void print_string_literal(char *buf,size_t len){
  for(int i=0;i<len;++i){
    printf("\\x%2.2x",(unsigned int)(buf[i])&0xff);
  }
  printf("\n");
}
int main(){
  printf("If win() function at %p is called, the input is the answer.\nlength of flag is %lu\n",win,FLAG_SIZE);
  fgets(buf,255,stdin);
  for(int i=0;buf[i]!='\0';++i){
    if(buf[i]=='\n'){
      buf[i]='\0';
    }
  }
  AES_init_ctx_iv(&ctx,(uint8_t*)key,(uint8_t*)iv);
  AES_CBC_encrypt_buffer(&ctx,(uint8_t*)buf,strlen(buf));
  if(memcmp(ENC_FLAG,buf,sizeof(ENC_FLAG))==0){
    win();
  }
  return 1;
}
