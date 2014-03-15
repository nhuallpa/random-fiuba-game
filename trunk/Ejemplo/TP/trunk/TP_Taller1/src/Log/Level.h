#ifndef LEVEL_H_
#define LEVEL_H_

namespace Log
{

enum Level
{
	// mascaras de bits, se combinan con | (bitwise or)
	FATAL = 0x01,
	ERROR = 0x02,
	WARN = 0x04,
	INFO = 0x08,
	DEBUG = 0x10,

	ALL = 0x1F
};

} /* namespace Log */
#endif /* LEVEL_H_ */
