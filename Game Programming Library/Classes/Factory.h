#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include <memory>
#include <functional>

namespace GPL
{
	template<typename Key,class Base>
	class Factory
	{
	public:
		Factory() = default;

		template<class Derived>
		void RegisterObject(const Key key)
		{
			this->instance_map.insert(std::pair<Key,std::function<void(std::unique_ptr<Base>&)>>(key,Factory::InstanceObject<Derived>));
		}

		void CreateObject(std::unique_ptr<Base>& base,const Key key)
		{
			this->instance_map[key](base);
		}
	private:
		std::map<Key,std::function<void(std::unique_ptr<Base>&)>> instance_map;
		Factory(const Factory&) = delete;
		Factory& operator=(const Factory&) = delete;

		template<class Derived>
		static void InstanceObject(std::unique_ptr<Base>& base)
		{
			base = make_unique<Derived>();
		}
	};
}

#endif