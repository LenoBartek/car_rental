#pragma once
#include <stdint.h>
#include <string>

class Security
{
private:
	enum settings
	{
		t_cost = 8,
		m_cost = (1 << 16),
		parallelism = 4,
		HASHLEN = 32,
		SALTLEN = 16,
		ENCODEDLEN = 100
	};

	std::string encoded{};
	std::string secret{"$argon2id$v=19$m=65536,t=8,p=4$"};
	uint8_t salt[SALTLEN+1]{};

public:

	~Security();
	int8_t encodePassword(const std::string& pwd);
	int8_t verifyPassword(const std::string& pwd, std::string& encoded) const;

	std::string getEncoded() const;
};