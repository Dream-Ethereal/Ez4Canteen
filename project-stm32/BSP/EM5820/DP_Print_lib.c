#include "DP_Print_inc.h"

static unsigned char gucCheckPassWord=0;

void EM5820_init(void)
{
	//�����ӡ����
	InitializePrint();

	//������ӡŨ�� Ϊ30Ũ��
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x23);
	UART_SendByte(huart3, 0x53);
	UART_SendByte(huart3, 0x54);
	UART_SendByte(huart3, 0x44);
	UART_SendByte(huart3, 0x50);
	UART_SendByte(huart3, 0x27);
	
}

/* ��ʼ����ӡ���������ӡ���� a*/
void InitializePrint(void)
{
	/* ��ʼ����ӡ���������ӡ���� */
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x40);
	gucCheckPassWord = 1;
}

void EM5820_printData(Order order)
{
	uint8_t text[100];

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"Ez4Canteen");

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"================================");

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "#%s", order.sortNum);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "%s", order.postscript);
	Print_ASCII((unsigned char*)text);

	SetBold(0x00);
	
	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1); //�����С
	sprintf((char *)text, "�µ�ʱ��: %s", order.completedTime);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(0);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "��ע��%s", order.remark);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	//Sel_Align_Way(0);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"        ����      ���� ���� �ܼ�");
	//Print_ASCII((unsigned char*)"        0000      0000 0000 0000");
	for(int i = 0; i < order.goodsCount; i++)
	{
		InitializePrint();
		sprintf((char *)text, "%-18s %-2d  X%-2d %5s", order.goodsDetails[i].name, order.goodsDetails[i].price, order.goodsDetails[i].number, order.goodsDetails[i].amount);
		Print_ASCII((unsigned char*)text);
	}

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "�ܼƣ�  ��%s", order.amount);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	
	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "�µ��ˣ�%s ����/Ůʿ", order.userName);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "��ϵ��ʽ��%s", order.mobile);
	Print_ASCII((unsigned char*)text);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	sprintf((char *)text, "������ţ�%s", order.orderNo);
	Print_ASCII((unsigned char*)text);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"NOTICE");

	select_lines(2);

	InitializePrint();
	Sel_Align_Way(1);	//����
	SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"�õ��ͺ��뾡��ʳ��Ŷ~");

	select_lines(2);

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"�̼���ϵ�绰��13587670731");

	SetBold(0x01);

	InitializePrint();
	Sel_Align_Way(1);	//����
	//SetCharacterSize(1, 1);	//�����С
	Print_ASCII((unsigned char*)"--------------------------------");

	SetBold(0x00);
	
	select_lines(4);
	InitializePrint();
	Print_ASCII((unsigned char*)" ");
}



/*
** ������ void select_lines(uint8_t times)
** ������ times  ���еĴ���
   ���ܣ� ����
*/
void select_lines(uint8_t times)
{
	uint8_t i;
	for(i=1;i<=times;i++)
	{
		print_And_Line();  /* ���λ��� */ 
	}
	
}

/*
** ������ void init_putstr(uint8_t *buf, unsigned char nsel)
** ������ *buf  �ַ�����  nsel  ���뷽ʽ 0���� 1���� 2����
   ������ print_show_str()�����еĲ��ִ����һ����װ��
	 ���ܣ�	��ʼ����ӡ���Ͷ��뷽ʽ��ѡ�� 
*/
void  init_putstr(uint8_t *buf, unsigned char nsel)
{
		/* ��ʼ����ӡ�� */
		InitializePrint();
	
		/* 0����1���С�2���� */
		Sel_Align_Way(nsel);
		Print_ASCII(buf);
}


/* ÿ����һ�Σ���ӡλ������ƶ�һ���ֵķ���λ  a*/
void jump_lattice(void)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x09);
}
 
/* ��ӡ���������ݲ���ǰ�ƽ�һ��  a*/
void print_And_Line(void)
{

	/* ����һ�����з� */
	UART_SendByte(huart3, 0x0A);
}


/*
** ������ Print_ASCII(unsigned char *buf)
** ������ buf  Ҫ���͵��ַ�������
   ���ܣ� ��Ҫ��ӡ���ַ������뻺���� 
*/
void Print_ASCII(unsigned char *buf)
{
	while(*buf != '\0')
    {
    	UART_SendByte(huart3, *buf++);
    }   
}


