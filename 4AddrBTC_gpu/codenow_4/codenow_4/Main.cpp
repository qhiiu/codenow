// // MAXX.SetBase10("115792089237316195423570985008687907852837564279074904382605163141518161494336"); // full
// MAXX.SetBase10("11579208923731619542357098500868790785283756427907490438260516314151"); // remove 10th-end

#include "Timer.h"
#include "KeyHunt.h"
#include "Base58.h"
#include <string>
#include <cassert>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <map>
#include <cstring>

using namespace std;
 
#define RANDOM 0
#define INPUT 1

//-----------------------------------------------------------------------
void CtrlHandler(int signum) {
	printf("\nBYE");
	printf("\nBYE\n\n");
	exit(signum);
}
//-----------------------------------------------------------------------
void check_file_exist(){
	FILE* file;
    file = fopen("$.txt", "r");
    if (file!=NULL)  {   
        printf("\n $.txt exists ======$$$$====== \n");
    	printf("\n.\n.\n.\n.\n.\n --- DONE !! check and take money !! ---- \n.\n.\n.\n.\n.\n.\n");

        exit(-1);   
    }
}
//-----------------------------------------------------------------------
uint64_t check_data(std::string priv)
{
    std::string fileName;
    fileName = "xData.txt";

    ifstream file(fileName);
    string line;
	uint64_t n = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            n += 1;
            if (priv == line){
              std::cout << std::endl <<"-------- Had in Database !!! exit() -------"<< std::endl << std::endl;
              exit(0);
            }
        }
        file.close();
    } else {   
        std::cout << "\n\nErr file !!! Don't have file : " << fileName << std::endl;
        exit(-1);
    }
	return n;
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------
//---CODENOW - START  --------------------------------------------------------------------

//============== BECH_32 - start ================================================================================
	static const char* charset = "qpzry9x8gf2tvdw0s3jn54khce6mua7l";
	
//----------------------------------------------------------
	static int convert_bits(uint8_t* out, size_t* outlen, int outbits, const uint8_t* in, size_t inlen, int inbits, int pad) {
	uint32_t val = 0;
	int bits = 0;
	uint32_t maxv = (((uint32_t)1) << outbits) - 1;
	while (inlen--) {
		val = (val << inbits) | *(in++);
		bits += inbits;
		while (bits >= outbits) {
		bits -= outbits;
		out[(*outlen)++] = (val >> bits) & maxv;
		}
	}
	if (pad) {
		if (bits) {
		out[(*outlen)++] = (val << (outbits - bits)) & maxv;
		}
	} else if (((val << (outbits - bits)) & maxv) || bits >= inbits) {
		return 0;
	}
	return 1;
	}

//----------------------------------------------------------
	uint32_t bech32_polymod_step(uint32_t pre) {
	uint8_t b = pre >> 25;
	return ((pre & 0x1FFFFFF) << 5) ^
		(-((b >> 0) & 1) & 0x3b6a57b2UL) ^
		(-((b >> 1) & 1) & 0x26508e6dUL) ^
		(-((b >> 2) & 1) & 0x1ea119faUL) ^
		(-((b >> 3) & 1) & 0x3d4233ddUL) ^
		(-((b >> 4) & 1) & 0x2a1462b3UL);
	}

//----------------------------------------------------------
	int bech32_encode(char *output, const char *hrp, const uint8_t *data, size_t data_len) {
	uint32_t chk = 1;
	size_t i = 0;
	while (hrp[i] != 0) {
		int ch = hrp[i];
		if (ch < 33 || ch > 126) {
		return 0;
		}

		if (ch >= 'A' && ch <= 'Z') return 0;
		chk = bech32_polymod_step(chk) ^ (ch >> 5);
		++i;
	}
	if (i + 7 + data_len > 90) return 0;
	chk = bech32_polymod_step(chk);
	while (*hrp != 0) {
		chk = bech32_polymod_step(chk) ^ (*hrp & 0x1f);
		*(output++) = *(hrp++);
	}
	*(output++) = '1';
	for (i = 0; i < data_len; ++i) {
		if (*data >> 5) return 0;
		chk = bech32_polymod_step(chk) ^ (*data);
		*(output++) = charset[*(data++)];
	}
	for (i = 0; i < 6; ++i) {
		chk = bech32_polymod_step(chk);
	}
	chk ^= 1;
	for (i = 0; i < 6; ++i) {
		*(output++) = charset[(chk >> ((5 - i) * 5)) & 0x1f];
	}
	*output = 0;
	return 1;
	}

