#pragma once

struct TestEnvData
{

};

class TestEnv : public ::testing::Environment
{
public:
    TestEnv();

    static TestEnvData data;
};

