#include "gtest/gtest.h"

#if defined(__ANDROID__)
// This flag is implemented but not declared in the public header.
GTEST_DECLARE_bool_(death_test_use_fork);
#endif

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::FLAGS_gtest_death_test_style = "threadsafe";
#if defined(__ANDROID__)
  // Raw clone() can fail before the death-test statement runs on Android.
  testing::FLAGS_gtest_death_test_use_fork = true;
#endif
  return RUN_ALL_TESTS();
}
