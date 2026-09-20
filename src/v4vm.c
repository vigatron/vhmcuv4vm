#include "v4vm.h"

#include <stdio.h>

uint8_t     rega, regb, regc, regd;     // Registers
uint8_t     regt;                       // Temporary register
uint8_t     reg_memh;                   // MEMORY HAddr

// FLAGS
uint8_t     flage, flagl, flagb, flagsh;

uint8_t     mem[2*1024];
uint8_t     cod[2*1024];

uint8_t     stkd[512];
uint16_t    stkr[256];

uint16_t    idxstkd;
uint16_t    idxstkr;

uint16_t    pc;

uint8_t     opcode;
uint8_t     PFXNN;


#define     PCP1                    cod[pc+1]
#define     MEMADDR(ADDRH, ADDRL)   ((((uint16_t)ADDRH)<<8)+ADDRL)
#define     RADDR                   ((uint16_t)pc)+((int8_t)PCP1)
#define     RCOND(X)                pc = (X) ? RADDR : (pc + 2)


extern const uint8_t ilen[];
extern const char *szitbl[];

uint8_t     EXTERNAL_READPORT(uint8_t portn);
void        EXTERNAL_WRITEPORT(uint8_t portn, uint8_t val);

const char * getLabelName(uint16_t offs);


void GCMP(uint8_t v1, uint8_t v2) {
    flage = v1 == v2;   // Flag EQU
    flagl = v1 < v2;    // Flag LESS
    flagb = v1 > v2;    // Flag GREATER
}


void instr_00() /* NOP */           { }
void instr_01() /* RET */           { pc = stkr[--idxstkr]; }

/* */
void instr_02() { }

/* */
void instr_03() { }

/* */
void instr_04() { }

/* */
void instr_05() { rega = flagsh; }

/* */
void instr_06() { }

/* */
void instr_07() { }


/* CLR NREG */
void instr_08() { rega = 0; }
void instr_48() { regb = 0; }
void instr_88() { regc = 0; }
void instr_C8() { regd = 0; }

/* SET NREG */
void instr_09() { rega = 1; }
void instr_49() { regb = 1; }
void instr_89() { regc = 1; }
void instr_C9() { regd = 1; }

/* TMP NREG */
void instr_0A() { regt = rega; }
void instr_4A() { regt = regb; }
void instr_8A() { regt = regc; }
void instr_CA() { regt = regd; }

/* */
void instr_0B() { }
void instr_4B() { }
void instr_8B() { }
void instr_CB() { }

/* INC NREG */
void instr_0C() { rega++; }
void instr_4C() { regb++; }
void instr_8C() { regc++; }
void instr_CC() { regd++; }

/* DEC NREG */
void instr_0D() { rega--; }
void instr_4D() { regb--; }
void instr_8D() { regc--; }
void instr_CD() { regd--; }

/* RMEMI [MEMH:NREG] -> REGT */
void instr_0E() { regt = mem[ MEMADDR(reg_memh, rega) ]; }
void instr_4E() { regt = mem[ MEMADDR(reg_memh, regb) ]; }
void instr_8E() { regt = mem[ MEMADDR(reg_memh, regc) ]; }
void instr_CE() { regt = mem[ MEMADDR(reg_memh, regd) ]; }

/* WMEMI [MEMH:NREG] <- REGT */
void instr_0F() { mem[ MEMADDR(reg_memh, rega) ] = regt; }
void instr_4F() { mem[ MEMADDR(reg_memh, regb) ] = regt; }
void instr_8F() { mem[ MEMADDR(reg_memh, regc) ] = regt; }
void instr_CF() { mem[ MEMADDR(reg_memh, regd) ] = regt; }


// -------------------------------------------------

/* PUSH NREG */
void instr_10() { stkd[idxstkd++] = rega; }
void instr_50() { stkd[idxstkd++] = regb; }
void instr_90() { stkd[idxstkd++] = regc; }
void instr_D0() { stkd[idxstkd++] = regd; }

/* POP  NREG */
void instr_11() { rega = stkd[--idxstkd]; }
void instr_51() { regb = stkd[--idxstkd]; }
void instr_91() { regc = stkd[--idxstkd]; }
void instr_D1() { regd = stkd[--idxstkd]; }

/* MOV  NREG */
void instr_12() { rega = regt; }
void instr_52() { regb = regt; }
void instr_92() { regc = regt; }
void instr_D2() { regd = regt; }

/* */
void instr_13()  { }
void instr_53()  { }
void instr_93()  { }
void instr_D3()  { }

/* AND	NREG */
void instr_14() { rega &= regt; }
void instr_54() { regb &= regt; }
void instr_94() { regc &= regt; }
void instr_D4() { regd &= regt; }

