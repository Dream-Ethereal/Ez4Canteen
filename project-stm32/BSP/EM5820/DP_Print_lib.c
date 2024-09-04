#include "DP_Print_inc.h"

static unsigned char gucCheckPassWord=0;

void EM5820_init(void)
{
	//清除打印缓冲
	InitializePrint();

	//调整打印浓度 为30浓度
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x53);
	UART_SendByte(huart3, 0x54);
	UART_SendByte(huart3, 0x44);
	UART_SendByte(huart3, 0x50);
	UART_SendByte(huart3, 0x27);
	
}

/* 初始化打印机，清除打印缓冲 a*/
void InitializePrint(void)
{
	/* 初始化打印机，清除打印缓冲 */
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x40);
	gucCheckPassWord = 1;
}

void EM5820_printData(Order order)
{
	uint8_t text[100];

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"Ez4Canteen");

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"================================");

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "#%s", order.sortNum);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "%s", order.postscript);
	Print_ASCII((unsigned char*)text);

	SetBold(0x00);
	
	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1); //字体大小
	sprintf((char *)text, "下单时间: %s", order.completedTime);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(0);	//居左
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "备注：%s", order.remark);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	//Sel_Align_Way(0);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"        菜名      单价 数量 总价");
	//Print_ASCII((unsigned char*)"        0000      0000 0000 0000");
	for(int i = 0; i < order.goodsCount; i++)
	{
		InitializePrint();
		sprintf((char *)text, "%-18s %-2d  X%-2d %5s", order.goodsDetails[i].name, order.goodsDetails[i].price, order.goodsDetails[i].number, order.goodsDetails[i].amount);
		Print_ASCII((unsigned char*)text);
	}

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "总计：  ￥%s", order.amount);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	
	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "下单人：%s 先生/女士", order.userName);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "联系方式：%s", order.mobile);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	sprintf((char *)text, "订单编号：%s", order.orderNo);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"NOTICE");

	select_lines(2);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"拿到餐后，请尽快食用哦~");

	select_lines(2);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"商家联系电话：13587670731");

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//居中
	//SetCharacterSize(1, 1);	//字体大小
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	
	select_lines(4);
	InitializePrint();
	Print_ASCII((unsigned char*)" ");
}



/*
** 函数： void select_lines(uint8_t times)
** 参数： times  换行的次数
   功能： 换行
*/
void select_lines(uint8_t times)
{
	uint8_t i;
	for(i=1;i<=times;i++)
	{
		print_And_Line();  /* 单次换行 */ 
	}
	
}

/*
** 函数： void init_putstr(uint8_t *buf, unsigned char nsel)
** 参数： *buf  字符数据  nsel  对齐方式 0居左 1居中 2居右
   描述： print_show_str()函数中的部分代码进一步封装，
	 功能：	初始化打印机和对齐方式的选择 
*/
void  init_putstr(uint8_t *buf, unsigned char nsel)
{
		/* 初始化打印机 */
		InitializePrint();
	
		/* 0居左、1居中、2居右 */
		Sel_Align_Way(nsel);
		Print_ASCII(buf);
}


/* 每调用一次，打印位置向后移动一定字的符单位  a*/
void jump_lattice(void)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x09);
}
 
/* 打印缓冲区数据并向前推进一行  a*/
void print_And_Line(void)
{

	/* 发送一个换行符 */
	UART_SendByte(huart3, 0x0A);
}


/*
** 函数： Print_ASCII(unsigned char *buf)
** 参数： buf  要发送的字符串数据
   功能： 把要打印的字符串放入缓冲区 
*/
void Print_ASCII(unsigned char *buf)
{
	while(*buf != '\0')
    {
    	UART_SendByte(huart3, *buf++);
    }   
}


/* 设置字符右侧的间距为interval X 0.125mm a*/
void Set_Right_Interval(unsigned char interval)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x20);
	UART_SendByte(huart3, interval);
}


/* 选择打印模式 a*/
void Set_Print_Mode(unsigned char optbit)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x21);
	UART_SendByte(huart3, optbit);
}

/* 设定从一行的开始到将要打印字符的位置距离为(Lpos+Hpos*256)*0.125mm  a*/
void Set_Print_Position(unsigned char Lpos,unsigned char Hpos)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x24);
	UART_SendByte(huart3, Lpos);
	UART_SendByte(huart3, Hpos);
}


