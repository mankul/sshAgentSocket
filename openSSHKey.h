#ifndef OPENSSHKEY
#define OPENSSHKEY

#include "config.h"


class OpenSSHKey{
	public:
		SSHKey * publicKey;
		SSHKey * privateKey;

<<<<<<< HEAD
	OpenSSHKey();
	~OpenSSHKey();
	
=======
		OpenSSHKey(); // Constructor
		~OpenSSHKey();

		SSHKey * loadRSAPublicKey();
		SSHKey * loacRSAPrivateKey();

		SSHKey * storeRSAPublicKey();
		SSHKey * storeRSAPrivateKey();
>>>>>>> bf5bcfe2e7f77aa3aa9d3291f15a9223ed9a43d0

};

#endif
