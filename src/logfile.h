 #include <iostream>
#include <fstream>
#include <string>
#include <ctime> //get current time
#include <sys/stat.h> //using mkdir
#include <unistd.h> // using readlink
#include <limits.h> // using PATH_MAX

#ifndef CLOGFILE_H
#define CLOGFILE_H
class CLogFile
{
public:
	CLogFile();
	~CLogFile();
	bool DirectoryExists(const std::string& directoryPath);
	void LogToFile(const std::string& message);
	void SetNamePlayer(const std::string& PlayerName);
	const std::string& GetNamePlayer() const ;
private:
	std::string m_Player;
};
#endif // CLOGFILE_H