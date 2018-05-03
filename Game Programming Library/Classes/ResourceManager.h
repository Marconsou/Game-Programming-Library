#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>

namespace GPL
{
	template<class Type>
	class ResourceManager
	{
	public:
		ResourceManager() = default;

		ResourceManager& operator=(ResourceManager&& resource_manager)
		{
			this->resources = std::move(resource_manager.resources);
			return *this;
		}

		Type& AddResource(const std::string& id,const bool resource_from_file)
		{
			return std::get<0>(this->resources.insert(std::make_pair(id,std::make_tuple(Type(),resource_from_file))).first->second);
		}

		Type& GetResource(const std::string& id)
		{
			return std::get<0>(this->resources.find(id)->second);
		}

		const Type& GetResource(const std::string& id) const
		{
			return std::get<0>(this->resources.find(id)->second);
		}

		const std::map<const std::string,std::tuple<Type,bool>>& GetResources() const
		{
			return this->resources;
		}

		void RemoveResource(const std::string& id)
		{
			this->resources.erase(id);
		}

		void Clear()
		{
			this->resources.clear();
		}
	private:
		std::map<const std::string,std::tuple<Type,bool>> resources;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
	};
}

#endif