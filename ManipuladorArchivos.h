#ifndef MANIPULADORARCHIVOS_H_
#define MANIPULADORARCHIVOS_H_

#include <iostream>
using namespace std;

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <string.h>
#include <iosfwd>
#include <sstream>

using namespace std;


class ManipuladorArchivos {

public:
	ManipuladorArchivos();
	virtual ~ManipuladorArchivos();
	vector<string> getArchivos(string dir, string prefijo, string sufijo);
	void borrarArchivos(string dir, string prefijo, string sufijo);
	void creoCarpeta(string dir);

};

#endif /* MANIPULADORARCHIVOS_H_ */
