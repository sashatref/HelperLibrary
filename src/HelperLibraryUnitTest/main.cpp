#include "TestEnv.h"

int main(int argc, char ** argv)
{
    ExtendApp a(argc, argv);

    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new TestEnv());
    return RUN_ALL_TESTS();
}
