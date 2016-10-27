#pragma once

#include "Utils.h"

struct Register
{
    enum Registers
    {
        INVALID = 0,
        AH, AL, AX, BH, BL,
        BP, BPL, BX, CH, CL,
        CS, CX, DH, DI, DIL,
        DL, DS, DX, EAX, EBP,
        EBX, ECX, EDI, EDX, EFLAGS,
        EIP, EIZ, ES, ESI, ESP,
        FPSW, FS, GS, IP, RAX,
        RBP, RBX, RCX, RDI, RDX,
        RIP, RIZ, RSI, RSP, SI,
        SIL, SP, SPL, SS, CR0,
        CR1, CR2, CR3, CR4, CR5,
        CR6, CR7, CR8, CR9, CR10,
        CR11, CR12, CR13, CR14, CR15,
        DR0, DR1, DR2, DR3, DR4,
        DR5, DR6, DR7, DR8, DR9,
        DR10, DR11, DR12, DR13, DR14,
        DR15, FP0, FP1, FP2, FP3,
        FP4, FP5, FP6, FP7,
        K0, K1, K2, K3, K4,
        K5, K6, K7, MM0, MM1,
        MM2, MM3, MM4, MM5, MM6,
        MM7, R8, R9, R10, R11,
        R12, R13, R14, R15,
        ST0, ST1, ST2, ST3,
        ST4, ST5, ST6, ST7,
        XMM0, XMM1, XMM2, XMM3, XMM4,
        XMM5, XMM6, XMM7, XMM8, XMM9,
        XMM10, XMM11, XMM12, XMM13, XMM14,
        XMM15, XMM16, XMM17, XMM18, XMM19,
        XMM20, XMM21, XMM22, XMM23, XMM24,
        XMM25, XMM26, XMM27, XMM28, XMM29,
        XMM30, XMM31, YMM0, YMM1, YMM2,
        YMM3, YMM4, YMM5, YMM6, YMM7,
        YMM8, YMM9, YMM10, YMM11, YMM12,
        YMM13, YMM14, YMM15, YMM16, YMM17,
        YMM18, YMM19, YMM20, YMM21, YMM22,
        YMM23, YMM24, YMM25, YMM26, YMM27,
        YMM28, YMM29, YMM30, YMM31, ZMM0,
        ZMM1, ZMM2, ZMM3, ZMM4, ZMM5,
        ZMM6, ZMM7, ZMM8, ZMM9, ZMM10,
        ZMM11, ZMM12, ZMM13, ZMM14, ZMM15,
        ZMM16, ZMM17, ZMM18, ZMM19, ZMM20,
        ZMM21, ZMM22, ZMM23, ZMM24, ZMM25,
        ZMM26, ZMM27, ZMM28, ZMM29, ZMM30,
        ZMM31, R8B, R9B, R10B, R11B,
        R12B, R13B, R14B, R15B, R8D,
        R9D, R10D, R11D, R12D, R13D,
        R14D, R15D, R8W, R9W, R10W,
        R11W, R12W, R13W, R14W, R15W,
        ENDING
    };

    Registers reg;

    CompareFunction<Register> compare = nullptr;

    explicit Register()
        : reg(INVALID) { }

    explicit Register(CompareFunction<Register> compare)
        : reg(INVALID), compare(compare) { }

    explicit Register(Registers reg)
        : reg(reg) { }

    bool Equals(const Register & other, State & state) const
    {
        if(compare)
            return compare(*this, other, state);
        if(other.compare)
            return other.compare(other, *this, state);

        return reg == other.reg;
    }

    bool operator==(const Register & other) const = delete;

    OPNEQ(Register);

    int Size() const
    {
        switch(reg)
        {
        case RAX:
        case RBX:
        case RCX:
        case RDX:
        case RBP:
        case RSP:
        case RSI:
        case RDI:
        case R8:
        case R9:
        case R10:
        case R11:
        case R12:
        case R13:
        case R14:
        case R15:
            return sizeof(uint64_t);
        case EAX:
        case EBX:
        case ECX:
        case EDX:
        case EBP:
        case ESP:
        case ESI:
        case EDI:
        case R8D:
        case R9D:
        case R10D:
        case R11D:
        case R12D:
        case R13D:
        case R14D:
        case R15D:
            return sizeof(uint32_t);
        case AX:
        case BX:
        case CX:
        case DX:
        case BP:
        case SP:
        case SI:
        case DI:
        case R8W:
        case R9W:
        case R10W:
        case R11W:
        case R12W:
        case R13W:
        case R14W:
        case R15W:
            return sizeof(uint16_t);
        case AH:
        case AL:
        case BH:
        case BL:
        case CH:
        case CL:
        case DH:
        case DL:
        case BPL:
        case SPL:
        case SIL:
        case DIL:
        case R8B:
        case R9B:
        case R10B:
        case R11B:
        case R12B:
        case R13B:
        case R14B:
        case R15B:
            return sizeof(uint8_t);
        default:
            __debugbreak();
        }
        return 0;
    }

    int Offset() const
    {
        switch(reg)
        {
        case AH:
        case BH:
        case CH:
        case DH:
            return 1;
        default:
            return 0;
        }
    }
};