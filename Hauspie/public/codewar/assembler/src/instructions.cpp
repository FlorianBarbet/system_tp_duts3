#include <iostream>
#include "instructions.h"
#include <QtDebug>
#include "config.h"

#include "label.h"

/*************************************************

 Operand: description byte:
 00 -> immediate
 01 -> address
 02 -> register
 03 -> pre-dec
 04 -> indirect
 05 -> post-inc
 06 -> label (so it will need to be changed by a 0 after label processing)



 *************************************************/


IInstruction::eOperandType IInstruction::tokenToOperandCode(const QString &token, unsigned short &code)
{
   switch (token[0].toAscii())
   {
      case '#': // immediate
      {
	 unsigned short val;
	 int base;
	 QString string_val;
	 if (token.startsWith("#0X"))
	 {
	    // hexadecimal
	    base = 16;
	    string_val = token.mid(3);
	 }
	 else if (token.startsWith("#B"))
	 {
	    // binary
	    base = 2;
	    string_val = token.mid(2);
	 }
	 else
	 {
	    base = 10;
	    string_val = token.mid(1);
	 }
	 qDebug() << QString("Converting %1 in base %2").arg(string_val).arg(base);
	 bool ok;
	 if (token[1].toAscii() == '-')
	 {
	    // negative decimal value
	    short v = string_val.toShort(&ok, base);
	    val = *((unsigned short*)&v);
	 }
	 else
	    val = string_val.toUShort(&ok, base);
	 if (!ok)
	 {
	    _error = tr("invalid token %1").arg(token);
	    break;
	 }

	 code = val;
	 return IMMEDIATE;
      }
      break;
      case '@': // address
      {
	 bool ok;
	 unsigned short addr = token.mid(1).toUShort(&ok,16);
	 if (!ok)
	 {
	    _error = tr("invalid token %1").arg(token);
	    break;
	 }
	 code = addr;
	 return ADDRESS;
      }
      break;
      case 'S':
      case 'P':
      case 'R': // register
      {
	 if (token.size() != 2)
	    goto operand_label;  // the operand is a label beginning with S or P
	 if (token[0].toAscii() != 'R' && token != "SP" && token != "PC")
	    goto operand_label;  // idem
	 if (!token[1].isDigit() && token[0].toAscii() == 'R')
	    goto operand_label;  // 2 letters label beginning with an R
 	 if (token[1].toAscii() > '7' && token[0].toAscii() == 'R')
 	    goto operand_label; // R8 or R9 used as label


	 int register_index;
	 if (token[0] == 'R')
	    register_index = token[1].digitValue();
	 else if (token[0] == 'S')
	    register_index = 7; // SP = R7
	 else
	    register_index = 6; // PC = R6
	 code = register_index; // register
	 return REGISTER;
      }
      break;
      case '-': // pre-dec
      {
	 int register_index;
	 if (token[2] == 'R')
	    register_index = token[3].digitValue();
	 else if (token[2] == 'S')
	    register_index = 7; // SP = R7
	 else
	    register_index = 6; // PC = R6
	 code = register_index;
	 return PRE_DEC;
      }
      break;
      case '(': // indirect or post-inc
      {
	 int register_index;
	 if (token[1] == 'R')
	    register_index = token[2].digitValue();
	 else if (token[1] == 'S')
	    register_index = 7; // SP = R7
	 else
	    register_index = 6; // PC = R6
	 code = register_index;
	 return token.endsWith("+") ? POST_INC : INDIRECT;
      }
      break;
      default:
      {

	operand_label:
	 // in that case, this operand is a label
	 // first, need to know if we need a relative or absolute address
	 if (opcode() >= BCC && opcode() <= BSR)
	 {
	    // relative
	    short addr = 0;
	    CLabelHandler::get().relative(token, currentPC(), addr);
	    code = addr;
	    return IMMEDIATE;
	 }
	 else if (!(opcode() >= JCC && opcode() <= JSR))
	 {
	    // label but not a Jxx or Bxx instruction, error
	    _error = tr("label %1 is used for a non jump or branch instruction").arg(token);
	    break;
	 }
	 // absolute
	 unsigned short addr = 0;
	 CLabelHandler::get().absolute(token,addr);
	 code = addr;
	 return IMMEDIATE;
      }
      break;
   }
   return INVALID;
}


