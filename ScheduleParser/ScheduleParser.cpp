#include "ScheduleParser.hpp"

void https_get_request(const std::string& server, const std::string& path)
{
    std::string wrapAPIKey = "gHrkPDXxPpmDYelmcTNr8R7G1XRqiQ1u";
    try
    {
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
        while (std::getline(response_stream, header) && header != "\r")
            std::cout << header << "\n";

        std::cout << "\n";

        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error))
            std::cout << &response;
        
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

//TEST
/* int main()
{
    std::string server = "wrapapi.com";
    std::string path = "/use/tal3nt3d/botaybmstu/schedule/0.1.1?wrapAPIKey=gHrkPDXxPpmDYelmcTNr8R7G1XRqiQ1u";

    https_get_request(server, path);

    return 0;
} */
