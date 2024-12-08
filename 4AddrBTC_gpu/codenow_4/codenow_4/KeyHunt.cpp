







#include "KeyHunt.h"
#include "GmpUtil.h"
#include "Base58.h"
#include "hash/sha256.h"
#include "hash/keccak160.h"
#include "IntGroup.h"
#include "Timer.h"
#include "hash/ripemd160.h"
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <pthread.h>
using namespace std;

Point Gn[CPU_GRP_SIZE / 2]; 
Point _2Gn;


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

#include <cstdint>
#include <cstddef>
#include <cstring>


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
	uint32_t hiiu_bech32_polymod_step(uint32_t pre) {
	uint8_t b = pre >> 25;
	return ((pre & 0x1FFFFFF) << 5) ^
		(-((b >> 0) & 1) & 0x3b6a57b2UL) ^
		(-((b >> 1) & 1) & 0x26508e6dUL) ^
		(-((b >> 2) & 1) & 0x1ea119faUL) ^
		(-((b >> 3) & 1) & 0x3d4233ddUL) ^
		(-((b >> 4) & 1) & 0x2a1462b3UL);
	}

//----------------------------------------------------------
	int hiiu_bech32_encode(char *output, const char *hrp, const uint8_t *data, size_t data_len) {
	uint32_t chk = 1;
	size_t i = 0;
	while (hrp[i] != 0) {
		int ch = hrp[i];
		if (ch < 33 || ch > 126) {
		return 0;
		}

		if (ch >= 'A' && ch <= 'Z') return 0;
		chk = hiiu_bech32_polymod_step(chk) ^ (ch >> 5);
		++i;
	}
	if (i + 7 + data_len > 90) return 0;
	chk = hiiu_bech32_polymod_step(chk);
	while (*hrp != 0) {
		chk = hiiu_bech32_polymod_step(chk) ^ (*hrp & 0x1f);
		*(output++) = *(hrp++);
	}
	*(output++) = '1';
	for (i = 0; i < data_len; ++i) {
		if (*data >> 5) return 0;
		chk = hiiu_bech32_polymod_step(chk) ^ (*data);
		*(output++) = charset[*(data++)];
	}
	for (i = 0; i < 6; ++i) {
		chk = hiiu_bech32_polymod_step(chk);
	}
	chk ^= 1;
	for (i = 0; i < 6; ++i) {
		*(output++) = charset[(chk >> ((5 - i) * 5)) & 0x1f];
	}
	*output = 0;
	return 1;
	}

//----------------------------------------------------------
int hiiu_segwit_addr_encode(char *output, const char *hrp, int witver, const uint8_t *witprog, size_t witprog_len) {
	uint8_t data[65];
	size_t datalen = 0;
	if (witver > 16) return 0;
	if (witver == 0 && witprog_len != 20 && witprog_len != 32) return 0;
	if (witprog_len < 2 || witprog_len > 40) return 0;
	data[0] = witver;
	convert_bits(data + 1, &datalen, 5, witprog, witprog_len, 8, 1);
	++datalen;
	return hiiu_bech32_encode(output, hrp, data, datalen);
}

//============== BECH_32 - end ================================================================================


//============== HIIU::BITCOIN - start =============================================================================
#include <iostream>

class hiiu_Bitcoin 
{
	public:
		std::string hash160ToAddr(int type, uint32_t* _hash160); //return STRING 
};  
//-------------------------------------------------------------------- 

std::string hiiu_Bitcoin::hash160ToAddr(int type, uint32_t* _hash160){

	Secp256K1* hiiu_secp = new Secp256K1();   
	hiiu_secp->Init();	

	unsigned char address[25];

	switch (type) { 
		case P2PKH_C:
		case P2PKH_U:
			address[0] = 0x00;
			break;			
		case P2SH:
			address[0] = 0x05;
			break;	
		case BECH32: // codenow-here
			memcpy(address + 1, _hash160, 20);
			char addr_bech32[128];
			hiiu_segwit_addr_encode(addr_bech32, "bc", 0, address + 1, 20);
			return std::string(addr_bech32);
			break;
	}

	memcpy(address + 1, _hash160, 20);
	sha256_checksum(address, 21, address + 21);
	std::string addr = EncodeBase58(address, address + 25);

	delete hiiu_secp;
	return addr;
}
//============== HIIU::BITCOIN - end =============================================================================

/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////


