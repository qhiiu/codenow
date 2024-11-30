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
    fileName = "x.txt";

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
void init_value(int mode, uint64_t xN,Int& priv_dec, Int& rangeStart, Int& rangeEnd)
{
	std::cout<< "===================================================\n";   

    map<int, char*> list_range_dec;
        list_range_dec[67] = "7378697629";
        list_range_dec[68] = "14757395258";
        list_range_dec[69] = "29514790517";
        list_range_dec[70] = "59029581035";
        list_range_dec[71] = "118059162071";
        list_range_dec[72] = "236118324143";
        list_range_dec[73] = "472236648286";
        list_range_dec[74] = "944473296573";
        list_range_dec[75] = "1888946593147";
        list_range_dec[76] = "3777893186295";
        list_range_dec[77] = "7555786372591";
        list_range_dec[78] = "15111572745182";
        list_range_dec[79] = "30223145490365";
        list_range_dec[80] = "60446290980731";
        list_range_dec[81] = "120892581961462";
        list_range_dec[82] = "241785163922925";
        list_range_dec[83] = "483570327845851";
        list_range_dec[84] = "967140655691703";
        list_range_dec[85] = "1934281311383406";
        list_range_dec[86] = "3868562622766813";
        list_range_dec[87] = "7737125245533626";
        list_range_dec[88] = "15474250491067253";
        list_range_dec[89] = "30948500982134506";
        list_range_dec[90] = "61897001964269013";
        list_range_dec[91] = "123794003928538027";
        list_range_dec[92] = "247588007857076054";
        list_range_dec[93] = "495176015714152109";
        list_range_dec[94] = "990352031428304219";
        list_range_dec[95] = "1980704062856608439";
        list_range_dec[96] = "3961408125713216879";
        list_range_dec[97] = "7922816251426433759";
        list_range_dec[98] = "15845632502852867518";
        list_range_dec[99] = "31691265005705735037";
        list_range_dec[100] = "63382530011411470074";
        list_range_dec[101] = "126765060022822940149";
        list_range_dec[102] = "253530120045645880299";
        list_range_dec[103] = "507060240091291760598";
        list_range_dec[104] = "1014120480182583521197";
        list_range_dec[105] = "2028240960365167042394";
        list_range_dec[106] = "4056481920730334084789";
        list_range_dec[107] = "8112963841460668169578";
        list_range_dec[108] = "16225927682921336339157";
        list_range_dec[109] = "32451855365842672678315";
        list_range_dec[110] = "64903710731685345356631";
        list_range_dec[111] = "129807421463370690713262";
        list_range_dec[112] = "259614842926741381426524";
        list_range_dec[113] = "519229685853482762853049";
        list_range_dec[114] = "1038459371706965525706099";
        list_range_dec[115] = "2076918743413931051412198";
        list_range_dec[116] = "4153837486827862102824397";
        list_range_dec[117] = "8307674973655724205648794";
        list_range_dec[118] = "16615349947311448411297588";
        list_range_dec[119] = "33230699894622896822595176";
        list_range_dec[120] = "66461399789245793645190353";
        list_range_dec[121] = "132922799578491587290380706";
        list_range_dec[122] = "265845599156983174580761412";
        list_range_dec[123] = "531691198313966349161522824";
        list_range_dec[124] = "1063382396627932698323045648";
        list_range_dec[125] = "2126764793255865396646091296";
        list_range_dec[126] = "4253529586511730793292182592";
        list_range_dec[127] = "8507059173023461586584365185";
        list_range_dec[128] = "17014118346046923173168730371";
        list_range_dec[129] = "34028236692093846346337460743";
        list_range_dec[130] = "68056473384187692692674921486";
        list_range_dec[131] = "136112946768375385385349842972";
        list_range_dec[132] = "272225893536750770770699685945";
        list_range_dec[133] = "544451787073501541541399371890";
        list_range_dec[134] = "1088903574147003083082798743781";
        list_range_dec[135] = "2177807148294006166165597487563";
        list_range_dec[136] = "4355614296588012332331194975126";
        list_range_dec[137] = "8711228593176024664662389950253";
        list_range_dec[138] = "17422457186352049329324779900506";
        list_range_dec[139] = "34844914372704098658649559801013";
        list_range_dec[140] = "69689828745408197317299119602026";
        list_range_dec[141] = "139379657490816394634598239204052";
        list_range_dec[142] = "278759314981632789269196478408104";
        list_range_dec[143] = "557518629963265578538392956816209";
        list_range_dec[144] = "1115037259926531157076785913632418";
        list_range_dec[145] = "2230074519853062314153571827264836";
        list_range_dec[146] = "4460149039706124628307143654529672";
        list_range_dec[147] = "8920298079412249256614287309059344";
        list_range_dec[148] = "17840596158824498513228574618118689";
        list_range_dec[149] = "35681192317648997026457149236237378";
        list_range_dec[150] = "71362384635297994052914298472474756";
        list_range_dec[151] = "142724769270595988105828596944949513";
        list_range_dec[152] = "285449538541191976211657193889899027";
        list_range_dec[153] = "570899077082383952423314387779798054";
        list_range_dec[154] = "1141798154164767904846628775559596109";
        list_range_dec[155] = "2283596308329535809693257551119192218";
        list_range_dec[156] = "4567192616659071619386515102238384436";
        list_range_dec[157] = "9134385233318143238773030204476768872";
        list_range_dec[158] = "18268770466636286477546060408953537745";
        list_range_dec[159] = "36537540933272572955092120817907075491";
        list_range_dec[160] = "73075081866545145910184241635814150982";

    map<int, std::string> list_addr;
        list_addr[67] = "1BY8GQbnueYofwSuFAT3USAhGjPrkxDdW9";
        list_addr[68] = "1MVDYgVaSN6iKKEsbzRUAYFrYJadLYZvvZ";
        list_addr[69] = "19vkiEajfhuZ8bs8Zu2jgmC6oqZbWqhxhG";
        list_addr[70] = "";
        list_addr[71] = "1PWo3JeB9jrGwfHDNpdGK54CRas7fsVzXU";
        list_addr[72] = "1JTK7s9YVYywfm5XUH7RNhHJH1LshCaRFR";
        list_addr[73] = "12VVRNPi4SJqUTsp6FmqDqY5sGosDtysn4";
        list_addr[74] = "1FWGcVDK3JGzCC3WtkYetULPszMaK2Jksv";
        list_addr[75] = "";
        list_addr[76] = "1DJh2eHFYQfACPmrvpyWc8MSTYKh7w9eRF";
        list_addr[77] = "1Bxk4CQdqL9p22JEtDfdXMsng1XacifUtE";
        list_addr[78] = "15qF6X51huDjqTmF9BJgxXdt1xcj46Jmhb";
        list_addr[79] = "1ARk8HWJMn8js8tQmGUJeQHjSE7KRkn2t8";
        list_addr[80] = "";
        list_addr[81] = "15qsCm78whspNQFydGJQk5rexzxTQopnHZ";
        list_addr[82] = "13zYrYhhJxp6Ui1VV7pqa5WDhNWM45ARAC";
        list_addr[83] = "14MdEb4eFcT3MVG5sPFG4jGLuHJSnt1Dk2";
        list_addr[84] = "1CMq3SvFcVEcpLMuuH8PUcNiqsK1oicG2D";
        list_addr[85] = "";
        list_addr[86] = "1K3x5L6G57Y494fDqBfrojD28UJv4s5JcK";
        list_addr[87] = "1PxH3K1Shdjb7gSEoTX7UPDZ6SH4qGPrvq";
        list_addr[88] = "16AbnZjZZipwHMkYKBSfswGWKDmXHjEpSf";
        list_addr[89] = "19QciEHbGVNY4hrhfKXmcBBCrJSBZ6TaVt";
        list_addr[90] = "";
        list_addr[91] = "1EzVHtmbN4fs4MiNk3ppEnKKhsmXYJ4s74";
        list_addr[92] = "1AE8NzzgKE7Yhz7BWtAcAAxiFMbPo82NB5";
        list_addr[93] = "17Q7tuG2JwFFU9rXVj3uZqRtioH3mx2Jad";
        list_addr[94] = "1K6xGMUbs6ZTXBnhw1pippqwK6wjBWtNpL";
        list_addr[95] = "";
        list_addr[96] = "15ANYzzCp5BFHcCnVFzXqyibpzgPLWaD8b";
        list_addr[97] = "18ywPwj39nGjqBrQJSzZVq2izR12MDpDr8";
        list_addr[98] = "1CaBVPrwUxbQYYswu32w7Mj4HR4maNoJSX";
        list_addr[99] = "1JWnE6p6UN7ZJBN7TtcbNDoRcjFtuDWoNL";
        list_addr[100] = "";
        list_addr[101] = "1CKCVdbDJasYmhswB6HKZHEAnNaDpK7W4n";
        list_addr[102] = "1PXv28YxmYMaB8zxrKeZBW8dt2HK7RkRPX";
        list_addr[103] = "1AcAmB6jmtU6AiEcXkmiNE9TNVPsj9DULf";
        list_addr[104] = "1EQJvpsmhazYCcKX5Au6AZmZKRnzarMVZu";
        list_addr[105] = "";
        list_addr[106] = "18KsfuHuzQaBTNLASyj15hy4LuqPUo1FNB";
        list_addr[107] = "15EJFC5ZTs9nhsdvSUeBXjLAuYq3SWaxTc";
        list_addr[108] = "1HB1iKUqeffnVsvQsbpC6dNi1XKbyNuqao";
        list_addr[109] = "1GvgAXVCbA8FBjXfWiAms4ytFeJcKsoyhL";
        list_addr[110] = "";
        list_addr[111] = "1824ZJQ7nKJ9QFTRBqn7z7dHV5EGpzUpH3";
        list_addr[112] = "18A7NA9FTsnJxWgkoFfPAFbQzuQxpRtCos";
        list_addr[113] = "1NeGn21dUDDeqFQ63xb2SpgUuXuBLA4WT4";
        list_addr[114] = "174SNxfqpdMGYy5YQcfLbSTK3MRNZEePoy";
        list_addr[115] = "";
        list_addr[116] = "1MnJ6hdhvK37VLmqcdEwqC3iFxyWH2PHUV";
        list_addr[117] = "1KNRfGWw7Q9Rmwsc6NT5zsdvEb9M2Wkj5Z";
        list_addr[118] = "1PJZPzvGX19a7twf5HyD2VvNiPdHLzm9F6";
        list_addr[119] = "1GuBBhf61rnvRe4K8zu8vdQB3kHzwFqSy7";
        list_addr[120] = "";
        list_addr[121] = "1GDSuiThEV64c166LUFC9uDcVdGjqkxKyh";
        list_addr[122] = "1Me3ASYt5JCTAK2XaC32RMeH34PdprrfDx";
        list_addr[123] = "1CdufMQL892A69KXgv6UNBD17ywWqYpKut";
        list_addr[124] = "1BkkGsX9ZM6iwL3zbqs7HWBV7SvosR6m8N";
        list_addr[125] = "";
        list_addr[126] = "1AWCLZAjKbV1P7AHvaPNCKiB7ZWVDMxFiz";
        list_addr[127] = "1G6EFyBRU86sThN3SSt3GrHu1sA7w7nzi4";
        list_addr[128] = "1MZ2L1gFrCtkkn6DnTT2e4PFUTHw9gNwaj";
        list_addr[129] = "1Hz3uv3nNZzBVMXLGadCucgjiCs5W9vaGz";
        list_addr[130] = "1Fo65aKq8s8iquMt6weF1rku1moWVEd5Ua";
        list_addr[131] = "16zRPnT8znwq42q7XeMkZUhb1bKqgRogyy";
        list_addr[132] = "1KrU4dHE5WrW8rhWDsTRjR21r8t3dsrS3R";
        list_addr[133] = "17uDfp5r4n441xkgLFmhNoSW1KWp6xVLD";
        list_addr[134] = "13A3JrvXmvg5w9XGvyyR4JEJqiLz8ZySY3";
        list_addr[135] = "16RGFo6hjq9ym6Pj7N5H7L1NR1rVPJyw2v";
        list_addr[136] = "1UDHPdovvR985NrWSkdWQDEQ1xuRiTALq";
        list_addr[137] = "15nf31J46iLuK1ZkTnqHo7WgN5cARFK3RA";
        list_addr[138] = "1Ab4vzG6wEQBDNQM1B2bvUz4fqXXdFk2WT";
        list_addr[139] = "1Fz63c775VV9fNyj25d9Xfw3YHE6sKCxbt";
        list_addr[140] = "1QKBaU6WAeycb3DbKbLBkX7vJiaS8r42Xo";
        list_addr[141] = "1CD91Vm97mLQvXhrnoMChhJx4TP9MaQkJo";
        list_addr[142] = "15MnK2jXPqTMURX4xC3h4mAZxyCcaWWEDD";
        list_addr[143] = "13N66gCzWWHEZBxhVxG18P8wyjEWF9Yoi1";
        list_addr[144] = "1NevxKDYuDcCh1ZMMi6ftmWwGrZKC6j7Ux";
        list_addr[145] = "19GpszRNUej5yYqxXoLnbZWKew3KdVLkXg";
        list_addr[146] = "1M7ipcdYHey2Y5RZM34MBbpugghmjaV89P";
        list_addr[147] = "18aNhurEAJsw6BAgtANpexk5ob1aGTwSeL";
        list_addr[148] = "1FwZXt6EpRT7Fkndzv6K4b4DFoT4trbMrV";
        list_addr[149] = "1CXvTzR6qv8wJ7eprzUKeWxyGcHwDYP1i2";
        list_addr[150] = "1MUJSJYtGPVGkBCTqGspnxyHahpt5Te8jy";
        list_addr[151] = "13Q84TNNvgcL3HJiqQPvyBb9m4hxjS3jkV";
        list_addr[152] = "1LuUHyrQr8PKSvbcY1v1PiuGuqFjWpDumN";
        list_addr[153] = "18192XpzzdDi2K11QVHR7td2HcPS6Qs5vg";
        list_addr[154] = "1NgVmsCCJaKLzGyKLFJfVequnFW9ZvnMLN";
        list_addr[155] = "1AoeP37TmHdFh8uN72fu9AqgtLrUwcv2wJ";
        list_addr[156] = "1FTpAbQa4h8trvhQXjXnmNhqdiGBd1oraE";
        list_addr[157] = "14JHoRAdmJg3XR4RjMDh6Wed6ft6hzbQe9";
        list_addr[158] = "19z6waranEf8CcP8FqNgdwUe1QRxvUNKBG";
        list_addr[159] = "14u4nA5sugaswb6SZgn5av2vuChdMnD9E5";
        list_addr[160] = "1NBC8uXJy1GiJ6drkiZa1WuKn51ps7EPTv";

    int solved_P[14] = {66, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130};

    // address = list_addr[P]; 
    int P = 67
    // generate Priv_dec + addr + range
	Int rStart_priv_dec, rEnd_priv_dec;
    rStart_priv_dec.SetBase10(list_range_dec[P]);
    rEnd_priv_dec.SetBase10(list_range_dec[P+1]);

    switch (mode){
        case RANDOM:
            while (true)
            {
                priv_dec.Rand(&rStart_priv_dec);
                priv_dec.Add(&rStart_priv_dec);

                //--- add d_x int priv_dec
                Int d_x;
                d_x.SetBase10("9999999");
                d_x.Rand(&d_x);
                priv_dec.Add(&d_x);

                if (priv_dec.IsGreaterOrEqual(&rStart_priv_dec) && 
                    priv_dec.IsLowerOrEqual(&rEnd_priv_dec)){ 
                        break; 
                }
            }
            break;

        case INPUT:
            std::cout << "\nRANGE__INPUT : " << rStart_priv_dec.GetBase10() << " - " << rEnd_priv_dec.GetBase10();
            char* input_priv_dec = new char[100];

            while (true)
            {
                std::cout << "\ninput__priv_dec : "; 
                cin.getline(input_priv_dec, 100);

                priv_dec.SetBase10(input_priv_dec);     

                if (priv_dec.IsGreaterOrEqual(&rStart_priv_dec) && 
                    priv_dec.IsLowerOrEqual(&rEnd_priv_dec)){ 
                        break; 
                }
            }
        break;
    }
    
    Int _10B, _xNB;
    _10B.SetBase10("10000000000"); 
    _xNB = _10B;
    _xNB.Mult(xN);

    //rangeStart
    rangeStart = priv_dec; // 10 billions
    rangeStart.Mult(&_10B);
    //rangEnd
    rangeEnd = rangeStart;
    rangeEnd.Add(&_xNB);

            // // --------------------- test -----------------------------
            // address = "13zb1hQbWVsc2S7ZTZnP2G4undNNpdh5so";
            // rangeStart.SetBase16("2832ed74f00000000");
            // rangeEnd.SetBase16("2832ed74f90000000");
            // // --------------------- test=end -------------------------
            // --------------------- test -----------------------------
            // address = "13BbTbEmtoNgcL2ERkYSPwuxb9xdEjgfnt";
            rangeStart.SetBase16("fa504f9d4982fe985188e2f9abd1a4ae3b6a230f54fc679495e8a70500f0e0d3");
            rangeEnd.SetBase16("fa504f9d4982fe985188e2f9abd1a4ae3b6a230f54fc679495e8a705fff0e0d3");
            // --------------------- test=end -------------------------
    std::cout << "\nPUZZLE      : " << P;
    // std::cout << "\nADDRESS     : " << address;
    std::cout << "\nRANGE START : " << list_range_dec[P];
    std::cout << "\nRANGE END   : " << list_range_dec[P+1] << "\n";

    //print priv_dec info 
    uint64_t nChecked = 0;
    Int priv_dec_copy = priv_dec;
    for (int i = 0; i < xN; i++){
        std::cout << "\nPriv_dec ======> " << priv_dec_copy.GetBase10(); //print 
        nChecked = check_data(priv_dec_copy.GetBase10()); // check priv
        priv_dec_copy.AddOne(); // increase priv 
    } 
    std::cout << "\n\nnChecked : " << nChecked ;
} 



















































