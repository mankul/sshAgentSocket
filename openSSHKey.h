#ifndef OPENSSHKEY
#define OPENSSHKEY

#include "config.h"


class OpenSSHKey{
	public:
		SSHKey * publicKey;
		SSHKey * privateKey;

		OpenSSHKey(); // Constructor
		~OpenSSHKey();

		SSHKey * loadRSAPublicKey();
		SSHKey * loacRSAPrivateKey();

		SSHKey * storeRSAPublicKey();
		SSHKey * storeRSAPrivateKey();

};

#endif