/* OR	NREG */
void instr_15() { rega |= regt; }
void instr_55() { regb |= regt; }
void instr_95() { regc |= regt; }
void instr_D5() { regd |= regt; }

/* XOR	NREG */
void instr_16() { rega ^= regt; }
void instr_56() { regb ^= regt; }
void instr_96() { regc ^= regt; }
void instr_D6() { regd ^= regt; }

/* CMP0	NREG */
void instr_17() { GCMP(rega, 0); }
void instr_57() { GCMP(regb, 0); }
void instr_97() { GCMP(regc, 0); }
void instr_D7() { GCMP(regd, 0); }

/* CMP1	NREG */
void instr_18() { GCMP(rega, 1); }
void instr_58() { GCMP(regb, 1); }
void instr_98() { GCMP(regc, 1); }
void instr_D8() { GCMP(regd, 1); }

/* */
void instr_19() { }
void instr_59() { }
void instr_99() { }
void instr_D9() { }

/* SHR	NREG */
void instr_1A() { flagsh = rega & 1; rega >>= 1; }
void instr_5A() { flagsh = regb & 1; regb >>= 1; }
void instr_9A() { flagsh = regc & 1; regc >>= 1; }
void instr_DA() { flagsh = regd & 1; regd >>= 1; }

/* SHL	NREG */
void instr_1B() { flagsh = (rega & 0x80) ? 1:0 ; rega <<= 1; }
void instr_5B() { flagsh = (regb & 0x80) ? 1:0 ; regb <<= 1; }
void instr_9B() { flagsh = (regc & 0x80) ? 1:0 ; regc <<= 1; }
void instr_DB() { flagsh = (regd & 0x80) ? 1:0 ; regd <<= 1; }

/* */
void instr_1C() {}
void instr_5C() {}
void instr_9C() {}
void instr_DC() {}

/* ADD	NREG, TMP */
void instr_1D() { rega += regt; }
void instr_5D() { regb += regt; }
void instr_9D() { regc += regt; }
void instr_DD() { regd += regt; }

/* SUB	NREG, TMP */
void instr_1E() { rega -= regt; }
void instr_5E() { regb -= regt; }
void instr_9E() { regc -= regt; }
void instr_DE() { regd -= regt; }

/* CMP	NREG, TMP */
void instr_1F() { GCMP(rega, regt); }
void instr_5F() { GCMP(regb, regt); }
void instr_9F() { GCMP(regc, regt); }
void instr_DF() { GCMP(regd, regt); }

// -------------------------------------------------

/* INIT NREG, M8 */
void instr_20() { rega = PCP1; }
void instr_60() { regb = PCP1; }
void instr_A0() { regc = PCP1; }
void instr_E0() { regd = PCP1; }

/* IN	NREG, M8    */
void instr_21()  { rega = EXTERNAL_READPORT(PCP1); }
void instr_61()  { regb = EXTERNAL_READPORT(PCP1); }
void instr_A1()  { regc = EXTERNAL_READPORT(PCP1); }
void instr_E1()  { regd = EXTERNAL_READPORT(PCP1); }

/* OUT	M8, NREG    */
void instr_22()  { EXTERNAL_WRITEPORT(PCP1, rega); }
void instr_62()  { EXTERNAL_WRITEPORT(PCP1, regb); }
void instr_A2()  { EXTERNAL_WRITEPORT(PCP1, regc); }
void instr_E2()  { EXTERNAL_WRITEPORT(PCP1, regd); }

/* */
void instr_23()  {  }
void instr_63()  {  }
void instr_A3()  {  }
void instr_E3()  {  }


/* AND NREG, M8 */
void instr_24()   { rega &= cod[pc+1]; }
void instr_64()   { regb &= cod[pc+1]; }
void instr_A4()   { regc &= cod[pc+1]; }
void instr_E4()   { regd &= cod[pc+1]; }

/* OR  NREG, M8 */
void instr_25()   { rega |= cod[pc+1]; }
void instr_65()   { regb |= cod[pc+1]; }
void instr_A5()   { regc |= cod[pc+1]; }
void instr_E5()   { regd |= cod[pc+1]; }

/* XOR NREG, M8 */
void instr_26()   { rega ^= cod[pc+1]; }
void instr_66()   { regb ^= cod[pc+1]; }
void instr_A6()   { regc ^= cod[pc+1]; }
void instr_E6()   { regd ^= cod[pc+1]; }

void instr_27() {}
void instr_67() {}
void instr_A7() {}
void instr_E7() {}

