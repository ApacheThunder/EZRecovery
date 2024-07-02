#include <nds.h>
#include "tonccpy.h"
#include "ezcard.h"

u16 Read_S98NOR_ID() {
	u16 ID1;
	*((vu16 *)(FlashBase_S98)) = 0xF0 ;	
	*((vu16 *)(FlashBase_S98+0x555*2)) = 0xAA;
	*((vu16 *)(FlashBase_S98+0x2AA*2)) = 0x55;
	*((vu16 *)(FlashBase_S98+0x555*2)) = 0x90;
	ID1 = *((vu16 *)(FlashBase_S98+0xE*2));
	return ID1;
}	

void SetRompage(u16 page) {
	*(vu16 *)0x9fe0000 = 0xd200;
	*(vu16 *)0x8000000 = 0x1500;
	*(vu16 *)0x8020000 = 0xd200;
	*(vu16 *)0x8040000 = 0x1500;
	*(vu16 *)0x9880000 = page; //C4
	*(vu16 *)0x9fc0000 = 0x1500;
}

void SetSDControl(u16 control) {
	*(u16 *)0x9fe0000 = 0xd200;
	*(u16 *)0x8000000 = 0x1500;
	*(u16 *)0x8020000 = 0xd200;
	*(u16 *)0x8040000 = 0x1500;
	*(u16 *)0x9400000 = control;
	*(u16 *)0x9fc0000 = 0x1500;
}

void Set_RTC_status(u16 status) {
	*(u16 *)0x9fe0000 = 0xd200;
	*(u16 *)0x8000000 = 0x1500;
	*(u16 *)0x8020000 = 0xd200;
	*(u16 *)0x8040000 = 0x1500;
	*(u16 *)0x96A0000 = status;
	*(u16 *)0x9fc0000 = 0x1500;
}

void SetSPIControl(u16 control) {
	*(u16 *)0x9fe0000 = 0xd200;
	*(u16 *)0x8000000 = 0x1500;
	*(u16 *)0x8020000 = 0xd200;
	*(u16 *)0x8040000 = 0x1500;
	*(u16 *)0x9660000 = control;
	*(u16 *)0x9fc0000 = 0x1500;
}

void SetSPIWrite(u16 control) {
	*(u16 *)0x9fe0000 = 0xd200;
	*(u16 *)0x8000000 = 0x1500;
	*(u16 *)0x8020000 = 0xd200;
	*(u16 *)0x8040000 = 0x1500;
	*(u16 *)0x9680000 = control;
	*(u16 *)0x9fc0000 = 0x1500;
}

void SPI_Enable() { SetSPIControl(1); }

void SPI_Disable() { SetSPIControl(0); }

void SPI_Write_Enable() { SetSPIWrite(1); }

void SPI_Write_Disable() { SetSPIWrite(0); }

u16 Read_FPGA_ver() {
	u16 Read_SPI;
	SPI_Enable();	
	Read_SPI =  *(vu16 *)0x9E00000; 
	SPI_Disable();
	return Read_SPI;
}

void SetbufferControl(u16 control) {
	*(u16 *)0x9fe0000 = 0xd200;
	*(u16 *)0x8000000 = 0x1500;
	*(u16 *)0x8020000 = 0xd200;
	*(u16 *)0x8040000 = 0x1500;
	*(u16 *)0x9420000 = control; //A1
	*(u16 *)0x9fc0000 = 0x1500;
}

u16 SD_Response() {	return *(vu16*)0x9E00000; }

void Send_FATbuffer(u32* buffer, u32 mode) {
	SetbufferControl(1);
	tonccpy((void*)0x09E00000, buffer, 0x400);
	// dmaCopy(buffer,(void*)0x9E00000, 0x400);
	if(mode == 2) {
		SetbufferControl(0);
		return;
	}
	SetbufferControl(3);	
	
	if(mode == 1) {
		SetbufferControl(0);
		return;
	}
	
	u16 res;
	while(1) {
		res = SD_Response();
		if(res != 0x0000)break;
	}
	
	while(1) {
		res = SD_Response();	
		if(res != 0x0001)break;
	}
	SetbufferControl(0);		
}