//----------------------------------------------------------
int segwit_addr_encode(char *output, const char *hrp, int witver, const uint8_t *witprog, size_t witprog_len) {
	uint8_t data[65];
	size_t datalen = 0;
	if (witver > 16) return 0;
	if (witver == 0 && witprog_len != 20 && witprog_len != 32) return 0;
	if (witprog_len < 2 || witprog_len > 40) return 0;
	data[0] = witver;
	convert_bits(data + 1, &datalen, 5, witprog, witprog_len, 8, 1);
	++datalen;
	return bech32_encode(output, hrp, data, datalen);
}

//============== BECH_32 - end ================================================================================

//======================== HIIU_DECODE_BECH32 - START ====================================================================
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <cstdio>

static const int8_t charset_rev[128] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    15, -1, 10, 17, 21, 20, 26, 30,  7,  5, -1, -1, -1, -1, -1, -1,
    -1, 29, -1, 24, 13, 25,  9,  8, 23, -1, 18, 22, 31, 27, 19, -1,
     1,  0,  3, 16, 11, 28, 12, 14,  6,  4,  2, -1, -1, -1, -1, -1,
    -1, 29, -1, 24, 13, 25,  9,  8, 23, -1, 18, 22, 31, 27, 19, -1,
     1,  0,  3, 16, 11, 28, 12, 14,  6,  4,  2, -1, -1, -1, -1, -1
};

int bech32_decode_nocheck(uint8_t *data, size_t *data_len, const char *input) {

  uint8_t acc=0;
  uint8_t acc_len=8;
  size_t out_len=0;

  size_t input_len = strlen(input);
  for (int i = 0; i < input_len; i++) {

    if(input[i]&0x80)
      return false;

    int8_t c = charset_rev[tolower(input[i])];
    if(c<0)
      return false;

    if (acc_len >= 5) {
      acc |= c << (acc_len - 5);
      acc_len -= 5;
    } else {
      int shift = 5 - acc_len;
      data[out_len++] = acc | (c >> shift);
      acc_len = 8-shift;
      acc = c << acc_len;
    }

  }

  data[out_len++] = acc;
  *data_len = out_len;

  return true;

}

int bech32_decode(char* hrp, uint8_t *data, size_t *data_len, const char *input) {
  uint32_t chk = 1;
  size_t i;
  size_t input_len = strlen(input);
  size_t hrp_len;
  int have_lower = 0, have_upper = 0;
  if (input_len < 8 || input_len > 90) {
    return 0;
  }
  *data_len = 0;
  while (*data_len < input_len && input[(input_len - 1) - *data_len] != '1') {
    ++(*data_len);
  }
  hrp_len = input_len - (1 + *data_len);
  if (1 + *data_len >= input_len || *data_len < 6) {
    return 0;
  }
  *(data_len) -= 6;
  for (i = 0; i < hrp_len; ++i) {
    int ch = input[i];
    if (ch < 33 || ch > 126) {
      return 0;
    }
    if (ch >= 'a' && ch <= 'z') {
      have_lower = 1;
    } else if (ch >= 'A' && ch <= 'Z') {
      have_upper = 1;
      ch = (ch - 'A') + 'a';
    }
    hrp[i] = ch;
    chk = bech32_polymod_step(chk) ^ (ch >> 5);
  }
  hrp[i] = 0;
  chk = bech32_polymod_step(chk);
  for (i = 0; i < hrp_len; ++i) {
    chk = bech32_polymod_step(chk) ^ (input[i] & 0x1f);
  }
  ++i;
  while (i < input_len) {
    int v = (input[i] & 0x80) ? -1 : charset_rev[(int)input[i]];
    if (input[i] >= 'a' && input[i] <= 'z') have_lower = 1;
    if (input[i] >= 'A' && input[i] <= 'Z') have_upper = 1;
    if (v == -1) {
      return 0;
    }
    chk = bech32_polymod_step(chk) ^ v;
    if (i + 6 < input_len) {
      data[i - (1 + hrp_len)] = v;
    }
    ++i;
  }
  if (have_lower && have_upper) {
    return 0;
  }
  return chk == 1;
}