// ----------------------------------------------------------------------------

// KeyHunt::KeyHunt(const std::vector<unsigned char>& hashORxpoint, const std::string& outputFile,
// 	const Int rangeStart, const Int rangeEnd, const Int priv_dec,uint64_t xN, uint64_t P, bool& should_exit)
// {
KeyHunt::KeyHunt(uint32_t* arrData_P2PKH, uint32_t* arrData_P2SH, uint32_t* arrData_BECH32, const std::string& outputFile,
	const Int rangeStart, const Int rangeEnd, const Int priv_dec,uint64_t xN, bool& should_exit)
{
	this->priv_dec = priv_dec;
	this->xN = xN;
	// this->P = P;

	this->outputFile = outputFile;
	this->nbGPUThread = 0;
	this->rangeStart = rangeStart;
	this->rangeEnd = rangeEnd;
	this->rangeDiff2.Set(&this->rangeEnd);
	this->rangeDiff2.Sub(&this->rangeStart);

	secp = new Secp256K1();
	secp->Init();

	// for (size_t i = 0; i < 5; i++){
	// 	hash160_target_KEYHUNT[i] = hash160_target[i];
	// }

    // store number tpye of addr 
    // this->n_P2PKH = arrData_P2PKH[0];
    // this->n_P2SH = arrData_P2SH[0];
    // this->n_BECH32 = arrData_BECH32[0];

	//
	// this->arrData_P2PKH_KEYHUNT[n_P2PKH];
	// this->arrData_P2SH_KEYHUNT[n_P2SH];
	// this->arrData_BECH32_KEYHUNT[n_BECH32];

	// for (size_t i = 0; i < n_P2PKH; i++){
	// 	this->arrData_P2PKH_KEYHUNT[i] = arrData_P2PKH[i];
	// }

	// for (size_t i = 0; i < n_P2SH; i++){
	// 	this->arrData_P2SH_KEYHUNT[i] = arrData_P2SH[i];
	// }

	// for (size_t i = 0; i < n_BECH32; i++){
	// 	this->arrData_BECH32_KEYHUNT[i] = arrData_BECH32[i];
	// }

	this->arrData_P2PKH_KEYHUNT = arrData_P2PKH;
	this->arrData_P2SH_KEYHUNT = arrData_P2SH;
	this->arrData_BECH32_KEYHUNT = arrData_BECH32;


	printf("\n");

	InitGenratorTable();
}

// ----------------------------------------------------------------------------

void KeyHunt::InitGenratorTable()
{
	// Compute Generator table G[n] = (n+1)*G 
	Point g = secp->G;
	Gn[0] = g;
	g = secp->DoubleDirect(g);
	Gn[1] = g;
	for (int i = 2; i < CPU_GRP_SIZE / 2; i++) {
		g = secp->AddDirect(g, secp->G);
		Gn[i] = g;
	}
	// _2Gn = CPU_GRP_SIZE*G
	_2Gn = secp->DoubleDirect(Gn[CPU_GRP_SIZE / 2 - 1]);

	char* ctimeBuff;
	time_t now = time(NULL);
	ctimeBuff = ctime(&now);
	printf("Start Time   : %s", ctimeBuff);
	printf("Global start : %s (%d bit)\n", this->rangeStart.GetBase16().c_str(), this->rangeStart.GetBitLength());
	printf("Global end   : %s (%d bit)\n", this->rangeEnd.GetBase16().c_str(), this->rangeEnd.GetBitLength());
	printf("Global range : %s (%d bit)\n", this->rangeDiff2.GetBase16().c_str(), this->rangeDiff2.GetBitLength());
}

// ----------------------------------------------------------------------------

#include <fstream>
KeyHunt::~KeyHunt()
{	
	printf("\n\n");
	// save data
	std::string fileSaveData_name;
	fileSaveData_name = "xData.txt";

	std::cout<<"\nFile save : " << fileSaveData_name;

	std::ofstream saveData(fileSaveData_name, std::ios::app); //create x67.txt to write_append

    Int priv_dec_copy = this->priv_dec;
    for (int i = 0; i < this->xN; i++) // loop to save each priv_dec 
    {
        saveData <<"\n"<< priv_dec_copy.GetBase10(); // write data into file
		std::cout << "\nsaved : "<< priv_dec_copy.GetBase10();
        priv_dec_copy.AddOne(); 
    }

    saveData.close();   // close file

	// print end_time 
	char* ctimeBuff;
	time_t now = time(NULL);
	ctimeBuff = ctime(&now);
	std::cout << std::endl << "END TIME : " << ctimeBuff << std::endl;
	std::cout <<"======================================================" << std::endl << std::endl;
	
	delete secp;
}

