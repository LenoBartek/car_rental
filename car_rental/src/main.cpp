#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include <iostream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

#include "Security.h"

int main()
{
	/*mongocxx::instance inst{};
	mongocxx::uri uri("mongodb://admin:password@localhost:27018");
	
	try {
		mongocxx::client client(uri);
		mongocxx::database db = client["my-db"];
		mongocxx::collection coll = db["books"];

		mongocxx::cursor cursor = coll.find({});
		for (auto&& doc : cursor) {
			std::cout << bsoncxx::to_json(doc) << "\n";
		}
	}
	catch (const std::exception& e) {
		std::cout << "connection failed: " << e.what() << "\n";
		return EXIT_FAILURE;
	}*/

	std::string password{ "password123" };
	std::string encoded{};
	Security sec;

	int a = sec.encodePassword(password);

	if (a == 0)
	{
		encoded = sec.getEncoded();	
		std::cout << encoded << '\n' << encoded.length();
	}

	a = sec.verifyPassword(password, encoded);

	if (a == 0)
	{
		std::cout << "\nCorrect passowrd" << '\n';
	}

	return EXIT_SUCCESS;
}
