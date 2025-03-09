#include "FileHelper.h"

#include <filesystem>

using namespace std;

void EnsureDirectoryExists(const std::filesystem::path& path)
{
	if (!exists(path))
	{
		create_directories(path);
	}
}

void EnsureParenDirectoryExists(const MyString& fileName)
{
	const filesystem::path filePath(fileName.GetCStr());
	const filesystem::path directoryPath = filePath.parent_path();

	EnsureDirectoryExists(directoryPath);
}

void EnsureDirectoryExists(const MyString& directory)
{
	const filesystem::path path(directory.GetCStr());

	EnsureDirectoryExists(path);
}

void CopyFilesOnly(const MyString& source, const MyString& destination)
{
	EnsureDirectoryExists(destination);

	for (const auto& entry : filesystem::directory_iterator(source.GetCStr()))
	{
		if (is_regular_file(entry.status()))
		{
			copy(entry.path(), destination.GetCStr() / entry.path().filename(), filesystem::copy_options::overwrite_existing);
		}
	}
}
