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
#ifndef __LABEL_H__
#define __LABEL_H__

#include <map>
#include <QString>

#define FIRST_ADDRESS 0x10

class CLabelHandler
{
   public:
      static CLabelHandler &get();

      bool absolute(const QString &label, unsigned short &addr) const;
      bool relative(const QString &label, unsigned short PC, short &addr) const;
      
      bool registerLabel(const QString &label);

      void advanceAddr(int byteCount);

   protected:
      CLabelHandler();

      typedef std::map<QString, unsigned short> LabelList;
      LabelList _labels;
      unsigned short _currentAddr;
};

#endif
