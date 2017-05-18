#include <QDebug>
#include "assembler.h"
#include "instructions.h"
#include "config.h"
#include <QFile>
#include <iostream>


int main(int argc, char * argv[])
{

   if (argc == 2)
   {
      if (strcmp(argv[1], "--list") == 0)
      {
	 IInstruction::listInstructions();
	 return 0;
      }
   }

   if (argc != 3)
   {
      std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
      return 1;
   }
   
   QFile in(argv[1]);

   if (!in.exists())
   {
      std::cerr << argv[1] << ": File does not exists" << std::endl;
      return 1;
   }

   if (!in.open(QIODevice::ReadOnly))
   {
      std::cerr << argv[1] << ": Cannot open file: " << (const char*) in.errorString().toAscii() << std::endl;
      return 1;
   }

   QFile out(argv[2]);
   
   if (!out.open(QIODevice::WriteOnly))
   {
      std::cerr << argv[2] << ": Cannot open file for writing: " << (const char*) out.errorString().toAscii() << std::endl;
      return 1;
   }

   CAssembler assembler;

   if (assembler.assemble(in, out))
      return 0;
   else
      return 1;
}
