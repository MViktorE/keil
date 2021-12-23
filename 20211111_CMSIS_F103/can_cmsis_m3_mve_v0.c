#include "can_cmsis_m3_mve_v0.h"

extern uint8_t flagRxCan;
extern uint32_t canRx0Data[3];
uint8_t canRx0DataCounter = 0;

void CAN1_RX0_IRQHandler (void) {
    flagRxCan = 1;
    canRx0Data[canRx0DataCounter] = CAN1->sFIFOMailBox[0].RDLR;
    canRx0DataCounter++;
    if (canRx0DataCounter>2)
        canRx0DataCounter = 0;
    CAN1->RF0R |= CAN_RF0R_RFOM0;          /* interrupt flag */
}

uint8_t can_init(void){
    /* Initialization mode */
    CAN1->MCR |= CAN_MCR_INRQ;              /* Initialization Request */
    CAN1->MCR &= ~CAN_MCR_SLEEP;            /* Sleep Mode OFF */
    CAN1->MCR |= CAN_MCR_NART;              /* Bit 4 NART :  No automatic retransmission*/
    CAN1->BTR &= ~CAN_BTR_BRP;              /* clean */
    CAN1->BTR |= 8 << CAN_BTR_BRP_Pos;      /* Baud Rate Prescaler CAN_BTR_BRP[9:0] */
                                            /* tq = (BRP[9:0]+1) x tPCLK */
                                            /* tq = (8+1)*(1/36MHz)= 250ns*/
    CAN1->BTR &= ~(0xF << CAN_BTR_TS1_Pos); /* clean */
    CAN1->BTR |= 12 << CAN_BTR_TS1_Pos;     /* TS1[3:0]: Time segment 1 */
                                            /* tBS1 = tq x (TS1[3:0] + 1) = 3.25 us */
    CAN1->BTR &= ~(7 << CAN_BTR_TS2_Pos);   /* clean */
    CAN1->BTR |=   1 << CAN_BTR_TS2_Pos;    /* TS2[2:0]: Time segment 2 */
                                            /* tBS2 = tq x (TS2[2:0] + 1) = 500 ns */
    /* Bits 25:24 SJW[1:0]: Resynchronization jump width - in Reset Value 1 tRJW = tq x (SJW[1:0] + 1) = 500 ns */
    /* Bit 30 LBKM: Loop back mode (debug) 0: Loop Back Mode disabled*/
    /* Bit 31 SILM: Silent mode (debug) 0: Normal operation */
    
    /*The filter scale and mode configuration must be configured before entering Normal Mode.*/
    
    /* TRANSMISSION SETTING */
    /* CAN TX mailbox identifier register (CAN_TI0R) */
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;            /* Bit 1 RTR: Remote transmission request 0: Data frame */
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE;            /* Bit 2 IDE: Identifier extension 0: Standard identifier */
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;           /* clean Bits 31:21 STID[10:0]/EXID[28:18]: Standard identifier or extended identifier */ 
    CAN1->sTxMailBox[0].TIR |= (0x556U << CAN_TI0R_STID_Pos); /* Tx Frame ID = 1 /max_val = 3777 */
    
    /* CAN mailbox data length control and time stamp register (CAN_TDT0R)*/
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;/* clean */
    CAN1->sTxMailBox[0].TDTR |= (8 << CAN_TDT0R_DLC_Pos); /* Bits 3:0 DLC[3:0]: Data length code */
    
    /* RECEIVE SETTING */ 
    /* Filters */
    /* CAN filter master register (CAN_FMR) Reset value: 0x2A1C 0E01 */
    /* CAN1->FMR |= CAN_FMR_FINIT - doesn't use because Reset value - In init state*/
    CAN1->FMR |= CAN_FMR_FINIT;
    /* CAN filter mode register (CAN_FM1R) Mask or list mode - Reset value: 0x0000 0000 - all in mask mode */ 
    /* !!! */
    CAN1->FS1R |= CAN_FS1R_FSC0;
    /* !!! */
    /* CAN filter ID and Mask *//* Filter bank i register x (CAN_FiRx) (i=0..27, x=1, 2) */
    /* CAN filter ID */
    //CAN1->sFilterRegister[0].FR1 &= ~(0x7FFU << CAN_F0R1_FB5_Pos); /* ID = 1 */
    //CAN1->sFilterRegister[0].FR1 = (1U << CAN_F0R1_FB5_Pos); /* ID = 1 */
    CAN1->sFilterRegister[0].FR1 = 0;
    CAN1->sFilterRegister[0].FR2 = 0;
    //CAN1->sFilterRegister[0].FR2 &= ~(0x7FFU << CAN_F0R2_FB5_Pos); /* Mask = all */
    /* CAN filter FIFO assignment register (CAN_FFA1R) - Reset value: 0x0000 0000 - 0: Filter assigned to FIFO 0 */
    /* CAN filter activation register (CAN_FA1R) Reset value: 0x0000 0000 */
    CAN1->FMR &= ~CAN_FMR_FINIT;
    CAN1->FA1R |= CAN_FA1R_FACT0; /* 1: Filter 0 is active */

    /* Interrupt ENABLE */
    CAN1->IER |= CAN_IER_FMPIE0; 
    
    /* Go to Noramal mode */
    CAN1->MCR &= ~CAN_MCR_INRQ;
    return 0;
}

