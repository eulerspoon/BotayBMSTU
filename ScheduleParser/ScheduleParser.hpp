#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <codecvt>
using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
class ScheduleParser{
public:
    static void https_get_request(const std::string& server, const std::string& path);
    static std::vector<std::string> split(const std::string &str, char delimiter);
    static void make_schedule();
    static std::vector<std::wstring> getClasses (int dayIndex, int classIndex);
};