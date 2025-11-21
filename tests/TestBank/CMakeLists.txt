add_library(TestBank STATIC TestBank.cc)
target_include_directories(TestBank PUBLIC ./)
target_link_libraries(TestBank PUBLIC ATM)
