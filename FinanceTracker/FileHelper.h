#pragma once
#include "MyString.h"

void EnsureParenDirectoryExists(const MyString& fileName);
void EnsureDirectoryExists(const MyString& directory);
void CopyFilesOnly(const MyString& source, const MyString& destination);
