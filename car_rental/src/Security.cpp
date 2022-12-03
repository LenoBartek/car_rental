#include "Security.h"
#include "argon2.h"
#include <sodium/randombytes.h>
#include <ranges>

Security::~Security() {}

int8_t Security::encodePassword(const std::string& pwd)
{
	randombytes_buf(salt, SALTLEN);
	char buff[ENCODEDLEN]{};

	const int8_t result = (argon2_hash(t_cost, m_cost, parallelism, pwd.c_str(), pwd.length(),
		salt, SALTLEN, nullptr, HASHLEN, buff, ENCODEDLEN,
		argon2_type::Argon2_id, ARGON2_VERSION_13));
	
	std::string temp{ buff };
	auto p = (temp | std::views::split('$') | std::views::drop(4)).front().begin();
	secret.clear();
	secret = { temp.begin(), p };
	encoded = { p, temp.end() };

	return result;
}

int8_t Security::verifyPassword(const std::string& pwd, std::string& encoded) const
{
	encoded.insert(0, secret);
	return (argon2_verify(encoded.c_str(), pwd.c_str(), pwd.length(), argon2_type::Argon2_id));
}

std::string Security::getEncoded() const
{
	return encoded;
}
