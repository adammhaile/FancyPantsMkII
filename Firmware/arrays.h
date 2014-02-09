#ifndef ARRAYS_H
#define ARRAYS_H
/*
Complete map of pixel index to pixel x,y coordinates
Note that you call as pixels[y][x] 
The array works better this way and looks like the way
the strips are oriented.
*/
uint8_t _pixels[42][12] = 
{
	{251,168,167,84,83,0,255,82,83,165,166,249},
	{250,169,166,85,82,1,0,81,84,164,167,248},
	{249,170,165,86,81,2,1,80,85,163,168,247},
	{248,171,164,87,80,3,2,79,86,162,169,246},
	{247,172,163,88,79,4,3,78,87,161,170,245},
	{246,173,162,89,78,5,4,77,88,160,171,244},
	{245,174,161,90,77,6,5,76,89,159,172,243},
	{244,175,160,91,76,7,6,75,90,158,173,242},
	{243,176,159,92,75,8,7,74,91,157,174,241},
	{242,177,158,93,74,9,8,73,92,156,175,240},
	{241,178,157,94,73,10,9,72,93,155,176,239},
	{240,179,156,95,72,11,10,71,94,154,177,238},
	{239,180,155,96,71,12,11,70,95,153,178,237},
	{238,181,154,97,70,13,12,69,96,152,179,236},
	{237,182,153,98,69,14,13,68,97,151,180,235},
	{236,183,152,99,68,15,14,67,98,150,181,234},
	{235,184,151,100,67,16,15,66,99,149,182,233},
	{234,185,150,101,66,17,16,65,100,148,183,232},
	{233,186,149,102,65,18,17,64,101,147,184,231},
	{232,187,148,103,64,19,18,63,102,146,185,230},
	{231,188,147,104,63,20,19,62,103,145,186,229},
	{230,189,146,105,62,21,20,61,104,144,187,228},
	{229,190,145,106,61,22,21,60,105,143,188,227},
	{228,191,144,107,60,23,22,59,106,142,189,226},
	{227,192,143,108,59,24,23,58,107,141,190,225},
	{226,193,142,109,58,25,24,57,108,140,191,224},
	{225,194,141,110,57,26,25,56,109,139,192,223},
	{224,195,140,111,56,27,26,55,110,138,193,222},
	{223,196,139,112,55,28,27,54,111,137,194,221},
	{222,197,138,113,54,29,28,53,112,136,195,220},
	{221,198,137,114,53,30,29,52,113,135,196,219},
	{220,199,136,115,52,31,30,51,114,134,197,218},
	{219,200,135,116,51,32,31,50,115,133,198,217},
	{218,201,134,117,50,33,32,49,116,132,199,216},
	{217,202,133,118,49,34,33,48,117,131,200,215},
	{216,203,132,119,48,35,34,47,118,130,201,214},
	{215,204,131,120,47,36,35,46,119,129,202,213},
	{214,205,130,121,46,37,36,45,120,128,203,212},
	{213,206,129,122,45,38,37,44,121,127,204,211},
	{212,207,128,123,44,39,38,43,122,126,205,210},
	{211,208,127,124,43,40,39,42,123,125,206,209},
	{210,209,126,125,42,41,40,41,124,255,207,208}

};
//{ //Should be this, but I lost a couple pixels and am cheating in software to fix it
//	{251,168,167,84,83,0,0,83,84,167,168,251},
//	{250,169,166,85,82,1,1,82,85,166,169,250},
//	{249,170,165,86,81,2,2,81,86,165,170,249},
//	{248,171,164,87,80,3,3,80,87,164,171,248},
//	{247,172,163,88,79,4,4,79,88,163,172,247},
//	{246,173,162,89,78,5,5,78,89,162,173,246},
//	{245,174,161,90,77,6,6,77,90,161,174,245},
//	{244,175,160,91,76,7,7,76,91,160,175,244},
//	{243,176,159,92,75,8,8,75,92,159,176,243},
//	{242,177,158,93,74,9,9,74,93,158,177,242},
//	{241,178,157,94,73,10,10,73,94,157,178,241},
//	{240,179,156,95,72,11,11,72,95,156,179,240},
//	{239,180,155,96,71,12,12,71,96,155,180,239},
//	{238,181,154,97,70,13,13,70,97,154,181,238},
//	{237,182,153,98,69,14,14,69,98,153,182,237},
//	{236,183,152,99,68,15,15,68,99,152,183,236},
//	{235,184,151,100,67,16,16,67,100,151,184,235},
//	{234,185,150,101,66,17,17,66,101,150,185,234},
//	{233,186,149,102,65,18,18,65,102,149,186,233},
//	{232,187,148,103,64,19,19,64,103,148,187,232},
//	{231,188,147,104,63,20,20,63,104,147,188,231},
//	{230,189,146,105,62,21,21,62,105,146,189,230},
//	{229,190,145,106,61,22,22,61,106,145,190,229},
//	{228,191,144,107,60,23,23,60,107,144,191,228},
//	{227,192,143,108,59,24,24,59,108,143,192,227},
//	{226,193,142,109,58,25,25,58,109,142,193,226},
//	{225,194,141,110,57,26,26,57,110,141,194,225},
//	{224,195,140,111,56,27,27,56,111,140,195,224},
//	{223,196,139,112,55,28,28,55,112,139,196,223},
//	{222,197,138,113,54,29,29,54,113,138,197,222},
//	{221,198,137,114,53,30,30,53,114,137,198,221},
//	{220,199,136,115,52,31,31,52,115,136,199,220},
//	{219,200,135,116,51,32,32,51,116,135,200,219},
//	{218,201,134,117,50,33,33,50,117,134,201,218},
//	{217,202,133,118,49,34,34,49,118,133,202,217},
//	{216,203,132,119,48,35,35,48,119,132,203,216},
//	{215,204,131,120,47,36,36,47,120,131,204,215},
//	{214,205,130,121,46,37,37,46,121,130,205,214},
//	{213,206,129,122,45,38,38,45,122,129,206,213},
//	{212,207,128,123,44,39,39,44,123,128,207,212},
//	{211,208,127,124,43,40,40,43,124,127,208,211},
//	{210,209,126,125,42,41,41,42,125,126,209,210}
//};

