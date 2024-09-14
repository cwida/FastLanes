#include "gtest/gtest.h"

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	//	// Registers a global test environment, and verifies that the
	//	// registration function returns its argument.
	//	auto* const env = new Environment;
	//	Check(testing::AddGlobalTestEnvironment(env) == env, "AddGlobalTestEnvironment() should return its argument.");
	return RUN_ALL_TESTS();
}