void instr_28() { }
void instr_68() { }
void instr_A8() { }
void instr_E8() { }

void instr_29() { }
void instr_69() { }
void instr_A9() { }
void instr_E9() { }


/* RMEM [PCP1] -> REGN */
void instr_2A() { rega = mem[MEMADDR(reg_memh, PCP1)]; }
void instr_6A() { regb = mem[MEMADDR(reg_memh, PCP1)]; }
void instr_AA() { regc = mem[MEMADDR(reg_memh, PCP1)]; }
void instr_EA() { regd = mem[MEMADDR(reg_memh, PCP1)]; }

/* WMEM [PCP1] <- REGN */
void instr_2B() { mem[MEMADDR(reg_memh, PCP1)] = rega; }
void instr_6B() { mem[MEMADDR(reg_memh, PCP1)] = regb; }
void instr_AB() { mem[MEMADDR(reg_memh, PCP1)] = regc; }
void instr_EB() { mem[MEMADDR(reg_memh, PCP1)] = regd; }

/* MEMPAGE #[PCP1] */
void instr_2C() { reg_memh = PCP1; }
/* */
void instr_6C() { }
/* */
void instr_AC() { }
/* */
void instr_EC() { }


/* ADD	NREG, M8    */
void instr_2D()  { rega += cod[pc+1]; }
void instr_6D()  { regb += cod[pc+1]; }
void instr_AD()  { regc += cod[pc+1]; }
void instr_ED()  { regd += cod[pc+1]; }

/* SUB	NREG, M8    */
void instr_2E()  { rega -= cod[pc+1]; }
void instr_6E()  { regb -= cod[pc+1]; }
void instr_AE()  { regc -= cod[pc+1]; }
void instr_EE()  { regd -= cod[pc+1]; }

/* CMP	NREG, M8    */
void instr_2F()  { GCMP(rega, PCP1); }
void instr_6F()  { GCMP(regb, PCP1); }
void instr_AF()  { GCMP(regc, PCP1); }
void instr_EF()  { GCMP(regd, PCP1); }


// -------------------------------------------------

void instr_30() /* JE      */ { RCOND(flage);   }
void instr_31() /* JNE     */ { RCOND(!flage);  }
void instr_32() /* JL      */ { RCOND(flagl);   }
void instr_33() /* JNL     */ { RCOND(!flagl);  }
void instr_34() /* JB      */ { RCOND(flagb);   }
void instr_35() /* JNB     */ { RCOND(!flagb);  }
void instr_36() /* JZ      */ { }
void instr_37() /* JNZ     */ { }
void instr_38() /* JSS0    */ { RCOND(!flagsh); }
void instr_39() /* JSS1    */ { RCOND( flagsh); }
void instr_3A() /* JOVER   */ { }
void instr_3B() /* JNOVER  */ { }
void instr_3C() /* JPOS    */ { }
void instr_3D() /* JNEG    */ { }

void instr_3E() /* RJMP  */   {
    int8_t roffs = cod[pc+1];
    uint16_t ep = pc + roffs;
    pc = ep;
}

/* RCALL */
void instr_3F() {

    stkr[idxstkr++] = pc + 2; // save ret point
    int8_t roffs = cod[pc+1];
    uint16_t ep = pc + roffs;
    pc = ep;

}


void instr_40() /* */ { }
void instr_41() /* */ { }
void instr_42() /* */ { }
void instr_43() /* */ { }
void instr_44() { }
void instr_45() { }
void instr_46() { }
void instr_47() { }

void instr_70() /* */ { }
void instr_71() /* */ { }
void instr_72() /* */ { }
void instr_73() /* */ { }
void instr_74() /* */ { }
void instr_75() /* */ { }
void instr_76() /* */ { }
void instr_77() /* */ { }
void instr_78() /* */ { }
void instr_79() /* */ { }
void instr_7A() /* */ { }
void instr_7B() /* */ { }
void instr_7C() /* */ { }
void instr_7D() /* */ { }
void instr_7E() /* */ { }
void instr_7F() /* */ { }

void instr_80() /* */ { }
void instr_81() /* */ { }
void instr_82() /* */ { }
void instr_83() /* */ { }
void instr_84() { }
void instr_85() { }
void instr_86() { }
void instr_87() { }

void instr_B0() /* */ { }
void instr_B1() /* */ { }
void instr_B2() /* */ { }
void instr_B3() /* */ { }
void instr_B4() /* */ { }
void instr_B5() /* */ { }
void instr_B6() /* */ { }
void instr_B7() /* */ { }
void instr_B8() /* */ { }
void instr_B9() /* */ { }
void instr_BA() /* */ { }
void instr_BB() /* */ { }
void instr_BC() /* */ { }
void instr_BD() /* */ { }
void instr_BE() /* */ { }
void instr_BF() /* */ { }