// ----------------------------------------------------------------------------

void KeyHunt::print_and_save_data(std::string addr, std::string pAddr, std::string pAddrHex, std::string pubKey, std::string typeAddr)
{
	FILE* f = stdout;
	bool needToClose = false;

	if (outputFile.length() > 0) {
		f = fopen(outputFile.c_str(), "a");
		if (f == NULL) {
			printf("\n\nCannot open %s for writing\n\n\n", outputFile.c_str());
			f = stdout;
		}	else {	needToClose = true; }
	}

	if (!needToClose){ printf("\n"); }

	// save into file
	fprintf(f, "\n=================================================================================\n\n");
	fprintf(f, "Address: -----> %s <-----\n\n", addr.c_str());
	fprintf(f, "Priv (HEX): %s\n", pAddrHex.c_str());
	fprintf(f, "typeAddr : %s\n\n", typeAddr.c_str());
	fprintf(f, "Priv (WIF): %s\n\n", pAddr.c_str());
	// fprintf(f, "PubK (HEX): %s\n", pubKey.c_str());
	fprintf(f, "=================================================================================\n");

	//print info to screen
	fprintf(stdout, "\n=================================================================================\n\n");
	fprintf(stdout, "Address: -----> %s <----- ", addr.c_str());
	fprintf(stdout, "typeAddr : %s\n\n", typeAddr.c_str());
	fprintf(stdout, "Priv (HEX): %s\n", pAddrHex.c_str());
	fprintf(stdout, "Priv (WIF): %s\n\n", pAddr.c_str());
	// fprintf(stdout, "PubK (HEX): %s\n", pubKey.c_str()); 
	fprintf(stdout, "=================================================================================\n");

	if (needToClose){ fclose(f); }

	printf("\n.\n.\n.\n.\n.\n --- DONE !! check and take money !! ---- \n.\n.\n.\n.\n.\n.\n");
	// exit(-1);
}

// ----------------------------------------------------------------------------

bool KeyHunt::checkPrivKey(std::string addr, Int& key, int32_t incr, uint32_t typeAddr)
{
	Int k(&key);
	k.Add((uint64_t)incr);

	// Check addresses
	Point p = secp->ComputePublicKey(&k);

	std::string px = p.x.GetBase16();

	// std::string chkAddr = secp->GetAddress(1, p);

	std::string type_addr;
	switch (typeAddr)
	{
	case P2PKH_C:
		type_addr = "P2PKH_C";
		break;
	case P2PKH_U:
		type_addr = "P2PKH_U";
		break;
	case P2SH:
		type_addr = "P2SH";
		break;
	case BECH32:
		type_addr = "BECH32";
		break;
	}
	
	print_and_save_data(addr, secp->GetPrivAddress(1, k), k.GetBase16(), secp->GetPublicKeyHex(1, p), type_addr);
	return true;
}

// ----------------------------------------------------------------------------

void* _FindKeyGPU(void* lpParam)
{
	TH_PARAM* p = (TH_PARAM*)lpParam;
	p->obj->FindKeyGPU(p);
	return 0;
}

// ----------------------------------------------------------------------------

void KeyHunt::getGPUStartingKeys(Int & tRangeStart, Int & tRangeEnd, int groupSize, int nbThread, Int * keys, Point * p)
{
	Int tRangeDiff(tRangeEnd);
	Int tRangeStart2(tRangeStart);
	Int tRangeEnd2(tRangeStart);

	Int tThreads;
	tThreads.SetInt32(nbThread);
	tRangeDiff.Set(&tRangeEnd);
	tRangeDiff.Sub(&tRangeStart);
	tRangeDiff.Div(&tThreads);

	int rangeShowThreasold = 3;
	int rangeShowCounter = 0;

	for (int i = 0; i < nbThread; i++) {

		tRangeEnd2.Set(&tRangeStart2);
		tRangeEnd2.Add(&tRangeDiff);

		keys[i].Set(&tRangeStart2);

		tRangeStart2.Add(&tRangeDiff);

		Int k(keys + i);
		k.Add((uint64_t)(groupSize / 2));	// Starting key is at the middle of the group
		p[i] = secp->ComputePublicKey(&k);
	}

}