/*
设置左边间距 a
*/
void Set_Left_Interval(unsigned char nL, unsigned char nH)
{
	if(!gucCheckPassWord)
		return;


	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, nL);
	UART_SendByte(huart3, nH);
}

/* 选择/取消用户自定义字符集  a*/
void Sel_Custom_Character(unsigned char SelOpt)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x25);
	UART_SendByte(huart3, SelOpt);
}
/* 用户自定义字符集 a*/
void UserDefineCharacter(unsigned char yByte,unsigned char xDot, unsigned char DefChar,unsigned char *pData)
{
	unsigned short int len;
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x26);
	UART_SendByte(huart3, yByte);
	UART_SendByte(huart3, DefChar);
	UART_SendByte(huart3, DefChar);
	UART_SendByte(huart3, xDot);
	len = yByte*xDot;
	while(len)
	{
		UART_SendByte(huart3, *pData++);
		len--;
	}
}

/* 选择位图模式 a*/
void Sel_Bitmap_Mode(unsigned char mode,unsigned char DatLenLowByte,unsigned char DatLenHightByte,unsigned char *pDotData)
{
	unsigned short int i;
	
	if(!gucCheckPassWord)
		return;
	
	if((mode!=0) && (mode!=1) && (mode!=32) && (mode!=33))
		return;
	
	if(DatLenHightByte > 3)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x2A);
	UART_SendByte(huart3, mode);
	UART_SendByte(huart3, DatLenLowByte);
	UART_SendByte(huart3, DatLenHightByte);
	
	i=DatLenLowByte + DatLenHightByte*256;
	
	while(i)
	{
		UART_SendByte(huart3, *pDotData++);
		i--;
	}
}

/* 设置下划线有无及规格  a*/
void Set_UnderLine(unsigned char Opt)
{
	if(!gucCheckPassWord)
		return;
	
	if(Opt > 2)
	{
		Opt=2;
	}
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x2D);
	UART_SendByte(huart3, Opt);
}

/* 设置缺省行间距3.75mm  a*/
void SetDefaultLineInterval(void)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x32);
}

/* 取消自定义字符  a*/
void Del_UserDefineCharacter(unsigned char SelCharacter)
{
	if(!gucCheckPassWord)
		return;
	if((SelCharacter < 32) || (SelCharacter > 126))
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x3F);
	UART_SendByte(huart3, SelCharacter);
}


/* Position 水平定位位置（设置横向跳格位置） a */
void SetHorizPosition(unsigned char Position)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x44);
	UART_SendByte(huart3, Position);
	UART_SendByte(huart3, Position);
	UART_SendByte(huart3, 0x00);
}

/* 选择/取消加粗模式 a*/
void SetBold(unsigned char opt)
{
	if(!gucCheckPassWord)
		return;
	if(opt>0x01)
	{
		opt=0x01;
	}
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x45);
	UART_SendByte(huart3, opt);
}
/* 打印并进纸nstep*0.125mm  a*/
void PrintGoPage(unsigned char nstep)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x4A);
	UART_SendByte(huart3, nstep);
}
/* 选择语言字符 a*/  
void SelCountryCharacter(unsigned char nsel)
{
	if(!gucCheckPassWord)
		return;
		
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x74);
	UART_SendByte(huart3, nsel);
}

/* 选择/取消顺时针旋转 90°  a*/
void Set_Rotate(unsigned char nsel)
{
	if(!gucCheckPassWord)
		return;
	
	if(nsel>1)
	{
		nsel=1;
	}
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x56);
	UART_SendByte(huart3, nsel);
}


/* 选择对齐方式 a*/
void Sel_Align_Way(unsigned char nsel)
{
	if(!gucCheckPassWord)
		return;
	
	if(nsel > 2)
	{
		nsel = 2;
	}
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x61);
	UART_SendByte(huart3, nsel);
}

/* 选择/取消倒置打印模式  a*/
void SetReversal(unsigned char nsel)
{
	if(!gucCheckPassWord)
		return;
	
	if(nsel > 1)
	{
		nsel = 1;
	}
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x7B);
	UART_SendByte(huart3, nsel);
	
}

