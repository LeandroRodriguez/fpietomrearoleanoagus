#include "ManipuladorArchivos.h"
#include <stdlib.h>

ManipuladorArchivos::ManipuladorArchivos() {
}

ManipuladorArchivos::~ManipuladorArchivos() {
	// TODO Auto-generated destructor stub
}


vector<string> ManipuladorArchivos::getArchivos(string dir, string prefijo, string sufijo){

	DIR *dp;
	struct dirent *dirp;

	vector<string> archivos = vector<string> ();

	if ((dp = opendir(dir.c_str())) == NULL) {
		stringstream cmdtemp;
		cmdtemp << "mkdir " << dir;
		system(cmdtemp.str().c_str());
		dp = opendir(dir.c_str());

	}
	while ((dirp = readdir(dp)) != NULL) {
		if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
			continue;

	    stringstream prefix, suffix;
		prefix << prefijo;
        suffix << sufijo;

        if ((string(dirp->d_name).find(prefix.str()) != string::npos)
                && (string(dirp->d_name).find(suffix.str()) != string::npos))
        	archivos.push_back(string(dirp->d_name));

	}

	closedir(dp);
	return archivos;
}

void ManipuladorArchivos::borrarArchivos(string dir, string prefijo, string sufijo) {
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(dir.c_str())) == NULL) {
        return;
    }

    while ((dirp = readdir(dp)) != NULL) {
        if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, ".."))
            continue;

        stringstream prefix, suffix;
        prefix << prefijo;
        suffix << sufijo;

        if ((string(dirp->d_name).find(prefix.str()) != string::npos)
                && (string(dirp->d_name).find(suffix.str()) != string::npos)){

            string aux = dir;
			string otro(dirp->d_name);
			string result = dir + otro;
        	cout << result << endl;
        	unlink(result.c_str());
        }

    }
    closedir(dp);
}

void ManipuladorArchivos::creoCarpeta(string dir){
    DIR *dp;
	if ((dp = opendir(dir.c_str())) == NULL) {
			stringstream cmdtemp;
			cmdtemp << "mkdir " << dir;
			system(cmdtemp.str().c_str());
			dp = opendir(dir.c_str());

		}
	 closedir(dp);


};
