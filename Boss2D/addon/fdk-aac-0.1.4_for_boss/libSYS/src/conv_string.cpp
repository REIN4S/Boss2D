
/* -----------------------------------------------------------------------------------------------------------
Software License for The Fraunhofer FDK AAC Codec Library for Android

?Copyright  1995 - 2013 Fraunhofer-Gesellschaft zur F?derung der angewandten Forschung e.V.
  All rights reserved.

 1.    INTRODUCTION
The Fraunhofer FDK AAC Codec Library for Android ("FDK AAC Codec") is software that implements
the MPEG Advanced Audio Coding ("AAC") encoding and decoding scheme for digital audio.
This FDK AAC Codec software is intended to be used on a wide variety of Android devices.

AAC's HE-AAC and HE-AAC v2 versions are regarded as today's most efficient general perceptual
audio codecs. AAC-ELD is considered the best-performing full-bandwidth communications codec by
independent studies and is widely deployed. AAC has been standardized by ISO and IEC as part
of the MPEG specifications.

Patent licenses for necessary patent claims for the FDK AAC Codec (including those of Fraunhofer)
may be obtained through Via Licensing (www.vialicensing.com) or through the respective patent owners
individually for the purpose of encoding or decoding bit streams in products that are compliant with
the ISO/IEC MPEG audio standards. Please note that most manufacturers of Android devices already license
these patent claims through Via Licensing or directly from the patent owners, and therefore FDK AAC Codec
software may already be covered under those patent licenses when it is used for those licensed purposes only.

Commercially-licensed AAC software libraries, including floating-point versions with enhanced sound quality,
are also available from Fraunhofer. Users are encouraged to check the Fraunhofer website for additional
applications information and documentation.

2.    COPYRIGHT LICENSE

Redistribution and use in source and binary forms, with or without modification, are permitted without
payment of copyright license fees provided that you satisfy the following conditions:

You must retain the complete text of this software license in redistributions of the FDK AAC Codec or
your modifications thereto in source code form.

You must retain the complete text of this software license in the documentation and/or other materials
provided with redistributions of the FDK AAC Codec or your modifications thereto in binary form.
You must make available free of charge copies of the complete source code of the FDK AAC Codec and your
modifications thereto to recipients of copies in binary form.

The name of Fraunhofer may not be used to endorse or promote products derived from this library without
prior written permission.

You may not charge copyright license fees for anyone to use, copy or distribute the FDK AAC Codec
software or your modifications thereto.

Your modified versions of the FDK AAC Codec must carry prominent notices stating that you changed the software
and the date of any change. For modified versions of the FDK AAC Codec, the term
"Fraunhofer FDK AAC Codec Library for Android" must be replaced by the term
"Third-Party Modified Version of the Fraunhofer FDK AAC Codec Library for Android."

3.    NO PATENT LICENSE

NO EXPRESS OR IMPLIED LICENSES TO ANY PATENT CLAIMS, including without limitation the patents of Fraunhofer,
ARE GRANTED BY THIS SOFTWARE LICENSE. Fraunhofer provides no warranty of patent non-infringement with
respect to this software.

You may use this FDK AAC Codec software or modifications thereto only for purposes that are authorized
by appropriate patent licenses.

4.    DISCLAIMER

This FDK AAC Codec software is provided by Fraunhofer on behalf of the copyright holders and contributors
"AS IS" and WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, including but not limited to the implied warranties
of merchantability and fitness for a particular purpose. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE for any direct, indirect, incidental, special, exemplary, or consequential damages,
including but not limited to procurement of substitute goods or services; loss of use, data, or profits,
or business interruption, however caused and on any theory of liability, whether in contract, strict
liability, or tort (including negligence), arising in any way out of the use of this software, even if
advised of the possibility of such damage.

5.    CONTACT INFORMATION

Fraunhofer Institute for Integrated Circuits IIS
Attention: Audio and Multimedia Departments - FDK AAC LL
Am Wolfsmantel 33
91058 Erlangen, Germany

www.iis.fraunhofer.de/amm
amm-info@iis.fraunhofer.de
----------------------------------------------------------------------------------------------------------- */

/**************************  Fraunhofer IIS FDK SysLib  **********************

   Author(s):
   Description: string conversion functions

******************************************************************************/



#include BOSS_FDKAAC_U_genericStds_h //original-code:"genericStds.h"
#include BOSS_FDKAAC_U_conv_string_h //original-code:"conv_string.h"

INT charBuf2HexString(char *string, UCHAR *charBuf, INT charBufLength)
{
  INT i;
  UCHAR c1, c2;

  /* sanity checks */
  /* check array length */
  if (charBufLength == 0) {
    return -1;
  }

  /* define hex string Table */
  UCHAR hexSymb[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

  /* calculate corresponding hex string from charBuffer */
  for (i=0;i<charBufLength;i++) {
    c1 = ((charBuf[i])>>4)&0x0f; /* upper nibble */
    c2 = (charBuf[i])&0x0f;      /* lower nibble */

    string[i*2]   = hexSymb[c1];  /* convert to string */
    string[i*2+1] = hexSymb[c2];  /* convert to string */
  }

  /* terminate string */
  string[charBufLength<<1]='\0';

  return 0;

}

INT hexString2CharBuf(const char *string, UCHAR *charBuf, UINT charBufLength)
{
  UINT i, k = 0;
  UCHAR hNibble, lNibble;

  /* sanity checks */
  if (string[0] == '\0') {
    return -1; /* invalid string size */
  }

  if (charBufLength<=0){
    return -2; /* invalid buffer size */
  }

  /* convert to hex characters to corresponding 8bit value */
  for (i=0;(string[i]!='\0')&&((i>>1)<charBufLength);i+=2) {
    k = i>>1;
    hNibble = hexChar2Dec(string[i]);
    lNibble = hexChar2Dec(string[i+1]);
    if ((hNibble == 16) || (lNibble == 16)) {
      return -3; /* invalid character */
    }
    charBuf[k] = ((hNibble<<4)&0xf0) + lNibble;
  }

  /* check if last character was string terminator */
  if ((string[i-2]!=0) && (string[i]!=0)) {
    return -1; /* invalid string size */
  }

  /* fill charBuffer with zeros */
  for (i=k+1;i<charBufLength;i++) {
    charBuf[i] = 0;
  }

  return 0;

}

UCHAR hexChar2Dec(const char c)
{
  INT r = 0;
  if ((c >= '0') && (c <= '9'))
    r = c-'0';
  else if ((c >= 'a') && (c <= 'f'))
    r = c-'a'+10;
  else if ((c >= 'A') && (c <= 'F'))
    r = c-'A'+10;
  else
    r = 16; /* invalid hex character */

  return (UCHAR)r;
}
