#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include "TexturesID.h"


template<typename Key, typename T >
class ResourceHolder
{
public:
	ResourceHolder();
	~ResourceHolder();
	void load(const Key& ID, const std::string& filePath);
	void add(const Key& ID, std::unique_ptr<T> resource);

	const T* getPointerToResource(const Key& ID) const;
	const T& getResource(const Key& ID) const;
protected:
	std::unordered_map< Key,
		std::unique_ptr< T > > resourceMap;

	T missingResource;
};

template<typename Key, typename T>
inline ResourceHolder<Key, T>::ResourceHolder()
{
}

template<typename Key, typename T>
inline ResourceHolder<Key, T>::~ResourceHolder()
{
}

template<typename Key, typename T>
inline void ResourceHolder<Key, T>::load(const Key& ID, const std::string& filePath)
{
	std::unique_ptr<T> resource = std::make_unique<T>();
	resource->loadFromFile(filePath);
	resourceMap.insert(std::pair < Key, std::unique_ptr <T> >(ID, std::move(resource)));
}

template<typename Key, typename T>
inline void ResourceHolder<Key, T>::add(const Key& ID, std::unique_ptr<T> resource)
{
	resourceMap.insert(std::pair < Key, std::unique_ptr <T> >(ID, std::move(resource)));
}

template<typename Key, typename T>
inline const T* ResourceHolder<Key, T>::getPointerToResource(const Key& ID) const
{
	auto found = resourceMap.find(ID);
	if (found != resourceMap.end())
	{
		return found->second.get();
	}
	return &missingResource;
}

template<typename Key, typename T>
inline const T& ResourceHolder<Key, T>::getResource(const Key& ID) const
{
	auto found = resourceMap.find(ID);
	if (found != resourceMap.end())
	{
		return *found->second;
	}
	return missingResource;
}

typedef ResourceHolder<TextureID, sf::Texture> TexturesHolder;
