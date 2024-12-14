#include <iostream>
#include <cstdint>
// uint64_t convertNumToImage(){

//     std::string image = ;

//     return image
// }

int main()
{
    int nb = 101; // nb = number
    std::string list[nb];
    list[100] = "message : be a strong man, take your adventurous life, make your dream come true, have a great career, live the wonderful life befor you become dust and sand";
    list[0] = "egg";
    list[1] = "";
    list[2] = "";
    list[3] = "lips";
    list[4] = "chair, seat";
    list[5] = "";
    list[6] = "lock";
    list[7] = "hammer";
    list[8] = "roly-poly toy";
    list[9] = "flag";

    list[10] = "";
    list[11] = "chopsticks";
    list[12] = "harp";
    list[13] = "B = bitcoin";
    list[14] = "H = petronas twin tower (kula lampur - malaysia)";
    list[15] = "$ = money";
    list[16] = "";
    list[17] = "triangle ruler";
    list[18] = "";
    list[19] = "safety pin";
    
    list[20] = "snail";
    list[21] = "";
    list[22] = "";
    list[23] = "";
    list[24] = "";
    list[25] = "the scale ";
    list[26] = "";
    list[27] = "";
    list[28] = "";
    list[29] = "cao cát - parrot";

    list[30] = "spider";
    list[31] = "";
    list[32] = "";
    list[33] = "";
    list[34] = "buffalo's head";
    list[35] = "scissor";
    list[36] = "";
    list[37] = ""; // reindeer's face ? 
    list[38] = "crab";
    list[39] = "scorpion"; 
    
    list[40] = "";
    list[41] = "boat";
    list[42] = "chicken's head";
    list[43] = "";
    list[44] = "camel (camel's back)";
    list[45] = "";
    list[46] = "";
    list[47] = ""; // mouse
    list[48] = "";
    list[49] = ""; // chameleon
    
    list[50] = "";
    list[51] = "";
    list[52] = "heart";
    list[53] = ""; //jellyfish
    list[54] = "";
    list[55] = "S vn";
    list[56] = "";
    list[57] = "fan"; // notice
    list[58] = "";
    list[59] = "";
    
    list[60] = "";
    list[61] = "";
    list[62] = "";
    list[63] = "key";
    list[64] = "";
    list[65] = "";
    list[66] = "eyes";
    list[67] = "";
    list[68] = "";
    list[69] = "";
    
    list[70] = "";
    list[71] = "";
    list[72] = "";
    list[73] = "";
    list[74] = "";
    list[75] = "";
    list[76] = "";
    list[77] = "gun"; //new
    list[78] = "";
    list[79] = "";
    
    list[80] = "monkey's face"; // ?
    list[81] = "";
    list[82] = "motobike"; //?
    list[83] = "bee"; //notice
    list[84] = "";
    list[85] = "bow tie";
    list[86] = "";
    list[87] = "";
    list[88] = "car";
    list[89] = "";
    
    list[90] = "turtle";
    list[91] = "";
    list[92] = "baby";
    list[93] = ""; // dog's face
    list[94] = "";
    list[95] = "";
    list[96] = "%";
    list[97] = "";
    list[98] = "moon";
    list[99] = "sun";

    for (int i = 0; i < nb; i++)
    {
        // std::cout << list[i];
        if( list[i] == "" ){
            std::cout << "\n list["<<i<<"]";
        }
    }
    
    printf("\n");
    return 0;

}
