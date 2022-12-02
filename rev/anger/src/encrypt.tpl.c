#include<stdio.h>
#include<string.h>
#include"tiny-AES-c/aes.h"
char FLAG[1024]="${flag}";
const size_t BLOCK_SIZE_BYTE=128/8;
struct AES_ctx ctx;
const char key[]="This is the key";
const char iv[]="This is the iv.";
void win(){
  printf("you win!");
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
  size_t flag_len=strlen(FLAG);
  AES_init_ctx_iv(&ctx,(uint8_t*)key,(uint8_t*)iv);
  AES_CBC_encrypt_buffer(&ctx,(uint8_t*)FLAG,flag_len);
  print_string_literal(FLAG,(flag_len%BLOCK_SIZE_BYTE==0?flag_len:(flag_len/BLOCK_SIZE_BYTE+1)*BLOCK_SIZE_BYTE ));
}
