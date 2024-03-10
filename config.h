#ifndef CONFIG
#define CONFIG

// #define int32 (unsigned int)
// #define int8 (unsigned char)

typedef unsigned char int8;
typedef unsigned int int32;



struct SSHKey{
	char * key;
	int32 size;

};


#endif