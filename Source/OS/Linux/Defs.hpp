#pragma once

#include <string.h>
#include <stdio.h>
#include <Definitions.hpp>

char* flush_strerror(int err); // a thread safe implementation of strerror and sure never returns nullptr