/* �����ַ��Ҳ�ļ��Ϊinterval X 0.125mm a*/
void Set_Right_Interval(unsigned char interval)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x20);
	UART_SendByte(huart3, interval);
}


/* ѡ���ӡģʽ a*/
void Set_Print_Mode(unsigned char optbit)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x21);
	UART_SendByte(huart3, optbit);
}

/* �趨��һ�еĿ�ʼ����Ҫ��ӡ�ַ���λ�þ���Ϊ(Lpos+Hpos*256)*0.125mm  a*/
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
������߼�� a
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

/* ѡ��/ȡ���û��Զ����ַ���  a*/
void Sel_Custom_Character(unsigned char SelOpt)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x25);
	UART_SendByte(huart3, SelOpt);
}
/* �û��Զ����ַ��� a*/
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

/* ѡ��λͼģʽ a*/
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

/* �����»������޼����  a*/
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

/* ����ȱʡ�м��3.75mm  a*/
void SetDefaultLineInterval(void)
{
	if(!gucCheckPassWord)
		return;
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x32);
}

/* ȡ���Զ����ַ�  a*/
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


/* Position ˮƽ��λλ�ã����ú�������λ�ã� a */
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

/* ѡ��/ȡ���Ӵ�ģʽ a*/
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
/* ��ӡ����ֽnstep*0.125mm  a*/
void PrintGoPage(unsigned char nstep)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x4A);
	UART_SendByte(huart3, nstep);
}
/* ѡ�������ַ� a*/  
void SelCountryCharacter(unsigned char nsel)
{
	if(!gucCheckPassWord)
		return;
		
	UART_SendByte(huart3, 0x1B);
	UART_SendByte(huart3, 0x74);
	UART_SendByte(huart3, nsel);
}

/* ѡ��/ȡ��˳ʱ����ת 90��  a*/
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


/* ѡ����뷽ʽ a*/
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

/* ѡ��/ȡ�����ô�ӡģʽ  a*/
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

/* ����/ѡ���ַ���С a*/
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

/* ��������λͼ */
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
/* ��ӡ����λͼ */
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

/* �ڰ׷��Դ�ӡ  a*/
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


/* ������߾� a*/
void Set_LeftSpaceNum(unsigned char nL,unsigned char nH)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, nL);
	UART_SendByte(huart3, nH);
}


/* ѡ�� HRI �ַ��Ĵ�ӡλ�� a*/
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

/* ѡ������߶� a*/
void Set_BarCodeHight(unsigned char verticalDotNum)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x68);
	
	UART_SendByte(huart3, verticalDotNum);
}


/*  ��ӡ���� a*/
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
/* ������������߼�� a*/
void Set_BarCodeLeftSpace(unsigned char nL, unsigned char nH)
{
	if(!gucCheckPassWord)
		return;


	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x4C);
	UART_SendByte(huart3, nL);
	UART_SendByte(huart3, nH);
}

/* ������Ŀ��  a*/
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
/* ���ú����ַ���ӡģʽ     a*/
void SetChinesemode(unsigned char opt)
{
	
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x21);
	UART_SendByte(huart3, opt);
}

/* ѡ����ģʽ a*/
void SelChineseChar(void)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x26);
}
/*ȡ����ӡ�����ִ�ӡģʽ a*/
void DisChineseChar(void)
{
	if(!gucCheckPassWord)
		return;
	
	UART_SendByte(huart3, 0x1C);
	UART_SendByte(huart3, 0x2E);
}
/* ѡ�����ı����ʽ a */
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



 /*���ܣ���ӡ����ҳ����ʱ������ֽ a*/
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

/*		��ӡ��դλͼ a */
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

/* ����QR Code����ά�룩��Ԫ��С a*/
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


/* ���ô������ȼ�  a*/
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


/* QRCode�������������뻺�� a*/
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
/* QR Code ��ӡ���뻺��Ķ�ά����   a*/
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
** ������void Barcode_sw(unsigned char mode)    
** ������mode 0��ֹ��1����
   ���ܣ��������ӡʹ�� 
*/
void Barcode_sw(unsigned char mode)
{
	UART_SendByte(huart3, 0x1D);
	UART_SendByte(huart3, 0x45);
	UART_SendByte(huart3, 0x43);
	UART_SendByte(huart3, mode);
}