void instr_C0() /* */ { }
void instr_C1() /* */ { }
void instr_C2() /* */ { }
void instr_C3() /* */ { }
void instr_C4() { }
void instr_C5() { }
void instr_C6() { }
void instr_C7() { }

void instr_F0() /* */ { }
void instr_F1() /* */ { }
void instr_F2() /* */ { }
void instr_F3() /* */ { }
void instr_F4() /* */ { }
void instr_F5() /* */ { }
void instr_F6() /* */ { }
void instr_F7() /* */ { }
void instr_F8() /* */ { }
void instr_F9() /* */ { }
void instr_FA() /* */ { }
void instr_FB() /* */ { }
void instr_FC() /* */ { }
void instr_FD() /* */ { }

void instr_FE() /* JMPABS/16> */  {
    pc++; uint16_t a=cod[pc]; a<<=8;
    pc++; a+=cod[pc]; pc=a; }

void instr_FF() /* CALLABS/16> */ {
    pc++; uint16_t a=cod[pc]; a<<=8;
    pc++; a+=cod[pc];
    pc++; stkr[idxstkr++]=pc;
    pc=a; }


const void *functbl[] = {

    // 00
    (void *)instr_00, (void *)instr_01, (void *)instr_02, (void *)instr_03,
    (void *)instr_04, (void *)instr_05, (void *)instr_06, (void *)instr_07,
    (void *)instr_08, (void *)instr_09, (void *)instr_0A, (void *)instr_0B,
    (void *)instr_0C, (void *)instr_0D, (void *)instr_0E, (void *)instr_0F,

    (void *)instr_10, (void *)instr_11, (void *)instr_12, (void *)instr_13,
    (void *)instr_14, (void *)instr_15, (void *)instr_16, (void *)instr_17,
    (void *)instr_18, (void *)instr_19, (void *)instr_1A, (void *)instr_1B,
    (void *)instr_1C, (void *)instr_1D, (void *)instr_1E, (void *)instr_1F,

    (void *)instr_20, (void *)instr_21, (void *)instr_22, (void *)instr_23,
    (void *)instr_24, (void *)instr_25, (void *)instr_26, (void *)instr_27,
    (void *)instr_28, (void *)instr_29, (void *)instr_2A, (void *)instr_2B,
    (void *)instr_2C, (void *)instr_2D, (void *)instr_2E, (void *)instr_2F,

    (void *)instr_30, (void *)instr_31, (void *)instr_32, (void *)instr_33,
    (void *)instr_34, (void *)instr_35, (void *)instr_36, (void *)instr_37,
    (void *)instr_38, (void *)instr_39, (void *)instr_3A, (void *)instr_3B,
    (void *)instr_3C, (void *)instr_3D, (void *)instr_3E, (void *)instr_3F,

    // 40
    (void *)instr_40, (void *)instr_41, (void *)instr_42, (void *)instr_43,
    (void *)instr_44, (void *)instr_45, (void *)instr_46, (void *)instr_47,
    (void *)instr_48, (void *)instr_49, (void *)instr_4A, (void *)instr_4B,
    (void *)instr_4C, (void *)instr_4D, (void *)instr_4E, (void *)instr_4F,

    (void *)instr_50, (void *)instr_51, (void *)instr_52, (void *)instr_53,
    (void *)instr_54, (void *)instr_55, (void *)instr_56, (void *)instr_57,
    (void *)instr_58, (void *)instr_59, (void *)instr_5A, (void *)instr_5B,
    (void *)instr_5C, (void *)instr_5D, (void *)instr_5E, (void *)instr_5F,

    (void *)instr_60, (void *)instr_61, (void *)instr_62, (void *)instr_63,
    (void *)instr_64, (void *)instr_65, (void *)instr_66, (void *)instr_67,
    (void *)instr_68, (void *)instr_69, (void *)instr_6A, (void *)instr_6B,
    (void *)instr_6C, (void *)instr_6D, (void *)instr_6E, (void *)instr_6F,

    (void *)instr_70, (void *)instr_71, (void *)instr_72, (void *)instr_73,
    (void *)instr_74, (void *)instr_75, (void *)instr_76, (void *)instr_77,
    (void *)instr_78, (void *)instr_79, (void *)instr_7A, (void *)instr_7B,
    (void *)instr_7C, (void *)instr_7D, (void *)instr_7E, (void *)instr_7F,

    // 80
    (void *)instr_80, (void *)instr_81, (void *)instr_82, (void *)instr_83,
    (void *)instr_84, (void *)instr_85, (void *)instr_86, (void *)instr_87,
    (void *)instr_88, (void *)instr_89, (void *)instr_8A, (void *)instr_8B,
    (void *)instr_8C, (void *)instr_8D, (void *)instr_8E, (void *)instr_8F,

    (void *)instr_90, (void *)instr_91, (void *)instr_92, (void *)instr_93,
    (void *)instr_94, (void *)instr_95, (void *)instr_96, (void *)instr_97,
    (void *)instr_98, (void *)instr_99, (void *)instr_9A, (void *)instr_9B,
    (void *)instr_9C, (void *)instr_9D, (void *)instr_9E, (void *)instr_9F,

    (void *)instr_A0, (void *)instr_A1, (void *)instr_A2, (void *)instr_A3,
    (void *)instr_A4, (void *)instr_A5, (void *)instr_A6, (void *)instr_A7,
    (void *)instr_A8, (void *)instr_A9, (void *)instr_AA, (void *)instr_AB,
    (void *)instr_AC, (void *)instr_AD, (void *)instr_AE, (void *)instr_AF,

    (void *)instr_B0, (void *)instr_B1, (void *)instr_B2, (void *)instr_B3,
    (void *)instr_B4, (void *)instr_B5, (void *)instr_B6, (void *)instr_B7,
    (void *)instr_B8, (void *)instr_B9, (void *)instr_BA, (void *)instr_BB,
    (void *)instr_BC, (void *)instr_BD, (void *)instr_BE, (void *)instr_BF,

    // C0
    (void *)instr_C0, (void *)instr_C1, (void *)instr_C2, (void *)instr_C3,
    (void *)instr_C4, (void *)instr_C5, (void *)instr_C6, (void *)instr_C7,
    (void *)instr_C8, (void *)instr_C9, (void *)instr_CA, (void *)instr_CB,
    (void *)instr_CC, (void *)instr_CD, (void *)instr_CE, (void *)instr_CF,

    (void *)instr_D0, (void *)instr_D1, (void *)instr_D2, (void *)instr_D3,
    (void *)instr_D4, (void *)instr_D5, (void *)instr_D6, (void *)instr_D7,
    (void *)instr_D8, (void *)instr_D9, (void *)instr_DA, (void *)instr_DB,
    (void *)instr_DC, (void *)instr_DD, (void *)instr_DE, (void *)instr_DF,

    (void *)instr_E0, (void *)instr_E1, (void *)instr_E2, (void *)instr_E3,
    (void *)instr_E4, (void *)instr_E5, (void *)instr_E6, (void *)instr_E7,
    (void *)instr_E8, (void *)instr_E9, (void *)instr_EA, (void *)instr_EB,
    (void *)instr_EC, (void *)instr_ED, (void *)instr_EE, (void *)instr_EF,

    (void *)instr_F0, (void *)instr_F1, (void *)instr_F2, (void *)instr_F3,
    (void *)instr_F4, (void *)instr_F5, (void *)instr_F6, (void *)instr_F7,
    (void *)instr_F8, (void *)instr_F9, (void *)instr_FA, (void *)instr_FB,
    (void *)instr_FC, (void *)instr_FD, (void *)instr_FE, (void *)instr_FF

};

