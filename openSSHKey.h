#ifndef OPENSSHKEY
#define OPENSSHKEY

#include "config.h"


class OpenSSHKey{
	public:
		SSHKey * publicKey;
		SSHKey * privateKey;

	OpenSSHKey();
	~OpenSSHKey();
	

};

#endif