/* 设置/选择字符大小 a*/
void SetCharacterSize(unsigned char width,unsigned char hight)
{
	if(!gucCheckPassWord)
		return;
	
	if(width > 7)
	{
		width = 7;
	}
	if(hight > 7)
	{
		hight = 7;
	}
	
	hight = hight&0x0f;
	width = (width&0x0f)<<4;
	width = width | hight;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x21);
	UART_SendByte(huart3, width);
	
}

/* 定义下载位图 */
void DownLoadBitmap(unsigned char xDot,unsigned char yDot,unsigned char *pDat)
{
	unsigned short int len;
	
	if(!gucCheckPassWord)
		return;
	
	if(yDot > 48)
		return;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x2A);
	UART_SendByte(huart3, xDot*8);
	UART_SendByte(huart3, yDot*8);
	len = xDot*yDot/8;
	
	while(len)
	{
		UART_SendByte(huart3, *pDat++);
		len--;
	}
	
}
/* 打印下载位图 */
void PrintDownLoadBitmap(unsigned char mode)
{
	if(!gucCheckPassWord)
		return;
	
	if(mode > 3)
	{
		mode = 3;
	}	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x2F);
	UART_SendByte(huart3, mode);
}

/* 黑白反显打印  a*/
void Set_Inverse(unsigned char opt)
{
	if(!gucCheckPassWord)
		return;
	
	if(opt>1)
	{
		opt=1;
	}
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x42);
	UART_SendByte(huart3, opt);
}


/* 设置左边距 a*/
void Set_LeftSpaceNum(unsigned char nL,unsigned char nH)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, nL);
	UART_SendByte(huart3, nH);
}


/* 选择 HRI 字符的打印位置 a*/
void Set_HRIPosition(unsigned char opt)
{
	if(!gucCheckPassWord)
		return;
	
	if(opt>3)
	{
		opt=3;
	}
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x48);
	UART_SendByte(huart3, opt);
}

/* 选择条码高度 a*/
void Set_BarCodeHight(unsigned char verticalDotNum)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x68);
	
	UART_SendByte(huart3, verticalDotNum);
}


/*  打印条码 a*/
void PrintBarCode(unsigned char CodeType,unsigned char *pData,unsigned char pDataLen)
{
	if(!gucCheckPassWord)
		return;
	
	if((CodeType == 65) || (CodeType == 66))
	{
		if((pDataLen < 11) || (pDataLen > 12))
			return;
	}
	else if(CodeType == 67)
	{
		if((pDataLen < 12) || (pDataLen > 13))
			return;
	}
	else if(CodeType == 68)
	{
		if((pDataLen < 7) || (pDataLen > 8))
			return;
	}
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x6B);
	UART_SendByte(huart3, CodeType);
	
	if(CodeType == 0x47)
	{	
		UART_SendByte(huart3, pDataLen+2);
		UART_SendByte(huart3, 0x41);
	}
	else
	
	{
		UART_SendByte(huart3, pDataLen);
	}

	while(pDataLen)
	{
		UART_SendByte(huart3, *pData++);
		pDataLen--;
	}
	
	if(CodeType == 0x47)
	{
		UART_SendByte(huart3, 0x41);
	}
	
	UART_SendByte(huart3, 0x00);
}
/* 设置条形码左边间距 a*/
void Set_BarCodeLeftSpace(unsigned char nL, unsigned char nH)
{
	if(!gucCheckPassWord)
		return;


	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, nL);
	UART_SendByte(huart3, nH);
}

/* 条形码的宽度  a*/
void Set_BarCodeWidth(unsigned char widthsel)
{
	if(!gucCheckPassWord)
		return;
	
	if(widthsel < 2)
	{
		widthsel = 2;
	}
	else if(widthsel > 6)
	{
		widthsel = 6;
	}
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x77);
	UART_SendByte(huart3, widthsel);
}
/* 设置汉字字符打印模式     a*/
void SetChinesemode(unsigned char opt)
{
	
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x21);
	UART_SendByte(huart3, opt);
}

