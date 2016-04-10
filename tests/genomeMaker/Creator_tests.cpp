#ifndef UNIT_TESTS_READER_H
#define UNIT_TESTS_READER_H

#include "gtest/gtest.h"
#include "../../src/genomeMaker/Randomiser.h"
#include "../../src/genomeMaker/Creator.h"

TEST( Creator_Tests, create_DNA ) {
    auto creator = genomeMaker::Creator( "test_file" );
    creator.create_DNA();
}

#endif //UNIT_TESTS_READER_H