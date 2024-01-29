#include <sys/types.h>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>             // uuid class
#include <boost/uuid/uuid_generators.hpp>  // generators
#include <boost/uuid/uuid_io.hpp>          // streaming operators etc.
#include "resource.hpp"

class Users : public Resource {
    Users() = default;

    int record(std::string& access_token,
               boost::uuids::uuid member_id = boost::uuids::random_generator()()) {

        return _post("/users", access_token,
                     Headers{{"member-id", boost::uuids::to_string(member_id)}});
    }

    int remove(const int& user_id, std::string& access_token) {

        return _delete("/users/" + std::to_string(user_id), access_token);
    }

    int get_information(const int& user_id, std::string& access_token) {

        return _get("/users/" + std::to_string(user_id), access_token);
    }
};