#include <string>

class OAuth2Client {
public:
    OAuth2Client() = default;

    template <typename... Args>
    int get(std::string &endpoint, Args &&...args);
    template <typename... Args>
    int put(std::string &endpoint, Args &&...args);
    template <typename... Args>
    int post(std::string &endpoint, Args &&...args);
    template <typename... Args>
    int remove(std::string &endpoint, Args &&...args);
    ~OAuth2Client() = default;
};
