/* This file is part of cwasm.                        
 *									 
 * cwasm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by	 
 * the Free Software Foundation, either version 3 of the License, or	 
 * (at your option) any later version.					 
 * 									 
 * cwasm is distributed in the hope that it will be useful,		 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 
 * GNU General Public License for more details.				 
 * 									 
 * You should have received a copy of the GNU General Public License	 
 * along with cwasm.  If not, see <http://www.gnu.org/licenses/>.	 
 */

#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <QStringList>
#include <QCoreApplication>
#include <QByteArray>

class IInstruction
{
      Q_DECLARE_TR_FUNCTIONS(IInstruction);
   public:
      virtual ~IInstruction(){}

      virtual bool checkOperands(QStringList &operands) = 0;
      virtual QString name() const = 0;
      QString error() const { return _error; };

      // these functions/members will allow code generation


      // this function gets the full opcode of the instruction
      virtual QByteArray fullOpCode(QStringList &operands) = 0;

      // return the number of operand
      virtual int operandCount() const = 0;

      unsigned short &currentPC() {return _currentPC;}

      static void listInstructions();

   protected:
      typedef enum
      {
	 REGISTER,
	 PRE_DEC,
	 INDIRECT,
	 POST_INC,
	 IMMEDIATE,
	 ADDRESS,
	 INVALID,
      } eOperandType;

      friend class CInstructionFactory;
      // return the 5 bits opcode of the instruction
      virtual int &opcode() { return _opcode; };

      // return the "type" of the operand (IMMEDIATE, ADDRESS etc...
      virtual eOperandType tokenToOperandCode(const QString &token, unsigned short &code);

      QString _error;
      int _opcode;
      unsigned short _currentPC; // used to process relative labels
};

class CZeroOperandInstruction : public IInstruction
{
   public:
      virtual bool checkOperands(QStringList &operands);
      virtual int operandCount() const { return 0; }
      virtual QByteArray fullOpCode(QStringList &operands);
};

class COneOperandInstruction : public IInstruction
{
   public:
      virtual bool checkOperands(QStringList &operands);
      virtual int operandCount() const { return 1; }
      virtual QByteArray fullOpCode(QStringList &operands);
};

class CTwoOperandInstruction : public IInstruction
{
   public:
      virtual bool checkOperands(QStringList &operands);
      virtual int operandCount() const { return 2; }
      virtual QByteArray fullOpCode(QStringList &operands);
};


class CInstructionFactory
{
   public:
      static IInstruction *create(const QString &name);
};


// the instructions

class CMOVE : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "MOVE"; }
      virtual QByteArray fullOpCode(QStringList &operands);
      virtual bool checkOperands(QStringList &operands);

      int hl;
};

class CPUSH : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "PUSH"; }
};

class CPOP : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "POP"; }
};

class CADD : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "ADD"; }
};

class CCMP : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "CMP"; }
};

class CSUB : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "SUB"; }
};

class CLSL : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "LSL"; }
};

class CLSR : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "LSR"; }
};

class CAND : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "AND"; }
};

class COR : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "OR"; }
};

class CXOR : public CTwoOperandInstruction
{
   public:
      virtual QString name() const { return "XOR"; }
};

class CNOT : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "NOT"; }
};



class CBEQ : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BEQ"; }
};

class CBNE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BNE"; }
};

class CBLT : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BLT"; }
};

class CBLE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BLE"; }
};

class CBGT : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BGT"; }
};

class CBGE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BGE"; }
};


class CBRA : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BRA"; }
};

// -------------------------------------

class CJEQ : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JEQ"; }
};

class CJNE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JNE"; }
};

class CJLT : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JLT"; }
};

class CJLE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JLE"; }
};

class CJGT : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JGT"; }
};

class CJGE : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JGE"; }
};


class CJMP : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JMP"; }
};

// ------------------------------------------------

class CBSR : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "BSR"; }
};

class CJSR : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "JSR"; }
};

class CRTS : public CZeroOperandInstruction
{
   public:
      virtual QString name() const { return "RTS"; }
};

class CTRAP : public COneOperandInstruction
{
   public:
      virtual QString name() const { return "TRAP"; }
};

class CRTE : public CZeroOperandInstruction
{
   public:
      virtual QString name() const { return "RTE"; }
};



enum
{
   MOVE = 0,
   PUSH,
   POP,
   ADD,
   CMP,
   SUB,
   LSL,
   LSR,
   AND,
   OR,
   XOR,
   NOT,

   BCC,
   BGT = BCC,
   BCS, 
   BLT = BCS,
   BEQ,
   BNE,
   BLE,
   BGE,
   BRA,
   BSR,

   JCC,
   JGT = JCC,
   JCS,
   JLT = JCS,
   JEQ,
   JNE,
   JLE,
   JGE,
   JMP,
   JSR,

   RTS,
   TRAP,
   RTE,
};




#endif
