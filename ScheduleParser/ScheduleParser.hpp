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
    static void https_get_request(const std::string& server, const std::string& path){
    std::string wrapAPIKey = "gHrkPDXxPpmDYelmcTNr8R7G1XRqiQ1u";
    try{
        boost::asio::io_context io_context;

        ssl::context ctx(ssl::context::sslv23);
        ctx.set_default_verify_paths();

        ssl::stream<tcp::socket> socket(io_context, ctx);

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(server, "https");

        boost::asio::connect(socket.lowest_layer(), endpoints);

        socket.handshake(ssl::stream_base::client);

        std::string request = 
            "GET " + path + " HTTP/1.1\r\n" +
            "Host: " + server + "\r\n" +
            "Accept: */*\r\n" +
            "Connection: close\r\n\r\n";

        boost::asio::write(socket, boost::asio::buffer(request));

        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        std::istream response_stream(&response);
        std::string http_version;
        unsigned int status_code;
        std::string status_message;
        response_stream >> http_version >> status_code;
        std::getline(response_stream, status_message);

        if (!response_stream || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Неверный ответ\n";
            return;
        }
        if (status_code != 200)
        {
            std::cout << "Ответ не 200 OK: " << status_code << " " << status_message << "\n";
            return;
        }

        boost::asio::read_until(socket, response, "\r\n\r\n");

        std::string header;
        while (std::getline(response_stream, header) && header != "\r");

        boost::system::error_code error;
        std::ofstream file ("ScheduleBuf.txt", std::ios_base::app | std::ios_base::binary);
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)){
            file << &response;
        }
        file.close();
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
        }
        catch (std::exception& e){
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }
    static std::vector<std::string> split(const std::string &str, char delimiter){
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        if (token.front() == ' '){
            std::string prev;
            prev = tokens.back();
            tokens.pop_back();
            prev += token;
            tokens.push_back(prev);
        }
        else{
            tokens.push_back(token);
        }
    }
    return tokens;
    }
    static void make_schedule(){
        setlocale(0, "Russian");
        std::string server = "wrapapi.com";
        std::string path;
        std::ifstream file("URL_Adress_For_Parser.txt");
        while (file >> path){
            ScheduleParser::https_get_request(server, path);
        }
        file.close();
        std::ifstream schedulebuf("ScheduleBuf.txt");
        std::string str;
        getline(schedulebuf, str);
        std::vector<std::string> database = ScheduleParser::split(str, ']');
        std::string data;
        for (int i = 0; i < database.size(); i++){
            data = database[i];
            if (data.find("Расписание") != std::string::npos){    
                data = data.substr(data.find("Расписание ") - 1, data.find("stateToken") - data.find("Расписание") - 3);
                schedulebuf.close();
                std::ofstream schedule("Schedule.txt", std::ios_base::app);
                std::vector<std::string> tokens = ScheduleParser::split(data, ',');
                std::vector<std::string> days;
                std::vector<std::string> time;
                std::vector<std::string> ScheduleCH;
                std::vector<std::string> ScheduleZN;
                days.push_back("\"""Понедельник""\"");
                days.push_back("\"""Вторник""\"");
                days.push_back("\"""Среда""\"");
                days.push_back("\"""Четверг""\"");
                days.push_back("\"""Пятница""\"");
                days.push_back("\"""Суббота""\"");
                time.push_back("\"""8:3010:05""\"");
                time.push_back("\"""10:1511:50""\"");
                time.push_back("\"""12:0013:35""\"");
                time.push_back("\"""13:5015:25""\"");
                time.push_back("\"""15:4017:15""\"");
                time.push_back("\"""17:2519:00""\"");
                time.push_back("\"""19:1020:45""\"");
                for (int j = 0; j < 6; j++){
                    for (int i = 0; i < tokens.size(); i++){
                        if (tokens[i] == days[j]){
                            ScheduleCH.push_back(days[j]);
                            ScheduleZN.push_back(days[j]);
                            int begin = i + 4;
                            int shift = 0;
                            for (int k = 1; k < 8; k++){
                                if (tokens[begin + shift + 2] != time[k]){
                                    ScheduleCH.push_back(tokens[begin + shift]);
                                    ScheduleZN.push_back(tokens[begin + shift]);
                                    ScheduleCH.push_back(tokens[begin + shift + 1]);
                                    ScheduleZN.push_back(tokens[begin + shift + 2]);
                                    shift += 3;
                                }
                                else{
                                    ScheduleCH.push_back(tokens[begin + shift]);
                                    ScheduleZN.push_back(tokens[begin + shift]);
                                    ScheduleCH.push_back(tokens[begin + shift + 1]);
                                    ScheduleZN.push_back(tokens[begin + shift + 1]);

                                    shift += 2;
                                }
                            }
                        }
                    }
                }
                for (int i = 0; i < ScheduleCH.size(); i += 2){
                    if (i == 0) schedule << "Числитель" << "\n";
                    if(i % 15 == 0){
                        schedule << ScheduleCH[i] << "\n";
                        schedule << ScheduleCH[i + 1] << ' ' << ScheduleCH[i + 2] << "\n";
                        i++;
                    }
                    else{
                        schedule << ScheduleCH[i] << ' ' << ScheduleCH[i + 1] << "\n";
                    }
                }
                for (int i = 0; i < ScheduleZN.size(); i += 2){
                    if (i == 0) schedule << "Знаменатель" << "\n";
                    if(i % 15 == 0){
                        schedule << ScheduleZN[i] << "\n";
                        schedule << ScheduleZN[i + 1] << ' ' << ScheduleZN[i + 2] << "\n";
                        i++;
                    }
                    else{
                        schedule << ScheduleZN[i] << ' ' << ScheduleZN[i + 1] << "\n";
                    }
                }
                schedule.close();
            }
        }
        schedulebuf.close();
    }
    static std::vector<std::wstring> getClasses (int dayIndex, int classIndex){
        std::vector<std::wstring> classes;
        std::ifstream schedule("Schedule.txt");
        std::string line;
        std::vector<std::string> data;
        if (classIndex > 6){
            classIndex += 42;
        }
        while(getline(schedule, line)){
            data.push_back(line);
        }
        schedule.close();
        for (int i = dayIndex*7 + dayIndex + 2 + classIndex; i < data.size(); i += 98){
            std::wstring wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(data[i]);
            classes.push_back(wstr);
        }
        for (int i = 0; i < classes.size(); i++){
            std::wcout << classes[i] << '\n';
        }
        return classes;
    }
};