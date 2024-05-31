#include "ScheduleParser.hpp"

class State{
public:
    virtual void handle(std::vector<std::string>& ScheduleCH, std::vector<std::string>& ScheduleZN, std::vector<std::string>& tokens, int& begin) = 0;
};

class ConcreteStateA : public State {
public:
    void handle(std::vector<std::string>& ScheduleCH, std::vector<std::string>& ScheduleZN, std::vector<std::string>& tokens, int& begin) override {
        ScheduleCH.push_back(tokens[begin]);
        ScheduleZN.push_back(tokens[begin]);
        ScheduleCH.push_back(tokens[begin + 1]);
        ScheduleZN.push_back(tokens[begin + 2]);
        begin += 3;
    }
};

class ConcreteStateB : public State {
public:
    void handle(std::vector<std::string>& ScheduleCH, std::vector<std::string>& ScheduleZN, std::vector<std::string>& tokens, int& begin) override {
        ScheduleCH.push_back(tokens[begin]);
        ScheduleZN.push_back(tokens[begin]);
        ScheduleCH.push_back(tokens[begin + 1]);
        ScheduleZN.push_back(tokens[begin + 1]);
        begin += 2;
    }
};

class Context{
private:
    State* state_;
public:
    Context() : state_(nullptr){};
    Context(State* state) : state_(nullptr){ state_ = state; }
    void set_state(State* s){
        delete[] state_;
        state_ = s;
    }
    void request(std::vector<std::string>& ScheduleCH, std::vector<std::string>& ScheduleZN, std::vector<std::string> tokens, int& begin){ state_->handle(ScheduleCH, ScheduleZN, tokens, begin); }
};

std::vector<std::wstring> ScheduleParser::getClasses (int dayIndex, int classIndex){
    std::vector<std::wstring> classes;
    std::vector<std::string> strclasses;
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
        data[i] = data[i].substr(data[i].find(' ') + 1, data[i].size() - data[i].find(' ') - 1);
        if ((data[i].size() > 4) && (data[i] != "\"""ВУЦ""\"") && (data[i] != "\"""Самостоятельная работа""\"") && (data[i] != "\"""Практика""\"")){
            bool fl = true;
            for (const auto &item : strclasses){
                if (item == data[i]){
                    fl = false;
                }
            }
            if (fl){
                std::wstring wstr = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(data[i]);
                classes.push_back(wstr);
                strclasses.push_back(data[i]);
            }
        }
    }
    return classes;
}

void ScheduleParser::https_get_request(const std::string& server, const std::string& path){
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

std::vector<std::string> ScheduleParser::split(const std::string &str, char delimiter){
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

void ScheduleParser::fill_weeks(std::vector<std::string>& ScheduleCH, std::vector<std::string>& ScheduleZN, std::vector<std::string> tokens, std::vector<std::string> days, std::vector<std::string> time){
    for (int j = 0; j < 6; j++){
        for (int i = 0; i < tokens.size(); i++){
            if (tokens[i] == days[j]){
                ScheduleCH.push_back(days[j]);
                ScheduleZN.push_back(days[j]);
                int begin = i + 4;
                for (int k = 1; k < 8; k++){
                    Context* context;
                    if (tokens[begin + 2] != time[k]){
                        context = new Context(new ConcreteStateA);
                    }
                    else{
                        context = new Context(new ConcreteStateB);
                    }
                    context->request(ScheduleCH, ScheduleZN, tokens, begin);
                    delete context;
                }
            }
        }
    }
}

void ScheduleParser::parse_schedule_to_txt(std::vector<std::string> ScheduleCH, std::vector<std::string> ScheduleZN, std::ofstream& schedule){
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
}

static void fill_days(std::vector<std::string>& days){
    days.push_back("\"""Понедельник""\"");
    days.push_back("\"""Вторник""\"");
    days.push_back("\"""Среда""\"");
    days.push_back("\"""Четверг""\"");
    days.push_back("\"""Пятница""\"");
    days.push_back("\"""Суббота""\"");
}

static void fill_time(std::vector<std::string>& time){
    time.push_back("\"""8:3010:05""\"");
    time.push_back("\"""10:1511:50""\"");
    time.push_back("\"""12:0013:35""\"");
    time.push_back("\"""13:5015:25""\"");
    time.push_back("\"""15:4017:15""\"");
    time.push_back("\"""17:2519:00""\"");
    time.push_back("\"""19:1020:45""\"");
}

static void clear_schedule(){
    std::ofstream schedule;
    schedule.open("Schedule.txt", std::ios_base::trunc);
    schedule.close();
}

static void clear_schedulebuf(){
    std::ofstream schedulebuf;
    schedulebuf.open("ScheduleBuf.txt", std::ios_base::trunc);
    schedulebuf.close();
}

void ScheduleParser::make_schedule(){
    setlocale(0, "Russian");
    clear_schedule();
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
            std::ofstream schedule("Schedule.txt", std::ios_base::app);
            std::vector<std::string> tokens = ScheduleParser::split(data, ',');
            std::vector<std::string> days;
            std::vector<std::string> time;
            std::vector<std::string> ScheduleCH;
            std::vector<std::string> ScheduleZN;
            fill_days(days);
            fill_time(time);
            ScheduleParser::fill_weeks(ScheduleCH, ScheduleZN, tokens, days, time);
            ScheduleParser::parse_schedule_to_txt(ScheduleCH, ScheduleZN, schedule);
            schedule.close();
        }
    }
    clear_schedulebuf();
    schedulebuf.close();
}