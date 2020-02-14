#include <iostream>
#include <fstream>
using namespace std;

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"

int main() {
	using namespace httplib;
	SSLClient client("localhost", 4443);

	fstream cred_input("credentials.txt", ios::in);
	std::string login, password;
	cred_input >> login >> password;

	using json = nlohmann::json;
	json auth_body = {
		{"email", login},
		{"password", password}
	};

	Headers auth_headers = {
		{"Accept", "application/json"}
	};

	auto auth_response = client.Post("/login", auth_headers, auth_body.dump(), "application/json");

	if (auth_response != nullptr)
		cout << auth_response->body << "\n";

	return 0;
}