//-----------------------------------------------------------------------
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

//---CODENOW - START  --------------------------------------------------------------------
// Function to trim leading and trailing spaces and newlines
void trim(std::string &str) {
    str.erase(0, str.find_first_not_of(" \t\r\n"));  // Erase leading whitespaces and newline characters
    str.erase(str.find_last_not_of(" \t\r\n") + 1);  // Erase trailing whitespaces and newline characters
}

// Funtion to convert listAddr to array of data h[5]
void listAddr_to_arrData(){

    check_file_exist(); // check file $.txt

	// Global Init
	Timer::Init();
	rseed(Timer::getSeed32());

	// bool gpuAutoGrid = true;
	vector<int> gpuId = { 0 };
	vector<int> gridSize;


    // std::string address = "";
	Int priv_dec, rangeStart, rangeEnd;

    //set value
    int xN = 10;
    int mode = 1;
    init_value(mode, xN, priv_dec, rangeStart, rangeEnd);

	std::string outputFile = "$.txt";
    std::cout << "\n\nOUTPUT FILE  : " << outputFile;













    //------------- listAddr -> arrData ----start--------------------
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


	std::cout << std::endl <<"n_P2PKH : " << n_P2PKH;
	std::cout << std::endl <<"n_P2SH : " << n_P2SH;
	std::cout << std::endl <<"n_BECH32 : " << n_BECH32;
    
	
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

    //------------- listAddr -> arrData ----end--------------------









    if (gridSize.size() == 0) {
        for (int i = 0; i < gpuId.size(); i++) {
            gridSize.push_back(-1);
            gridSize.push_back(128);
        }
	}

	signal(SIGINT, CtrlHandler);

	KeyHunt* v;
    bool should_exit = false;
	// v = new KeyHunt(hash160_target, outputFile, rangeStart, rangeEnd, priv_dec, xN, P, should_exit);
	v = new KeyHunt(arrData_P2PKH, arrData_P2SH, arrData_BECH32, outputFile, rangeStart, rangeEnd, priv_dec, xN, should_exit);
	v->Search(gpuId, gridSize, should_exit);

	delete v;
}



//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//---CODENOW - END --------------------------------------------------------------------
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------




















int main(){
    listAddr_to_arrData();
    
	return 0;
};
