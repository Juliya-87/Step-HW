#include "FileHelper.h"

#include <filesystem>

using namespace std;

void CopyFilesOnly(const MyString& source, const MyString& destination)
{
	const filesystem::path sourcePath(source.GetCStr());
	const filesystem::path destinationPath(destination.GetCStr());

	if (!exists(destinationPath))
	{
		create_directories(destinationPath);
	}

	for (const auto& entry : filesystem::directory_iterator(sourcePath))
	{
		if (is_regular_file(entry.status()))
		{
			copy(entry.path(), destinationPath / entry.path().filename(), filesystem::copy_options::overwrite_existing);
		}
	}
}
