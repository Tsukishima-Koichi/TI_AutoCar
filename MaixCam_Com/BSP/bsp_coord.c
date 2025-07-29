#include "bsp_coord.h"

// 全局坐标数据变量
COORD_DATA Coord_Data = {0};

uint8_t Coord_DMA_Buffer[63] = {0};

void Coord_Init(void)
{
    DL_DMA_setSrcAddr(DMA, DMA_COORD_CHAN_ID, (uint32_t)(&UART_COORD_INST->RXDATA));
    DL_DMA_setDestAddr(DMA, DMA_COORD_CHAN_ID, (uint32_t) &Coord_DMA_Buffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_COORD_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_COORD_CHAN_ID);

    NVIC_EnableIRQ(UART_COORD_INST_INT_IRQN);
}

void UART_COORD_INST_IRQHandler(void)
{
    uint8_t checkSum, packCnt = 0;
    extern uint8_t Coord_DMA_Buffer[63];
    uint8_t load[16] = {0};

    DL_DMA_disableChannel(DMA, DMA_COORD_CHAN_ID);
    uint8_t rxSize = 32 - DL_DMA_getTransferSize(DMA, DMA_COORD_CHAN_ID);

    if(DL_UART_isRXFIFOEmpty(UART_COORD_INST) == false)
        Coord_DMA_Buffer[rxSize++] = DL_UART_receiveData(UART_COORD_INST);

    while(rxSize >= PACK_LEN)
    {
        checkSum=0;
        for(int i=packCnt*PACK_LEN+1; i<packCnt*PACK_LEN+3+LOAD_LEN; i++)
            checkSum = (checkSum + Coord_DMA_Buffer[i]) & 0xFF;

        if((Coord_DMA_Buffer[packCnt*PACK_LEN] == PACK_HEAD) 
            //&& (checkSum == Coord_DMA_Buffer[packCnt*PACK_LEN+2+LOAD_LEN+1])
            //&& (Coord_DMA_Buffer[packCnt*PACK_LEN+2+LOAD_LEN+2] == PACK_TAIL))
        )
        {
            for (int i=0; i<LOAD_LEN; i++)
                load[i] = Coord_DMA_Buffer[packCnt*PACK_LEN+3+i];

            Coord_Data.red_x = (int32_t)((load[3] << 24) | (load[2] << 16) | (load[1] << 8) | (load[0])); 
            Coord_Data.red_y = (int32_t)((load[7] << 24) | (load[6] << 16) | (load[5] << 8) | (load[4])); 
            Coord_Data.blue_x = (int32_t)((load[11] << 24) | (load[10] << 16) | (load[9] << 8) | (load[8])); 
            Coord_Data.blue_y = (int32_t)((load[15] << 24) | (load[14] << 16) | (load[13] << 8) | (load[12])); 
        }

        rxSize -= PACK_LEN;
        packCnt++;
    }

    uint8_t dummy[4];
    DL_UART_drainRXFIFO(UART_COORD_INST, dummy, 4);

    DL_DMA_setDestAddr(DMA, DMA_COORD_CHAN_ID, (uint32_t) &Coord_DMA_Buffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_COORD_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_COORD_CHAN_ID);
}

