#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tiny-AES-c/aes.h"
#include"keccak-tiny/keccak-tiny.h"
#include<sys/ptrace.h>
const size_t SHAKE_LEN=256;
const char ENC_FLAG[]="${enc_flag}";
const size_t FLAG_SIZE=${flag_len}-1;
struct AES_ctx ctx;
const char key[]="This is the key";
const char iv[]="This is the iv.";
char buf[512];
char buf2[512];
uint8_t sha3buf[4096];
static inline int hvdetect(){
  unsigned int  dummy = 0,out = 0;
  __asm volatile(
      "cpuid"
      :"=a" (dummy),
      "=b" (dummy),
      "=c" (out),
      "=d" (dummy)
      :"0"  (1),
      "1"  (0),
      "2"  (0)
      );
  return (out & 0x80000000);
}
static inline int dbgdetect(){
  int fail_cnt = 0;
  const int LOOP_NUM=2;
  for(int i=0;i<LOOP_NUM;++i){
    if(ptrace(PTRACE_TRACEME, 0, 0, 0) == -1)
      fail_cnt++;
  }
  if(fail_cnt == LOOP_NUM){
    return 1;
  }
  ptrace(PTRACE_DETACH, getpid(), 0, 0);
  return 0;
}
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
  if(hvdetect()){
    printf("You use hypervisor!\n");
    exit(1);
  }
  fgets(buf,255,stdin);
  memcpy(buf2,buf,256);
  for(int i=0;buf[i]!='\0';++i){
    if(buf[i]=='\n'){
      buf[i]='\0';
    }
  }
  AES_init_ctx_iv(&ctx,(uint8_t*)key,(uint8_t*)iv);
  
  shake256(sha3buf,SHAKE_LEN,buf2,strlen(buf2));
  {
    char tmp;
    for(int i=0;i<SHAKE_LEN/8;++i){
      tmp|=sha3buf[i];
    }
    if(tmp==0){
      printf("oops\n");
      exit(1);
    }
  }
  AES_CBC_encrypt_buffer(&ctx,(uint8_t*)buf,strlen(buf));
  if(dbgdetect()){
    printf("You use debugger!\n");
    exit(1);
  }
  if(memcmp(ENC_FLAG,buf,sizeof(ENC_FLAG))==0){
    win();
  }
  return 1;
}
