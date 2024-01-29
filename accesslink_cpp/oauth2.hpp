#include <boost/format/format_fwd.hpp>
#include <iterator>
#include <string>
#include "cpr/error.h"
#include "cpr/parameters.h"
#include "utils.hpp"
#include "cpr/cpr.h"
#include "cpr/response.h"
#include "boost/format.hpp"

using cpr::Response;

class OAuth2Client {
public:
    OAuth2Client(const std::string &url, const std::string &authorization_url,
                 const std::string &access_token_url, const std::string &redirect_url,
                 const int &client_id, const std::string &client_secret)
        : url_(url),
          authorization_url_(authorization_url),
          access_token_url_(access_token_url),
          redirect_url_(redirect_url),
          client_id_(client_id),
          client_secret_(client_secret){};

    std::string get_auth_headers(const std::string &access_token);

    std::string get_authorization_url(const std::string &response_type);

    std::string get_access_code(const std::string &authorization_code);

    Kwargs __build_endpoint(Kwargs &kw);

    Kwargs __build_auth(Kwargs &kw);

    Kwargs __build_request(Kwargs &kw);

    std::string parse_response(Response &response) {

        if (response.status_code >= 400) {
            boost::format fmt =
                boost::format("%1 %2: %3") % response.status_code % response.reason % response.text;
            std::string message = fmt.str();
            throw cpr::Error(response.status_code, std::move(message));
        }

        if (response.status_code == 204) {
            return "";  /// not sure, need details
        }

        try {
            ///here will be returned a JSON object - need to work on it
        } catch (...) {          ///actually in python they catch value-error, i didnt find it:-)
            return response.text;
        }
        return "";
    };

    auto __request( std::string method, Kwargs &kw) {
        kw = __build_request(kw);
        Response response;
        method = "";  // must be something with request i guess
        return parse_response(response);
    };

    auto get(std::string &endpoint, Kwargs &kw) {
        return __request("get", kw.Add({"endpoint", endpoint}));
    }

    auto put(std::string &endpoint, Kwargs &kw) {
        return __request("put", kw.Add({"endpoint", endpoint}));
    }

    auto post(std::string &endpoint, Kwargs &kw) {
        return __request("post", kw.Add({"endpoint", endpoint}));
    }

    auto remove(std::string &endpoint, Kwargs &kw) {
        return __request("delete", kw.Add({"endpoint", endpoint}));
    }
    ~OAuth2Client() = default;

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const int client_id_;
    const std::string client_secret_;
};
