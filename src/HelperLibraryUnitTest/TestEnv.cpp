#include "TestEnv.h"
#include "models/myclass.h"
#include "models/testobject.h"

TestEnvData TestEnv::data;

TestEnv::TestEnv()
{
    MyClass::registerType();
    TestObject::registerType();
}
