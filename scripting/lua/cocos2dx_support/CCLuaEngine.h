/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __CC_LUA_ENGINE_H__
#define __CC_LUA_ENGINE_H__

extern "C" {
#include "lua.h"
}

#include "ccTypes.h"
#include "cocoa/CCObject.h"
#include "touch_dispatcher/CCTouch.h"
#include "cocoa/CCSet.h"
#include "base_nodes/CCNode.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaStack.h"
#include "CCLuaValue.h"

NS_CC_BEGIN

namespace extension {
    class CCTableViewCell;
    class CCTableView;
}

namespace ui {
    class Widget;
}

/** Lua support for cocos2d-x
 *  @js NA
 *  @lua NA
 */
class CCLuaEngine : public CCScriptEngineProtocol
{
public:
    static CCLuaEngine* defaultEngine(void);    
    virtual ~CCLuaEngine(void);
    
    virtual ccScriptType getScriptType() {
        return kScriptTypeLua;
    };

    CCLuaStack *getLuaStack(void) {
        return m_stack;
    }
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path);
    
    /**
     @brief Add lua loader, now it is used on android
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByCCObject(CCObject* pObj);
    
    /** Remove script side user data */
    virtual void removeScriptUserData(int nRefId);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Reallocate Lua function reference
     */
    virtual int reallocateScriptHandler(int nHandler);
    
    /** 
     @brief check if two script function handlers point to same function 
     */
    virtual bool isScriptFunctionSame(int handler1, int handler2);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes);
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);

    virtual int executeCallFuncActionEvent(CCCallFunc* pAction, CCObject* pTarget = NULL);
    virtual int executeSchedule(ccScriptFunction& func, float dt);
    virtual int executeLayerTouchesEvent(CCLayer* pLayer, const char* pEventName, CCSet *pTouches);
    virtual int executeLayerTouchEvent(CCLayer* pLayer, const char* pEventName, CCTouch *pTouch);
    
    /** execute a accelerometer event */
    virtual int executeAccelerometerEvent(ccScriptFunction& func, CCAcceleration* pAccelerationValue);
    
    /// common event
    virtual int executeEvent(ccScriptFunction& func, const char* pEventName, CCObject* collector = NULL, SEL_ScriptReturnedValueCollector sel = NULL);
    
    virtual int executeEventWithArgs(ccScriptFunction& func, CCArray* pArgs, CCObject* collector = NULL, SEL_ScriptReturnedValueCollector sel = NULL);

    virtual void executeObjectDestructor(CCObject* obj);
    
    virtual bool handleAssert(const char *msg);
    virtual bool parseConfig(CCScriptEngineProtocol::ConfigType type, const std::string& str);
    
private:
    CCLuaEngine(void)
    : m_stack(NULL)
    {
    }
    
    bool init(void);
    
    static CCLuaEngine* m_defaultEngine;
    CCLuaStack *m_stack;
};

NS_CC_END

#endif // __CC_LUA_ENGINE_H__
