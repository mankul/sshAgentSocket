#ifndef OPENSSHKEY
#define OPENSSHKEY

#include "config.h"

struct SSHKey{

	char * key;
	int32 size;

	

};

class OpenSSHKey{
	public:
		SSHKey * publicKey;
		SSHKey * privateKey;
};

#endif