/* 选择汉字模式 a*/
void SelChineseChar(void)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x26);
}
/*取消打印机汉字打印模式 a*/
void DisChineseChar(void)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x2E);
}
/* 选择中文编码格式 a */
void Set_ChineseCode(unsigned char selopt)
{
	if(!gucCheckPassWord)
		return;
	
	if(selopt > 3)
		selopt = 3;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x43);
	UART_SendByte(huart3, 0x44);
	UART_SendByte(huart3, 0x54);
	UART_SendByte(huart3, 0x59);
	UART_SendByte(huart3, selopt);
}



 /*功能：打印测试页结束时进行切纸 a*/
void TestPrintPage(void)
{
		
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x53);
	UART_SendByte(huart3, 0x45);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, 0x46);

	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x53);

}

/*		打印光栅位图 a */
void PrintGratinmap(unsigned char mode,unsigned int xDot,unsigned int yDot,unsigned char *pData)
{
	unsigned char tmp;
	unsigned int len;
	
	if(!gucCheckPassWord)
		return;
	
	if(mode > 3)
	{
		mode = 3;
	}
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x76);
	UART_SendByte(huart3, 0x30);
	UART_SendByte(huart3, mode);
	xDot = xDot / 8;
	tmp = (unsigned char)(xDot & 0x00ff);
	UART_SendByte(huart3, tmp);
	tmp = (unsigned char)((xDot>>8) & 0x00ff);
	UART_SendByte(huart3, tmp);
	tmp = (unsigned char)(yDot & 0x00ff);
	UART_SendByte(huart3, tmp);
	tmp = (unsigned char)((yDot>>8) & 0x00ff);
	UART_SendByte(huart3, tmp);
	len = xDot * yDot;
	while(len)
	{
		UART_SendByte(huart3, *pData++);
		
		len--;
	}
}

/* 设置QR Code（二维码）单元大小 a*/
void Set_QRcodeMode(unsigned char mode)
{
	if(!gucCheckPassWord)
		return;
	
	if(mode > 16)
		mode = 16;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x28);
	UART_SendByte(huart3, 0x6B);
	UART_SendByte(huart3, 0x03);
	UART_SendByte(huart3, 0x00);
	UART_SendByte(huart3, 0x31);
	UART_SendByte(huart3, 0x43);
	UART_SendByte(huart3, mode);
}


/* 设置错误纠错等级  a*/
void Set_QRCodeAdjuLevel(unsigned char level)
{
	if(!gucCheckPassWord)
		return;
	
	if(level < 0x30)
	{
		level = 0x30;
	}
	else if(level > 0x33)
	{
		level = 0x33;
	}
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x28);
	UART_SendByte(huart3, 0x6B);
	UART_SendByte(huart3, 0x03);
	UART_SendByte(huart3, 0x00);
	UART_SendByte(huart3, 0x31);
	UART_SendByte(huart3, 0x45);
	UART_SendByte(huart3, level);
}


/* QRCode传输数据至编码缓存 a*/
void Set_QRCodeBuffer(unsigned int Len,unsigned char *pData)
{
	unsigned char tmp;
	if(!gucCheckPassWord)
		return;
	
	if(Len < 3)
	{
		return;
	}
	
	Len += 3;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x28);
	UART_SendByte(huart3, 0x6B);
	tmp = (unsigned char)(Len & 0x00ff);
	UART_SendByte(huart3, tmp);
	tmp = (unsigned char)((Len >> 8)&0x00ff);
	UART_SendByte(huart3, tmp);
	UART_SendByte(huart3, 0x31);
	UART_SendByte(huart3, 0x50);
	UART_SendByte(huart3, 0x30);
	Len -= 3;
	while(Len)
	{
		UART_SendByte(huart3, *pData++);
		Len--;
	}
	UART_SendByte(huart3, 0x00);
}
/* QR Code 打印编码缓存的二维条码   a*/
void PrintQRCode(void)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x28);
	UART_SendByte(huart3, 0x6B);
	UART_SendByte(huart3, 0x03);
	UART_SendByte(huart3, 0x00);
	UART_SendByte(huart3, 0x31);
	UART_SendByte(huart3, 0x51);
	UART_SendByte(huart3, 0x30);
	UART_SendByte(huart3, 0x00);
}


/*
** 函数：void Barcode_sw(unsigned char mode)    
** 参数：mode 0禁止，1启用
   功能：条形码打印使能 
*/
void Barcode_sw(unsigned char mode)
{
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x45);
	UART_SendByte(huart3, 0x43);
	UART_SendByte(huart3, mode);
}




