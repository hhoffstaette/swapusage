
#ifndef MATCHER_H_
#define MATCHER_H_

#include <string>
#include <regex.h>

class Matcher
{
private:
	regex_t _re;

public:
	Matcher(const std::string& expression);
	Matcher(const Matcher& other) = delete;
	Matcher& operator = (const Matcher& other) = delete;
	~Matcher();

	bool match(const std::string& value);
};

#endif /* MATCHER_H_ */
