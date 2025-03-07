#include "FileHelper.h"

#include <filesystem>

using namespace std::filesystem;

void CopyFilesOnly(const MyString& source, const MyString& destination)
{
	const path sourcePath(source.GetCStr());
	const path destinationPath(destination.GetCStr());

	if (!exists(destinationPath))
	{
		create_directories(destinationPath);
	}

	for (const auto& entry : directory_iterator(sourcePath))
	{
		if (is_regular_file(entry.status()))
		{
			copy(entry.path(), destinationPath / entry.path().filename(), copy_options::overwrite_existing);
		}
	}
}
