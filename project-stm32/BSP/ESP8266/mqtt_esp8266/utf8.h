#ifndef __utf8__h
#define __utf8__h
char enc_utf8_to_unicode_one(unsigned char* pInput, unsigned char *Unic);
unsigned short ff_convert (  /* Converted code, 0 means conversion error */
  unsigned short  chr,  /* Character code to be converted */
  unsigned int  dir   /* 0: Unicode to OEMCP, 1: OEMCP to Unicode */
);
unsigned short  read_oem2uni(int i,unsigned int dir);
unsigned short u8f_gb2312(unsigned char* u8f_buf,unsigned char* gb2312_buf);
#endif//
