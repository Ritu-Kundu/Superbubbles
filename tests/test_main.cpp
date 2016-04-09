//
// GTest main
//

#include "../src/eadib_log/Logger.h"
#include "gtest/gtest.h"

TEST( GTEST, testing ) {
    LOG( "GTest main: assertion test.." );
    ASSERT_TRUE( true );
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}