void KeyHunt::FindKeyGPU(TH_PARAM * ph)
{
	bool ok = true;

// #ifdef WITHGPU

	// Global init
	int thId = ph->threadId; 
	Int tRangeStart = ph->rangeStart;
	Int tRangeEnd = ph->rangeEnd;

	GPUEngine* g;

	g = new GPUEngine(secp, ph->gridSizeX, ph->gridSizeY, ph->gpuId, this->maxFound,
						arrData_P2PKH_KEYHUNT, arrData_P2SH_KEYHUNT, arrData_BECH32_KEYHUNT); 
	
	// g->PrintCudaInfo(); //hiiu

	int nbThread = g->GetNbThread();
	printf("nbThread: %d\n", nbThread );
	printf("GPU	: %s\n\n", g->deviceName.c_str());
	
		
	Point* p = new Point[nbThread];
	Int* keys = new Int[nbThread];
	std::vector<ITEM> found;
	counters[thId] = 0;

	getGPUStartingKeys(tRangeStart, tRangeEnd, g->GetGroupSize(), nbThread, keys, p);
	ok = g->SetKeys(p);

	ph->hasStarted = true; 

	// ==================== core of process is here ====================================== 
	while (ok && !endOfSearch) { // if found right key --> run inside
		ok = g->LaunchSEARCH_MODE_SA(found);
		for (int i = 0; i < (int)found.size() && !endOfSearch; i++) {
			ITEM it = found[i];
					
							/// test-here 
							hiiu_Bitcoin bitcoin;

							//hash160 --> addr 
							std::string addr;
							addr = bitcoin.hash160ToAddr(it.typeAddr, (uint32_t*)it.hash); 

				if (checkPrivKey(addr, keys[it.thId], it.incr, it.typeAddr)) {	nbFoundKey++;	}
		}

		if (ok) {
			for (int i = 0; i < nbThread; i++) {
				keys[i].Add((uint64_t)STEP_SIZE);
			}
			counters[thId] += (uint64_t)(STEP_SIZE)*nbThread; // Point 
		}
	}

	delete[] keys;
	delete[] p;
	delete g;

	ph->isRunning = false;

}

// ----------------------------------------------------------------------------

bool KeyHunt::isAlive(TH_PARAM * p)
{
	bool isAlive = true;
	int total = nbGPUThread;
	for (int i = 0; i < total; i++)
		isAlive = isAlive && p[i].isRunning;

	return isAlive;
}

// ----------------------------------------------------------------------------

bool KeyHunt::hasStarted(TH_PARAM * p)
{
	bool hasStarted = true;
	int total = nbGPUThread;
	for (int i = 0; i < total; i++)
		hasStarted = hasStarted && p[i].hasStarted;

	return hasStarted;
}

// ----------------------------------------------------------------------------

