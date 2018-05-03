#ifndef RESOURCEFILE_H
#define RESOURCEFILE_H

#include <iomanip>
#include <fstream>
#include <memory>
#include "BuildDLL.h"

namespace GPL
{
	class ResourceFile
	{
	public:
		GPL_DLL static void SetResourceFileName(const std::string& resource_file_name);
		GPL_DLL static bool Write(const std::string& new_resource_file_name);
		GPL_DLL static std::size_t Read(const int resource_id,const std::string& new_resource_file_name);
		GPL_DLL static std::size_t Read(const int resource_id,std::unique_ptr<char[]>& memory_buffer);
	private:
		static std::string resource_file_name;
		ResourceFile() = delete;
		static std::streamoff FileSize(std::ifstream& file);
		static std::size_t ReadBase(const int resource_id,const std::string& new_resource_file_name,std::unique_ptr<char[]>& memory_buffer,const bool use_memory_buffer);
	};
}

#endif