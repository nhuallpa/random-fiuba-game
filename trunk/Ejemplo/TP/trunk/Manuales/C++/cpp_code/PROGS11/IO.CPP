#include <fstream.h>
#include <strstream.h>
#include <iomanip.h>
#include <string.h>

const int lineSize = 128;

int Annotate (const char *inProg, const char *inData)
{
	ifstream 	prog(inProg, ios::in);
    ifstream 	data(inData, ios::in);
	char	 	pLine[lineSize];
	char	 	dLine[lineSize];
    istrstream	line(dLine, lineSize);
    char	 	*prefix = "Error";
	int		 	prefixLen = strlen(prefix);
    int		 	progLine = 0;
	int		 	lineNo;

	if (!prog || !data) {
    	cerr << "Can't open input files\n";
		return -1;
	}

	while (data.getline(dLine, lineSize, '\n')) {
		if (strncmp(dLine, prefix, prefixLen) == 0) {
			line.seekg(0);
        	line.ignore(lineSize, ' ');
			line >> lineNo;
			line.ignore(lineSize, ',');

			while (progLine < lineNo && prog.getline(pLine, lineSize))
				++progLine;
			cout << setw(4) << setfill('0') << progLine
				 << " " << pLine << endl;
			cout << "     " << prefix << ":" << dLine + line.tellg() << endl;
        }
	}
	prog.close();
	data.close();
    return 0;
}

int main (void)
{
	return Annotate("prog.dat", "data.dat");
}