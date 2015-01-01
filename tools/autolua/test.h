#ifndef __SIMPLE_CLASS_H__
#define __SIMPLE_CLASS_H__

#include <string>

namespace cocos2d {
typedef struct {
	int i;
} CCPoint;
}

class BaseClass {
public:
    void baseMethod(float* f);
};

class SimpleNativeClass : public BaseClass
{
public:
	SimpleNativeClass();
	static void processInt(std::string s);
	static int processInt(std::string s, cocos2d::CCPoint f, float fd);
};

#endif