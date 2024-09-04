#include "Fs.h"
char enc_get_utf8_size(char utf8){
  char temp=0;
  int i;
  for(i=0;i<6;i++){
    if(utf8 &(0x80>>i))
    {
      temp++;
    }
    else
    {
      break;
    }
    
  }
  return temp;
}

char enc_utf8_to_unicode_one(unsigned char* pInput, unsigned char *Unic)
{
  
    // b1 表示UTF-8编码的pInput中的高字节, b2 表示次高字节, ...
    char b1, b2, b3, b4, b5, b6;
  
    *Unic = 0x0; // 把 *Unic 初始化为全零
    char utfbytes = enc_get_utf8_size(*pInput);
    unsigned char *pOutput = (unsigned char *) Unic;
    switch ( utfbytes )
    {
        case 0:
            *pOutput     = *pInput;
            utfbytes++;
            break;
        case 2:
            b1 = *pInput;
            b2 = *(pInput + 1);
            if ( (b2 & 0xE0) != 0x80 )
                return 0;
            *pOutput     = (b1 << 6) + (b2 & 0x3F);
            *(pOutput+1) = (b1 >> 2) & 0x07;
            break;
        case 3:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b2 << 6) + (b3 & 0x3F);
            *(pOutput+1) = (b1 << 4) + ((b2 >> 2) & 0x0F);
            break;
        case 4:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b3 << 6) + (b4 & 0x3F);
            *(pOutput+1) = (b2 << 4) + ((b3 >> 2) & 0x0F);
            *(pOutput+2) = ((b1 << 2) & 0x1C)  + ((b2 >> 4) & 0x03);
            break;
        case 5:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            b5 = *(pInput + 4);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b4 << 6) + (b5 & 0x3F);
            *(pOutput+1) = (b3 << 4) + ((b4 >> 2) & 0x0F);
            *(pOutput+2) = (b2 << 2) + ((b3 >> 4) & 0x03);
            *(pOutput+3) = (b1 << 6);
            break;
        case 6:
            b1 = *pInput;
            b2 = *(pInput + 1);
            b3 = *(pInput + 2);
            b4 = *(pInput + 3);
            b5 = *(pInput + 4);
            b6 = *(pInput + 5);
            if ( ((b2 & 0xC0) != 0x80) || ((b3 & 0xC0) != 0x80)
                    || ((b4 & 0xC0) != 0x80) || ((b5 & 0xC0) != 0x80)
                    || ((b6 & 0xC0) != 0x80) )
                return 0;
            *pOutput     = (b5 << 6) + (b6 & 0x3F);
            *(pOutput+1) = (b5 << 4) + ((b6 >> 2) & 0x0F);
            *(pOutput+2) = (b3 << 2) + ((b4 >> 4) & 0x03);
            *(pOutput+3) = ((b1 << 6) & 0x40) + (b2 & 0x3F);
            break;
        default:
            return 0;
            break;
    }
    return utfbytes;
}
unsigned short  read_oem2uni(int i,unsigned int dir)
{
  if(dir)
  {
    File file = SPIFFS.open("/oem2uni.bin", "r");
    if(!file)
    {
        Serial.print("erro");  
    }
    unsigned short Temp;
    unsigned char temp_l,temp_h;
    file.seek(i * 2, SeekSet);
    file.read(&temp_l,1);
    file.read(&temp_h,1);
    Temp=(temp_h<<8)+temp_l;
    file.close();
    return  Temp; 
  }
  else
  {
    File file = SPIFFS.open("/uni2oem.bin", "r");
    if(!file)
    {
        Serial.print("erro");  
    }
    unsigned short Temp;
    unsigned char temp_l,temp_h;
    file.seek(i * 2, SeekSet);
    file.read(&temp_l,1);
    file.read(&temp_h,1);
    Temp=(temp_h<<8)+temp_l;
    file.close();
    return  Temp;      
  } 
}


unsigned short ff_convert (  /* Converted code, 0 means conversion error */
  unsigned short  chr,  /* Character code to be converted */
  unsigned int  dir   /* 0: Unicode to OEMCP, 1: OEMCP to Unicode */
)
{
  unsigned short c;
  int i, n, li, hi;
  if (chr < 0x80) { /* ASCII */
    c = chr;
  } else {
    if (dir) {    /* OEMCP to unicode */
      hi = 21792;
    } else {    /* Unicode to OEMCP */
      hi = 21792;
    }
    li = 0;
    for (n = 16; n; n--) {
      i = li + (hi - li) / 2;
      if (chr == read_oem2uni(2*i,dir)) break;
      if (chr > read_oem2uni(2*i,dir))
        li = i;
      else
        hi = i;
        //Serial.println("Times");
       // Serial.println(n);
        //Serial.println(2*i);
       // Serial.println(read_oem2uni(2*i,dir));
    }
    c = n ? read_oem2uni(2*i+1,dir) : 0;
  }

  return c;
}
unsigned short u8f_gb2312(unsigned  char* u8f_buf,unsigned char* gb2312_buf)
{
    int i=0;
    int j=0;
    int k=0;
    unsigned char buf[8];
    while(u8f_buf[i]!=0x00)
    {
        for(j=0;j<8;j++)
        {
          buf[j]=0x00;
        }
        i+=enc_utf8_to_unicode_one((u8f_buf+i),buf);
        for(j=0;j<8;j++)
        {
           if(buf[j]==0x00)
           {
              break;
           }
        }
        if(j==1) gb2312_buf[k++]=buf[0];
        else if(j==2)
        {
          unsigned short temp1=ff_convert((buf[1]<<8)+buf[0],0) ;
          gb2312_buf[k++]=temp1>>8;
          gb2312_buf[k++]=temp1;
        }
    }
    gb2312_buf[k++]=0x00;
    return k;
}