/*
Vectors below calculated with the following python code
center point is (5.5,20.5) since the coords are X:0-11, Y:0-41
power of 4 used on x axis to accomodate for pixels being further apart in x axis

from math import *
[[int(sqrt(pow(x - 5.5, 4) + pow(y - 20.5, 2))) for x in range(12)] for y in range(42)]
*/
uint8_t _vectors[42][12] = 
{
	{36, 28, 23, 21, 20, 20, 20, 20, 21, 23, 28, 36},
	{35, 28, 23, 20, 19, 19, 19, 19, 20, 23, 28, 35},
	{35, 27, 22, 19, 18, 18, 18, 18, 19, 22, 27, 35},
	{34, 26, 21, 18, 17, 17, 17, 17, 18, 21, 26, 34},
	{34, 26, 20, 17, 16, 16, 16, 16, 17, 20, 26, 34},
	{33, 25, 19, 16, 15, 15, 15, 15, 16, 19, 25, 33},
	{33, 24, 18, 15, 14, 14, 14, 14, 15, 18, 24, 33},
	{33, 24, 18, 14, 13, 13, 13, 13, 14, 18, 24, 33},
	{32, 23, 17, 13, 12, 12, 12, 12, 13, 17, 23, 32},
	{32, 23, 16, 13, 11, 11, 11, 11, 13, 16, 23, 32},
	{32, 22, 16, 12, 10, 10, 10, 10, 12, 16, 22, 32},
	{31, 22, 15, 11, 9, 9, 9, 9, 11, 15, 22, 31},
	{31, 21, 14, 10, 8, 8, 8, 8, 10, 14, 21, 31},
	{31, 21, 14, 9, 7, 7, 7, 7, 9, 14, 21, 31},
	{30, 21, 13, 9, 6, 6, 6, 6, 9, 13, 21, 30},
	{30, 20, 13, 8, 5, 5, 5, 5, 8, 13, 20, 30},
	{30, 20, 13, 7, 5, 4, 4, 5, 7, 13, 20, 30},
	{30, 20, 12, 7, 4, 3, 3, 4, 7, 12, 20, 30},
	{30, 20, 12, 6, 3, 2, 2, 3, 6, 12, 20, 30},
	{30, 20, 12, 6, 2, 1, 1, 2, 6, 12, 20, 30},
	{30, 20, 12, 6, 2, 0, 0, 2, 6, 12, 20, 30},
	{30, 20, 12, 6, 2, 0, 0, 2, 6, 12, 20, 30},
	{30, 20, 12, 6, 2, 1, 1, 2, 6, 12, 20, 30},
	{30, 20, 12, 6, 3, 2, 2, 3, 6, 12, 20, 30},
	{30, 20, 12, 7, 4, 3, 3, 4, 7, 12, 20, 30},
	{30, 20, 13, 7, 5, 4, 4, 5, 7, 13, 20, 30},
	{30, 20, 13, 8, 5, 5, 5, 5, 8, 13, 20, 30},
	{30, 21, 13, 9, 6, 6, 6, 6, 9, 13, 21, 30},
	{31, 21, 14, 9, 7, 7, 7, 7, 9, 14, 21, 31},
	{31, 21, 14, 10, 8, 8, 8, 8, 10, 14, 21, 31},
	{31, 22, 15, 11, 9, 9, 9, 9, 11, 15, 22, 31},
	{32, 22, 16, 12, 10, 10, 10, 10, 12, 16, 22, 32},
	{32, 23, 16, 13, 11, 11, 11, 11, 13, 16, 23, 32},
	{32, 23, 17, 13, 12, 12, 12, 12, 13, 17, 23, 32},
	{33, 24, 18, 14, 13, 13, 13, 13, 14, 18, 24, 33},
	{33, 24, 18, 15, 14, 14, 14, 14, 15, 18, 24, 33},
	{33, 25, 19, 16, 15, 15, 15, 15, 16, 19, 25, 33},
	{34, 26, 20, 17, 16, 16, 16, 16, 17, 20, 26, 34},
	{34, 26, 21, 18, 17, 17, 17, 17, 18, 21, 26, 34},
	{35, 27, 22, 19, 18, 18, 18, 18, 19, 22, 27, 35},
	{35, 28, 23, 20, 19, 19, 19, 19, 20, 23, 28, 35},
	{36, 28, 23, 21, 20, 20, 20, 20, 21, 23, 28, 36},
};

