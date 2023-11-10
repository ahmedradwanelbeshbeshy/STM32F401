/*
 * Bit_Wise_Operations.h
 *
 * Created: 10/20/2023 9:02:36 PM
 *  Author: ahmed radwan
 */ 


#ifndef BIT_WISE_OPERATIONS_H_
#define BIT_WISE_OPERATIONS_H_

#define SET_BIT(Reg,Bit)                  (Reg|=(1<<Bit))
#define CLR_BIT(Reg,Bit)                  (Reg&=~(1<<Bit))
#define TGL_BIT(Reg,Bit)                  (Reg^=(1<<Bit))
#define GET_BIT(Reg,Bit)                  ((Reg>>Bit)&1)
#define RSHIFT_REG(Reg,No)                (Reg>>=No)
#define LSHIFT_REG(Reg,No)                (Reg<<=No)
#define CRSHIFT_REG(Reg,No)               (Reg=(Reg>>No)|(Reg<<(8-No)))
#define CLSHIFT_REG(Reg,No)               (Reg=(Reg<<No)|(Reg>>(8-No)))
#define ASSIGN_REG(Reg,Value)             (Reg=Value)
#define SET_REG(Reg)                      (Reg=0XFF)
#define CLR_REG(Reg)                      (Reg=0X00)
#define TGL_REG(Reg)                      (Reg^=0XFF)
#define SET_H_NIB(Reg)                    (Reg|=0XF0)
#define SET_L_NIB(Reg)                    (Reg|=0XF)
#define CLR_H_NIB(Reg)                    (Reg&=0XF)
#define CLR_L_NIB(Reg)                    (Reg&=0XF0)
#define GET_H_NIB(Reg)                    (Reg>>4)
#define GET_L_NIB(Reg)                    ((Reg<<4)>>4)
#define ASSIGN_H_NIB(Reg,Value)           (Reg|=(Value&0XF0))
#define ASSIGN_L_NIB(Reg,Value)           (Reg|=(Value&0XF))
#define TGL_H_NIB(Reg)                    (Reg^=0XF0)
#define TGL_L_NIB(Reg)                    (Reg^=0XF)
#define SWAP_NIB(Reg)                     (Reg=((ReG&0XF0)>>4)|((Reg&0XF)<<4))
#define write_2BITS(REG,source,mode)      (REG=((((REG>>(2*source))&mode)|mode)<<(2*source))|REG)


#define CONC(B7, B6, B5, B4, B3, B2, B1, B0) CONC_HELPER(B7, B6, B5, B4, B3, B2, B1, B0)
#define CONC_HELPER(B7, B6, B5, B4, B3, B2, B1, B0) (0b##B7##B6##B5##B4##B3##B2##B1##B0)
#define Peripheral_BitBand(Reg, Bit) (*((volatile unsigned long *)(Perihperal_Alias_Base + (((((unsigned long)(Reg))) - Peripheral_base) * (32)) + (Bit * (4)))))


#endif /* BIT_WISE_OPERATIONS_H_ */