// -----------------------------------------------------
// Zero operand

QByteArray CZeroOperandInstruction::fullOpCode(QStringList &operands)
{
   QByteArray code;
   code.resize(2);
   unsigned short *data = (unsigned short*) code.data();
   data[0] = opcode() << 11;
   return code;
}


bool CZeroOperandInstruction::checkOperands(QStringList &operands)
{
   if (operands.size() != 0)
   {
      _error = tr("Passing %1 operands to instruction %2 which does not allow any").arg(operands.size()).arg(name());
      return false;
   }
   return true;
}


// -----------------------------------------------------
// One operand

QByteArray COneOperandInstruction::fullOpCode(QStringList &operands)
{
   
   QByteArray code;
   unsigned short opval;
   eOperandType type;
   if ((type = tokenToOperandCode(operands[0], opval)) == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[0]);
      return code;
   }

   // Only a register is allowed if push or pop
   if (opcode() == PUSH || opcode() == POP)
   {
      if (type == IMMEDIATE || type == ADDRESS)
      {
	 _error = tr("incompatible operand %1 for instruction %1").arg(name()).arg(operands[1]);
	 return code;
      }
   }
   
   code.resize(2);
   unsigned short *data = (unsigned short *) code.data();
   data[0] = opcode() << 11 | type << 8 | (char) opval;
   return code;
}

bool COneOperandInstruction::checkOperands(QStringList &operands)
{
   if (operands.size() != 1)
   {
      _error = tr("Passing %1 operands to instruction %2 which only allows one").arg(operands.size()).arg(name());
      return false;
   }
   return true;
}


// -----------------------------------------------------
// Two operands

QByteArray CTwoOperandInstruction::fullOpCode(QStringList &operands)
{
   QByteArray code;
   unsigned short op1_val;
   unsigned short op2_val;
   eOperandType op1_type;
   eOperandType op2_type;

   op1_type = tokenToOperandCode(operands[0], op1_val);
   op2_type = tokenToOperandCode(operands[1], op2_val);

   if (op1_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[0]);
      return code;
   }

   if (op2_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[1]);
      return code;
   }

   if (op2_type != REGISTER)
   {
      _error = tr("Must have a register as destination operand");
      return code;
   }

   code.resize(2);
   unsigned short *data = (unsigned short *) code.data();
   
   *data = (opcode() << 11) | // opcode
      ((op2_val & 0x7) << 8) | // destination register
      ((op1_type & 0x7) << 5) | // source type
      ((op1_val & 0x1F)); // source val
   return code;
       
}

bool CTwoOperandInstruction::checkOperands(QStringList &operands)
{
   if (operands.size() != 2)
   {
      _error = tr("Passing %1 operands to instruction %2 which only allows two").arg(operands.size()).arg(name());
      return false;
   }

   // destination of a two operand instruction is always a register
   QString op1 = operands[0].toUpper();
   QString op2 = operands[1].toUpper();
   
   if (op2[0] != 'R' && op2 != "SP" && op2 != "PC")
   {
      _error = tr("Destination operand of %1 must be a register").arg(name());
      return false;
   }

   return true;
}

// ------------------------------------
// MOVE special case

bool CMOVE::checkOperands(QStringList &operands)
{
   if (operands.size() != 2)
   {
      _error = tr("Passing %1 operands to instruction %2 which only allows two").arg(operands.size()).arg(name());
      return false;
   }

   unsigned short op1_val;
   unsigned short op2_val;
   eOperandType op1_type;
   eOperandType op2_type;

   op1_type = tokenToOperandCode(operands[0], op1_val);
   op2_type = tokenToOperandCode(operands[1], op2_val);

   if (op1_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[0]);
      return false;
   }

   if (op2_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[1]);
      return false;
   }

   if ((op1_type == IMMEDIATE || op1_type == ADDRESS) && (op2_type == ADDRESS || op2_type == IMMEDIATE))
   {
      _error = tr("Only one operand can be an immediate/address");
      return false;
   }

   if (op2_type == IMMEDIATE)
   {
      _error = tr("Operand 2 cannot be an immediate value");
      return false;
   }

   return true;
}

