#include <iostream>
#include <fstream>
using namespace std;

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
using namespace httplib;

#include "json.hpp"
using json = nlohmann::json;

void SetProperty(string token_, string thing_, string property_, string value_) {
	SSLClient client("localhost", 4443);

	string path = "/things/" + thing_ + "/properties/" + property_;

	Headers headers = {
		{"Accept", "application/json"},
		{"Authorization:Bearer", token_}
	};

	json property_json = {
		{property_, value_}
	};

	client.Put(path.c_str(), headers, property_json.dump(), "application/json");
}

string GetProperty(string token_, string thing_, string property_) {
	SSLClient client("localhost", 4443);

	string path = "/things/" + thing_ + "/properties/" + property_;

	Headers headers = {
		{"Accept", "application/json"},
		{"Content-Type", "application / json"},
		{"Authorization:Bearer", token_}
	};

	auto response = client.Get(path.c_str(), headers);

	if (response == nullptr)
		return "";

	json response_json = json::parse(response->body);
	return response_json[property_].get<string>();
}

string Authorize(const string& login_, const string& password_) {
	SSLClient client("localhost", 4443);

	json body = {
		{"email", login_},
		{"password", password_}
	};

	Headers headers = {
		{"Accept", "application/json"}
	};

	auto response = client.Post("/login", headers, body.dump(), "application/json");
	if (response == nullptr)
		return "";

	return response->body;
}

int main() {
	fstream cred_input("credentials.txt", ios::in);
	string login, password;
	cred_input >> login >> password;

	string token = Authorize(login, password);

	return 0;
}