int segwit_addr_decode(int* witver, uint8_t* witdata, size_t* witdata_len, const char* hrp, const char* addr) {
  uint8_t data[84];
  char hrp_actual[84];
  size_t data_len;
  if (!bech32_decode(hrp_actual, data, &data_len, addr)) return 0;
  if (data_len == 0 || data_len > 65) return 0;
  if (strncmp(hrp, hrp_actual, 84) != 0) return 0;
  if (data[0] > 16) return 0;
  *witdata_len = 0;
  if (!convert_bits(witdata, witdata_len, 8, data + 1, data_len - 1, 5, 0)) return 0;
  if (*witdata_len < 2 || *witdata_len > 40) return 0;
  if (data[0] == 0 && *witdata_len != 20 && *witdata_len != 32) return 0;
  *witver = data[0];
  return 1;
}

//-------------------------------------------------------

void hiiu_decodeBech32(const char* addr,  uint32_t* _hash160) {
    unsigned char hash[20];   // Mảng lưu hash160
    size_t witdata_len;
    int witver;
    // const char* addr = "bc1qyr2956nky56hqr8fuzepdccejse4mw994lyftn";

    // Giải mã địa chỉ SegWit thành hash160
    segwit_addr_decode(&witver, hash, &witdata_len, "bc", addr);
    
    // printf("\nhash160: ");
    // for (size_t i = 0; i < witdata_len; i++) {  printf("%02x", hash[i]); }

	// 20 bytes --> uint32_t _hash160[5]
	memcpy(_hash160, hash, 20);

}
//======================== HIIU_DECODE_BECH32 - END ====================================================================

//---CODENOW - START  --------------------------------------------------------------------

void hiiu_decodeBase58(std::string address, uint32_t* _hash160){
	// std::cout << address; 

	vector<unsigned char> hashORxpoint;
	hashORxpoint.clear();

	if (DecodeBase58(address, hashORxpoint)) {
		hashORxpoint.erase(hashORxpoint.begin() + 0);
		hashORxpoint.erase(hashORxpoint.begin() + 20, hashORxpoint.begin() + 24);
	}

	uint8_t hash160Keccak[20];

	for (size_t i = 0; i < hashORxpoint.size(); i++) {
		hash160Keccak[i] = hashORxpoint.at(i); // --- hash160 đây hash160Keccak[i]
	}
	
	// 20 bytes --> uint32_t _hash160[5]
	memcpy(_hash160 , hash160Keccak , 20);
}





