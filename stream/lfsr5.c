/*
   Copyright 2020 Andrew Li, Gavin Li

   li.andrew.mail@gmail.com
   gavinux@gmail.com

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdint.h>

/*
 * y = x^5 + x^2 + 1 (0,2,5)
 * maximum length = 2^m - 1 = 2^5-1=31
 */
uint32_t lfsr5(void)
{
	static uint8_t lfsr = 3;
	lfsr = lfsr >> 1 | ((lfsr & (1<<2) ? 1:0) ^ (lfsr & 1)) << (5-1);
	return lfsr;
}

