#include "logfile.h"

CLogFile::CLogFile()
{
    m_Player = "GuestPlayer";
}
CLogFile::~CLogFile()
{
    m_Player = "";
}


bool CLogFile::DirectoryExists(const std::string& directoryPath) {
    struct stat l_buffer;
    return (stat(directoryPath.c_str(), &l_buffer) == 0 && S_ISDIR(l_buffer.st_mode));
}

//Can call LogToFile any where
void CLogFile::LogToFile(const std::string& message) {
    char buffer[PATH_MAX];
    std::string newDir{};
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);

    if (len != -1) {
        buffer[len] = '\0';
        std::string programPath(buffer);
        size_t lastSlashPos = programPath.rfind('/');
        if (lastSlashPos != std::string::npos) {
            std::string parentDir = programPath.substr(0, lastSlashPos);
            newDir = parentDir + "/Log/";//path log
            if (!DirectoryExists(newDir)) {
                if (mkdir(newDir.c_str(), 0777) == 0) {
                    std::cout << "Created new folder: " << newDir << std::endl;
                }
                else {
                    std::cerr << "Error create folder." << std::endl;
                }
            }
        }
    }
    else {
        std::cerr << "Error getting program path" << std::endl;
    }
    // Open the snaklelog.txt file to write. If the file does not exist, it will automatically create a new one.
    std::ofstream logFile(newDir + "/snakelog.txt", std::ios::app);

    // Check if the file opened successfully
    if (logFile.is_open()) {
        // Get the current time
        time_t now = std::time(nullptr);
        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "[%Y/%m/%d %H:%M:%S]", localtime(&now));

        // Record time and log content to file
        logFile << timestamp << " " << message << std::endl;

        // Close file
        logFile.close();
    }
    else {
        std::cerr << "Can not Open " << newDir << "snakelog.txt to write log." << std::endl;
    }
}

void CLogFile::SetNamePlayer(const std::string& PlayerName) {
    m_Player = PlayerName;
}
const std::string& CLogFile::GetNamePlayer() const {
    return m_Player;
}
//[AuNV] (2023/10//06) <----- 