//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
void init_value(int mode, uint64_t xN,Int& privDec, Int& rangeStart, Int& rangeEnd)
{
    Int MINN, MAXX;
    MINN.SetBase10("0");
    // MAXX.SetBase16("fffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364140"); // full
    MAXX.SetBase10("11579208923731619542357098500868790785283756427907490438260516314151"); // remove 10th-end
    // std::cout << std::endl << "MAXX-10 : " << MAXX.GetBase10();
    // std::cout << std::endl << "MAXX-16 : " <<  MAXX.GetBase16();

    switch (mode){
        case RANDOM:
            privDec.Rand(&MAXX);
            // std::cout << std::endl << "privDec-10 : " << privDec.GetBase10();
            // std::cout << std::endl << "privDec-16 : " << privDec.GetBase16();
            break;

        case INPUT:
            std::cout << "\nRANGE__INPUT : "<< MINN.GetBase10() << " - " << MAXX.GetBase10();
            char* input_privDec = new char[64];

            while (true) 
            {
                std::cout << "\ninput__privDec : "; 
                cin.getline(input_privDec, 64);

                privDec.SetBase10(input_privDec);     

                if (privDec.IsGreaterOrEqual(&MINN) && privDec.IsLowerOrEqual(&MAXX)){ 
                    break; 
                }
            }

            // break;
        }

        // set _10B
        Int _10B, _xN10B;
        _10B.SetBase10("10000000000"); 
        // set xN10B = _10B then multiple to xN
        _xN10B = _10B;
        _xN10B.Mult(xN); 


        //set --- rangeStart
        rangeStart = privDec; 
        rangeStart.Mult(&_10B);
        // std::cout << std::endl << "rangeStart-10 :  " << rangeStart.GetBase10();
        // std::cout << std::endl << "rangeStart-16 :  " << rangeStart.GetBase16() << std::endl;

        //set --- rangEnd
        rangeEnd = rangeStart;
        rangeEnd.Add(&_xN10B);
        // std::cout << std::endl << "rangeEnd-10 :    " << rangeEnd.GetBase10();
        // std::cout << std::endl << "rangeEnd-16 :    " << rangeEnd.GetBase16() << std::endl;

        //print privDec info 
        uint64_t nChecked = 0;
        Int privDec_copy = privDec; 
        for (int i = 0; i < xN; i++){
            std::cout << "\nprivDec ======> " << privDec_copy.GetBase10(); //print 
            nChecked = check_data(privDec_copy.GetBase10()); // check priv 
            privDec_copy.AddOne(); // increase priv 
        } 
        std::cout << "\n\nnChecked : " << nChecked ; 


        //================= TEST-start ==================================================
 
        //13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so 
        //2832ed74f2b5e35ee 
        // rangeStart.SetBase16("2832ed74f00000000");
        // rangeEnd.SetBase16("2832ed74f2fffffff");


        // 1AUNPZwNmyDhxy7M4rVctPBW6dL2ZrG4fK
        //35da1daf9584d5308b54b0d753d93f59c5b55fdea71d8cccd9941ab73c21bfcc        rangeStart.SetBase16("2832ed74f00000000");
        rangeStart.SetBase16("35da1daf9584d5308b54b0d753d93f59c5b55fdea71d8cccd9941ab730000000");
        rangeEnd.SetBase16("35da1daf9584d5308b54b0d753d93f59c5b55fdea71d8cccd9941ab740000000");
        // rangeEnd.SetBase16("35da1daf9584d5308b54b0d753d93f59c5b55fdea71d8cccd9941ab750000000");

        //================= TEST-end ==================================================
    
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------


//---CODENOW - START  --------------------------------------------------------------------
// Function to trim leading and trailing spaces and newlines
void trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t\r\n"));  // Erase leading whitespaces and newline characters
    str.erase(str.find_last_not_of(" \t\r\n") + 1);  // Erase trailing whitespaces and newline characters
}

