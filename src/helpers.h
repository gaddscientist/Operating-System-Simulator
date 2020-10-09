#pragma once
#include <string>
#include "process.h"
#include "scheduler.h"

// Methods
std::vector<std::string> ParseTemplate(const std::string tp);
std::string Randomize(std::string& str);
void createProcesses(int numProcesses, std::string templateFile);