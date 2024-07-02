#ifndef EZCARD_H
#define EZCARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <nds/ndstypes.h>

#define FlashBase_S98 		(u32)0x09000000

u16 Read_S98NOR_ID();
void SetRompage(u16 page);
void SetSDControl(u16 control);
void Set_RTC_status(u16 status);
void SetSPIControl(u16 control);
void SetSPIWrite(u16 control);
void SPI_Enable();
void SPI_Disable();
void SPI_Write_Enable();
void SPI_Write_Disable();
u16 Read_FPGA_ver();
u16 SD_Response();
void SetbufferControl(u16 control);
void Send_FATbuffer(u32* buffer, u32 mode);

#ifdef __cplusplus
}
#endif
#endif