uint8_t vector(uint8_t x, uint8_t y)
{
	if(x >= 12 || y >= 42) return 0;
	return _vectors[y][x];
}


uint32_t _wheel[384] = 
{
	8323072,
	8257792,
	8192512,
	8127232,
	8061952,
	7996672,
	7931392,
	7866112,
	7800832,
	7735552,
	7670272,
	7604992,
	7539712,
	7474432,
	7409152,
	7343872,
	7278592,
	7213312,
	7148032,
	7082752,
	7017472,
	6952192,
	6886912,
	6821632,
	6756352,
	6691072,
	6625792,
	6560512,
	6495232,
	6429952,
	6364672,
	6299392,
	6234112,
	6168832,
	6103552,
	6038272,
	5972992,
	5907712,
	5842432,
	5777152,
	5711872,
	5646592,
	5581312,
	5516032,
	5450752,
	5385472,
	5320192,
	5254912,
	5189632,
	5124352,
	5059072,
	4993792,
	4928512,
	4863232,
	4797952,
	4732672,
	4667392,
	4602112,
	4536832,
	4471552,
	4406272,
	4340992,
	4275712,
	4210432,
	4145152,
	4079872,
	4014592,
	3949312,
	3884032,
	3818752,
	3753472,
	3688192,
	3622912,
	3557632,
	3492352,
	3427072,
	3361792,
	3296512,
	3231232,
	3165952,
	3100672,
	3035392,
	2970112,
	2904832,
	2839552,
	2774272,
	2708992,
	2643712,
	2578432,
	2513152,
	2447872,
	2382592,
	2317312,
	2252032,
	2186752,
	2121472,
	2056192,
	1990912,
	1925632,
	1860352,
	1795072,
	1729792,
	1664512,
	1599232,
	1533952,
	1468672,
	1403392,
	1338112,
	1272832,
	1207552,
	1142272,
	1076992,
	1011712,
	946432,
	881152,
	815872,
	750592,
	685312,
	620032,
	554752,
	489472,
	424192,
	358912,
	293632,
	228352,
	163072,
	97792,
	32512,
	32512,
	32257,
	32002,
	31747,
	31492,
	31237,
	30982,
	30727,
	30472,
	30217,
	29962,
	29707,
	29452,
	29197,
	28942,
	28687,
	28432,
	28177,
	27922,
	27667,
	27412,
	27157,
	26902,
	26647,
	26392,
	26137,
	25882,
	25627,
	25372,
	25117,
	24862,
	24607,
	24352,
	24097,
	23842,
	23587,
	23332,
	23077,
	22822,
	22567,
	22312,
	22057,
	21802,
	21547,
	21292,
	21037,
	20782,
	20527,
	20272,
	20017,
	19762,
	19507,
	19252,
	18997,
	18742,
	18487,
	18232,
	17977,
	17722,
	17467,
	17212,
	16957,
	16702,
	16447,
	16192,
	15937,
	15682,
	15427,
	15172,
	14917,
	14662,
	14407,
	14152,
	13897,
	13642,
	13387,
	13132,
	12877,
	12622,
	12367,
	12112,
	11857,
	11602,
	11347,
	11092,
	10837,
	10582,
	10327,
	10072,
	9817,
	9562,
	9307,
	9052,
	8797,
	8542,
	8287,
	8032,
	7777,
	7522,
	7267,
	7012,
	6757,
	6502,
	6247,
	5992,
	5737,
	5482,
	5227,
	4972,
	4717,
	4462,
	4207,
	3952,
	3697,
	3442,
	3187,
	2932,
	2677,
	2422,
	2167,
	1912,
	1657,
	1402,
	1147,
	892,
	637,
	382,
	127,
	127,
	65662,
	131197,
	196732,
	262267,
	327802,
	393337,
	458872,
	524407,
	589942,
	655477,
	721012,
	786547,
	852082,
	917617,
	983152,
	1048687,
	1114222,
	1179757,
	1245292,
	1310827,
	1376362,
	1441897,
	1507432,
	1572967,
	1638502,
	1704037,
	1769572,
	1835107,
	1900642,
	1966177,
	2031712,
	2097247,
	2162782,
	2228317,
	2293852,
	2359387,
	2424922,
	2490457,
	2555992,
	2621527,
	2687062,
	2752597,
	2818132,
	2883667,
	2949202,
	3014737,
	3080272,
	3145807,
	3211342,
	3276877,
	3342412,
	3407947,
	3473482,
	3539017,
	3604552,
	3670087,
	3735622,
	3801157,
	3866692,
	3932227,
	3997762,
	4063297,
	4128832,
	4194367,
	4259902,
	4325437,
	4390972,
	4456507,
	4522042,
	4587577,
	4653112,
	4718647,
	4784182,
	4849717,
	4915252,
	4980787,
	5046322,
	5111857,
	5177392,
	5242927,
	5308462,
	5373997,
	5439532,
	5505067,
	5570602,
	5636137,
	5701672,
	5767207,
	5832742,
	5898277,
	5963812,
	6029347,
	6094882,
	6160417,
	6225952,
	6291487,
	6357022,
	6422557,
	6488092,
	6553627,
	6619162,
	6684697,
	6750232,
	6815767,
	6881302,
	6946837,
	7012372,
	7077907,
	7143442,
	7208977,
	7274512,
	7340047,
	7405582,
	7471117,
	7536652,
	7602187,
	7667722,
	7733257,
	7798792,
	7864327,
	7929862,
	7995397,
	8060932,
	8126467,
	8192002,
	8257537,
	8323072
};

uint32_t Wheel(uint16_t pos)
{
	if(pos > 384) return 0;
	return _wheel[pos];
}

#endif