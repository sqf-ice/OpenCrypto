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

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sha3.h"

/*
 * echo -n 'A' > f.txt
 * openssl dgst -sha3-512 f.txt
 */

/* test vectors from https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values */


int main(int argc, char *argv[])
{
	int i;
	sha3_ctx_t ctx;
	uint8_t vec[] = {"A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3A3"};

	/* shake-128, message of length 0
	 * https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE128_Msg0.pdf
	 */
	uint8_t expected1[] = {
		"7F9C2BA4E88F827D616045507605853E"
			"D73B8093F6EFBC88EB1A6EACFA66EF26"
			"3CB1EEA988004B93103CFB0AEEFD2A68"
			"6E01FA4A58E8A3639CA8A1E3F9AE57E2"
			"35B8CC873C23DC62B8D260169AFA2F75"
			"AB916A58D974918835D25E6A435085B2"
			"BADFD6DFAAC359A5EFBB7BCC4B59D538"
			"DF9A04302E10C8BC1CBF1A0B3A5120EA"
			"17CDA7CFAD765F5623474D368CCCA8AF"
			"0007CD9F5E4C849F167A580B14AABDEF"
			"AEE7EEF47CB0FCA9767BE1FDA69419DF"
			"B927E9DF07348B196691ABAEB580B32D"
			"EF58538B8D23F87732EA63B02B4FA0F4"
			"873360E2841928CD60DD4CEE8CC0D4C9"
			"22A96188D032675C8AC850933C7AFF15"
			"33B94C834ADBB69C6115BAD4692D8619"
			"F90B0CDF8A7B9C264029AC185B70B83F"
			"2801F2F4B3F70C593EA3AEEB613A7F1B"
			"1DE33FD75081F592305F2E4526EDC096"
			"31B10958F464D889F31BA010250FDA7F"
			"1368EC2967FC84EF2AE9AFF268E0B170"
			"0AFFC6820B523A3D917135F2DFF2EE06"
			"BFE72B3124721D4A26C04E53A75E30E7"
			"3A7A9C4A95D91C55D495E9F51DD0B5E9"
			"D83C6D5E8CE803AA62B8D654DB53D09B"
			"8DCFF273CDFEB573FAD8BCD45578BEC2"
			"E770D01EFDE86E721A3F7C6CCE275DAB"
			"E6E2143F1AF18DA7EFDDC4C7B70B5E34"
			"5DB93CC936BEA323491CCB38A388F546"
			"A9FF00DD4E1300B9B2153D2041D205B4"
			"43E41B45A653F2A5C4492C1ADD544512"
			"DDA2529833462B71A41A45BE97290B6F"};	

	/* shake-128, 1600-bit message
	 * https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE128_Msg1600.pdf
	 */
	uint8_t expected2[] = {
		"131AB8D2B594946B9C81333F9BB6E0CE"
			"75C3B93104FA3469D3917457385DA037"
			"CF232EF7164A6D1EB448C8908186AD85"
			"2D3F85A5CF28DA1AB6FE343817197846"
			"7F1C05D58C7EF38C284C41F6C2221A76"
			"F12AB1C04082660250802294FB871802"
			"13FDEF5B0ECB7DF50CA1F8555BE14D32"
			"E10F6EDCDE892C09424B29F597AFC270"
			"C904556BFCB47A7D40778D390923642B"
			"3CBD0579E60908D5A000C1D08B98EF93"
			"3F806445BF87F8B009BA9E94F7266122"
			"ED7AC24E5E266C42A82FA1BBEFB7B8DB"
			"0066E16A85E0493F07DF4809AEC084A5"
			"93748AC3DDE5A6D7AAE1E8B6E5352B2D"
			"71EFBB47D4CAEED5E6D633805D2D323E"
			"6FD81B4684B93A2677D45E7421C2C6AE"
			"A259B855A698FD7D13477A1FE53E5A4A"
			"6197DBEC5CE95F505B520BCD9570C4A8"
			"265A7E01F89C0C002C59BFEC6CD4A5C1"
			"09258953EE5EE70CD577EE217AF21FA7"
			"0178F0946C9BF6CA8751793479F6B537"
			"737E40B6ED28511D8A2D7E73EB75F8DA"
			"AC912FF906E0AB955B083BAC45A8E5E9"
			"B744C8506F37E9B4E749A184B30F43EB"
			"188D855F1B70D71FF3E50C537AC1B0F8"
			"974F0FE1A6AD295BA42F6AEC74D123A7"
			"ABEDDE6E2C0711CAB36BE5ACB1A5A11A"
			"4B1DB08BA6982EFCCD716929A7741CFC"
			"63AA4435E0B69A9063E880795C3DC5EF"
			"3272E11C497A91ACF699FEFEE206227A"
			"44C9FB359FD56AC0A9A75A743CFF6862"
			"F17D7259AB075216C0699511643B6439"};

	/* shake-256, message of length 0
	 * https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE256_Msg0.pdf
	 */
	uint8_t expected3[] = {
		"46B9DD2B0BA88D13233B3FEB743EEB24"
			"3FCD52EA62B81B82B50C27646ED5762F"
			"D75DC4DDD8C0F200CB05019D67B592F6"
			"FC821C49479AB48640292EACB3B7C4BE"
			"141E96616FB13957692CC7EDD0B45AE3"
			"DC07223C8E92937BEF84BC0EAB862853"
			"349EC75546F58FB7C2775C38462C5010"
			"D846C185C15111E595522A6BCD16CF86"
			"F3D122109E3B1FDD943B6AEC468A2D62"
			"1A7C06C6A957C62B54DAFC3BE87567D6"
			"77231395F6147293B68CEAB7A9E0C58D"
			"864E8EFDE4E1B9A46CBE854713672F5C"
			"AAAE314ED9083DAB4B099F8E300F01B8"
			"650F1F4B1D8FCF3F3CB53FB8E9EB2EA2"
			"03BDC970F50AE55428A91F7F53AC266B"
			"28419C3778A15FD248D339EDE785FB7F"
			"5A1AAA96D313EACC890936C173CDCD0F"
			"AB882C45755FEB3AED96D477FF96390B"
			"F9A66D1368B208E21F7C10D04A3DBD4E"
			"360633E5DB4B602601C14CEA737DB3DC"
			"F722632CC77851CBDDE2AAF0A33A07B3"
			"73445DF490CC8FC1E4160FF118378F11"
			"F0477DE055A81A9EDA57A4A2CFB0C839"
			"29D310912F729EC6CFA36C6AC6A75837"
			"143045D791CC85EFF5B21932F23861BC"
			"F23A52B5DA67EAF7BAAE0F5FB1369DB7"
			"8F3AC45F8C4AC5671D85735CDDDB09D2"
			"B1E34A1FC066FF4A162CB263D6541274"
			"AE2FCC865F618ABE27C124CD8B074CCD"
			"516301B91875824D09958F341EF274BD"
			"AB0BAE316339894304E35877B0C28A9B"
			"1FD166C796B9CC258A064A8F57E27F2A"};

	/* shake-256, 1600-bit message
	 * https://csrc.nist.gov/CSRC/media/Projects/Cryptographic-Standards-and-Guidelines/documents/examples/SHAKE256_Msg1600.pdf
	 */
	uint8_t expected4[] = {
		"CD8A920ED141AA0407A22D59288652E9"
			"D9F1A7EE0C1E7C1CA699424DA84A904D"
			"2D700CAAE7396ECE96604440577DA4F3"
			"AA22AEB8857F961C4CD8E06F0AE6610B"
			"1048A7F64E1074CD629E85AD7566048E"
			"FC4FB500B486A3309A8F26724C0ED628"
			"001A1099422468DE726F1061D99EB9E9"
			"3604D5AA7467D4B1BD6484582A384317"
			"D7F47D750B8F5499512BB85A226C4243"
			"556E696F6BD072C5AA2D9B69730244B5"
			"6853D16970AD817E213E470618178001"
			"C9FB56C54FEFA5FEE67D2DA524BB3B0B"
			"61EF0E9114A92CDBB6CCCB98615CFE76"
			"E3510DD88D1CC28FF99287512F24BFAF"
			"A1A76877B6F37198E3A641C68A7C42D4"
			"5FA7ACC10DAE5F3CEFB7B735F12D4E58"
			"9F7A456E78C0F5E4C4471FFFA5E4FA05"
			"14AE974D8C2648513B5DB494CEA84715"
			"6D277AD0E141C24C7839064CD08851BC"
			"2E7CA109FD4E251C35BB0A04FB05B364"
			"FF8C4D8B59BC303E25328C09A882E952"
			"518E1A8AE0FF265D61C465896973D749"
			"0499DC639FB8502B39456791B1B6EC5B"
			"CC5D9AC36A6DF622A070D43FED781F5F"
			"149F7B62675E7D1A4D6DEC48C1C71645"
			"86EAE06A51208C0B791244D307726505"
			"C3AD4B26B6822377257AA152037560A7"
			"39714A3CA79BD605547C9B78DD1F596F"
			"2D4F1791BC689A0E9B799A37339C0427"
			"5733740143EF5D2B58B96A363D4E0807"
			"6A1A9D7846436E4DCA5728B6F760EEF0"
			"CA92BF0BE5615E96959D767197A0BEEB"};

	uint8_t msg[20];
	uint8_t exp1[512];
	uint8_t exp2[512];
	uint8_t exp3[512];
	uint8_t exp4[512];
	uint8_t out[512];

	hex2ba(vec, msg, sizeof(msg));
	hex2ba(expected1, exp1, sizeof(exp1));
	hex2ba(expected2, exp2, sizeof(exp2));
	hex2ba(expected3, exp3, sizeof(exp3));
	hex2ba(expected4, exp4, sizeof(exp4));

	shake128_init(&ctx);
	shake_xof(&ctx);
	for (i=0; i<512; i+=32)
		shake_out(&ctx, &out[i], 32);
	assert(!memcmp(exp1, out, sizeof(exp1)));

	shake128_init(&ctx);
	for (i=0; i<200; i+=20)
		shake_update(&ctx, msg, 20);
	shake_xof(&ctx);
	for (i=0; i<512; i+=32)
		shake_out(&ctx, &out[i], 32);
	assert(!memcmp(exp2, out, sizeof(exp2)));

	shake256_init(&ctx);
	shake_xof(&ctx);
	for (i=0; i<512; i+=32)
		shake_out(&ctx, &out[i], 32);
	assert(!memcmp(exp3, out, sizeof(exp3)));

	shake256_init(&ctx);
	for (i=0; i<200; i+=20)
		shake_update(&ctx, msg, 20);
	shake_xof(&ctx);
	for (i=0; i<512; i+=32)
		shake_out(&ctx, &out[i], 32);
	assert(!memcmp(exp4, out, sizeof(exp4)));

	printf("ALL TESTS PASSED!\n");
	return 0;
}