typedef void (*callinstr)(void);


void v4vmrun() {

    // RESET
    idxstkd = 0;
    idxstkr = 0;
    pc = 0;
    reg_memh = 0;

    uint16_t oldpc = 0xFFFF;
    uint16_t cycle = 0;

    uint16_t i;

    while(1) {

        opcode = cod[pc];

        printf("CYCL# %4d ", cycle++ );
        for(i=0;i<16;i++) { printf("%c", i < idxstkr ? '+' : ' '); }

        printf(" %-32s ", getLabelName(pc));

        printf("PC=%.4X : %.2X[%.2X] ", pc, opcode, cod[pc+1]);
        printf(" %-22s ", szitbl[opcode]);

        callinstr fcall = (callinstr)functbl[opcode];
        fcall();
        pc += ilen[opcode];

        printf(" > %.2X %.2X %.2X %.2X T:%.2X ", rega, regb, regc, regd, regt);
        printf(" SP[%.4X,D:%.4X]", idxstkr, idxstkd );
        printf(" FLGS: E%d SH%d ", flage, flagsh? 1:0);
        printf("\n");

        if(pc == oldpc) {
            printf("LOOP LOCK, BREAK\n");
            break;
        } else oldpc = pc;

    }

}

uint8_t * getMEMSEG() { return mem; }
uint8_t * getCODSEG() { return cod; }

