#pragma once
#include "CoreHeader.h"
#include "Object.h"

NAMESPACE_OPEN(GEngine);

enum ResourceType
{
	Image, Audio
};

class Resource abstract : public Object 
{
public:
	Resource(const ResourceType rType);
	virtual ~Resource();

	ResourceType Type() const { return _rType; }

private:
	ResourceType _rType;
};



NAMESPACE_CLOSE;