QByteArray CMOVE::fullOpCode(QStringList &operands)
{
   QByteArray code;
   unsigned short op1_val;
   unsigned short op2_val;
   eOperandType op1_type;
   eOperandType op2_type;

   op1_type = tokenToOperandCode(operands[0], op1_val);
   op2_type = tokenToOperandCode(operands[1], op2_val);

   if (op1_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[0]);
      return code;
   }

   if (op2_type == INVALID)
   {
      _error = tr("invalid operand %1").arg(operands[1]);
      return code;
   }

   code.resize(4);
   unsigned short *data = (unsigned short *)code.data();
   data[0] = (opcode() << 11) | (hl << 9 )| (op1_type << 6) | (op2_type << 3);

   if (op1_type == IMMEDIATE || op1_type == ADDRESS)
   {
      // op1 is immediate/address so last 3 bits of the first 2 bytes word are the destination register index
      data[0] |= op2_val;
      data[1] = op1_val; // op1 is an immediate value
   }
   else
   {
      // op1 is a register (or so) so the last 3 bits of the first 2 bytes word are the source register index
      data[0] |= op1_val;
      data[1] = op2_val;
   }
   return code;
}

#define NEW_INST(a) if (up_name == #a)		\
   { \
      IInstruction *i = new C##a(); \
      i->opcode() = (a);	     \
      return i;			     \
   }

#define NEW_INST2(text,inst) if (up_name == #text)	\
   { \
      IInstruction *i = new C##inst(); \
      i->opcode() = (inst);	     \
      return i;			     \
   }

IInstruction *CInstructionFactory::create(const QString &name)
{
   QString up_name = name.toUpper();

   qDebug() << "Checking instruction " << up_name;

   if (up_name == "MOVE" || up_name == "MOVE.L" || up_name == "MOVE.H")
   {
      CMOVE *i = new CMOVE();
      i->opcode() = MOVE;
      if (up_name == "MOVE.L")
	 i->hl = 1;
      else if (up_name == "MOVE.H")
	 i->hl = 2;
      else
	 i->hl = 3;
      return i;
   }

   NEW_INST(PUSH);
   NEW_INST(POP);
   NEW_INST(ADD);
   NEW_INST(CMP);
   NEW_INST(SUB);
   NEW_INST(LSL);
   NEW_INST(LSR);
   NEW_INST(AND);
   NEW_INST(OR);
   NEW_INST(XOR);
   NEW_INST(NOT);

   NEW_INST(BGT);
   NEW_INST2(BCC,BGT);

   NEW_INST(BLT);
   NEW_INST2(BCS,BLT);

   NEW_INST(BEQ);
   NEW_INST(BNE);
   NEW_INST(BLE);
   NEW_INST(BGE);
   NEW_INST(BRA);

   NEW_INST(JGT);
   NEW_INST2(JCC,JGT);

   NEW_INST(JLT);
   NEW_INST2(JCS,JLT);

   NEW_INST(JEQ);
   NEW_INST(JNE);
   NEW_INST(JLE);
   NEW_INST(JGE);
   NEW_INST(JMP);

   NEW_INST(BSR);
   NEW_INST(JSR);
   NEW_INST(RTS);
   NEW_INST(TRAP);
   NEW_INST(RTE);

   return NULL;
}

static const char *instr[] = {
   "MOVE",
   "PUSH",
   "POP",
//    "PUSHSR",
//    "POPSR",
   "ADD",
   "CMP",
   "SUB",
   "LSL",
   "LSR",
   "AND",
   "OR",
   "XOR",
   "NOT",

   "BCC/BGT",
   "BCS/BLT",
   "BEQ",
   "BNE",
//    "BLT",
   "BLE",
//    "BGT",
   "BGE",
   "BRA",
   "BSR",

   "JCC/JGT",
   "JCS/JLT",
   "JEQ",
   "JNE",
//    "JLT",
   "JLE",
//    "JGT",
   "JGE",
   "JMP",
   "JSR",

   "RTS",
   "TRAP",
   "RTE",
};

void IInstruction::listInstructions()
{

   for (int i = MOVE ; i <= RTE ; ++i)
   {
      printf("%-8s %02X(%02X) %d\n", instr[i], i, i << 3, i);
   }

};
