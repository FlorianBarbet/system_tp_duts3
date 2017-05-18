#include "assembler.h"
#include "label.h"

#include "instructions.h"
#include <QtDebug>
#include <QTextStream>
#include <QDataStream>
#include <QStringList>
#include <QRegExp>
#include <iostream>

#include "label.h"
#include "config.h"


bool CAssembler::assemble(QFile &in, QFile &out)
{
   QTextStream ins(&in);
   QString s;
   int line_number = 0;
   bool error = false;

   _currentPC = FIRST_ADDRESS;
   _firstPass = true;
   _assembledProgram.clear();


   while (!ins.atEnd())
   {
      s = ins.readLine();
      if (!handleLine(s, ++line_number))
	 error = true;
   }
   if (error)
   {
      std::cerr << (const char *) tr("assembly failed").toAscii() <<std::endl;
      return false;
   }

   // first pass has been done
   // lets done the second one so that all the labels are ok
   _firstPass = false;
   error = false;
   _currentPC = FIRST_ADDRESS;
   line_number = 0;
   _assembledProgram.clear();
   ins.seek(0);
   while (!ins.atEnd())
   {
      s = ins.readLine();
      if (!handleLine(s, ++line_number))
	 error = true;
   }
   if (error)
   {
      std::cerr << (const char *) tr("assembly failed in second pass... something weired happened").toAscii() << std::endl;
      return false;
   }
   out.write(_assembledProgram);
   return true;
}

bool CAssembler::handleLine(QString &line, int lineNumber)
{
   qDebug() << QString("Processing line %1").arg(lineNumber);

   // asm line is : 1: an optional label, 2: an instruction, 3: operand1 (optional), 4: operand2, 5 comment
   QString reg_exp;

   reg_exp = "(";
   reg_exp += "^\\w+:"; // label
   reg_exp += "|r\\d"; // register

   reg_exp += "|\\(r\\d\\)"; // (register)
   reg_exp += "|-\\(r\\d\\)"; // -(register)
   reg_exp += "|\\(r\\d\\)\\+"; // (register)+

   reg_exp += "|\\(sp\\)"; // (sp)
   reg_exp += "|-\\(sp\\)"; // -(sp)
   reg_exp += "|\\(sp\\)\\+"; // (sp)+

   reg_exp += "|\\(pc\\)"; // (sp)
   reg_exp += "|-\\(pc\\)"; // -(sp)
   reg_exp += "|\\(pc\\)\\+"; // (sp)+

   reg_exp += "|#-?\\d+"; // immediate
   reg_exp += "|#0x[\\da-fA-F]+"; // immediate hexa
   reg_exp += "|#b[01]+"; // immediate binary
   reg_exp += "|@[\\da-fA-F]+"; // adress is always hexa
   reg_exp += "|[\\w\\.]+"; // identifier (instruction)
//   reg_exp += "|\\w+(\\.[lh])?"; // identifier (instruction)
   reg_exp += "|;.*"; // comment
   reg_exp += ")";

   QRegExp asm_line(reg_exp, Qt::CaseInsensitive);

   int pos = 0;
   QStringList tokens;
   while ((pos = asm_line.indexIn(line,pos)) > -1)
   {
      if (asm_line.cap(0)[0] != ';')
	 tokens << asm_line.cap(0).toUpper(); // not a comment
      pos += asm_line.matchedLength();
   }

   qDebug() << QString("Found %1 tokens").arg(tokens.size());


   if (tokens.size() == 0)
      return true;

   qDebug() << QString("PC: %1").arg(QString::number(_currentPC, 16));
   // now the line has been tokenized, lets analyse them
   // an assembly line starts with an optionnal label
   if (tokens.front().endsWith(":"))
   {
      tokens.front().chop(1);
      qDebug() << "Label: " << tokens.front();
      if (!CLabelHandler::get().registerLabel(tokens.front()) && _firstPass)
	 std::cerr << (const char*) QString("Line %1: label %2 already exists").arg(lineNumber).arg(tokens.front()).toAscii() << std::endl;
      tokens.pop_front();
   }
   

   if (tokens.size() == 0)
      return true; // a line can have only a label, not a problem

   // then the instruction
   IInstruction *i = CInstructionFactory::create(tokens.front());
   if (i != NULL)
      qDebug() << i->name();
   else
   {
      std::cerr << (const char *) QString("Line %1: unknown instruction %2").arg(lineNumber).arg(tokens.front()).toAscii() << std::endl;
      return false;
   }
   i->currentPC() = _currentPC;
   tokens.pop_front();
   
   qDebug() << tokens;
   if (!i->checkOperands(tokens))
   {
      std::cerr << (const char*) QString("Line %1: %2").arg(lineNumber).arg(i->error()).toAscii() << std::endl;
      delete i;
      return false;
   }
   
   qDebug() << QString("Instruction %1 has %2 operands").arg(i->name()).arg(i->operandCount());
   qDebug() << tokens;
   qDebug() << "The full opcode is";
   QByteArray opcode = i->fullOpCode(tokens);

   if (opcode.size() == 0)
      std::cerr << (const char*)  QString("Line %1: %2").arg(lineNumber).arg(i->error()).toAscii() << std::endl;

   //qDebug() << opcode.toHex();

   CLabelHandler::get().advanceAddr(opcode.size());
   _currentPC +=  opcode.size();
   
   _assembledProgram.append(opcode);
   delete i;
   return true;
}
