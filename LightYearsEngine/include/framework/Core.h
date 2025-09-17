#pragma once
#ifndef CORE_H
#define CORE_H

#include <stdio.h>

namespace ly
{
	// Simple logging macro, ... means variadic arguments
#define LOG(M, ...) printf("[LOG] " M "\n", ##__VA_ARGS__)
#define WARN(M, ...) printf("[WARN] " M "\n", ##__VA_ARGS__)
#define ERROR(M, ...) printf("[ERROR] " M "\n", ##__VA_ARGS__)
}

#endif // CORE_H