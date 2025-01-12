#include "cli.h"

// Конструктор
CMDParser::CMDParser() {}

string CMDParser::getConfigPath()
{
    return this->config_path;
}

string CMDParser::getAddress()
{
    return this->address;
}

int CMDParser::getPort()
{
    return this->port;
}

string CMDParser::getInputPath()
{
    return this->input_path;
}

string CMDParser::getOutputPath()
{
    return this->output_path;
}

// Метод для разбора аргументов
void CMDParser::parseArgs(int argc, char *argv[])
{
    if (argc == 1) {
        // Если параметры не были переданы, показываем справку
        this->showHelp();
        return;
    }

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            this->showHelp();
        else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address") == 0)
        {
            if (i + 1 < argc)
                this->address = argv[++i];
            else
                throw ClientError("Missing value for address parameter", __func__);
        }
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0)
        {
            if (i + 1 < argc)
                this->port = stoi(argv[++i]);
            else
                throw ClientError("Missing value for port parameter", __func__);
        }
        else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0)
        {
            if (i + 1 < argc)
                this->input_path = argv[++i];
            else
                throw ClientError("Missing value for input parameter", __func__);
        }
        else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0)
        {
            if (i + 1 < argc)
                this->output_path = argv[++i];
            else
                throw ClientError("Missing value for output parameter", __func__);
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0)
        {
            if (i + 1 < argc)
                this->config_path = argv[++i];
            else
                throw ClientError("Missing value for config parameter", __func__);
        }
        else
            throw ClientError("Unknown parameter: " + string(argv[i]), __func__);
    }
}

// Метод для показа справки
void CMDParser::showHelp()
{
    cout << "Usage: vclient [options]\n"
         << "Options:\n"
         << "  -h, --help            Show this help message and exit\n"
         << "  -a, --address ADDRESS Server address (default: 127.0.0.1)\n"
         << "  -p, --port PORT       Server port (default: 33333)\n"
         << "  -i, --input PATH      Path to input data file\n"
         << "  -o, --output PATH     Path to output data file\n"
         << "  -c, --config PATH     Path to config file (default: ./config/vclient.conf)\n";
}
