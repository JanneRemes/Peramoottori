#ifndef RESOURCE_H
#define RESOURCE_H

#include <android\asset_manager.h>
#include <resources\Image.h>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <iostream>


namespace pm
{
	class Resource
	{
	public:
		std::string name;

		Resource();
		~Resource();

	};
}
#endif //!RESOURCE_H