uint64_t KeyHunt::getGPUCount()
{
	uint64_t count = 0;
	for (int i = 0; i < nbGPUThread; i++)
		count += counters[0x80L + i];
	return count;
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

void KeyHunt::SetupRanges(uint32_t totalThreads)
{
	Int threads;
	threads.SetInt32(totalThreads);
	rangeDiff.Set(&rangeEnd);
	rangeDiff.Sub(&rangeStart);
	rangeDiff.Div(&threads);
}

// ----------------------------------------------------------------------------
void KeyHunt::Search(std::vector<int> gpuId, std::vector<int> gridSize, bool& should_exit)
{
	double t0, t1;
	endOfSearch = false;
	nbGPUThread = (int)gpuId.size() ;
	
	nbFoundKey = 0;

	// setup ranges
	SetupRanges(nbGPUThread);

	memset(counters, 0, sizeof(counters));

	TH_PARAM* params = (TH_PARAM*)malloc((nbGPUThread) * sizeof(TH_PARAM));
	memset(params, 0, (nbGPUThread) * sizeof(TH_PARAM));

	// Launch GPU threads
	for (int i = 0; i < nbGPUThread; i++) {
		params[i].obj = this;
		params[i].threadId = 0x80L + i;
		params[i].isRunning = true;
		params[i].gpuId = gpuId[i];
		params[i].gridSizeX = gridSize[2 * i];
		params[i].gridSizeY = gridSize[2 * i + 1];

		params[i].rangeStart.Set(&rangeStart);
		rangeStart.Add(&rangeDiff);
		params[i].rangeEnd.Set(&rangeStart);

		pthread_t thread_id;
		pthread_create(&thread_id, NULL, &_FindKeyGPU, (void*)(params + (i)));
	}

	setvbuf(stdout, NULL, _IONBF, 0);

	printf("\n");

	uint64_t lastCount = 0;
	uint64_t gpuCount = 0;
	uint64_t lastGPUCount = 0;

	// Key rate smoothing filter
#define FILTER_SIZE 8
	double lastkeyRate[FILTER_SIZE];
	double lastGpukeyRate[FILTER_SIZE];
	uint32_t filterPos = 0;

	double keyRate = 0.0;
	double gpuKeyRate = 0.0;
	char timeStr[256];

	memset(lastkeyRate, 0, sizeof(lastkeyRate));
	memset(lastGpukeyRate, 0, sizeof(lastkeyRate));

	// Wait that all threads have started
	while (!hasStarted(params)) {
		Timer::SleepMillis(500);
	}

	// Reset timer
	Timer::Init();
	t0 = Timer::get_tick();
	startTime = t0;
	Int p100;
	Int ICount;
	p100.SetInt32(100);
	double completedPerc = 0;

	while (isAlive(params)) {

		// int delay = 1000;
		int delay = 2000;

		while (isAlive(params) && delay > 0) {
			Timer::SleepMillis(500);
			delay -= 500;
		}

		gpuCount = getGPUCount();
		uint64_t count = gpuCount;
		ICount.SetInt64(count);
		int completedBits = ICount.GetBitLength();
		completedPerc = CalcPercantage(ICount, rangeStart, rangeDiff2);

		t1 = Timer::get_tick();
		keyRate = (double)(count - lastCount) / (t1 - t0);
		gpuKeyRate = (double)(gpuCount - lastGPUCount) / (t1 - t0);
		lastkeyRate[filterPos % FILTER_SIZE] = keyRate;
		lastGpukeyRate[filterPos % FILTER_SIZE] = gpuKeyRate;
		filterPos++;

		// KeyRate smoothing
		double avgKeyRate = 0.0;
		double avgGpuKeyRate = 0.0;
		uint32_t nbSample;
		for (nbSample = 0; (nbSample < FILTER_SIZE) && (nbSample < filterPos); nbSample++) {
			avgKeyRate += lastkeyRate[nbSample];
			avgGpuKeyRate += lastGpukeyRate[nbSample];
		}
		avgKeyRate /= (double)(nbSample);
		avgGpuKeyRate /= (double)(nbSample);

		if (isAlive(params)) {
			memset(timeStr, '\0', 256);
			printf("\r[%s] [CPU+GPU: %.2f Mk/s] [GPU: %.2f Mk/s] [C: %lf %%] [T: %s (%d bit)]  ",
				toTimeStr(t1, timeStr),
				avgKeyRate / 1000000.0,
				avgGpuKeyRate / 1000000.0,
				completedPerc,
				formatThousands(count).c_str(),
				completedBits);
		}

		lastCount = count;
		lastGPUCount = gpuCount;
		t0 = t1;
		if (should_exit || nbFoundKey >= this->maxFound || completedPerc > 100.5)
			endOfSearch = true;
	}

	free(params);

	}

// ----------------------------------------------------------------------------

std::string KeyHunt::formatThousands(uint64_t x)
{
	char buf[32] = "";
	sprintf(buf, "%lu", x);

	std::string s(buf);
	int len = (int)s.length();
	int numCommas = (len - 1) / 3;
	if (numCommas == 0) {		return s;	}

	std::string result = "";
	int count = ((len % 3) == 0) ? 0 : (3 - (len % 3));
	for (int i = 0; i < len; i++) {
		result += s[i];
		if (count++ == 2 && i < len - 1) {
			result += ",";
			count = 0;
		}
	}
	return result;
}

// ----------------------------------------------------------------------------

char* KeyHunt::toTimeStr(int sec, char* timeStr)
{
	int h, m, s;
	h = (sec / 3600);
	m = (sec - (3600 * h)) / 60;
	s = (sec - (3600 * h) - (m * 60));
	sprintf(timeStr, "%0*d:%0*d:%0*d", 2, h, 2, m, 2, s);
	return (char*)timeStr;
}
