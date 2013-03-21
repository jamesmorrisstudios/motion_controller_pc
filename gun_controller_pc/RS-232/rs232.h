/*
***************************************************************************
*
* Author: Teunis van Beelen
*
* Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013 Teunis van Beelen
*
* teuniz@gmail.com
*
***************************************************************************
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation version 2 of the License.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
***************************************************************************
*
* This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
*
***************************************************************************
*/

/* last revision: February 1, 2013 */

/* For more info and how to use this libray, visit: http://www.teuniz.net/RS-232/ */

#include "../standardInclude.h"

#ifndef RS232_H
#define RS232_H

class RS232
{
public:
	RS232();
	int OpenComport(int, int);
	int PollComport(int, unsigned char *, int);
	int SendByte(int, unsigned char);
	int SendBuf(int, unsigned char *, int);
	void CloseComport(int);
	void cputs(int, const char *);
	int IsCTSEnabled(int);
	int IsDSREnabled(int);
	void enableDTR(int);
	void disableDTR(int);
	void enableRTS(int);
	void disableRTS(int);
};
#endif //RS232_H