// Funtion to convert listAddr to array of data h[5]
void run(){

    check_file_exist(); // check file $.txt

	// Global Init
	Timer::Init();
	rseed(Timer::getSeed32());

	// bool gpuAutoGrid = true;
	vector<int> gpuId = { 0 };
	vector<int> gridSize;


    // std::string address = "";
	Int privDec, rangeStart, rangeEnd;

    //set value
    int xN = 1;
    int mode = RANDOM;
    init_value(mode, xN, privDec, rangeStart, rangeEnd);

	std::string outputFile = "$.txt";
    std::cout << "\n\nOUTPUT FILE  : " << outputFile;



    // =========================== listAddr -> arrData ----start ===========================
    ifstream file_data("hiiu_data_bitcoin.txt");
    string addr;

    // store number tpye of addr
    uint32_t n_P2PKH = 0;
    uint32_t n_P2SH = 0;
    uint32_t n_BECH32 = 0;

    if (file_data.is_open()) {
        while (getline(file_data, addr)) {
            std::string firstLetter_addr(1, addr[0]);

            if (firstLetter_addr == "1") { n_P2PKH++; } 
			if (firstLetter_addr == "3") { n_P2SH++; } 
			if (firstLetter_addr == "b") { n_BECH32++; }
        }   
        file_data.close();
    } else {   std::cout << "Err file_data !!!" << std::endl;   }




    // list array data to store each type
    uint32_t arrData_P2PKH[5 * n_P2PKH + 1]; 
    uint32_t arrData_P2SH[5 * n_P2SH  + 1]; 
    uint32_t arrData_BECH32[5 * n_BECH32 + 1];  

	arrData_P2PKH[0] 	= n_P2PKH;
	arrData_P2SH[0] 	= n_P2SH;
	arrData_BECH32[0] 	= n_BECH32;
	
	uint32_t gen_hash160[5];

    // reset n_counter
    n_P2PKH = 0;
    n_P2SH = 0;
    n_BECH32 = 0;

    ifstream fileData("hiiu_data_bitcoin.txt");
    string addrLine;

    if (fileData.is_open()) {
        while (getline(fileData, addrLine)) {

            trim(addrLine);  // remove extra spaces or newlines
            std::string firstLetter_addrLine(1, addrLine[0]);
			// std::cout << "\nfirstLetter : " << firstLetter_addrLine << "\n" ;

            // check firstLetter to know tpye of addr (P2PKH - P2SH - BECH32=SEGWIT)
			//----------------------------------------------
            if (firstLetter_addrLine == "1") {

				hiiu_decodeBase58(addrLine, gen_hash160);
				// print
				// for (int i = 0; i < 5; i++){	printf("\n ==> gen_hash160[%d] : %d ",i , gen_hash160[i]); };
				
				arrData_P2PKH[5 * n_P2PKH + 1] = gen_hash160[0];
				arrData_P2PKH[5 * n_P2PKH + 2] = gen_hash160[1];
				arrData_P2PKH[5 * n_P2PKH + 3] = gen_hash160[2];
				arrData_P2PKH[5 * n_P2PKH + 4] = gen_hash160[3];
				arrData_P2PKH[5 * n_P2PKH + 5] = gen_hash160[4];

				n_P2PKH++;
            } 

			//----------------------------------------------
			if (firstLetter_addrLine == "3") {

				hiiu_decodeBase58(addrLine, gen_hash160);	
				//print			
				// for (int i = 0; i < 5; i++){	printf("\n ==> gen_hash160[%d] : %d ",i , gen_hash160[i]); };
				
				arrData_P2SH[5 * n_P2SH + 1] = gen_hash160[0];
				arrData_P2SH[5 * n_P2SH + 2] = gen_hash160[1];
				arrData_P2SH[5 * n_P2SH + 3] = gen_hash160[2];
				arrData_P2SH[5 * n_P2SH + 4] = gen_hash160[3];
				arrData_P2SH[5 * n_P2SH + 5] = gen_hash160[4];

				n_P2SH++;
            } 

			//----------------------------------------------
			if (firstLetter_addrLine == "b") {
				
				// uint32_t gen_hash160[5];
				hiiu_decodeBech32(addrLine.c_str(), gen_hash160);	
				//print			
				// for (int i = 0; i < 5; i++){	printf("\n ==> gen_hash160[%d] : %d ",i , gen_hash160[i]); };
				
				arrData_BECH32[5 * n_BECH32 + 1] = gen_hash160[0];
				arrData_BECH32[5 * n_BECH32 + 2] = gen_hash160[1];
				arrData_BECH32[5 * n_BECH32 + 3] = gen_hash160[2];
				arrData_BECH32[5 * n_BECH32 + 4] = gen_hash160[3];
				arrData_BECH32[5 * n_BECH32 + 5] = gen_hash160[4];

				n_BECH32++;
            }

			// printf("\n");
        }   
        fileData.close();

    } else {   std::cout << "Err file_data !!!" << std::endl;   }

    // =========================== listAddr -> arrData ---- end ===========================


    if (gridSize.size() == 0) {
        for (int i = 0; i < gpuId.size(); i++) {
            gridSize.push_back(-1);
            gridSize.push_back(128);
        }
	}

	signal(SIGINT, CtrlHandler);

	KeyHunt* v;
    bool should_exit = false;
	// v = new KeyHunt(hash160_target, outputFile, rangeStart, rangeEnd, privDec, xN, P, should_exit);
	v = new KeyHunt(arrData_P2PKH, arrData_P2SH, arrData_BECH32, outputFile, rangeStart, rangeEnd, privDec, xN, should_exit);
	v->Search(gpuId, gridSize, should_exit);

	delete v;
}

int main(){
    run();
    
	return 0;
};